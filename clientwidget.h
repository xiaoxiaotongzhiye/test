#ifndef CLIENTWIDGET_H
#define CLIENTWIDGET_H

#include <QMainWindow>
#include <QTcpSocket>
#include <QDebug>
#include "regw.h"
#include <QMessageBox>
#include "userw.h"
#include "user.h"

namespace Ui {
class ClientWidget;
}

class ClientWidget : public QMainWindow
{
    Q_OBJECT

public:
    explicit ClientWidget(QWidget *parent = nullptr);
    ~ClientWidget();
    QTcpSocket *socket;

private slots:
    void on_regBtn_clicked();

    void on_logBtn_clicked();

    void receiveMessage();

private:
    Ui::ClientWidget *ui;

signals:
    void sendUser(user *);
};

#endif // CLIENTWIDGET_H
