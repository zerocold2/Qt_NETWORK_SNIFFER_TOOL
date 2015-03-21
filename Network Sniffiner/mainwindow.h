#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QListWidgetItem>
#include"WinpcapSniffer.h"
#include "DESK_INFO/HardDiskManager.h"
#include<QStandardItemModel>
//#include "systeminfo.h"
#include <filters.h>
#include <report.h>
using namespace NetworkWrapper;
namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

    
public:
    explicit MainWindow(QWidget *parent = 0);
    CHardDiskManager manager;               /*HardDiskManager Class Opject*/
//    SystemInfo sysInfo;
    ~MainWindow();
    void getAdapters();
    int items;
    QStandardItemModel *smodel;
    Filters f;
    Report r;
    void getfilters();
    void getSystemInfo();
    void setUpDataModel();
    QList<QStandardItem *> prepareTreeRowItem(QStringList pckt);
    void repinfo();
private slots:
    void getPacket(QString);
    void on_actionSave_filter_triggered();

    void on_pushButton_26_clicked();

    void on_pushButton_27_clicked();

    void on_pushButton_30_clicked();

    void on_listWidget_3_itemActivated(QListWidgetItem *item);

    void on_pushButton_29_clicked();

    void on_listWidget_3_clicked(const QModelIndex &index);

    void on_checkBox_8_stateChanged(int arg1);

    void on_spinBox_2_valueChanged(int arg1);

    void on_spinBox_3_valueChanged(int arg1);
    void getDiskInfo(QString &path);
    void on_actionStart_2_triggered();

    void on_actionStop_2_triggered();

    void on_srcip_stateChanged(int arg1);
    void on_dstip_stateChanged(int arg1);

    void on_srcordstip_stateChanged(int arg1);

    void on_addip_clicked();

    void on_tcp_stateChanged(int arg1);

    void on_dns_clicked();

    void on_udp_stateChanged(int arg1);

    void on_rarp_clicked();

    void on_arp_clicked();

    void on_dhcp_clicked();

    void on_http_clicked();

    void on_smtp_clicked();

    void on_https_clicked();

    void on_ftp_clicked();

    void on_deleteip_clicked();

    void on_pushButton_7_clicked();

    void on_pushButton_8_clicked();

    void on_pushButton_9_clicked();

    void on_pushButton_10_clicked();

private:
    Ui::MainWindow *ui;
    WinpcapSniffer *sniffer;
};

#endif // MAINWINDOW_H
