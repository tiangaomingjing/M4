#ifndef FILLLIMITPTYWIDGET_H
#define FILLLIMITPTYWIDGET_H

#include <QWidget>

namespace Ui {
class FillLimitPtyWidget;
}

class FillLimitPtyWidget : public QWidget
{
  Q_OBJECT

public:
  explicit FillLimitPtyWidget(QWidget *parent = 0);
  ~FillLimitPtyWidget();

private slots:

  void on_btn_funcTree_clicked();

  void on_btn_ptyTree_clicked();

  void on_btn_cancel_clicked();

  void on_btn_ok_clicked();

private:
  Ui::FillLimitPtyWidget *ui;
  QString m_filePath;
};

#endif // FILLLIMITPTYWIDGET_H
