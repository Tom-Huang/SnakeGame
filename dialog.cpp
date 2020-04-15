#include "dialog.h"
#include "snake.h"
#include "ui_dialog.h"

Dialog::Dialog(QWidget* parent) : QDialog(parent), ui(new Ui::Dialog) {
    ui->setupUi(this);

    scene = new QGraphicsScene(this);
    ui->graphicsView->setScene(scene);
    ui->graphicsView->setRenderHint(QPainter::Antialiasing);
    ui->graphicsView->setFocus();

    int snake_width = 5;
    int map_quater_width = 50;
    int field_quater_width = map_quater_width * snake_width;
    scene->setSceneRect(-field_quater_width, -field_quater_width,
                        2 * field_quater_width, 2 * field_quater_width);

    QPen mypen = QPen(Qt::red);
    mypen.setWidth(5);
    QLineF TopLine(scene->sceneRect().topLeft(), scene->sceneRect().topRight());
    QLineF BottomLine(scene->sceneRect().bottomLeft(),
                      scene->sceneRect().bottomRight());
    QLineF LeftLine(scene->sceneRect().topLeft(),
                    scene->sceneRect().bottomLeft());
    QLineF RightLine(scene->sceneRect().topRight(),
                     scene->sceneRect().bottomRight());

    scene->addLine(TopLine, mypen);
    scene->addLine(BottomLine, mypen);
    scene->addLine(LeftLine, mypen);
    scene->addLine(RightLine, mypen);

    // set timer to refresh every 100ms
    timer = new QTimer(this);
    connect(timer, SIGNAL(timeout()), scene, SLOT(advance()));
    timer->start(50);

    // add snake
    Snake* my_snake = new Snake(snake_width, map_quater_width);
    scene->addItem(my_snake);
    my_snake->setFlag(QGraphicsItem::ItemIsFocusable);
    my_snake->setFocus();

    // add score board
}

Dialog::~Dialog() { delete ui; }
