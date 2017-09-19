#include "lockcheckbox.h"
#include <QVBoxLayout>
#include <QCheckBox>
#include <QLabel>

LockCheckBox::LockCheckBox(QWidget *parent) : QWidget(parent)
{
  QVBoxLayout *vlayout=new QVBoxLayout(this);
  QLabel*image=new QLabel(this);
  image->setPixmap(QPixmap(":/Lock_Locked.png"));
  QCheckBox *box=new QCheckBox(this);
  box->setText(tr("polarity reverse"));
  vlayout->addWidget(image);
  vlayout->addWidget(box);
  this->setLayout(vlayout);
}

