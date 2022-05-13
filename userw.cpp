#include "userw.h"
#include "ui_userw.h"

userW::userW(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::userW)
{
    ui->setupUi(this);
}

userW::~userW()
{
    delete ui;
}

void userW::setSocket(QTcpSocket *socket)
{
    this->socket = socket;
}

//功能同注册按钮，将窗口中的信息连接为字符串交给socket传输
void userW::on_updateBtn_clicked()
{
    QString sex=ui->rbtn1->isChecked()?"0":"1";
    QString temp="UPD:" + ui->nickName->text()+
               ":"+ ui->password->text() +
               ":"+ ui->phoneNum->text() +
               ":"+ ui->userName->text() +
               ":"+ ui->job->text()      +
               ":"+ sex +
               ":"+ ui->birth->text();
    socket->write(temp.toLocal8Bit());
    socket->flush();
}

void userW::on_canBtn_clicked()
{
    ClientWidget *cc = new ClientWidget;
    cc->show();
    this->hide();
}

//接受登录窗口传递过来用户信息的槽函数
void userW::getUser(user *uu)
{
        QDate birthD = QDate::fromString(uu->getBirthDay(),"yyyy-MM-dd");
        int sex= uu->getSex();
        ui->nickName->setText(uu->getNickName());
        ui->nickName->setEnabled(false);
        ui->password->setText(uu->getPassword());
        ui->phoneNum->setText(uu->getPhoneNum());
        ui->userName->setText(uu->getUserName());
        ui->job->setText(uu->getJob());
        ui->birth->setDate(birthD);
        if(sex==0){
            ui->rbtn1->setChecked(true);
            ui->rbtn2->setChecked(false);
        }
        else{
            ui->rbtn1->setChecked(false);
            ui->rbtn2->setChecked(true);
        }
}

