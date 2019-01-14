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
    bt2IsDown = false;

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
    ui->label_2->setMinimumSize(30,30);
    ui->label_2->setMaximumSize(30,30);
    ui->label_2->setPixmap(pix);
    ui->label_2->setScaledContents(true);
    QPalette pa;
    pa.setColor(QPalette::WindowText,Qt::white);
    ui->label_3->setPalette(pa);
    QFont font("Microsoft YaHei", 13, 50, false);
    font.setPointSize(15);
    ui->label_3->setFont(font);
    ui->label_3->setText("同禾年会抽奖小程序");
    //画按钮
    QIcon icon;
    icon.addFile(":/icon/icon/close.png");
    ui->pushButton->setIcon(icon);
    ui->pushButton->setStyleSheet("QPushButton{background: transparent;}");
    icon.addFile(":/icon/icon/max.png");
    ui->pushButton_2->setIcon(icon);
    ui->pushButton_2->setStyleSheet("QPushButton{background: transparent;}");
    icon.addFile(":/icon/icon/min.png");
    ui->pushButton_3->setIcon(icon);
    ui->pushButton_3->setStyleSheet("QPushButton{background: transparent;}");
    icon.addFile(":/icon/icon/setting.png");
    ui->pushButton_4->setIcon(icon);
    ui->pushButton_4->setStyleSheet("QPushButton{background: transparent;}");

}
void Widget::initCenter()
{
    Setting *setting = new Setting;
    this->strOne = setting->getFriSetting();
    this->strTwo = setting->getSecSetting();
    this->strThr = setting->getThrSetting();
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
    QDateTime current_date_time =QDateTime::currentDateTime();
    QString current_date =current_date_time.toString("yyyy_MM_dd");
    QString count = QString::number(dir.count());
    QString fileName = current_date.append("_");
    fileName.append(count);
    fileName.append(".txt");
    filepath.append("/");
    filepath.append(fileName);
}
void Widget::doComBox()
{
    conBoxList = strTwo.split("；");
    for(int i = 0; i < conBoxList.size(); i++)
        ui->comboBox->insertItem(i,conBoxList.at(i));
}

/*********************************end function*****************************************/


/********************************* slots *****************************************/
void Widget::on_pushButton_4_clicked()
{
    //设置窗口
    setting = new Setting;
    connect(setting, SIGNAL(changeComBox()), this, SLOT(changeComBox()));
    connect(setting, SIGNAL(btIsDown(bool)), this, SLOT(getShowPath(bool)));
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
    //1、得到抽奖人数
    peopleNum = ui->spinBox->value();
    qDebug() << "peopleNum: " << peopleNum;
    timer->start(10);
    for(int j = 0; j < randIntCopy.size(); j++)
        labelList.at(randIntCopy.at(j))->setStyleSheet("null;");
}

void Widget::on_pushButton_6_clicked()
{
    //停止
    timer->stop();
    QString comBoxStr = ui->comboBox->currentText();
    path = this->strOne.append("/");
    con = new Congratulation();
    con->getMessage(comBoxStr,fileCopy,randNum,path,filepath);
    con->show();
    con->activateWindow();
    files.removeAt(rand);
}

void Widget::on_pushButton_7_clicked()
{
    //查看中奖名单
    ex = new Exhibitors();
    ex->show();
    ex->activateWindow();
    if(bt2IsDown){
        strThr = setting->getThrSetting();
        ex->getpath(strThr);
        bt2IsDown = false;
    }else{
        ex->getpath(filepath);
    }
}
void Widget::doLottery()
{
    //抽奖
    time = QTime::currentTime();
    qsrand(time.msec()+time.second()*1000);
    for(int j = 0; j< randInt.size(); j++)
    {
        labelList.at(randInt.at(j))->setStyleSheet("null;");
    }
    randInt.clear();
    for(int i = 0; i < peopleNum; i++)
    {
        rand = qrand() % files.size();
        if(randInt.contains(rand)){
            i--;
            continue;
        }
        QString name = files.at(rand);
        randNum = fileCopy.indexOf(name);
        labelList.at(randNum)->setStyleSheet("border:15px solid red;");
        randInt.append(randNum);
        randIntCopy = randInt;
    }
    qDebug() << "randInt:" << randInt;



}
void Widget::changeComBox()
{
    strTwo = setting->getSecSetting();
    conBoxList = strTwo.split("；");
    ui->comboBox->clear();
    for(int j = 0; j < conBoxList.size(); j++)
        ui->comboBox->insertItem(j, conBoxList.at(j));
}
void Widget::getShowPath(bool bt2IsDown)
{
   this->bt2IsDown = bt2IsDown;
}

/*********************************end slots *****************************************/
