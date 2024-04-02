#include "seance.h"
#include <vector>
#include <string>
#include <QDebug>
#include <QSqlError>
#include <QInputDialog>
#include <QSslSocket>
#include <QTcpSocket>
#include <QSslSocket>
#include <QSslKey>
#include <QSslCertificate>
#include <cstdlib> // Pour la fonction rand()
#include <ctime>   // Pour initialiser le générateur de nombres aléatoires

int genererEntierQuatreChiffres() {
    // Initialiser le générateur de nombres aléatoires
    srand(time(0));

    // Générer un entier aléatoire entre 1000 et 9999 (inclus)
    return rand() % 9000 + 1000;
}

#include "seance.h"
using namespace std;
Seance::Seance()
{
    Id_seance = 0;
    dte = "";
    duree = 0;
    prix = 0.0;
    statut = "en cours";
    nom_patient = "";
    nom_kinee = "";
    nom_activite = "";
}

bool Seance::existance(int id)
{
    QSqlQuery query;
    query.prepare("SELECT * FROM SEANCE WHERE ID_SEANCE = ?");
    query.addBindValue(id);
    if(query.exec())
    {
        if(query.next())
        {
            // QMessageBox::information(this,  "ID existe", "ID déjà existant.");
            return false;
        }
    }
    return true;
}


Seance::Seance(int id,QString dte,int duree,double prix,QString statut,QString nom,QString nomk, QString noma)
{
    this->Id_seance=id;
    this->dte=dte;
    this->duree=duree;
    this->prix=prix;
    this->statut=statut;
    this->nom_patient=nom;
    this->nom_kinee=nomk;
    this->nom_activite=noma;

}




bool Seance::ajouter()
{
    QSqlQuery query;


    query.exec("SELECT MAX(ID_SEANCE) FROM SEANCE");
    int lastId = 0;
    if (query.next()) {
        lastId = query.value(0).toInt();
    }


    int newId = lastId + 1;

    QString res = QString::number(newId);
    query.prepare("INSERT INTO SEANCE (ID_SEANCE, DTE, DUREE, PRIX, STATUT, NOM_PATIENT, NOM_KINEES, NOM_ACTIVITY) VALUES (:id, :dte, :duree, :prix, :statut, :nom , :nomk, :noma)");

    query.bindValue(":id", newId);
    query.bindValue(":dte", dte);
    query.bindValue(":duree", duree);
    query.bindValue(":prix", prix);
    query.bindValue(":statut", statut);
    query.bindValue(":nom", nom_patient);
    query.bindValue(":nomk", nom_kinee);
    query.bindValue(":noma", nom_activite);

    return query.exec();
}


bool Seance::supprimer(int id){
    QSqlQuery query;
    QString res= QString::number(id);
    query.prepare("delete from SEANCE where Id_seance= :id");
    query.bindValue(":id",res);
    return query.exec();
}


QSqlQueryModel * Seance::afficher() {
    QSqlQueryModel * model = new QSqlQueryModel();
    model->setQuery("SELECT ID_SEANCE, DTE, DUREE, PRIX, STATUT, NOM_PATIENT, NOM_KINEES, NOM_ACTIVITY FROM SEANCE ORDER BY ID_SEANCE");
    model->setHeaderData(0, Qt::Horizontal, QObject::tr("ID_SEANCE"));
    model->setHeaderData(1, Qt::Horizontal, QObject::tr("DATE"));
    model->setHeaderData(2, Qt::Horizontal, QObject::tr("DUREE (min)"));
    model->setHeaderData(3, Qt::Horizontal, QObject::tr("PRIX (dt)"));
    model->setHeaderData(4, Qt::Horizontal, QObject::tr("STATUT"));
    model->setHeaderData(5, Qt::Horizontal, QObject::tr("NOM_PATIENT"));
    model->setHeaderData(6, Qt::Horizontal, QObject::tr("NOM_KINEES"));
    model->setHeaderData(7, Qt::Horizontal, QObject::tr("NOM_ACTIVITY"));



    return model;
}

QSqlQueryModel * Seance::afficher_sort() {
    QSqlQueryModel * model = new QSqlQueryModel();
    model->setQuery("SELECT ID_SEANCE, DTE, DUREE, PRIX, STATUT, NOM_PATIENT, NOM_KINEES, NOM_ACTIVITY FROM SEANCE ORDER BY PRIX");
    model->setHeaderData(0, Qt::Horizontal, QObject::tr("ID_SEANCE"));
    model->setHeaderData(1, Qt::Horizontal, QObject::tr("DATE"));
    model->setHeaderData(2, Qt::Horizontal, QObject::tr("DUREE (min)"));
    model->setHeaderData(3, Qt::Horizontal, QObject::tr("PRIX (dt)"));
    model->setHeaderData(4, Qt::Horizontal, QObject::tr("STATUT"));
    model->setHeaderData(5, Qt::Horizontal, QObject::tr("NOM_PATIENT"));
    model->setHeaderData(6, Qt::Horizontal, QObject::tr("NOM_KINEES"));
    model->setHeaderData(7, Qt::Horizontal, QObject::tr("NOM_ACTIVITY"));



    return model;
}

