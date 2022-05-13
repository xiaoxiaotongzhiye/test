#ifndef REGW_H
#define REGW_H

#include <QMainWindow>
#include "clientwidget.h"
#include <QTcpSocket>
#include <QByteArray>
#include <QString>

namespace Ui {
class regW;
}

class regW : public QMainWindow
{
    Q_OBJECT

public:
    explicit regW(QMainWindow *parent = nullptr);
    ~regW();
    void setSocket(QTcpSocket *);

private slots:
    void on_logBtn_clicked();

    void on_canBtn_clicked();

private:
    Ui::regW *ui;
    QTcpSocket *socket;
};

#endif // REGW_H
