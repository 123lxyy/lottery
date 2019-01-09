#include "congratulation.h"
#include "ui_congratulation.h"

Congratulation::Congratulation(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Congratulation)
{
    ui->setupUi(this);
    this->setWindowFlag(Qt::FramelessWindowHint);
}

Congratulation::~Congratulation()
{
    delete ui;
}

/********************************  function  ****************************************/
void Congratulation::getMessage(QString mes, QStringList list, int rand,QString path)
{
    this->mes = mes;
    this->list = list;
    this->rand = rand;
    this->path = path;
    //qDebug() << this->mes << "  " << this->list << "  " << this->rand;
    initTop();
    initCenter();
}
void Congratulation::initTop()
{
    QString str = "恭喜您，获得";
    str.append(this->mes);
    ui->label->setAlignment(Qt::AlignHCenter);
    ui->label->setText(str);
}
void Congratulation::initCenter()
{
    this->path.append(list.at(rand));
    //qDebug() << "get file path:" << this->path;
    QImage *image = new QImage;
    image->load(this->path);
    ui->label_2->setScaledContents(true);
    ui->label_2->setPixmap(QPixmap::fromImage(*image));
    //截取字符串
    QString str = list.at(rand);
    QStringList list = str.split(".");
    ui->label_3->setText(list[0]);
}
void Congratulation::initBottom()
{

}
/********************************end function****************************************/


/******************************** slots ****************************************/
void Congratulation::on_pushButton_clicked()
{

}
/********************************end slots****************************************/
