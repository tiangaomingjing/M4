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

  void on_btn_src_clicked();

  void on_btn_target_clicked();

  void on_btn_update_clicked();

private:
  void updataPtytree(const QString &srcFileName,const QString &targetFileName);

private:
  Ui::FillLimitPtyWidget *ui;
  QString m_filePath;
};

#endif // FILLLIMITPTYWIDGET_H
