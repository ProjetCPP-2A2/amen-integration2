#ifndef MONDELEGATE_H
#define MONDELEGATE_H

#include <QStyledItemDelegate>

class MonDelegate : public QStyledItemDelegate {
    Q_OBJECT

public:
    explicit MonDelegate(QObject *parent = nullptr);
    void paint(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) const override;
    QSize sizeHint(const QStyleOptionViewItem &option, const QModelIndex &index) const override;
private:
    QSize imageSize(const QString &imagePath) const;
    QPixmap scaledImage(const QString &imagePath, const QSize &size) const;
};

#endif // MONDELEGATE_H
