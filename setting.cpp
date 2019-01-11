#include "setting.h"
#include "ui_setting.h"

Setting::Setting(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Setting)
{
    ui->setupUi(this);
    this->setWindowFlag(Qt::FramelessWindowHint);
    QIcon icon;
    icon.addFile(":/icon/icon/close.png");
    ui->pushButton_4->setIcon(icon);
    ui->lineEdit_2->setText("./winDoc/2019_01_11_2.txt");
    strThr = ui->lineEdit_2->text();
    ui->lineEdit->setText("./image");
    strOne = ui->lineEdit->text();
    ui->textEdit->setText("一等奖；二等奖；三等奖；幸运奖");
    strTwo = ui->textEdit->toPlainText();
}

Setting::~Setting()
{
    delete ui;
}
void Setting::paintEvent(QPaintEvent *p)
{
    QPainter painter(this);
    QFont font("Microsoft YaHei", 13, 50, true);
    painter.setFont(font);
    painter.drawText(this->width()/2-10, 25, "设置");

    //画线
    QPen pen;
    pen.setColor(Qt::black);
    pen.setWidth(2);
    painter.drawLine(0, 40, this->width(), 40);

    //给按钮加图片
    QIcon icon;
    icon.addFile(":/icon/icon/file.png");
    ui->pushButton->setIcon(icon);
    icon.addFile(":/icon/icon/file.png");
    ui->pushButton_2->setIcon(icon);

}

/******************************  function **********************************/
QString Setting::getFriSetting()
{
    return strOne;
}
QString Setting::getSecSetting()
{
    return strTwo;
}
QString Setting::getThrSetting()
{
    return strThr;
}

void Setting::mousePressEvent(QMouseEvent *event)
{
    this->windowPos = this->pos();                // 获得部件当前位置
    this->mousePos = event->globalPos();     // 获得鼠标位置
    this->dPos = mousePos - windowPos;       // 移动后部件所在的位置
}
void Setting::mouseMoveEvent(QMouseEvent *event)
{
     this->move(event->globalPos() - this->dPos);
}
/******************************end function**********************************/


/******************************  slots **********************************/
void Setting::on_pushButton_clicked()
{
    fileDialog = new QFileDialog(this);
    fileDialog->setFileMode(QFileDialog::AnyFile);
    strOne =fileDialog->getExistingDirectory();
    ui->lineEdit->setText(strOne);
}

void Setting::on_pushButton_2_clicked()
{
    fileDialog = new QFileDialog(this);
    fileDialog->setFileMode(QFileDialog::AnyFile);
    strThr = fileDialog->getOpenFileName();
    ui->lineEdit_2->setText(strThr);
}

void Setting::on_pushButton_3_clicked()
{
    //传递设置里面的参数
    strTwo = ui->textEdit->toPlainText();
    this->close();
}
void Setting::on_pushButton_4_clicked()
{
    //关闭设置界面
    this->close();
}
/******************************end slots **********************************/


