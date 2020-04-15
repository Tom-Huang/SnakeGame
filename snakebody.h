#ifndef SNAKEBODY_H
#define SNAKEBODY_H
#include <QGraphicsRectItem>
#include <QPainter>

class SnakeBody : public QGraphicsRectItem {
   public:
    using QGraphicsRectItem::QGraphicsRectItem;
    SnakeBody();
    //    QRectF boundingRect() const;
    //    void paint(QPainter* painter, const QStyleOptionGraphicsItem* option,
    //               QWidget* widget);

    //   private:
    //    int snake_width;
};

#endif  // SNAKEBODY_H
