// MonDelegate.cpp
#include "delegateitem.h"
#include <QPixmap>
#include <QPainter>

MonDelegate::MonDelegate(QObject *parent) : QStyledItemDelegate(parent) {}

void MonDelegate::paint(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) const {
    if (index.column() == 1 ) {  // Colonne d'image
        QString cheminImage = index.data().toString();
        QSize targetSize = option.rect.size();  // Utilisez la taille de la cellule comme taille cible

        QPixmap image = scaledImage(cheminImage, targetSize);

        if (!image.isNull()) {
            QRect rect = option.rect;
            rect.setSize(targetSize);
            painter->drawPixmap(rect, image);
        }
    } else {
        QStyledItemDelegate::paint(painter, option, index);
    }
}

QSize MonDelegate::sizeHint(const QStyleOptionViewItem &option, const QModelIndex &index) const {
    if (index.column() == 1 ) {  // Colonne d'image
        QString cheminImage = index.data().toString();
        QPixmap image(cheminImage);

        // Définir la taille cible
        QSize targetSize(150, 150);  // Remplacez cela par la taille souhaitée

        // Redimensionner l'image tout en conservant le rapport d'aspect
        QSize scaledSize = image.scaled(targetSize, Qt::KeepAspectRatio).size();

        return scaledSize;
    } else {
        return QStyledItemDelegate::sizeHint(option, index);
    }
}
QSize MonDelegate::imageSize(const QString &imagePath) const {
    QPixmap image(imagePath);
    return image.size();
}

QPixmap MonDelegate::scaledImage(const QString &imagePath, const QSize &size) const {
    QPixmap image(imagePath);
    return image.scaled(size, Qt::KeepAspectRatio, Qt::SmoothTransformation);
}
