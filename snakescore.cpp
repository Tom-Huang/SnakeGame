#include "snakescore.h"

SnakeScore::SnakeScore(size_t init_length, QGraphicsItem* parent = 0)
    : QGraphicsTextItem(parent) {
    length = init_length;
    setPlainText(QString("Score: ") + QString::number(length));
    setDefaultTextColor(Qt::blue);
    setFont(QFont("times", 16));
}

void SnakeScore::increase() { length++; }

size_t SnakeScore::getScore() const { return length; }
