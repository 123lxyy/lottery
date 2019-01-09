#include "setting.h"
#include "ui_setting.h"

Setting::Setting(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Setting)
{
    ui->setupUi(this);
    this->setWindowFlag(Qt::FramelessWindowHint);
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
    strTwo = ui->textEdit->toPlainText();
    qDebug() << strOne;
    qDebug() << strTwo;
    qDebug() << strThr;
    Widget *w = new Widget;
    this->close();

}
/******************************end slots **********************************/
