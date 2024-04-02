#include "kinees.h"
kinees::kinees()
{
    id_kinees=0;
    nom="";
    prenom="";
    email="";
    mdp="";
    nb_patient=0;

}
kinees::kinees(int id,QString nom1,QString prenom1,QString email1,QString mdp1,int nb_patient1,QString image1)
{
    id_kinees=id;
    nom=nom1;
    prenom=prenom1;
    email=email1;
    mdp=mdp1;
    nb_patient=nb_patient1;
    image=image1;

}

int kinees::getId(){return id_kinees;}
QString kinees::getNom(){return nom;}
QString kinees::getPrenom(){return prenom;}
QString kinees::getEmail(){return email;}
QString kinees::getMdp(){return mdp;}
QString kinees::getImage(){return image;}
int kinees::getNb_Patient(){return nb_patient;}


void kinees::setID(int id){id_kinees=id;}
void kinees::setNom(QString n){nom=n;}
void kinees::setPrenom(QString n){prenom=n;}
void kinees::setEmail(QString n){email=n;}
void kinees::setMdp(QString n){mdp=n;}
void kinees::setNb_Patient(int n){nb_patient=n;}
void kinees::setImage(QString image1){image=image1;}

bool kinees::ajouter()
{
    QSqlQuery query;
    QSqlQuery query2;
    query2.exec("SELECT MAX(id_kinees) FROM kinees;");
    int maxId = 0;
    if(query2.next()){
    maxId = query2.value(0).toInt()+1;
    }
    QString res = QString::number(maxId);
    QString nb = QString::number(nb_patient);
    query.prepare("insert into KINEES(ID_KINEES,NOM,PRENOM,EMAIL,NB_PATIENT,MDP,IMAGE) values (:id,:nom,:prenom,:email,:nb_patient,:mdp,:image);");

    query.bindValue(":id",res);
    query.bindValue(":nom",nom);
    query.bindValue(":prenom",prenom);
    query.bindValue(":email",email);
    query.bindValue(":nb_patient",nb);
    query.bindValue(":mdp",mdp);
    query.bindValue(":image",image);

    return query.exec();

}

QStandardItemModel * kinees::afficher()
{
    QSqlQuery query;
     QStandardItemModel *model = new QStandardItemModel();
       query.prepare("SELECT ID_KINEES,IMAGE,NOM,PRENOM,EMAIL,NB_PATIENT,MDP FROM kinees ORDER BY id_kinees ASC");

       if(query.exec()) {

           model->setHorizontalHeaderLabels(QStringList() << "ID_KINEES" << "IMAGE" << "NOM"<< "PRENOM" << "EMAIL" << "NB_PATIENT" << "MDP" );

           while(query.next()) {
               QList<QStandardItem*> items;
               for(int i = 0; i < 7; ++i) {
                   if(i == 1) { // Remplacez 6 par l'index de la colonne d'image dans votre modèle
                       QPixmap pixmap(query.value(i).toString());
                       QStandardItem *item = new QStandardItem();
                       item->setData(QVariant(pixmap.scaled(150,150)), Qt::DecorationRole); // Ajustez la taille de l'image comme vous le souhaitez
                       items.append(item);
                   } else {
                       items.append(new QStandardItem(query.value(i).toString()));
                   }
               }
               model->appendRow(items);
           }



       }
        return model;


}

bool kinees::supprimer(int id1)
{

    QSqlQuery query;
    query.prepare("DELETE FROM kinees WHERE id_kinees = :id");
    query.bindValue(":id", id1);
    return query.exec();

}


QSqlQueryModel * kinees::update(int id1)
{
    QSqlQueryModel * model=new QSqlQueryModel();
    model->setQuery("select * from kinees where id_kinees=" + QString::number(id1));
    return model;
}

 QSqlQueryModel * kinees::LOGIN(QString email)
 {
     QSqlQueryModel * model=new QSqlQueryModel();
     model->setQuery("SELECT * FROM kinees WHERE EMAIL = '" + email + "'");
     return model;

 }

bool kinees::update()
{
    QSqlQuery query;
    query.prepare("UPDATE KINEES SET NOM=:nom, PRENOM=:prenom, EMAIL=:email, NB_PATIENT=:nb_patient, MDP=:mdp, IMAGE=:image WHERE ID_KINEES=:id");
    QString id = QString::number(id_kinees);
    QString nb = QString::number(nb_patient);
    query.bindValue(":id",id);
    query.bindValue(":nom",nom);
    query.bindValue(":prenom",prenom);
    query.bindValue(":email",email);
    query.bindValue(":nb_patient",nb);
    query.bindValue(":mdp",mdp);
    query.bindValue(":image",image);
    return query.exec();

}

QStandardItemModel * kinees::search(const QString nom)
{
    QSqlQuery query;
    QStandardItemModel *model = new QStandardItemModel();
    query.prepare("SELECT ID_KINEES,IMAGE,NOM,PRENOM,EMAIL,NB_PATIENT,MDP FROM kinees WHERE nom LIKE '%%" + nom + "%%'");
    if(query.exec()) {

        model->setHorizontalHeaderLabels(QStringList() << "ID_KINEES" << "IMAGE" << "NOM"<< "PRENOM" << "EMAIL" << "NB_PATIENT" << "MDP" );

        while(query.next()) {
            QList<QStandardItem*> items;
            for(int i = 0; i < 7; ++i) {
                if(i == 1) { // Remplacez 6 par l'index de la colonne d'image dans votre modèle
                    QPixmap pixmap(query.value(i).toString());
                    QStandardItem *item = new QStandardItem();
                    item->setData(QVariant(pixmap.scaled(150,150)), Qt::DecorationRole); // Ajustez la taille de l'image comme vous le souhaitez
                    items.append(item);
                } else {
                    items.append(new QStandardItem(query.value(i).toString()));
                }
            }
            model->appendRow(items);
        }



    }
      return model;
}

QStandardItemModel *kinees::tri(const QString arg1)
{
    QSqlQuery query;
    QStandardItemModel *model = new QStandardItemModel();

        if(arg1 == "ASC") {
            query.prepare("SELECT ID_KINEES,IMAGE,NOM,PRENOM,EMAIL,NB_PATIENT,MDP FROM kinees ORDER BY nb_patient ASC");
        } else if(arg1 == "DESC") {
            query.prepare("SELECT ID_KINEES,IMAGE,NOM,PRENOM,EMAIL,NB_PATIENT,MDP FROM kinees ORDER BY nb_patient DESC");
        } else {
            // Si la valeur est "NONE" ou autre chose, ne pas trier
            query.prepare("SELECT ID_KINEES,IMAGE,NOM,PRENOM,EMAIL,NB_PATIENT,MDP FROM kinees order by id_kinees asc");
        }

        if(query.exec()) {

            model->setHorizontalHeaderLabels(QStringList() << "ID_KINEES" << "IMAGE" << "NOM"<< "PRENOM" << "EMAIL" << "NB_PATIENT" << "MDP" );

            while(query.next()) {
                QList<QStandardItem*> items;
                for(int i = 0; i < 7; ++i) {
                    if(i == 1) { // Remplacez 6 par l'index de la colonne d'image dans votre modèle
                        QPixmap pixmap(query.value(i).toString());
                        QStandardItem *item = new QStandardItem();
                        item->setData(QVariant(pixmap.scaled(150,150)), Qt::DecorationRole); // Ajustez la taille de l'image comme vous le souhaitez
                        items.append(item);
                    } else {
                        items.append(new QStandardItem(query.value(i).toString()));
                    }
                }
                model->appendRow(items);
            }



        }
          return model;

}
