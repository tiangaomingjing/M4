#include "dialog.h"
#include "ui_dialog.h"
#include "qttreemanager.h"
#include <QMessageBox>
#include <QDebug>
#include <QDir>

enum TREE{
    TREE_NAME = 0,
    TREE_VALUE = 1,
    TREE_SCALE = 3,
    TREE_TYPE = 5,
    TREE_ADDRESS = 6,
};

Dialog::Dialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Dialog)
{
    ui->setupUi(this);
    layer = 0;
    showTree();
    connect(ui->writeButton, SIGNAL(clicked()), this, SLOT(write()));
    connect(ui->treeWidget, SIGNAL(itemClicked(QTreeWidgetItem*,int)), this, SLOT(treeItemClicked(QTreeWidgetItem*,int)));
    connect(ui->closeButton, SIGNAL(clicked()), this, SLOT(close()));
    connect(ui->readButton, SIGNAL(clicked()), this, SLOT(read()));
}

Dialog::~Dialog()
{
    delete ui;
}

void Dialog::showTree() {
    ui->progressBar->hide();
    QString filePath = "./PowerBoard.ui";
    m_tree = QtTreeManager::createTreeWidgetFromXmlFile(filePath);
    if (m_tree != NULL) {
        QTreeWidgetItem *startChild = m_tree->topLevelItem(1)->clone();
        QTreeWidgetItem *startRoot = ui->treeWidget->invisibleRootItem();
        addTreeItem(startRoot, startChild, 0);
        ui->treeWidget->expandAll();
        ui->treeWidget->resizeColumnToContents(0);
    }
}

void Dialog::addTreeItem(QTreeWidgetItem *root, QTreeWidgetItem *child, int count) {
    if (count < 4) {
        for (int i = 0; i < child->childCount(); i++) {
            QTreeWidgetItem *newRoot;
            QTreeWidgetItem *newChild;
            newChild = child->child(i)->clone();
            newRoot = child->child(i)->clone();
            newRoot->takeChildren();
            root->addChild(newRoot);
            addTreeItem(newRoot, newChild, count + 1);
        }
    }
}

void Dialog::write() {
    ui->lineEdit->setReadOnly(true);
    ui->readButton->setEnabled(false);
    QString typeText = ui->typeLabel->text();
    if (layer == 3) {
        QMessageBox msgBox;
        msgBox.setText("Are you sure to write\n" + typeText + "?");
        msgBox.setStandardButtons(QMessageBox::Yes | QMessageBox::No);
        msgBox.setDefaultButton(QMessageBox::No);
        int ret = msgBox.exec();
        switch (ret) {
            case QMessageBox::Yes:
                continueWrite = true;
                break;
            case QMessageBox::No:
                continueWrite = false;
                break;
            default:
                continueWrite = false;
                break;
        }
        if (continueWrite) {
            ui->progressBar->setRange(0, 100);
            ui->progressBar->show();
            QTreeWidgetItem *xmlBaseAdd;
            QTreeWidgetItem *writenItem;
            xmlBaseAdd = findItem("xmlBaseAddress");
            writenItem = findItem(itemText);
            bool ok;
            baseAdd = xmlBaseAdd->text(TREE_VALUE).toInt(&ok, 10);
            COM_ERROR error = COM_OK;
            error = static_cast<COM_ERROR>(GTSD_CMD_Open(updateProgessBar,
                                                     (void*)ui->progressBar, GTSD_COM_TYPE_RNNET));
            ui->progressBar->hide();
            if(error != COM_OK) {
                QMessageBox::warning(this, "Warning", "Connection Failed!", QMessageBox::Ok);
            } else {
                ui->progressBar->show();
                barCount = 0;
                ui->progressBar->setValue(0);
                writeEEprom(writenItem);
                ui->progressBar->hide();
                QMessageBox::information(this, "EEprom", "Finish!", QMessageBox::Ok);
            }
        }
    } else {
        QMessageBox::warning(this, "Warning", "Please select a specific type!", QMessageBox::Ok);
    }
    ui->lineEdit->setReadOnly(false);
    ui->readButton->setEnabled(true);
}

