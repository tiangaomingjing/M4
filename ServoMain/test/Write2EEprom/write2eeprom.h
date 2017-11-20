#ifndef WRITE2EEPROM_H
#define WRITE2EEPROM_H

#include <QMainWindow>

namespace Ui {
class write2eeprom;
}

class write2eeprom : public QMainWindow
{
    Q_OBJECT

public:
    explicit write2eeprom(QWidget *parent = 0);
    ~write2eeprom();

private:
    Ui::write2eeprom *ui;
};

#endif // WRITE2EEPROM_H
