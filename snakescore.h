#ifndef SNAKESCORE_H
#define SNAKESCORE_H
#include <QFont>
#include <QGraphicsTextItem>

class SnakeScore : public QGraphicsTextItem {
   public:
    using QGraphicsTextItem::QGraphicsTextItem;
    SnakeScore(size_t init_length, QGraphicsItem* parent);
    void increase();
    size_t getScore() const;

   private:
    size_t length;
};

#endif  // SNAKESCORE_H
