#include "connection.h"

connection::connection()
{

}

bool connection::createconnect()
{bool test=false;
db = QSqlDatabase::addDatabase("QODBC");
db.setDatabaseName("Source_Projet2A");
db.setUserName("amen");//inserer nom de l'utilisateur
db.setPassword("minousa");//inserer mot de passe de cet utilisateur

if (db.open())
test=true;





    return  test;
}

void connection::closeConnection(){ db.close(); }
