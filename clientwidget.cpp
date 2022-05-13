#include "clientwidget.h"
#include "ui_clientwidget.h"

ClientWidget::ClientWidget(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::ClientWidget)
{
    ui->setupUi(this);
    socket = new QTcpSocket(this);

    //连接TCP端口
    socket->connectToHost("127.0.0.1",1234);

    //连接从服务器收到的信号
    connect(socket,SIGNAL(readyRead()),this,SLOT(receiveMessage()));

}

ClientWidget::~ClientWidget()
{
    delete ui;
}

void ClientWidget::on_regBtn_clicked()
{
    regW *rr = new regW;
    //传递socket
    rr->setSocket(socket);
    rr->show();
    this->hide();
}

//用socket将登录信息传输给服务器验证
void ClientWidget::on_logBtn_clicked()
{
    QString temp="LOG:"+ui->nickNameLine->text()+":"+ui->passwordLine->text();
    socket->write(temp.toLocal8Bit());
    socket->flush();
}


//接受服务器反馈信息的槽函数
//接收字符串以LOG、REG、UPD开头分别代表登录、注册、修改的服务器反馈信息，函数中作出判断并分别处理
void ClientWidget::receiveMessage()
{
    QByteArray arr  = socket->readAll();
    QString str = QString::fromLocal8Bit(arr.data());
    QStringList strList=str.split(":");
    if(strList.value(0)=="LOG"){
        //登录成功则转到用户界面将用户信息显示
        if(strList.value(1)=="succeed"){
            QMessageBox::information(this,"inform",QString::fromLocal8Bit("登录成功！"));
            userW *mm=new userW;
            user *uu=new user;
            connect(this,SIGNAL(sendUser(user *)),mm,SLOT(getUser(user *)));
            uu->setNickName(strList.value(2));
            uu->setPassword(strList.value(3));
            uu->setPhoneNum(strList.value(4));
            uu->setUserName(strList.value(5));
            uu->setJob(strList.value(6));
            uu->setSex(strList.value(7).toUInt());
            uu->setBirthDay(strList.value(8));
            mm->setSocket(socket);
            emit sendUser(uu);
            mm->show();
            this->close();
        }
        else{
            QMessageBox::information(this,"inform",QString::fromLocal8Bit("用户名或密码错误！"));
        }
    }
    else if(strList.value(0)=="REG"){
        if(strList.value(1)=="succeed"){
            QMessageBox::information(this,"inform",QString::fromLocal8Bit("注册成功！"));
        }
        else{
            QMessageBox::information(this,"inform",QString::fromLocal8Bit("也不知道哪错了"));
        }
    }
    else if(strList.value(0)=="UPD"){
        if(strList.value(1)=="succeed"){
            QMessageBox::information(this,"inform",QString::fromLocal8Bit("修改成功！"));
        }
        else{
            QMessageBox::information(this,"inform",QString::fromLocal8Bit("有点问题"));
        }
    }
}
