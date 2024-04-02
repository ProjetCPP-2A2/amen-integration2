#include "ajouteractivite.h"
#include "ui_ajouteractivite.h"

AjouterActivite::AjouterActivite(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::AjouterActivite)
{
    ui->setupUi(this);
}

AjouterActivite::~AjouterActivite()
{
    delete ui;
}

