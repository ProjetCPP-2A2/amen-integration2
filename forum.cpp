#include "forum.h"

forum::forum()
{

}
forum::forum(QString nom1,QString com1):nom(nom1),com(com1){}


QString forum::getCom(){
    return com;
}
QString forum::getNom(){
    return nom;
}

void forum::setCom(QString com1){
    com=com1;
}
void forum::setNom(QString nom1){

    nom=nom1;
}
bool forum::ajouterForum(){
    QSqlQuery query1;
    query1.exec("SELECT MAX(id_forum) FROM FORUM ;");
    int maxId = 0;

    if(query1.next())
        maxId = query1.value(0).toInt() + 1;

    QSqlQuery query;
    QString res=QString::number(maxId);
    QString insert ="insert into forum(id_forum,nom,commentaire)  VALUES (:id,:nom,:com); ";
    query.prepare(insert);
    query.bindValue(":id",res);
    query.bindValue(":nom",nom);
    query.bindValue(":com",com);
    return query.exec();
}
