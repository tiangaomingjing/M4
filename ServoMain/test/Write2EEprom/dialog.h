#ifndef DIALOG_H
#define DIALOG_H

#include "ServoDriverComDll.h"
#include <QDialog>
#include <QTreeWidget>

namespace Ui {
class Dialog;
}

class Dialog : public QDialog
{
    Q_OBJECT

public:
    explicit Dialog(QWidget *parent = 0);
    ~Dialog();
private:
    Ui::Dialog *ui;
    void showTree();
    void addTreeItem(QTreeWidgetItem *root, QTreeWidgetItem *child, int count);
    QTreeWidgetItem* findItem(QString text);
    static void updateProgessBar(void *arg, qint16 *value);
    void writeEEprom(QTreeWidgetItem *item);
    void writeSingle(QTreeWidgetItem *item);
    bool writeSuccessful(Uint8* value, Uint8* result, Uint16 num);
    void readEEprom();
    QTreeWidgetItem* findItemByValue(Uint8* value, Uint16 num);
    void readEEpromItem(QTreeWidgetItem* root, QTreeWidgetItem* child);
	void readSingle(QTreeWidgetItem* newRoot, QTreeWidgetItem* newChild);
private:
    QTreeWidget *m_tree;
    int layer;
    int baseAdd;
    int barCount;
    QString itemText;
    bool continueWrite;
    bool continueRead;
private slots:
    void write();
    void read();
    void treeItemClicked(QTreeWidgetItem* item, int column);
};

#endif // DIALOG_H
