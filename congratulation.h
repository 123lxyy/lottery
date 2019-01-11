#ifndef CONGRATULATION_H
#define CONGRATULATION_H

#include <QWidget>
#include <QDebug>
#include <QSettings>
#include <QTextCodec>
#include <QFile>
#include <QMouseEvent>
#include <QPushButton>
#include <QPainter>
namespace Ui {
class Congratulation;
}

class Congratulation : public QWidget
{
    Q_OBJECT

public:
    explicit Congratulation(QWidget *parent = 0);
    void getMessage(QString mes, QStringList list, int rand,QString path, QString strThr);
    void initTop();
    void initCenter();
    void initBottom();
    ~Congratulation();
    void mousePressEvent(QMouseEvent *event);
    void mouseMoveEvent(QMouseEvent *event);
    void paintEvent(QPaintEvent *event);


private slots:
    void on_pushButton_clicked();
    //void settingToCon(QStringList list);

private:
    Ui::Congratulation *ui;
    QString mes;
    QStringList list;
    int rand;
    QString path;
    QStringList splitList;
    QPoint windowPos;
    QPoint mousePos;
    QPoint dPos;
    QString strThr;
};

#endif // CONGRATULATION_H
