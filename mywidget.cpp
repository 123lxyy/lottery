#include "mywidget.h"

MyWidget::MyWidget(QWidget *parent) :
    QWidget(parent)
{

}

MyWidget::~MyWidget()
{
    delete ui;
}
void MyWidget::paintEvent(QPaintEvent *event)
{
    Q_UNUSED(event);
    QBrush brush;
    brush.setColor("#B22222");
    brush.setStyle(Qt::SolidPattern);

    QPainter p(this);
    p.setPen(Qt::NoPen);
    p.setBrush(brush);
    p.drawRect(rect());
}
