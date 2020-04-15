#include "snake.h"
#include <QDebug>

Snake::Snake(int s_width, int m_quater_width)
    : snake_width(s_width), map_quater_width(m_quater_width), is_die(0) {
    initialize();
    connect(this, SIGNAL(bumpWall(const QString)), this,
            SLOT(GameoverMessage(const QString)));
    connect(this, SIGNAL(bumpSelf(const QString)), this,
            SLOT(GameoverMessage(const QString)));
}

QRectF Snake::boundingRect() const {
    double field_quater_width = snake_width * map_quater_width;
    return QRectF(-field_quater_width, -field_quater_width,
                  2 * field_quater_width, 2 * field_quater_width);
}

void Snake::initialize() {
    // set default direction
    direction = UP;

    // set random head position
    headX = 0;
    headY = 0;
    int margin = 10;
    if (qrand() % 1) {
        headX = qrand() % (map_quater_width - margin);
        headY = qrand() % (map_quater_width - margin);
    } else {
        headX = qrand() % -(map_quater_width - margin);
        headY = qrand() % -(map_quater_width - margin);
    }
    headX *= snake_width;
    headY *= snake_width;

    // append snake bodies
    bodies.clear();
    std::shared_ptr<SnakeBody> tmp_shared_ptr(
        new SnakeBody(headX, headY, snake_width, snake_width));
    bodies.push_back(tmp_shared_ptr);
    tmp_shared_ptr.reset(
        new SnakeBody(headX - snake_width, headY, snake_width, snake_width));
    bodies.push_back(tmp_shared_ptr);

    // set snake length
    length = bodies.size();

    // set snake score
    score = std::shared_ptr<SnakeScore>(new SnakeScore(0, this));
    score->setPos(-snake_width * map_quater_width,
                  -snake_width * map_quater_width);

    // initialize snake map
    m_snake_map =
        std::shared_ptr<SnakeMap>(new SnakeMap(snake_width, map_quater_width));
}

void Snake::advance(int phase) {
    if (!phase) {
        return;
    }
    double nextX = 0;
    double nextY = 0;
    switch (direction) {
        case LEFT:
            nextX = headX - snake_width;
            nextY = headY;
            break;
        case RIGHT:
            nextX = headX + snake_width;
            nextY = headY;
            break;
        case UP:
            nextX = headX;
            nextY = headY - snake_width;
            break;
        case DOWN:
            nextX = headX;
            nextY = headY + snake_width;
            break;
    }
    if (isNextFood(nextX, nextY)) {
        grow(nextX, nextY);
    } else if (isNextWall(nextX, nextY)) {
        emit bumpWall(QString("Your snake bumps into the wall!"));
    } else if (isNextSelf(nextX, nextY)) {
        emit bumpSelf(QString("Your snake eats itself!"));
    } else {
        move(nextX, nextY);
    }
    update();
}

void Snake::paint(QPainter* painter, const QStyleOptionGraphicsItem* option,
                  QWidget* widget) {
    QBrush mybrush(Qt::green);
    QPen mypen(Qt::black);
    mypen.setWidth(2);
    painter->setBrush(mybrush);
    painter->setPen(mypen);

    // paint snake bodies
    for (const auto& m_rec : bodies) {
        QRectF rec(m_rec->x(), m_rec->y(), snake_width, snake_width);
        painter->fillRect(rec, mybrush);
        painter->drawRect(rec);
    }

    // paint food
    QBrush foodbrush(Qt::red);
    painter->setBrush(foodbrush);
    for (const auto& food_pos : m_snake_map->getFoodPosSet()) {
        QRectF rec(food_pos.first, food_pos.second, snake_width, snake_width);
        painter->fillRect(rec, foodbrush);
        painter->drawRect(rec);
    }
}

void Snake::keyPressEvent(QKeyEvent* event) {
    switch (event->key()) {
        case Qt::Key_Up:
            if (direction == LEFT || direction == RIGHT) direction = UP;
            break;
        case Qt::Key_Down:
            if (direction == LEFT || direction == RIGHT) direction = DOWN;
            break;
        case Qt::Key_Left:
            if (direction == UP || direction == DOWN) direction = LEFT;
            break;
        case Qt::Key_Right:
            if (direction == UP || direction == DOWN) direction = RIGHT;
            break;
    }
}

void Snake::grow(double pos_x, double pos_y) {
    // extend snake bodies
    bodies.push_front(std::shared_ptr<SnakeBody>(
        new SnakeBody(pos_x, pos_y, snake_width, snake_width)));
    bodies[0]->setPos(pos_x, pos_y);
    headX = pos_x;
    headY = pos_y;
    // update food position
    m_snake_map->eraseFood(pos_x, pos_y);
    m_snake_map->generateFood();
    // update length
    length++;
    // update score
    score->increase();
    score->setPlainText(QString("Score: ") +
                        QString::number(score->getScore()));
}

void Snake::move(double pos_x, double pos_y) {
    std::size_t N = bodies.size();

    for (std::size_t i = N - 1; i > 0; --i) {
        double front_pos_x = bodies[i - 1]->x();
        double front_pos_y = bodies[i - 1]->y();
        //        qDebug() << front_pos_x << front_pos_y << endl;
        bodies[i]->setPos(front_pos_x, front_pos_y);
    }
    bodies[0]->setPos(pos_x, pos_y);
    //    qDebug() << pos_x << pos_y << endl;
    headX = pos_x;
    headY = pos_y;
    //    qDebug() << "head: " << headX << headY << endl;
}

bool Snake::isNextFood(double nextX, double nextY) {
    return m_snake_map->hasFoodat(nextX, nextY);
}

bool Snake::isNextWall(double nextX, double nextY) {
    double limit = snake_width * map_quater_width;
    if (fabs(nextX - limit) < 0.1 || fabs(nextX + limit) < 0.1 ||
        fabs(nextY - limit) < 0.1 || fabs(nextY + limit) < 0.1) {
        return true;
    }
    return false;
}

bool Snake::isNextSelf(double nextX, double nextY) {
    for (std::size_t i = 1; i < bodies.size(); ++i) {
        const auto& m_rec = bodies[i];
        if (fabs(nextX - m_rec->x()) < 0.1 && fabs(nextY - m_rec->y()) < 0.1) {
            qDebug() << nextX << m_rec->x() << nextY << m_rec->y() << endl;
            return true;
        }
    }
    return false;
}

void Snake::GameoverMessage(const QString msg) {
    msgbox.setText(msg);
    if (msgbox.exec() == QMessageBox::Ok) {
        initialize();
    };
}

void Snake::MsgBoxButtonClicked() { initialize(); }
