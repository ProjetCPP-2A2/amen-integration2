#ifndef AJOUTERACTIVITE_H
#define AJOUTERACTIVITE_H
#include <QStackedWidget>
#include <QMainWindow>

namespace Ui {
class AjouterActivite;
}

class AjouterActivite : public QMainWindow
{
    Q_OBJECT

public:
    explicit AjouterActivite(QWidget *parent = nullptr);
    ~AjouterActivite();

private:
    Ui::AjouterActivite *ui;
};

#endif // AJOUTERACTIVITE_H
