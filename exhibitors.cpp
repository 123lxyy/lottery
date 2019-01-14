#include "exhibitors.h"
#include "ui_exhibitors.h"

Exhibitors::Exhibitors(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Exhibitors)
{
    ui->setupUi(this);
    ui->label_3->setAlignment(Qt::AlignCenter);
    ui->label_5->setAlignment(Qt::AlignCenter);
    ui->label_6->setAlignment(Qt::AlignCenter);
    this->setWindowFlag(Qt::FramelessWindowHint);
    num_one = 0;
    num_two = 0;
    num_three = 0;
    QIcon icon;
    icon.addFile(":/icon/icon/close.png");
    ui->pushButton->setIcon(icon);
    ui->pushButton->setStyleSheet("QPushButton{background: transparent;}");
    font = new QFont();
    font->setFamily("黑体");
    font->setPointSize(10);
    //设置界面为模态框
    this->setWindowModality(Qt::ApplicationModal);
}

Exhibitors::~Exhibitors()
{
    delete ui;
}

void Exhibitors::readFile()
{
    QFile file(path);
    if(file.open(QIODevice::ReadOnly)){
       QByteArray array;
       while(file.atEnd() == false){
           array += file.readLine();
       }
       parse(array.data());
    }
    file.close();
}

void Exhibitors::parse(QString str)
{
    list = str.split(";");
    qDebug() << list;
    for(int i = 0; i < list.size(); i++)
    {
        QString s = list.at(i);
        typeList = s.split(":");
        if(s.contains("一等奖")){
            ui->label_3->setText(typeList[1]);
        }else if(s.contains("二等奖")){
            if(num_one == 0){
                ui->label_5->setText(typeList[1]);
                num_one++;
            }else if(num_one == 1)
                ui->label_6->setText(typeList[1]);
        }else if(s.contains("三等奖")){
            sanLabel = new QLabel;
            sanLabel->setFont(*font);
            sanLabel->setScaledContents(true);
            sanLabel->setText(typeList[1]);
            sanList.append(sanLabel);
            ui->gridLayout->addWidget(sanList.at(num_two), 1, num_two%6);
            num_two++;

        }else if(s.contains("幸运奖")){
            luckyLabel = new QLabel;
            luckyLabel->setFont(*font);
            luckyLabel->setScaledContents(true);
            luckyLabel->setText(typeList[1]);
            luckyList.append(luckyLabel);
            ui->gridLayout_2->addWidget(luckyList.at(num_three), num_three/6, num_three%6);
            num_three++;
        }
    }
}
void Exhibitors::mousePressEvent(QMouseEvent *event)
{
    this->windowPos = this->pos();                // 获得部件当前位置
    this->mousePos = event->globalPos();     // 获得鼠标位置
    this->dPos = mousePos - windowPos;       // 移动后部件所在的位置
}
void Exhibitors::mouseMoveEvent(QMouseEvent *event)
{
     this->move(event->globalPos() - this->dPos);
}
void Exhibitors::getpath(QString path)
{
    this->path = path;
    qDebug() << this->path;
    readFile();
}
void Exhibitors::paintEvent(QPaintEvent *event)
{
    QPainter p(this);
    p.drawPixmap(0,0,this->width(),this->height(),QPixmap(":/icon/icon/bg.jpg"));
}

void Exhibitors::on_pushButton_clicked()
{
    this->close();
}
