#include "dialogk.h"
#include "ui_dialogk.h"

Dialogk::Dialogk(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Dialogk)
{
    layout= new QFormLayout;
     ui->setupUi(this);
    setWindowTitle("Forum Window");
    afficher();
 ui->widget_2->setLayout(layout);

}

Dialogk::~Dialogk()
{
    delete ui;
}

void Dialogk::on_send_clicked()
{
MainWindow m;
    QString com= ui->lineEdit->text();

    forum f(m.k.getNom(),com);
    bool test=f.ajouterForum();
    if(test){
        ui->lineEdit->setText("");
        afficher();

    }
    else{
        QMessageBox::critical(nullptr, QObject::tr("OK"),
                    QObject::tr("commentaire non effectué .\n"
                                "Click Cancel to exit."), QMessageBox::Cancel);
    }
}
void Dialogk::afficher(){
    // Create a vertical layout
    clearLayout(layout);
    QSqlQuery query;
          if (query.exec("SELECT Nom, commentaire FROM forum ;")) {
              while (query.next()) {
                  QString nomValue = query.value(0).toString();
                  QString commentaireValue = query.value(1).toString();

                  QString displayString = nomValue + " : " + commentaireValue ;

                          // Create a label for each name-comment pair
                          QLabel* displayLabel = new QLabel(displayString, this);

                          // Add label to the layout
                            layout->addRow(displayLabel);                      }
          } else {
              qDebug() << "Error executing query of forum selection: " ;
          }

}
void Dialogk::clearLayout(QLayout *layout) {
    QLayoutItem *item;
    while ((item = layout->takeAt(0)) != nullptr) {
        if (item->layout()) {
            // Si l'élément est un layout, récursivement effacer son contenu
            clearLayout(item->layout());
            delete item->layout();
        }
        if (item->widget()) {
            // Si l'élément est un widget, le supprimer
            delete item->widget();
        }
        delete item;
    }
}
