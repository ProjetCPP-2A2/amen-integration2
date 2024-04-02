#include "activity.h"

//constructor
Activity::Activity(int id1,QString nom1,QString type1,QString degres1,int duree1,QString image,QString equip)
{
id=id1;
nom=nom1;
type=type1;
degres=degres1;
duree=duree1;
imageA=image;
nom_equip=equip;
}

//setters

void Activity::setId(int id1){
    id=id1;

}
void Activity::setNomActivite(QString nom1){
    nom=nom1;
}
void Activity::setTypeActivite(QString type1){
    type=type1;
}
void Activity::setDureeActivite(int duree1){
    duree=duree1;
}
void Activity::setDegresActivite(QString degres1){
    degres=degres1;
}
void Activity::setImage(QString image){
    imageA=image;
}

void Activity::setNomE(QString nomE){
    nom_equip=nomE;
}

//getters
int Activity::getId(){
    return id;
}
QString Activity::getNomActivite(){
    return nom;
}
QString Activity::getTypeActivite(){
    return  type;
}
int Activity::getDureeActivite(){
    return  duree;
}
QString Activity::getDegresActivite(){
    return degres;
}
QString Activity::getImage(){
    return imageA;
}
QString Activity ::getNomE(){
    return nom_equip;
}

//CRUD

bool Activity::ajouterActivite(){
    QSqlQuery query1;
    query1.exec("SELECT MAX(ID) FROM ACTIVITY ;");
    int maxId = 0;

   query1.next();

        maxId = query1.value(0).toInt() + 1;

   QSqlQuery query;
   QString res=QString::number(maxId);
   QString dur =QString::number(duree);
   QString insert ="insert into activity (id,type_activity,nom_activity,duree_activity,degres,image,equipement) VALUES (:id ,:type ,:nom,:duree, :degres ,:images,:equipement) ";

  query.prepare(insert);
  query.bindValue(":id",res);
  query.bindValue(":nom",nom);
  query.bindValue(":type",type);
  query.bindValue(":duree",dur);
  query.bindValue(":degres",degres);
  query.bindValue(":images",imageA);
  query.bindValue(":equipement",nom_equip);
  return query.exec();


}

bool Activity::supprimerActivite(int id1){
    QSqlQuery query;
        query.prepare("DELETE FROM activity WHERE id = :id");
        query.bindValue(":id", id1);
        return query.exec();
}

void Activity::afficherActivite(QTableView *tableView){
QSqlQueryModel *model= new QSqlQueryModel();
model->setQuery("select id,image,nom_activity,type_activity,duree_activity,degres,equipement from activity order by duree_activity ");



MonDelegate *delegate = new MonDelegate(tableView);  // Utilisez tableView comme parent
    tableView->setItemDelegateForColumn(1, delegate);


    tableView->setModel(model);

}

bool Activity ::UpdateActivite(){
    QSqlQuery query;
    QString dur =QString::number(duree);
    QString ID =QString::number(id);
    QString modifier ="update  activity set type_activity=:type, nom_activity=:nom, duree_activity=:duree , degres=:degres, image=:images, equipement=:equipement  where id= :id1  ";

   query.prepare(modifier);

   query.bindValue(":nom",nom);
   query.bindValue(":type",type);
   query.bindValue(":duree",dur);
   query.bindValue(":degres",degres);
   query.bindValue(":equipement",nom_equip);
   query.bindValue(":id1",ID);
   query.bindValue(":images",imageA);
   return query.exec();

}
QMap<QString,QString> Activity::recuperation(){
    QSqlQuery query;
    QMap<QString,QString> equipement;
    if(query.exec("select image,nom from equipement ")){
        while(query.next()){
               QString equipementI = query.value(0).toString();
               QString equipementN= query.value(1).toString();
               equipement[equipementN]=equipementI;
        }
    }
    return equipement;
}

bool Activity::nomUnique(QString name){

    QSqlQuery query;
        query.prepare("SELECT COUNT(*) FROM activity WHERE nom_activity = :nom");
        query.bindValue(":nom", name);

        if (!query.exec()) {
            QMessageBox::critical(nullptr, "Erreur", "Erreur lors de l'exécution de la requête");
            return false;
        }

        if (query.next()) {
            int count = query.value(0).toInt();
            if(count==0)
                return true;// Retourne vrai si le nom est unique, faux sinon
        }

        return false;
    }
void Activity::rechercheAc(QTableView *tableView,QString n){

    QSqlQueryModel * model=new QSqlQueryModel();
     model->setQuery("SELECT id,image,nom_activity,type_activity,duree_activity,degres,equipement FROM activity WHERE nom_activity LIKE '%%" + n + "%%'");
     tableView->setModel(model);


}


