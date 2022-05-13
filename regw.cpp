#include "regw.h"
#include "ui_regw.h"

regW::regW(QMainWindow *parent) :
    QMainWindow(parent),
    ui(new Ui::regW)
{
    ui->setupUi(this);
}


regW::~regW()
{
    delete ui;
}

void regW::setSocket(QTcpSocket *socket)
{
    this->socket = socket;
}

//注册按钮，将注册信息连接为字符串交给socket转发给服务器
void regW::on_logBtn_clicked()
{
    QString sex=ui->rbtn1->isChecked()?"0":"1";
    QString temp="REG:" + ui->nickName->text()+
            ":"+ ui->password->text() +
            ":"+ ui->phoneNum->text() +
            ":"+ ui->userName->text() +
            ":"+ ui->job->text()      +
            ":"+ sex +
            ":"+ ui->birth->text();
    socket->write(temp.toLocal8Bit());
    socket->flush();

    ClientWidget *cc = new ClientWidget;
    cc->show();
    this->hide();
}

void regW::on_canBtn_clicked()
{
    ClientWidget *cc = new ClientWidget;
    cc->show();
    this->hide();
}
