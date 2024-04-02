#ifndef KINEES_H
#define KINEES_H
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QSqlQueryModel>
#include <QString>
#include <QMessageBox>
#include <QStandardItemModel>
#include <QStandardItem>
#include <QTextDocument>
#include <QTextCursor>
#include <QTextTable>
#include <QPdfWriter>
#include <chrono>
#include <QFileDialog>
#include <QStandardItemModel>
#include <QStandardItem>
#include <QPixmap>
#include <QTextTableCell>
#include <QTextTableFormat>
#include <QFileInfo>
#include <QImage>
#include <QBuffer>


class kinees
{
public:
    kinees();
    kinees(int id,QString nom1,QString prenom1,QString email1,QString mdp1,int nb_patient1,QString image1);
    //getter//////////////////////////////////////////////////////////
    QString getNom();
    QString getPrenom();
    QString getEmail();
    QString getMdp();
    QString getImage();
    int getNb_Patient();
    int getId();
    //setter///////////////////////////////////////////////////////////
    void setNom(QString n);
    void setPrenom(QString n);
    void setEmail(QString n);
    void setMdp(QString n);
    void setNb_Patient(int n);
    void setID(int id);
    void setImage(QString image1);
    //CRUDSSSS///////////////////////////////////////////////////////
    bool ajouter();
    QStandardItemModel *afficher();
    bool supprimer(int id);
    QSqlQueryModel *update(int id1);
    bool update();
    QStandardItemModel *search(const QString nom);
    QStandardItemModel *tri(const QString arg1);
    QSqlQueryModel *LOGIN(QString email);
private :
    QString nom,prenom,email,mdp,image;
    int nb_patient,id_kinees;

};

#endif // KINEES_H
