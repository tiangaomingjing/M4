﻿#include "lockcheckbox.h"
#include <QVBoxLayout>
#include <QCheckBox>
#include <QLabel>
#include <QHBoxLayout>
#include <QSpacerItem>

LockCheckBox::LockCheckBox(QWidget *parent) : QWidget(parent)
{
  QVBoxLayout *vlayout=new QVBoxLayout(this);
  vlayout->setContentsMargins(0,0,0,0);
  vlayout->setSpacing(0);
  QHBoxLayout *hlayout=new QHBoxLayout;
  m_image=new QLabel(this);
  m_image->setPixmap(QPixmap(":/Lock_Locked.png"));
  m_image->setAlignment(Qt::AlignCenter);
  m_box=new QCheckBox(this);
  QSpacerItem *spacer=new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);
  QSpacerItem *spacer2=new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);
  hlayout->addItem(spacer);
  hlayout->addWidget(m_box);
  hlayout->addItem(spacer2);
  QLabel *text=new QLabel(this);
  text->setAlignment(Qt::AlignCenter);
  text->setText(tr("polarity reverse"));
  vlayout->addWidget(m_image);
  vlayout->addLayout(hlayout);
  vlayout->addWidget(text);
  this->setLayout(vlayout);
  setMouseTracking(true);
  setCheckStyleSheet();
  connect(m_box,SIGNAL(clicked(bool)),this,SLOT(setLockImage(bool)));
  connect(m_box,SIGNAL(clicked(bool)),this,SIGNAL(lockClicked(bool)));
}
bool LockCheckBox::isChecked()
{
  return m_box->isChecked();
}
void LockCheckBox::setChecked(bool checked)
{
  m_box->setChecked(checked);
}

void LockCheckBox::setCheckStyleSheet()
{
  QString style="QCheckBox {spacing: 1px;}QCheckBox::indicator {width: 64px;height: 64px;}QCheckBox::indicator:unchecked {image: url(:/checkbox_unchecked.png);}QCheckBox::indicator:unchecked:hover {image: url(:/checkbox_unchecked_hover.png);}"
  "QCheckBox::indicator:checked:hover {image: url(:/checkbox_checked_hover.png);}QCheckBox::indicator:checked {image: url(:/checkbox_checked.png);}";
  m_box->setStyleSheet(style);
}
void LockCheckBox::setLockImage(bool checked)
{
  if(checked)
  {
    m_image->setPixmap(QPixmap(":/Lock_Unlocked.png"));
  }
  else
  {
    m_image->setPixmap(QPixmap(":/Lock_Locked.png"));
  }
}


