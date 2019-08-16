#include "mainwidget.h"
#include "ui_mainwidget.h"

MainWidget::MainWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::MainWidget)
{
    ui->setupUi(this);
}

MainWidget::~MainWidget()
{
    delete ui;
}

void MainWidget::on_radioButtonServer_clicked()
{
    ServerState = true;
}

void MainWidget::on_radioButtonClient_clicked()
{
    ServerState = false;
}

void MainWidget::newuser()
{
    if(server_status==1){
        qDebug() << QString::fromUtf8("У нас новое соединение!");
        ui->textBrowserReceived->append(QString::fromUtf8("У нас новое соединение!"));
        QTcpSocket* clientSocket=tcpServer->nextPendingConnection();
        int idusersocs=clientSocket->socketDescriptor();
        qDebug() << idusersocs;
        SClients[idusersocs]=clientSocket;
        connect(SClients[idusersocs],SIGNAL(readyRead()),this, SLOT(slotReadClient()));
    }
}

void MainWidget::slotReadClient()
{
    QTcpSocket* clientSocket = qobject_cast<QTcpSocket *>(sender());
    int idusersocs=clientSocket->socketDescriptor();
    QTextStream os(clientSocket);
    os.setAutoDetectUnicode(true);
   /* os << "HTTP/1.0 200 Ok\r\n"
          "Content-Type: text/html; charset=\"utf-8\"\r\n"
          "\r\n"
          "<h1>Nothing to see here</h1>\n"
       << QDateTime::currentDateTime().toString() << "\n";
       */
    ui->textBrowserReceived->append("ReadClient:"+clientSocket->readAll()+"");
    // Если нужно закрыть сокет
    //clientSocket->close();
    //SClients.remove(idusersocs);
}

void MainWidget::on_pushButtonStart_clicked()
{
    if(ServerState)
    {
        tcpServer = new QTcpServer(this);
        connect(tcpServer, SIGNAL(newConnection()), this, SLOT(newuser()));
        if (!tcpServer->listen(QHostAddress::Any, 33333) && server_status==0) {
            qDebug() <<  QObject::tr("Unable to start the server: %1.").arg(tcpServer->errorString());
            ui->textBrowserReceived->append(tcpServer->errorString());
        }
        else
        {
            server_status=1;
            qDebug() << tcpServer->isListening() << "TCPSocket listen on port";
            ui->textBrowserReceived->append(QString::fromUtf8("Сервер запущен!"));
            qDebug() << QString::fromUtf8("Сервер запущен!");
        }
    }
    else
    {
        _pSocket = new QTcpSocket( this ); // <-- needs to be a member variable: QTcpSocket * _pSocket;
        connect( _pSocket, SIGNAL(readyRead()), SLOT(readTcpData()));
        _pSocket->connectToHost(ui->lineEditIP->text(), 33333);
    }
}

void MainWidget::on_pushButtonStop_clicked()
{
    if(ServerState)
    {
        if(server_status==1){
            foreach(int i,SClients.keys()){
                QTextStream os(SClients[i]);
                os.setAutoDetectUnicode(true);
                os << QDateTime::currentDateTime().toString() << "\n";
                SClients[i]->close();
                SClients.remove(i);
            }
            tcpServer->close();
            ui->textBrowserReceived->append(QString::fromUtf8("Сервер остановлен!"));
            qDebug() << QString::fromUtf8("Сервер остановлен!");
            server_status=0;
        }
    }
}


void MainWidget::readTcpData()
{
    //QByteArray data = _pSocket->readAll();
}


void MainWidget::on_pushButtonSend_clicked()
{
    if(ServerState)
    {

    }
    else
    {
        QByteArray data = ui->lineEditText->text().toLocal8Bit();
        //if( _pSocket->waitForConnected() )
       // {
            _pSocket->write( data );
      //  }
    }
}
