#ifndef DIALOG_H
#define DIALOG_H

#include <QDialog>
#include <QGraphicsScene>
#include <QGraphicsTextItem>
#include <QTimer>
#include <memory>

namespace Ui {
class Dialog;
}

class Dialog : public QDialog {
    Q_OBJECT

   public:
    explicit Dialog(QWidget* parent = nullptr);
    ~Dialog();

   private:
    Ui::Dialog* ui;
    QGraphicsScene* scene;
    QTimer* timer;
};

#endif  // DIALOG_H
