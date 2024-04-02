#include "MenuSlider.h"

// qcustommenuslider.cpp

QCustomMenuSlider::QCustomMenuSlider(Qt::Orientation orientation, QWidget *parent)
    : QSlider(orientation, parent)
{
    connect(this, &QSlider::valueChanged, this, &QCustomMenuSlider::updateMenu);
    menu.addAction("Réinitialiser la valeur", this, &QCustomMenuSlider::resetValue);
}

void QCustomMenuSlider::contextMenuEvent(QContextMenuEvent *event)
{
    menu.exec(event->globalPos());
}

void QCustomMenuSlider::updateMenu(int value)
{
    menu.setTitle(QString("Valeur actuelle : %1").arg(value));
}

void QCustomMenuSlider::resetValue()
{
    setValue(0);
}

