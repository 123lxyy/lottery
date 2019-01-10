#ifndef EXHIBITORS_H
#define EXHIBITORS_H

#include <QWidget>
#include <QFile>
#include <QDebug>
#include <QFont>
#include <QLabel>
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
};

#endif // EXHIBITORS_H
