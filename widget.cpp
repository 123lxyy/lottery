#include "widget.h"
#include "ui_widget.h"
#include "setting.h"
#include "congratulation.h"

Widget::Widget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Widget)
{
    ui->setupUi(this);
    //code = QTextCodec::codecForName("utf-8");
    initCenter();
    timer =new QTimer;
    this->setWindowFlag(Qt::FramelessWindowHint);
    this->setMinimumSize(740,480);
    this->setMaximumSize(740,480);
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
        qDebug() << files;
        for(int i =0 ;i< files.size();i++)
        {
            label[i] = new QLabel;
            label[i]->setMinimumSize(50,50);
            label[i]->setMaximumSize(50,50);
            label[i]->setScaledContents(true);
            path = "D:/qt project/lottery/image/";
            strAppend = path.append(files.at(i));
            qDebug() << strAppend;
            image = new QImage;
            image->load(strAppend);
            label[i]->setPixmap(QPixmap::fromImage(*image));
            ui->gridLayout->addWidget(label[i], i/10, i%10);
        }

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
    qDebug() << "enter!!";
    //设置窗口
    Setting *setting = new Setting;
    this->showNormal();
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
    timer->start(50);
}

void Widget::on_pushButton_6_clicked()
{
    //停止
    flag = true;
    timer->stop();
    QString comBoxStr = ui->comboBox->currentText();
    //qDebug() << comBoxStr;
    path = "D:/qt project/lottery/image/";
    Congratulation *con = new Congratulation();
    con->getMessage(comBoxStr,files,rand,path);
    con->show();
    con->activateWindow();
}

void Widget::on_pushButton_7_clicked()
{
    //查看中奖名单
}

void Widget::doLottery()
{
    //抽奖
    time = QTime::currentTime();
    qsrand(time.msec()+time.second()*1000);
    rand = qrand() % files.size();
    //qDebug() << "rand num:" << rand;

    flag = false;
    label[rand]->setStyleSheet("border:2px solid red;");
    sleep(20);
    if(!flag){
       label[rand]->setStyleSheet("null;");
       flag = true;
    }
}
/*********************************end slots *****************************************/
