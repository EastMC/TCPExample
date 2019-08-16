#ifndef MAINWIDGET_H
#define MAINWIDGET_H

#include <QWidget>
#include <qnetwork.h>
#include <QTcpSocket>
#include <QTcpServer>
#include <QObject>
#include <QByteArray>
#include <QDebug>
#include <QDateTime>

namespace Ui {
class MainWidget;
}

class MainWidget : public QWidget
{
    Q_OBJECT

public:
    explicit MainWidget(QWidget *parent = nullptr);
    ~MainWidget();

private slots:
    void on_radioButtonServer_clicked();
    void on_radioButtonClient_clicked();
    void newuser();
    void slotReadClient();
    void on_pushButtonStart_clicked();
    void on_pushButtonStop_clicked();
    void on_pushButtonSend_clicked();

    void readTcpData();
private:
    Ui::MainWidget *ui;
    bool ServerState{true};
    QTcpServer *tcpServer;
    int server_status{0};
    QMap<int,QTcpSocket *> SClients;
    QTcpSocket *_pSocket;
};

#endif // MAINWIDGET_H
