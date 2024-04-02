#ifndef DIALOGK_H
#define DIALOGK_H
#include"forum.h"
#include"mainwindow.h"
#include <QVBoxLayout>
#include <QHBoxLayout>
#include<QFormLayout>
#include <QLabel>
#include <QDialog>
#include<QMessageBox>
namespace Ui {
class Dialogk;
}

class Dialogk : public QDialog
{
    Q_OBJECT

public:
    explicit Dialogk(QWidget *parent = nullptr);
    ~Dialogk();
    void afficher();
    void clearLayout(QLayout *layout);
private slots:
    void on_send_clicked();

private:
    Ui::Dialogk *ui;
    forum f;
    QFormLayout* layout;

};

#endif // DIALOGK_H
