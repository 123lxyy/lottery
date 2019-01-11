#ifndef SETTING_H
#define SETTING_H

#include <QWidget>
#include <QPainter>
#include <QLabel>
#include <QFileDialog>
#include <QDebug>
#include <QMouseEvent>


namespace Ui {
class Setting;
}

class Setting : public QWidget
{
    Q_OBJECT

public:
    explicit Setting(QWidget *parent = 0);
    ~Setting();
    void init();
    void paintEvent(QPaintEvent *painter);
    QString getFriSetting();
    QString getSecSetting();
    QString getThrSetting();
    void mousePressEvent(QMouseEvent *event);
    void mouseMoveEvent(QMouseEvent *event);

private slots:
    void on_pushButton_clicked();
    void on_pushButton_2_clicked();
    void on_pushButton_3_clicked();
    void on_pushButton_4_clicked();


private:
    Ui::Setting *ui;
    QFileDialog *fileDialog;
    QString strOne;
    QString strTwo;
    QString strThr;
    QPoint windowPos;
    QPoint mousePos;
    QPoint dPos;
};

#endif // SETTING_H
