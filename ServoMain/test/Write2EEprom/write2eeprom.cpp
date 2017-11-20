#include "write2eeprom.h"
#include "ui_write2eeprom.h"

write2eeprom::write2eeprom(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::write2eeprom)
{
    ui->setupUi(this);
}

write2eeprom::~write2eeprom()
{
    delete ui;
}
