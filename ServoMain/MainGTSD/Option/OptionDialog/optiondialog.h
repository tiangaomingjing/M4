﻿#ifndef OPTIONDIALOG_H
#define OPTIONDIALOG_H

#include <QDialog>

namespace Ui {
class OptionDialog;
}
class Option;
class OptionDialog : public QDialog
{
  Q_OBJECT

public:
  explicit OptionDialog(Option *option ,QWidget *parent = 0);
  ~OptionDialog();
private:
  void initialUiByOptionData();
private slots:
  void onListWidgetCurrentRowChanged(int row);
  void onRadioBtnGeneralClicked(bool checked);
  void onRadioBtnAdminClicked(bool checked);
  void onCheckBoxAmdinNeedClicked(bool checked);
  void onLineEditPWTextChanged(QString pw);
  void onCheckBoxAutoLoadClicked(bool checked);

  void onBtnApplyClicked();
  void onBtnCancelClicked();
  void onBtnOkClicked();

private:
  Ui::OptionDialog *ui;
  Option *m_option;
  bool m_accept;
};

#endif // OPTIONDIALOG_H