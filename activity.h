#ifndef ACTIVITY_H
#define ACTIVITY_H
#include <string>
#include<QString>
#include<QSqlQuery>
#include<QSqlQueryModel>
#include <QFileDialog>
#include<QDebug>
#include<QTableView>
#include<QMap>
#include<QMessageBox>
#include"delegateitem.h"

class Activity
{
public:
    //constructor

    Activity(int id1,QString nom1,QString type1,QString degres1,int duree1,QString image,QString equip);

    //setters

    void setNomActivite(QString nom1);
    void setTypeActivite(QString type1);
    void setDureeActivite(int duree1);
    void setDegresActivite(QString degres1);
    void setId(int id1);
    void setImage(QString image);
    void setNomE(QString nomE);

    //getters

    int getDureeActivite();
    QString getNomActivite();
    QString getTypeActivite();
     QString getDegresActivite();
      int getId();
    QString getImage();
    QString getNomE();
      //CRUD

      bool ajouterActivite();
      bool supprimerActivite(int id1);
     void afficherActivite(QTableView *tableView);
       bool UpdateActivite();
       bool nomUnique(QString name);
       void rechercheAc(QTableView *tableView,QString n);



       //recuperation des données
       QMap<QString,QString> recuperation();

private:
    int id,duree;
    QString nom,type,degres,imageA,nom_equip;

};

#endif // ACTIVITY_H
