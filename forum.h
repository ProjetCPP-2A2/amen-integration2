#ifndef FORUM_H
#define FORUM_H


#include <QSqlQuery>
#include <QDebug>

class forum
{
public:
    forum();
    forum(QString nom1,QString com1);
    //getter setters
    QString getNom();
    void setNom(QString nom1);
    QString getCom();
    void setCom(QString com1);

    //CR
     bool ajouterForum();


private :
      QString nom,com;
};

#endif // FORUM_H
