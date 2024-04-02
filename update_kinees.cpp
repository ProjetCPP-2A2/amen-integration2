#include "update_kinees.h"
#include "ui_update_kinees.h"

update_kinees::update_kinees(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::update_kinees)
{
    ui->setupUi(this);
}

update_kinees::~update_kinees()
{
    delete ui;
}
