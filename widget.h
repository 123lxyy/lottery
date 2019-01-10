#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <QPainter>
#include <QDir>
#include <QTextCodec>
#include <QTimer>
#include <QLabel>
#include <QTime>
#include <QListWidget>

#define  _size 103

namespace Ui {
class Widget;
}

class Widget : public QWidget
{
    Q_OBJECT

public:
    explicit Widget(QWidget *parent = 0);
    ~Widget();
    void initTop();
    void initCenter();
    void paintEvent(QPaintEvent *parent);
    void sleep(int msec);


private slots:
    void on_pushButton_4_clicked();
    void on_pushButton_3_clicked();
    void on_pushButton_2_clicked();
    void on_pushButton_clicked();
    void on_pushButton_5_clicked();
    void on_pushButton_6_clicked();
    void on_pushButton_7_clicked();
    void doLottery();

private:
    Ui::Widget *ui;
    int dir_count;
    QStringList stringlist;
    QString path;
    QString strAppend;
    QStringList files;
    QStringList fileCopy;
    QImage *image;
    QLabel *label;
    QTimer *timer;
    QTime time;
    int rand;
    int flag;
    int randNum;
    QList <QLabel *> labelList;

};

#endif // WIDGET_H
