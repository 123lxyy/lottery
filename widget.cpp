#include "widget.h"
#include "ui_widget.h"



Widget::Widget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Widget)
{
    ui->setupUi(this);
    initCenter();
    timer =new QTimer;
    this->setWindowFlag(Qt::FramelessWindowHint);
    connect(timer, SIGNAL(timeout()), this, SLOT(doLottery()));
    autoCreateFile();
    doComBox();
}

Widget::~Widget()
{
    delete ui;
}

/*********************************  function  *****************************************/
void Widget::initTop(QPaintEvent *parent)
{
    QPixmap pix;
    pix.load(":/icon/icon/home.png");
    ui->label_2->setMinimumSize(50,50);
    ui->label_2->setMaximumSize(50,50);
    ui->label_2->setPixmap(pix);
    ui->label_2->setScaledContents(true);
    QPalette pa;
    pa.setColor(QPalette::WindowText,Qt::white);
    ui->label_3->setPalette(pa);
    QFont font("Microsoft YaHei", 13, 50, true);
    font.setPointSize(20);
    ui->label_3->setFont(font);
    ui->label_3->setText("同禾年会抽奖小程序");
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
    this->strOne = setting->getFriSetting();
    this->strTwo = setting->getSecSetting();
    this->strThr = setting->getThrSetting();
    //qDebug() << "one two" << strOne << strThr;
    QDir dir(strOne);
    if(!dir.exists())
        return ;
    dir_count = dir.count();
    stringlist.append("*.jpg");
    stringlist.append("*.png");
    files = dir.entryList(stringlist, QDir::Files|QDir::Readable, QDir::Name);
    qDebug() << "files count is:" << files.size();
    fileCopy = files;

    for(int i =0 ;i< files.size();i++)
    {
        path = strOne;
        path.append("/");
        label = new QLabel;
        label->setMinimumSize(80,80);
        label->setMaximumSize(80,80);
        label->setScaledContents(true);
        labelList.append(label);
        strAppend = path.append(files.at(i));
        //qDebug() << strAppend;
        image = new QImage;
        image->load(strAppend);
        labelList.at(i)->setPixmap(QPixmap::fromImage(*image));
        ui->gridLayout->addWidget(labelList.at(i), i/15, i%15);
        path.clear();
    }
}
void Widget::paintEvent(QPaintEvent *parent)
{
    initTop(parent);
}
void Widget::sleep(int msec)
{
    QTime dieTime = QTime::currentTime().addMSecs(msec);
    while( QTime::currentTime() < dieTime )
        QCoreApplication::processEvents(QEventLoop::AllEvents, 100);
}
void Widget::autoCreateFile()
{
    filepath = "./winDoc";
    QDir dir(filepath);
    if(!dir.exists())
        dir.mkpath(filepath);
    //QFile *fileName = new QFile;
    QDateTime current_date_time =QDateTime::currentDateTime();
    QString current_date =current_date_time.toString("yyyy_MM_dd");
    QString count = QString::number(dir.count());
    QString fileName = current_date.append("_");
    fileName.append(count);
    fileName.append(".txt");
    filepath.append("/");
    filepath.append(fileName);
    qDebug() << "filepath:" << fileName;

}
void Widget::doComBox()
{
    conBoxList = strTwo.split("；");
    //qDebug() << "conBoxList:" << conBoxList;
    for(int i = 0; i < conBoxList.size(); i++)
        ui->comboBox->insertItem(i,conBoxList.at(i));
}

/*********************************end function*****************************************/


/********************************* slots *****************************************/
void Widget::on_pushButton_4_clicked()
{
    //设置窗口
    setting = new Setting;
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
    path = this->strOne.append("/");
    con = new Congratulation();
    qDebug() << "close filepath:" << filepath;
    con->getMessage(comBoxStr,fileCopy,randNum,path,filepath);
    con->show();
    con->activateWindow();
    files.removeAt(rand);
}

void Widget::on_pushButton_7_clicked()
{
    //查看中奖名单
    ex = new Exhibitors();
    ex->getpath(filepath);
    ex->show();
    ex->activateWindow();
}

void Widget::doLottery()
{
    //抽奖
    time = QTime::currentTime();
    qsrand(time.msec()+time.second()*1000);
    rand = qrand() % files.size();
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
