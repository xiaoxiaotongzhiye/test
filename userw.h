#ifndef USERW_H
#define USERW_H

#include <QMainWindow>
#include "clientwidget.h"
#include <QTcpSocket>
#include <QByteArray>
#include <QString>
#include "user.h"

namespace Ui {
class userW;
}

class userW : public QMainWindow
{
    Q_OBJECT

public:
    explicit userW(QWidget *parent = nullptr);
    ~userW();
    void setSocket(QTcpSocket *);

private slots:
    void on_updateBtn_clicked();

    void on_canBtn_clicked();

private:
    Ui::userW *ui;
    QTcpSocket *socket;

private slots:
    void getUser(user *);
};

#endif // USERW_H
