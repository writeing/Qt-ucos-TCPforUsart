#ifndef UPDCOMM_H
#define UPDCOMM_H

#include <QMainWindow>
#include <QMessageBox>
#include <QButtonGroup>
#include <QFileDialog>
#include <QDir>
#include <QTextStream>
#include <QUdpSocket>
#include <QHostAddress>
#include <QTextCodec>
#include <QProcess>
#include <QNetworkInterface>
#include <QTcpServer>
#include <QLocalServer>
#include <QLocalSocket>
namespace Ui {
class updComm;
}

class updComm : public QMainWindow
{
    Q_OBJECT

public:
    int revModel;
    int sendModel;
    int sendNum;
    int revNum;
    QButtonGroup getModelrev;
    QButtonGroup getModelsend;

    QTcpServer *tcpServer;
    explicit updComm(QWidget *parent = 0);
    ~updComm();

public:
    void showInfo(QString msg);
    void initTcp();
    QString getUserName();
    QString getIP();
private slots:

    void on_revText_clicked();

    void on_sendHEX_clicked();

    void on_revHex_clicked();

    void on_sendText_clicked();

    void on_pushButton_2_clicked();

    void on_pushButton_clicked();

    void on_pushButton_4_clicked();

    void on_pushButton_6_clicked();

    void on_pushButton_3_clicked();

    void on_Btnconnet_clicked();

    void on_pushButton_5_clicked();

    void on_pushButton_8_clicked();

    void readPendingDatagrams();

private:
    Ui::updComm *ui;
};

#endif // UPDCOMM_H
