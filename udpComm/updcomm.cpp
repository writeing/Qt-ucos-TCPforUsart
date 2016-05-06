#include "updcomm.h"
#include "ui_updcomm.h"



updComm::updComm(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::updComm)
{
    ui->setupUi(this);
    //初始化radio按钮按下之后的数据模式
    revModel = 1;
    sendModel = 1;
    //初始化rev Radio的按钮
    getModelrev.addButton(ui->revText,1);
    getModelrev.addButton(ui->revHex,2);
    //初始化send Radio的按钮
    getModelsend.addButton(ui->sendText,1);
    getModelsend.addButton(ui->sendHEX,2);

    //初始化发送接收的数量
    sendNum = 0;
    revNum = 0;
    QString num;

    ui->sendnum->setText(num.arg(sendNum));
    ui->revnum->setText(num.arg(revNum));
}

updComm::~updComm()
{
    delete ui;
}


void updComm::showInfo(QString msg)
{
    QMessageBox info;
    info.setText(msg);
    info.setStandardButtons(QMessageBox::Ok|QMessageBox::Cancel);
    info.setDefaultButton(QMessageBox::Ok);
    info.exec();
}
//4个radioButton
void updComm::on_revText_clicked()
{
    revModel = getModelrev.checkedId();
}

void updComm::on_sendHEX_clicked()
{
    sendModel = getModelsend.checkedId();
}

void updComm::on_revHex_clicked()
{
    revModel = getModelrev.checkedId();
}

void updComm::on_sendText_clicked()
{
    sendModel = getModelsend.checkedId();
}


//保存输入框数据
void updComm::on_pushButton_clicked()
{
    QFileDialog revsave;
    QString filename = revsave.getSaveFileName(this,tr("save rev data"),QDir::currentPath(),tr("Text Files (*.txt)"));
    QFile revfile(filename);
    if (!revfile.open(QIODevice::WriteOnly | QIODevice::Text))
          return;
    QString text = ui->tedRev->toPlainText();
    QTextStream out(&revfile);
    out<<text;
    revfile.close();
}
//保存输出框数据
void updComm::on_pushButton_4_clicked()
{
    QFileDialog sendsave;
    QString filename = sendsave.getSaveFileName(this,tr("save send data"),QDir::currentPath(),tr("Text Files (*.txt)"));
    QFile sendfile(filename);
    if (!sendfile.open(QIODevice::WriteOnly | QIODevice::Text))
          return;
    QString text = ui->tedRev->toPlainText();
    QTextStream out(&sendfile);
    out<<text;
    sendfile.close();
}
//发送文件
void updComm::on_pushButton_6_clicked()
{
    QFileDialog sendsave;
    QString filename = sendsave.getOpenFileName(this,tr("save send data"),QDir::currentPath());
    QFile readfile(filename);
    if (!readfile.open(QIODevice::ReadOnly | QIODevice::Text))
          return;
    QTextStream in(&readfile);
    while (!in.atEnd()) {
        QString line = in.readLine();
        ui->tedSend->append(line);
    }
    readfile.close();
}
//清空输入框按钮
void updComm::on_pushButton_3_clicked()
{
    ui->tedSend->clear();
}
//清空输出框按钮
void updComm::on_pushButton_2_clicked()
{
    ui->tedRev->clear();
}



void updComm::on_Btnconnet_clicked()
{
    if(ui->Btnconnet->text() == "连接")
    {
        ui->Btnconnet->setText(tr("关闭"));
        initTcp();
    }
    else
    {
        ui->Btnconnet->setText(tr("连接"));
//        udpSocket->close();
    }
}
void updComm::initTcp()
{    
    tcpServer = new QTcpServer(this);
    tcpServer->listen(QHostAddress::AnyIPv4,8888);
//    udpSocket = new QUdpSocket(this);
//    udpSocket->bind(8888);
    connect(tcpServer,SIGNAL(newConnection()),this,SLOT(readPendingDatagrams()));
}
void updComm::readPendingDatagrams()
{    
    showInfo("wxc");
    tcpServer->close();
//    QString fortunes="wxc";
//    QByteArray block;
//    QDataStream out(&block, QIODevice::WriteOnly);
//    out.setVersion(QDataStream::Qt_5_0);
//    out << (quint16)0;
//    out << fortunes.at(qrand() % fortunes.size());
//    out.device()->seek(0);
//    out << (quint16)(block.size() - sizeof(quint16));

//    // nextPendingConnection()可以返回下一个挂起的连接作为一个连接的QLocalSocket对象。
//    QLocalSocket *clientConnection = new QLocalSocket(this);
//    clientConnection = tcpServer->nextPendingConnection();
//    connect(clientConnection, SIGNAL(disconnected()),
//            clientConnection, SLOT(deleteLater()));

//    clientConnection->write(block);
//    clientConnection->flush();
//    clientConnection->disconnectFromServer();
//    tcpServer->hasPendingConnections();
//    tcpServer->
//    while (tcpServer->hasPendingDatagrams()) {
//            QByteArray datagram;
//            datagram.resize(tcpServer->);
//            QHostAddress sender;
//            quint16 senderPort;
//            tcpServer->readDatagram(datagram.data(), datagram.size(),&sender,&senderPort);

//            QString DataAsString = QTextCodec::codecForMib(106)->toUnicode(datagram);
//            ui->tedRev->append(DataAsString);
//        }
}
//发送按钮
void updComm::on_pushButton_5_clicked()
{

//    QByteArray datagram;
//    datagram.append(ui->tedSend->toPlainText());
//    udpSocket->writeDatagram(datagram,datagram.length(),QHostAddress::Broadcast,8888);
}
//清空接受和发送数据按钮
void updComm::on_pushButton_8_clicked()
{
    ui->sendnum->clear();
    ui->revnum->clear();
}
QString updComm::getUserName()
{
    QStringList envVariables;
    //将后面5个string存到envVariables环境变量中
    envVariables << "USERNAME.*" << "USER.*" << "USERDOMAIN.*"
                 << "HOSTNAME.*" << "DOMAINNAME.*";
    //系统中关于环境变量的信息存在environment中
    QStringList environment = QProcess::systemEnvironment();
    foreach (QString string, envVariables) {
        //indexOf为返回第一个匹配list的索引,QRegExp类是用规则表达式进行模式匹配的类
        int index = environment.indexOf(QRegExp(string));
        if (index != -1) {
            //stringList中存的是environment.at(index)中出现'='号前的字符串
            QStringList stringList = environment.at(index).split('=');
            if (stringList.size() == 2) {
                return stringList.at(1);//at(0)为文字"USERNAME."，at(1)为用户名
                break;
            }
        }
    }
    return "unknown";
}

QString updComm::getIP()
{
    //QList是Qt中一个容器模板类，是一个数组指针？
    QList<QHostAddress> list = QNetworkInterface::allAddresses();//此处的所有地址是指ipv4和ipv6的地址
    //foreach (variable, container),此处为按照容器list中条目的顺序进行迭代
    foreach (QHostAddress address, list) {
        if(address.protocol() == QAbstractSocket::IPv4Protocol)
            return address.toString();
    }
    return 0;
}
