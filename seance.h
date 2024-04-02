
#ifndef SEANCE_H
#define SEANCE_H

#include <QString>
#include <QVariant>
#include <QDate>
#include <QSqlQuery>
#include <QSqlQueryModel>
#include <vector>
#include <string>
#include<QMap>
#include<QDebug>
using namespace std;


class Seance
{
public:
    Seance();
    Seance(int,QString,int,double,QString,QString,QString,QString);


    /*void setIdKinee(int id);
    void setIdPatinet(int id);*/
    void setIdSeance(int id)
    {
        this->Id_seance = id;
    }
    void setDate(QString d)
    {
        dte = d;
    }
    void setDuree(int d)
    {
        duree = d;
    }
    void setPrix(double p)
    {
        prix = p;
    }
    void setStatut( QString s)
    {
        statut = s;
    }
    void setnom_patient( QString np)
    {
        nom_patient = np;
    }

    void setnom_kinee( QString nk)
    {
        nom_kinee = nk;
    }

    void setnom_activite( QString na)
    {
        nom_activite = na;
    }




    /*int getIdKinee();
    int getIdPatinet();*/
    int getIdSeance(){
        return Id_seance;
    }
    QString getDate(){
        return dte;
    }
    int getDuree(){
        return duree;
    }
    double getPrix(){
        return prix;
    }
    QString getStatut(){
        return statut;
    }
    QString getnom_patient(){
        return nom_patient;
    }
    QString getnom_kinee(){
        return nom_kinee;
    }
    QString getnom_activite(){
        return nom_activite;
    }

    bool ajouter();
    QSqlQueryModel * afficher();
    QSqlQueryModel * afficher_sort();
    QSqlQueryModel *Search(const QString& nomPatient);
    bool supprimer(int);
    bool modifier(int id, const QString& dte, int duree, double prix, const QString& statut, const QString& nom_patient, const QString& nom_kinees, const QString& nom_activite);
    vector<QString>recuperation_nom_patient();
    vector<QString>recuperation_nom_kinee();
    //vector<QString>recuperation_nom_activite();
    QMap<QString,QString>recuperation_nom_activite(QString email);
    vector<QString>recuperation_date();
    QSqlQueryModel * afficherPourDate(const QDate& date);
    bool existance(int id);





private:
    int Id_seance;
    /*int Id_kinee;
    int Id_patinet;*/
    QString dte;
    int duree;
    double prix;
    QString statut;
    QString nom_patient;
    QString nom_kinee;
    QString nom_activite;

};

#endif // SEANCE_H

