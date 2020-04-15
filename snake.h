#ifndef SNAKE_H
#define SNAKE_H
#include <QAbstractButton>
#include <QGraphicsItem>
#include <QGraphicsRectItem>
#include <QKeyEvent>
#include <QMessageBox>
#include <QObject>
#include <QPainter>
#include <deque>
#include <memory>
#include "snakebody.h"
#include "snakemap.h"
#include "snakescore.h"

enum Direction { UP = 0, RIGHT = 1, DOWN = 2, LEFT = 3 };

class Snake : public QObject, public QGraphicsItem {
    Q_OBJECT
   public:
    Snake(int snake_width, int map_quater_width);
    QRectF boundingRect() const;
    void initialize();
    void advance(int phase);
    void paint(QPainter* painter, const QStyleOptionGraphicsItem* option,
               QWidget* widget);
    void keyPressEvent(QKeyEvent* event);
    void grow(double pos_x, double pos_y);
    void move(double pos_x, double pos_y);
    bool isNextFood(double nextX, double nextY);
    bool isNextWall(double nextX, double nextY);
    bool isNextSelf(double nextX, double nextY);
   signals:
    void bumpWall(const QString msg);
    void bumpSelf(const QString msg);
   public slots:
    void GameoverMessage(const QString msg);
    void MsgBoxButtonClicked();

   private:
    std::deque<std::shared_ptr<SnakeBody>> bodies;
    double headX;
    double headY;
    Direction direction;
    size_t length;
    std::shared_ptr<SnakeScore> score;
    int snake_width;
    int map_quater_width;
    int is_die;
    std::shared_ptr<SnakeMap> m_snake_map;
    QMessageBox msgbox;
};

#endif  // SNAKE_H
