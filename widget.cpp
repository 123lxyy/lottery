#include "widget.h"
#include "ui_widget.h"
#include "setting.h"
#include "congratulation.h"
#include "exhibitors.h"

Widget::Widget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Widget)
{
    ui->setupUi(this);
    //code = QTextCodec::codecForName("utf-8");
    initCenter();
    timer =new QTimer;
    this->setWindowFlag(Qt::FramelessWindowHint);
    connect(timer, SIGNAL(timeout()), this, SLOT(doLottery()));

}

Widget::~Widget()
{
    delete ui;
}

/*********************************  function  *****************************************/
void Widget::initTop()
{
    QPainter painter(this);
    QBrush brush;
    brush.setColor("#B22222");
    brush.setStyle(Qt::SolidPattern);
    painter.setBrush(brush);
    painter.setPen(Qt::white);
    painter.drawRect(0, 0, this->width(),40);

    //绘画图片
    QPixmap pix;
    pix.load(":/icon/icon/home.png");
    painter.drawPixmap(8, 5, 40, 40,pix);

    //画字
    QFont font("Microsoft YaHei", 13, 50, true);
    painter.setFont(font);
    painter.drawText(60, 25, "同禾年会抽奖小程序");

    //画按钮
    QIcon icon;
    icon.addFile(":/icon/icon/close.png");
    ui->pushButton->setIcon(icon);
    icon.addFile(":/icon/icon/max.png");
    ui->pushButton_2->setIcon(icon);
    icon.addFile(":/icon/icon/min.png");
    ui->pushButton_3->setIcon(icon);
    icon.addFile(":/icon/icon/setting.png");
    ui->pushButton_4->setIcon(icon);
}
void Widget::initCenter()
{
    Setting *setting = new Setting;
    QString strOne;
    strOne = setting->getFriSetting();
    if(strOne.isEmpty()){
        QDir dir("D:/qt project/lottery/image");
        if(!dir.exists())
            return ;
        dir_count = dir.count();

        stringlist.append("*.jpg");
        stringlist.append("*.png");
        files = dir.entryList(stringlist, QDir::Files|QDir::Readable, QDir::Name);
        qDebug() << "files count is:" << files.size();
        fileCopy = files;
//        qDebug()<<Q_FUNC_INFO<<__LINE__<<files.size();
        for(int i =0 ;i< files.size();i++)
        {
            label = new QLabel;
            label->setMinimumSize(70,70);
            label->setMaximumSize(70,70);
            label->setScaledContents(true);
            labelList.append(label);
            path = "D:/qt project/lottery/image/";
            strAppend = path.append(files.at(i));
            image = new QImage;
            image->load(strAppend);
            labelList.at(i)->setPixmap(QPixmap::fromImage(*image));
            ui->gridLayout->addWidget(labelList.at(i), i/15, i%15);
        }
        qDebug() << "enter";

    }else{
        QDir dir(strOne);
        if(!dir.exists())
            return ;
    }

}
void Widget::paintEvent(QPaintEvent *parent)
{
    initTop();
}
void Widget::sleep(int msec)
{
    QTime dieTime = QTime::currentTime().addMSecs(msec);
       while( QTime::currentTime() < dieTime )
           QCoreApplication::processEvents(QEventLoop::AllEvents, 100);
}

/*********************************end function*****************************************/


/********************************* slots *****************************************/
void Widget::on_pushButton_4_clicked()
{
    //设置窗口
    Setting *setting = new Setting;
    setting->show();
    setting->activateWindow();
}

void Widget::on_pushButton_3_clicked()
{
    this->setWindowState(Qt::WindowMinimized);
}

void Widget::on_pushButton_2_clicked()
{
    this->setWindowState(Qt::WindowFullScreen);
}

void Widget::on_pushButton_clicked()
{
    this->close();
}

void Widget::on_pushButton_5_clicked()
{
    //开始
    timer->start(20);
}

void Widget::on_pushButton_6_clicked()
{
    //停止 
    timer->stop();
    flag = true;
    QString comBoxStr = ui->comboBox->currentText();
    //qDebug() << comBoxStr;
    path = "D:/qt project/lottery/image/";
    Congratulation *con = new Congratulation();
    qDebug() << "files num :" << files.count();
    con->getMessage(comBoxStr,fileCopy,randNum,path);
    con->show();
    con->activateWindow();
    files.removeAt(rand);
}

void Widget::on_pushButton_7_clicked()
{
    //查看中奖名单
    Exhibitors *ex = new Exhibitors;
    ex->show();
    ex->activateWindow();
}

void Widget::doLottery()
{
    //抽奖
    time = QTime::currentTime();
    qsrand(time.msec()+time.second()*1000);
    rand = qrand() % files.size();
    //qDebug() << "rand num:" << rand;
    QString name = files.at(rand);
    randNum = fileCopy.indexOf(name);
    qDebug() << "randNum :" << randNum;
    flag = false;
    labelList.at(randNum)->setStyleSheet("border:15px solid red;");
    sleep(10);
    if(!flag){
       labelList.at(randNum)->setStyleSheet("null;");
       flag = true;
    }
}
/*********************************end slots *****************************************/
