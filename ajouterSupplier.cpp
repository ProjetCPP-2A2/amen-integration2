#include "ajouterSupplier.h"
#include <QMessageBox>
#include <QSqlQueryModel>
#include <QTableView>
#include <QSqlError>

supplier::supplier(int id,QString nom,QString prenom, QString tel, int quantitee)
{
this->id=id;
this->nom=nom;
this->prenom=prenom;
this->tel=tel;
this->quantitee=quantitee;
}


bool supplier::ValidateForm()
{
    QString res  = QString::number(id);

    QRegularExpression regexID("^\\d+$"); // Accepte uniquement des chiffres
    QRegularExpression regexName("^[a-zA-Z]+$"); // Accepte uniquement des lettres
    QRegularExpression regexTel("^\\d{8}$"); // Accepte uniquement 8 chiffres
    QRegularExpression regexQuantitee("^\\d+$"); // Accepte uniquement des chiffres

    if (!regexID.match(res).hasMatch())
    {
        QMessageBox::information(nullptr, QObject::tr("Erreur"),
                    QObject::tr("L'ID doit être un nombre entier."), QMessageBox::Cancel);
        return false;
    }

    if (!regexName.match(nom).hasMatch())
    {
        QMessageBox::information(nullptr, QObject::tr("Erreur"),
                    QObject::tr("Le nom ne doit contenir que des lettres."), QMessageBox::Cancel);
        return false;
    }

    if (!regexName.match(prenom).hasMatch())
    {
        QMessageBox::information(nullptr, QObject::tr("Erreur"),
                    QObject::tr("Le prénom ne doit contenir que des lettres."), QMessageBox::Cancel);
        return false;
    }

    if (!regexTel.match(tel).hasMatch())
    {
        QMessageBox::information(nullptr, QObject::tr("Erreur"),
                    QObject::tr("Le téléphone doit être un nombre de 8 chiffres."), QMessageBox::Cancel);
        return false;
    }

    if (!regexQuantitee.match(QString::number(quantitee)).hasMatch())
    {
        QMessageBox::information(nullptr, QObject::tr("Erreur"),
                    QObject::tr("La quantité doit être un nombre entier."), QMessageBox::Cancel);
        return false;
    }

    return true;
}

bool supplier::ajouterSupplier()
{
    QSqlQuery query;
    QString res  = QString::number(id);
    QString res2 = QString::number(quantitee);

    query.prepare("insert into supplier (id, nom, prenom, tel, quantitee) values (:id, :nom, :prenom, :tel, :quantitee)");

    //creation des variables liées
    query.bindValue(":id",res);
    query.bindValue(":nom",nom);
    query.bindValue(":prenom",prenom);
    query.bindValue(":tel",tel);
    query.bindValue(":quantitee",res2);

    //appel de la fonction ValidateForm pour valider les données du formulaire
    if (ValidateForm()) //si les données sont valides
    {
        return query.exec(); //exécute la requête SQL et retourne le résultat
    }
    else //si les données ne sont pas valides
    {
        return false; //retourne false pour indiquer que l'ajout a échoué
    }

}




QSqlQueryModel * supplier::afficherSupplier()
{
    QSqlQueryModel * model=new QSqlQueryModel();
    model->setQuery("select * from supplier order by nom,prenom");
    model->setHeaderData(0,Qt::Horizontal,QObject::tr("ID"));
    model->setHeaderData(1,Qt::Horizontal,QObject::tr("Nom"));
    model->setHeaderData(2,Qt::Horizontal,QObject::tr("Prénom"));
    model->setHeaderData(3,Qt::Horizontal,QObject::tr("Tel"));
    model->setHeaderData(4,Qt::Horizontal,QObject::tr("Quantitee"));

    return model;

}

bool supplier::supprimerSupplier(int id)
{
    QSqlQuery query;
    QString res=QString::number(id);
    query.prepare("DELETE from supplier where ID = :id");
    query.bindValue(":id",res);

    return query.exec();
}




bool supplier::modifierSupplier()
{
    QSqlQuery query;
    QString res  = QString::number(id);
    QString res2 = QString::number(quantitee);

    query.prepare("update supplier set nom = :nom, prenom = :prenom, tel = :tel, quantitee = :quantitee where id = :id");

    //creation des variables liées
    query.bindValue(":id",res);
    query.bindValue(":nom",nom);
    query.bindValue(":prenom",prenom);
    query.bindValue(":tel",tel);
    query.bindValue(":quantitee",res2);

    //appel de la fonction ValidateForm pour valider les données du formulaire
    if (ValidateForm()) //si les données sont valides
    {
        return query.exec(); //exécute la requête SQL et retourne le résultat
    }
    else //si les données ne sont pas valides
    {
        return false; //retourne false pour indiquer que l'ajout a échoué
    }
}


QSqlQueryModel* supplier::chercher_nom(const QString& recherche) {
  QSqlQueryModel* model = new QSqlQueryModel();
  QString preparedQuery = "SELECT * from supplier WHERE prenom LIKE :recherche";
  QSqlQuery query ;
  query.prepare(preparedQuery);
  query.bindValue(":recherche", recherche + "%"); // Ajout du % pour la recherche partielle
  if (!query.exec()) {
    //qDebug() << "Erreur lors de la recherche : " << query.lastError().text();
    return nullptr;
  }

  model->setQuery(query);
  model->setHeaderData(0, Qt::Horizontal, QObject::tr("ID "));
  model->setHeaderData(1, Qt::Horizontal, QObject::tr("Nom"));
  model->setHeaderData(2, Qt::Horizontal, QObject::tr("Prenom "));
  model->setHeaderData(3, Qt::Horizontal, QObject::tr("tel"));
  model->setHeaderData(4, Qt::Horizontal, QObject::tr("Quantité"));

  return model;
}