void Dialog::treeItemClicked(QTreeWidgetItem* item, int column) {
    QString typeText = item->text(column);
    itemText = item->text(column);
    layer = 0;
    QTreeWidgetItem *currentItem = item;
    while (currentItem->parent() != NULL) {
        currentItem = currentItem->parent();
        typeText = currentItem->text(column) + "->\n" + typeText;
        layer++;
    }
    if (layer == 3) {
        ui->typeLabel->setText(typeText);
    } else {
        ui->typeLabel->setText("");
    }
}

QTreeWidgetItem* Dialog::findItem(QString text) {
    QTreeWidgetItemIterator treeIter(m_tree);
    QTreeWidgetItem *result = NULL;
    while (*treeIter){
        if ((*treeIter)->text(TREE_NAME) == text) {
            result = *treeIter;
            return result;
        }
        ++treeIter;
    }
    return result;
}

void Dialog::updateProgessBar(void *arg, qint16 *value)
{
  QProgressBar *bar=static_cast<QProgressBar *>(arg);
  bar->setValue(*value);
  qApp->processEvents();
  //qDebug()<<"value "<<*value;
}

void Dialog::writeEEprom(QTreeWidgetItem *item) {
    if(continueWrite) {
        writeSingle(item);
        barCount += 1;
        if (barCount%10 == 0) {
            ui->progressBar->setValue(barCount%100);
        }
        if (item->text(TREE_TYPE) == "Case") {
            bool ok;
            int index = item->text(TREE_VALUE).toInt(&ok, 10);
            writeEEprom(item->child(index));
        } else {
            for (int i = 0; i < item->childCount(); i++) {
                writeEEprom(item->child(i));
				qApp->processEvents();
            }
        }
    }
}

void Dialog::writeSingle(QTreeWidgetItem *item) {
    if (item->text(TREE_ADDRESS) != "-1" && item->text(TREE_ADDRESS) != "") {
        bool ok;
        double v;
        if (item->text(TREE_NAME) == "PCBA code") {
            double v_temp = ui->lineEdit->text().toDouble(&ok);
            if (ok) {
                v = v_temp * item->text(TREE_SCALE).toDouble();
            } else {
                QMessageBox::warning(this, "Warning", "PCBA code is not valid!", QMessageBox::Ok);
                continueWrite = false;
            }
        } else {
            v = item->text(TREE_VALUE).toDouble() * item->text(TREE_SCALE).toDouble();
        }
        if (continueWrite) {
            //v = int(v);
            //qDebug()<<QString::number(v, 'g', 8);
            Uint8 value[4];
            Uint8 result[4];
            int16 axis = 0;
            int count = 0;
            Uint16 ofst = item->text(TREE_ADDRESS).toInt(&ok, 16) + baseAdd;
            Uint16 num = 0;
            if (item->text(TREE_TYPE) == "Uint8") {
                value[0] = v;
                //qDebug()<<value[0];
                num = 1;
            } else if (item->text(TREE_TYPE) == "Uint16") {
                num = 2;
                value[0] = v;
                //qDebug()<<value[0];
                value[1] = int(v)>>8;
            } else if (item->text(TREE_TYPE) == "Uint32") {
                num = 4;
                value[0] = v;
                //qDebug()<<value[0];
                value[1] = int(v)>>8;
                value[2] = int(v)>>16;
                value[3] = int(v)>>24;
            }
            /*qDebug()<<"value[0] = "<<value[0];
            qDebug()<<"value[1] = "<<value[1];
            qDebug()<<"value[2] = "<<value[2];
            qDebug()<<"value[3] = "<<value[3];
			if (ofst == 46) {
				QString s1 = item->text(TREE_NAME);
				printf("");
			}*/
            GTSD_CMD_WriteEEPROMExt(axis, ofst, value, num, GTSD_COM_TYPE_RNNET, 0xf0);
            /*qDebug()<<"value[0] = "<<value[0];
            qDebug()<<"value[1] = "<<value[1];
            qDebug()<<"value[2] = "<<value[2];
            qDebug()<<"value[3] = "<<value[3];*/
            GTSD_CMD_ReadEEPROMExt(axis, ofst, result, num, GTSD_COM_TYPE_RNNET, 0xf0);
            count++;
            qApp->processEvents();
            /*qDebug()<<item->text(TREE_NAME);
            qDebug()<<"value[0] = "<<value[0];
            qDebug()<<"value[1] = "<<value[1];
            qDebug()<<"value[2] = "<<value[2];
            qDebug()<<"value[3] = "<<value[3];
            qDebug()<<"result[0] = "<<result[0];
            qDebug()<<"result[1] = "<<result[1];
            qDebug()<<"result[2] = "<<result[2];
            qDebug()<<"result[3] = "<<result[3];*/
            while (!writeSuccessful(value, result, num) && count < 3) {
                GTSD_CMD_WriteEEPROMExt(axis, ofst, value, num, GTSD_COM_TYPE_RNNET, 0xf0);
                GTSD_CMD_ReadEEPROMExt(axis, ofst, result, num, GTSD_COM_TYPE_RNNET, 0xf0);
                count++;
                qApp->processEvents();
            }
            if (!writeSuccessful(value, result, num)) {
                QString warnMsg = "Writing Failed on " + item->text(TREE_NAME) + "!";
                QMessageBox::warning(this, "Warning", warnMsg, QMessageBox::Ok);
                continueWrite = false;
            }
        }
    }
}

