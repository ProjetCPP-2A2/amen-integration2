// qcustommenuslider.h
#ifndef QCUSTOMMENUSLIDER_H
#define QCUSTOMMENUSLIDER_H

#include <QSlider>
#include <QMenu>
#include <QContextMenuEvent>

class QCustomMenuSlider : public QSlider
{
    Q_OBJECT

public:
    QCustomMenuSlider(Qt::Orientation orientation, QWidget *parent = nullptr);

protected:
    void contextMenuEvent(QContextMenuEvent *event) override;

private slots:
    void updateMenu(int value);
    void resetValue();

private:
    QMenu menu;
};

#endif // QCUSTOMMENUSLIDER_H
