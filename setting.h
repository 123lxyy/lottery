#ifndef SETTING_H
#define SETTING_H

#include <QWidget>
#include <QPainter>
#include <QLabel>
#include <QFileDialog>
#include <QDebug>
#include "widget.h"

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

private slots:
    void on_pushButton_clicked();
    void on_pushButton_2_clicked();
    void on_pushButton_3_clicked();

private:
    Ui::Setting *ui;
    QFileDialog *fileDialog;
    QString strOne;
    QString strTwo;
    QString strThr;
};

#endif // SETTING_H
