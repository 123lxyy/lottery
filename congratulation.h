#ifndef CONGRATULATION_H
#define CONGRATULATION_H

#include <QWidget>
#include <QDebug>
#include <QSettings>
#include <QTextCodec>
#include <QFile>
namespace Ui {
class Congratulation;
}

class Congratulation : public QWidget
{
    Q_OBJECT

public:
    explicit Congratulation(QWidget *parent = 0);
    void getMessage(QString mes, QStringList list, int rand,QString path);
    void initTop();
    void initCenter();
    void initBottom();
    ~Congratulation();

private slots:
    void on_pushButton_clicked();

private:
    Ui::Congratulation *ui;
    QString mes;
    QStringList list;
    int rand;
    QString path;
    QStringList splitList;

};

#endif // CONGRATULATION_H
