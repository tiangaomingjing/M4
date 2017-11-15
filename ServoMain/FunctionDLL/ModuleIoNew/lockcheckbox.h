#ifndef LOCKCHECKBOX_H
#define LOCKCHECKBOX_H

#include <QWidget>
class QLabel;
class QCheckBox;

class LockCheckBox : public QWidget
{
  Q_OBJECT
public:
  explicit LockCheckBox(int axisNum, QWidget *parent = 0);
  ~LockCheckBox();
  bool isChecked(void);
  void setChecked(bool checked);

  int axisNum() const;
  void setAxisNum(int axisNum);

  bool prevCheckState() const;
  void setPrevCheckState(bool prevCheckState);

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
  int m_axisNum;
  bool m_prevCheckState;
};

#endif // LOCKCHECKBOX_H
