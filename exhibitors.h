#ifndef EXHIBITORS_H
#define EXHIBITORS_H

#include <QWidget>
#include <QFile>
#include <QDebug>
#include <QFont>
#include <QLabel>
#include <QMouseEvent>
#include <QPainter>
namespace Ui {
class Exhibitors;
}

class Exhibitors : public QWidget
{
    Q_OBJECT

public:
    explicit Exhibitors(QWidget *parent = 0);
    ~Exhibitors();
    void readFile();
    void parse(QString str);
    void mousePressEvent(QMouseEvent *event);
    void mouseMoveEvent(QMouseEvent *event);
    void getpath(QString path);
    void paintEvent(QPaintEvent *event);

private slots:
    void on_pushButton_clicked();

private:
    Ui::Exhibitors *ui;
    QStringList list;
    QStringList typeList;
    int num_one,num_two,num_three;
    QLabel *sanLabel;
    QLabel *luckyLabel;
    QList <QLabel*> sanList;
    QList <QLabel*> luckyList;
    QFont *font;
    QPoint windowPos;
    QPoint mousePos;
    QPoint dPos;
    QString path;
};

#endif // EXHIBITORS_H
