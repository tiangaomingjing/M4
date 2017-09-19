#include "lockcheckbox.h"
#include <QVBoxLayout>
#include <QCheckBox>
#include <QLabel>

LockCheckBox::LockCheckBox(QWidget *parent) : QWidget(parent)
{
  QVBoxLayout *vlayout=new QVBoxLayout(this);
  QLabel*image=new QLabel(this);
  QCheckBox *box=new QCheckBox(this);
  vlayout->addWidget(image);
  vlayout->addWidget(box);
  this->setLayout(vlayout);
}

