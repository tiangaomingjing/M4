#ifndef LOCKCHECKBOX_H
#define LOCKCHECKBOX_H

#include <QWidget>
class QLabel;
class QCheckBox;

class LockCheckBox : public QWidget
{
  Q_OBJECT
public:
  explicit LockCheckBox(QWidget *parent = 0);
  bool isChecked(void);
  void setChecked(bool checked);

signals:
  void lockClicked(bool checked);

public slots:
private slots:
  void setLockImage(bool checked);
private:
  void setCheckStyleSheet();
private:
  QLabel*m_image;
  QCheckBox *m_box;
};

#endif // LOCKCHECKBOX_H