QSqlQueryModel *Seance::Search(const QString& nom)
{
    QSqlQueryModel *model = new QSqlQueryModel();

    if (nom.isEmpty())
    {
        model->setQuery("SELECT ID_SEANCE, DTE, DUREE, PRIX, STATUT, NOM_PATIENT, NOM_KINEES, NOM_ACTIVITY FROM SEANCE");
    }
    else
    {
        QString query = QString("SELECT ID_SEANCE, DTE, DUREE, PRIX, STATUT, NOM_PATIENT, NOM_KINEES, NOM_ACTIVITY FROM SEANCE WHERE NOM_KINEES LIKE '%" + nom + "%'");

        model->setQuery(query);
    }



    return model;
}





bool Seance::modifier(int id, const QString& dte, int duree, double prix, const QString& statut, const QString& nom, const QString& nom_kinees, const QString& nom_activite)
{
    QSqlQuery query;
    query.prepare("UPDATE SEANCE SET DTE = :dte, DUREE = :duree, PRIX = :prix, STATUT = :statut, NOM_PATIENT = :nom, NOM_KINEES = :nom_kinees, NOM_ACTIVITY = :nom_activite WHERE ID_SEANCE = :id");
    query.bindValue(":id", id);
    query.bindValue(":dte", dte);
    query.bindValue(":duree", duree);
    query.bindValue(":prix", prix);
    query.bindValue(":statut", statut);
    query.bindValue(":nom", nom);
    query.bindValue(":nom_kinees", nom_kinees);
    query.bindValue(":nom_activite", nom_activite);

    return query.exec();
}


vector<QString> Seance::recuperation_nom_patient() {
    vector<QString> patientNames;
    QSqlQuery query;
    if (query.exec("SELECT EMAIL FROM PATIENT")) {
        while (query.next()) {
            QString patientName = query.value(0).toString();
            patientNames.push_back(patientName);
        }
    }
    return patientNames;
}

vector<QString> Seance::recuperation_nom_kinee() {
    vector<QString> kineeNames;
    QSqlQuery query;
    if (query.exec("SELECT NOM FROM KINEES")) {
        while (query.next()) {
            QString kineetName = query.value(0).toString();
            kineeNames.push_back(kineetName);
        }
    }
    return kineeNames;
}


QMap<QString, QString> Seance::recuperation_nom_activite(QString email) {
    QMap<QString, QString> activityNames;
    QSqlQuery query1;
    query1.prepare("SELECT cas FROM patient WHERE email = :email");
    query1.bindValue(":email", email);

    if (query1.exec()) {
        if (query1.next()) {
            QString cas = query1.value(0).toString();
            QSqlQuery query;
            query.prepare("SELECT nom_activity, image FROM activity WHERE type_activity = :cas");
            query.bindValue(":cas", cas);

            if (query.exec()) {
                while (query.next()) {
                    QString acNom = query.value(0).toString();
                     QString acImage = query.value(1).toString();
                    activityNames[acNom] = acImage;
                }
            } else {
                qDebug() << "Erreur lors de l'exécution de la requête activity:" << query.lastError().text();
            }
        }
    } else {
        qDebug() << "Erreur lors de l'exécution de la requête patient:" << query1.lastError().text();
    }

    return activityNames;
}


vector<QString> Seance::recuperation_date() {
    vector<QString> dateseances;
    QSqlQuery query;
    if (query.exec("SELECT DTE FROM SEANCE")) {
        while (query.next()) {
            QString dateseance = query.value(0).toString();
            dateseances.push_back(dateseance);
        }
    }
    return dateseances;
}


QSqlQueryModel* Seance::afficherPourDate(const QDate& date) {
    QSqlQueryModel *model = new QSqlQueryModel();
    QSqlQuery query;
    query.prepare("SELECT ID_SEANCE, DTE, DUREE, PRIX, STATUT, NOM_PATIENT, NOM_KINEES, NOM_ACTIVITY FROM SEANCE WHERE DTE = ?");
    query.addBindValue(date.toString("yyyy-MM-dd"));

    if (!query.exec()) {
        qDebug() << "Erreur lors de l'exécution de la requête:" << query.lastError().text();
    } else {
        qDebug() << "Requête exécutée avec succès." ;
    }

    model->setQuery(query);

    return model;
}





