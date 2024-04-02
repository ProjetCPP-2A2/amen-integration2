#ifndef AJOUTERSUPPLIER_H
#define AJOUTERSUPPLIER_H
#include <QMainWindow>
#include <QSqlQuery>
#include <QSqlQueryModel>
#include <QString>





class supplier
{
    int id,quantitee;
    QString nom,prenom,tel;

public :
    //constructeurs
    supplier(){}
    supplier(int,QString,QString,QString,int);
    //getters
    int getid(){return id;}
    QString getnom(){return nom;}
    QString getprenom(){return prenom;}
    QString getTel(){return tel;}
    int getquantitee(){return quantitee;}
    //setters
    void setid(int id){this->id=id;}
    void setnom(QString Nom){nom=Nom;}
    void setprenom(QString Prenom){prenom=Prenom;}
    void setTel(QString Tel){tel=Tel;}
    void setquantitee(int Quantitee){quantitee=Quantitee;}

    //fonctionalites de base relatives a l'entite Supplier
    bool ajouterSupplier();
    bool ValidateForm();
    QSqlQueryModel * afficherSupplier();
    bool supprimerSupplier(int);
    //declaration de la fonction update dans le fichier supplier.h
    bool modifierSupplier();
    QSqlQueryModel* chercher_nom(const QString& recherche);



};
#endif // AJOUTERSUPPLIER_H

