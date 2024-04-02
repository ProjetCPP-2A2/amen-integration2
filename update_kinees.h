#ifndef UPDATE_KINEES_H
#define UPDATE_KINEES_H

#include <QMainWindow>

namespace Ui {
class update_kinees;
}

class update_kinees : public QMainWindow
{
    Q_OBJECT

public:
    explicit update_kinees(QWidget *parent = nullptr);
    ~update_kinees();

private:
    Ui::update_kinees *ui;
};

#endif // UPDATE_KINEES_H
