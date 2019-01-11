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
void Congratulation::getMessage(QString mes, QStringList list, int rand,QString path,QString strThr)
{
    this->mes = mes;
    this->list = list;
    this->rand = rand;
    this->path = path;
    this->strThr = strThr;
    //qDebug() << this->strThr;
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
    QImage *image = new QImage;
    image->load(path);
    ui->label_2->setScaledContents(true);
    ui->label_2->setPixmap(QPixmap::fromImage(*image));
    //截取字符串
    QString str = list.at(rand);
    splitList = str.split(".");
    ui->label_3->setText(splitList[0]);
}
void Congratulation::initBottom()
{

}
void Congratulation::mousePressEvent(QMouseEvent *event)
{
    this->windowPos = this->pos();                // 获得部件当前位置
    this->mousePos = event->globalPos();     // 获得鼠标位置
    this->dPos = mousePos - windowPos;       // 移动后部件所在的位置
}
void Congratulation::mouseMoveEvent(QMouseEvent *event)
{
     this->move(event->globalPos() - this->dPos);
}
void Congratulation::paintEvent(QPaintEvent *event)
{
    Q_UNUSED(event);
    QBrush brush;
    brush.setColor("#FFA500");
    brush.setStyle(Qt::SolidPattern);

    QPainter p(this);
    p.setPen(Qt::NoPen);
    p.setBrush(brush);
    p.drawRect(rect());

}

/********************************end function****************************************/


/******************************** slots ****************************************/
void Congratulation::on_pushButton_clicked()
{
    //将中奖人员写进文件
    qDebug() << "write file:" << strThr;
    QFile file(strThr);
    this->mes.append(":");
    this->mes.append(splitList[0]);
    this->mes.append(";");
    if(file.open(QIODevice::WriteOnly | QIODevice::Append | QIODevice::Text)){
        file.write(this->mes.toUtf8());
    }
    file.close();
    this->close();
}
/********************************end slots****************************************/