bool Dialog::writeSuccessful(Uint8* value, Uint8* result, Uint16 num) {
    for (int i = 0; i < num; i++) {
        if (value[i] != result[i]) {
            return false;
        }
    }
    return true;
}

void Dialog::read() {
    ui->lineEdit->setReadOnly(true);
    ui->writeButton->setEnabled(false);
    QMessageBox msgBox;
    msgBox.setText("Are you sure to read?");
    msgBox.setStandardButtons(QMessageBox::Yes | QMessageBox::No);
    msgBox.setDefaultButton(QMessageBox::No);
    int ret = msgBox.exec();
    switch (ret) {
        case QMessageBox::Yes:
            continueRead = true;
            break;
        case QMessageBox::No:
            continueRead = false;
            break;
        default:
            continueRead = false;
            break;
    }
    if (continueRead) {
        ui->progressBar->setRange(0, 100);
        ui->progressBar->show();
        QTreeWidgetItem *xmlBaseAdd;
        xmlBaseAdd = findItem("xmlBaseAddress");
        bool ok;
        baseAdd = xmlBaseAdd->text(TREE_VALUE).toInt(&ok, 10);
        COM_ERROR error = COM_OK;
        error = static_cast<COM_ERROR>(GTSD_CMD_Open(updateProgessBar,
                                                 (void*)ui->progressBar, GTSD_COM_TYPE_RNNET));
        ui->progressBar->hide();
        if(error != COM_OK) {
            QMessageBox::warning(this, "Warning", "Connection Failed!", QMessageBox::Ok);
        } else {
            ui->progressBar->show();
            barCount = 0;
            ui->progressBar->setValue(0);
            readEEprom();
            ui->progressBar->hide();
            QMessageBox::information(this, "EEprom", "Finish!", QMessageBox::Ok);
        }
    }
    ui->lineEdit->setReadOnly(false);
    ui->writeButton->setEnabled(true);
}

