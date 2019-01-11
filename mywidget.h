#ifndef MYWIDGET_H
#define MYWIDGET_H

#include <QWidget>
#include <QPainter>
#include <QBrush>
namespace Ui {
class MyWidget;
}
class MyWidget : public QWidget
{
    Q_OBJECT

public:
    explicit MyWidget(QWidget *parent = 0);
    ~MyWidget();
protected:
    void paintEvent(QPaintEvent *event);

private:
    Ui::MyWidget *ui;
};

#endif // MYWIDGET_H