void Dialog::readEEprom() {
    Uint8 result[4];
    int16 axis = 0;
    Uint16 ofst = 1 + baseAdd;
    Uint16 num = 4;
    GTSD_CMD_ReadEEPROMExt(axis, ofst, result, num, GTSD_COM_TYPE_RNNET, 0xf0);
    QTreeWidgetItem* treeItemTemp = findItemByValue(result, num);
    QTreeWidgetItem* currentItem = treeItemTemp;
    QTreeWidgetItem* treeItem = findItemByValue(result, num)->clone(); //m_tree里面的
	QTreeWidgetItem* readItem = findItemByValue(result, num)->clone();; //准备放到显示树里的
	readItem->takeChildren();

    barCount = 20;
    ui->progressBar->setValue(barCount);

    readEEpromItem(readItem, treeItem);
	//QString s1 = readItem->child(0)->child(0)->child(0)->text(1);
	
    QTreeWidgetItem* tempParent;
	QTreeWidgetItem* tempItem = readItem;
    for (int i = 0; i < 3; i++) {
        tempParent = currentItem->parent();
        tempParent->takeChildren();
        tempParent->addChild(tempItem);
        tempItem = tempParent;
        currentItem = tempParent;
    }
    ui->readTreeWidget->addTopLevelItem(tempParent->clone());
	ui->readTreeWidget->expandAll();
	ui->readTreeWidget->resizeColumnToContents(0);
}

QTreeWidgetItem* Dialog::findItemByValue(Uint8* value, Uint16 num) {
    int tempValue = 0;
    //int tempValue = 21000509;
    for (int i = 0; i < num; i++) {
        tempValue = tempValue + value[i] * pow(256, i);
    }
    QTreeWidgetItemIterator treeIter(m_tree);
    QTreeWidgetItem *result = NULL;
    while (*treeIter){
        if ((*treeIter)->text(TREE_VALUE) == QString::number(tempValue, 10)) {
            result = *treeIter;
            return result;
        }
        ++treeIter;
    }
    return result;
}

void Dialog::readEEpromItem(QTreeWidgetItem* root, QTreeWidgetItem* child) {
	QTreeWidgetItem *newRoot;
	QTreeWidgetItem *newChild;
	bool ok;
	if (child->text(TREE_TYPE) == "Case") {
		int index = child->text(TREE_VALUE).toInt(&ok, 10);
		newChild = child->child(index)->clone();
		newRoot = child->child(index)->clone();
		readSingle(newRoot, newChild);
		root->addChild(newRoot);
		readEEpromItem(newRoot, newChild);
	}
	else {
		for (int i = 0; i < child->childCount(); i++) {
			newChild = child->child(i)->clone();
			newRoot = child->child(i)->clone();
			readSingle(newRoot, newChild);
			root->addChild(newRoot);
			readEEpromItem(newRoot, newChild);
		}
    }
}

void Dialog::readSingle(QTreeWidgetItem* newRoot, QTreeWidgetItem* newChild) {
	newRoot->takeChildren();
	if (newRoot->text(TREE_ADDRESS) != "-1" && newRoot->text(TREE_ADDRESS) != "") {
		Uint8 result[4];
		int16 axis = 0;
		bool ok;
		Uint16 ofst = newRoot->text(TREE_ADDRESS).toInt(&ok, 16) + baseAdd;
		Uint16 num = 0;
		if (newRoot->text(TREE_TYPE) == "Uint8") {
			num = 1;
		}
		else if (newRoot->text(TREE_TYPE) == "Uint16") {
			num = 2;
		}
		else if (newRoot->text(TREE_TYPE) == "Uint32") {
			num = 4;
		}
		GTSD_CMD_ReadEEPROMExt(axis, ofst, result, num, GTSD_COM_TYPE_RNNET, 0xf0);
		double tempValue = 0;
		for (int j = 0; j < num; j++) {
			tempValue = tempValue + result[j] * pow(256, j);
		}
		double scale = newRoot->text(TREE_SCALE).toDouble(&ok);
		newRoot->setText(TREE_VALUE, QString::number(tempValue / scale));
		barCount += 1;
		if (barCount % 10 == 0) {
			ui->progressBar->setValue(barCount % 100);
		}
	}
}
