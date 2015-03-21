#include <windows.h>
#include "mainwindow.h"
#include "ui_mainwindow.h"
//#include "util/MEMORY_HANDEL.h"
#include "savedfilters.h"
#include "protocol_list.h"
#include "DESK_INFO/HardDiskManager.h"
#include <QIcon>
#include <QAction>
#include <QListWidget>
#include <QListWidgetItem>
#include <iostream>
#include <string>
#include <string.h>
#include <QLineEdit>
#include <stdio.h>
#include <QString>
#include <QMessageBox>
#include <QNetworkInterface>
#include <QFileDialog>
#include <stylesheet.h>
#include <QDir>


MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{

    ui->setupUi(this);
    StylesAplly();  //applly css style
    sniffer = new WinpcapSniffer(this);
    ui->tab->activateWindow();
    ui->pushButton_29->setEnabled(false);
    getAdapters();
    getSystemInfo();
    setUpDataModel();
    ui->lineEdit_24->setText(QDir::currentPath());
    QObject::connect(sniffer->wpcap->getInstance(),SIGNAL(packetArived(QString)),this,SLOT(getPacket(QString)));
    ui->splitter->hide();
}

void MainWindow::getfilters(){
    if(ui->tcp->isChecked())f.tcp=true;
    if(ui->udp->isChecked())f.udp=true;
    if(ui->arp->isChecked())f.arp=true;
    if(ui->rarp->isChecked())f.rarp=true;
    if(ui->smtp->isChecked())f.smtp=true;
    if(ui->dns->isChecked())f.dns=true;
    if(ui->ftp->isChecked())f.ftp=true;
    if(ui->http->isChecked())f.http=true;
    if(ui->https->isChecked())f.https=true;
    if(ui->dhcp->isChecked())f.dhcp=true;
    if(ui->srcip->isChecked())f.srcip=true;
    if(ui->dstip->isChecked())f.dstip=true;
    if(ui->srcordstip->isChecked())f.srcordstip=true;
    if(ui->ortcp->isChecked())f.ortcp=true;
    if(ui->andtcp->isChecked())f.andtcp=true;
    if(ui->orudp->isChecked())f.orudp=true;
    if(ui->andudp->isChecked())f.andudp=true;
    if(ui->ordns->isChecked())f.ordns=true;
    if(ui->anddns->isChecked())f.anddns=true;
    if(ui->orarp->isChecked())f.orarp=true;
    if(ui->andarp->isChecked())f.andarp=true;
    if(ui->orrarp->isChecked())f.orrarp=true;
    if(ui->andrarp->isChecked())f.andrarp=true;
    if(ui->ordhcp->isChecked())f.ordhcp=true;
    if(ui->anddhcp->isChecked())f.anddhcp=true;
    if(ui->orhttp->isChecked())f.orhttp=true;
    if(ui->andhttp->isChecked())f.andhttp=true;
    if(ui->orhttps->isChecked())f.orhttps=true;
    if(ui->andhttps->isChecked())f.andhttps=true;
    if(ui->orsmtp->isChecked())f.orsmtp=true;
    if(ui->andsmtp->isChecked())f.andsmtp=true;
    if(ui->orftp->isChecked())f.orftp=true;
    if(ui->andftp->isChecked())f.andftp=true;
    if(ui->srcip->isChecked()||ui->dstip->isChecked()||ui->srcordstip->isChecked())
        f.ip=ui->listip->currentItem()->text().toStdString();
    if(ui->tcp_port->isChecked())f.tcpport=true;
    if(ui->udp_port->isChecked())f.udpport=true;
    if(ui->srcport->isChecked())f.srcport=true;
    if(ui->dstport->isChecked())f.udpport=true;
    if(ui->srcordstport->isChecked())f.srcordstport=true;

    ////// return to false ///////
    if(!ui->tcp->isChecked())f.tcp=false;
    if(!ui->udp->isChecked())f.udp=false;
    if(!ui->arp->isChecked())f.arp=false;
    if(!ui->rarp->isChecked())f.rarp=false;
    if(!ui->smtp->isChecked())f.smtp=false;
    if(!ui->dns->isChecked())f.dns=false;
    if(!ui->ftp->isChecked())f.ftp=false;
    if(!ui->http->isChecked())f.http=false;
    if(!ui->https->isChecked())f.https=false;
    if(!ui->dhcp->isChecked())f.dhcp=false;
    if(!ui->srcip->isChecked())f.srcip=false;
    if(!ui->dstip->isChecked())f.dstip=false;
    if(!ui->srcordstip->isChecked())f.srcordstip=false;
    if(!ui->ortcp->isChecked())f.ortcp=false;
    if(!ui->andtcp->isChecked())f.andtcp=false;
    if(!ui->orudp->isChecked())f.orudp=false;
    if(!ui->andudp->isChecked())f.andudp=false;
    if(!ui->ordns->isChecked())f.ordns=false;
    if(!ui->anddns->isChecked())f.anddns=false;
    if(!ui->orarp->isChecked())f.orarp=false;
    if(!ui->andarp->isChecked())f.andarp=false;
    if(!ui->orrarp->isChecked())f.orrarp=false;
    if(!ui->andrarp->isChecked())f.andrarp=false;
    if(!ui->ordhcp->isChecked())f.ordhcp=false;
    if(!ui->anddhcp->isChecked())f.anddhcp=false;
    if(!ui->orhttp->isChecked())f.orhttp=false;
    if(!ui->andhttp->isChecked())f.andhttp=false;
    if(!ui->orhttps->isChecked())f.orhttps=false;
    if(!ui->andhttps->isChecked())f.andhttps=false;
    if(!ui->orsmtp->isChecked())f.orsmtp=false;
    if(!ui->andsmtp->isChecked())f.andsmtp=false;
    if(!ui->orftp->isChecked())f.orftp=false;
    if(!ui->andftp->isChecked())f.andftp=false;
    if(!ui->tcp_port->isChecked())f.tcpport=false;
    if(!ui->udp_port->isChecked())f.udpport=false;
    if(!ui->srcport->isChecked())f.srcport=false;
    if(!ui->dstport->isChecked())f.udpport=false;
    if(!ui->srcordstport->isChecked())f.srcordstport=false;

    if(ui->srcport->isChecked()||ui->dstport->isChecked()||ui->srcordstport->isChecked())
        f.n_port=ui->port_list->currentItem()->text().toStdString();
    if(ui->host_list->count()!=0)
        f.dsthost=ui->host_list->currentItem()->text().toShort();
}

void MainWindow::repinfo(){
    r.pcpfile=ui->lineEdit_24->text().toStdString();
    r.maxpcktlen=ui->spinBox_3->value();
    r.timeout=ui->spinBox_2->value();
    if(ui->checkBox_8->isChecked())
        r.promis="true";
    else
        r.promis="false";
    r.savedfile="report.rep";
    r.adaptrname=ui->listWidget_3->currentItem()->text().toStdString();
}

void MainWindow::getSystemInfo()
{
    ////////system info section///////////
    //    ui->ComputerName->setText();
    //    ui->OSName->setText(sysInfo.getOSName());
    //    ui->Processor->setText(sysInfo.getCPU());
    //    ui->Memory->setText(sysInfo.getMemory());

}

void MainWindow::setUpDataModel()
{
    items=0;
    smodel =new QStandardItemModel(1,8,this);
    smodel->setHeaderData(0,Qt::Horizontal,QObject::tr("Number"));
    smodel->setHeaderData(1,Qt::Horizontal,QObject::tr("Time"));
    smodel->setHeaderData(2,Qt::Horizontal,QObject::tr("Length"));
    smodel->setHeaderData(3,Qt::Horizontal,QObject::tr("Source"));
    smodel->setHeaderData(4,Qt::Horizontal,QObject::tr("Source Port"));
    smodel->setHeaderData(5,Qt::Horizontal,QObject::tr("Protocol"));
    smodel->setHeaderData(6,Qt::Horizontal,QObject::tr("Destination"));
    smodel->setHeaderData(7,Qt::Horizontal,QObject::tr("Destination Port"));
    ui->treeView_2->setModel(smodel);
    ui->treeView_2->setEditTriggers(QAbstractItemView::NoEditTriggers);
    ui->treeView_2->setUniformRowHeights(true);
    ui->treeView_2->setRowHidden(0,QModelIndex(),true);
}
void MainWindow::getPacket(QString pckt){
    QStringList columns= pckt.split("\t");
    if(columns.size()!= 8){
        qDebug()<<"pkt is "<<pckt;
    return;
    }

    QList<QStandardItem *> preparedRow =prepareTreeRowItem(columns)  ;
    smodel->appendRow(preparedRow);
    preparedRow.clear();

}
QList<QStandardItem *> MainWindow::prepareTreeRowItem(QStringList pckt)
{
    QList<QStandardItem *> rowItems;
    rowItems << new QStandardItem(QString::number(items++)/*pckt[0]*/);
    rowItems << new QStandardItem(pckt[1]);
    rowItems << new QStandardItem(pckt[2]);
    rowItems << new QStandardItem(pckt[3]);
    rowItems << new QStandardItem(pckt[4]);
    rowItems << new QStandardItem(pckt[5]);
    rowItems << new QStandardItem(pckt[6]);
    rowItems << new QStandardItem(pckt[7]);
    return rowItems;
}
MainWindow::~MainWindow()
{
    on_pushButton_29_clicked();
    delete ui;
}

void MainWindow::getAdapters()
{
    std::vector<Adapter> stdVec = sniffer->GetAdapters();
    QStringList qlist;
    int i=0;
    foreach(Adapter dev , stdVec){
        std::string s =dev.GetDescription();
        qlist.push_back(tr(s.c_str()));
        i++;
    }
    ui->listWidget_3->addItems(qlist);
}
void MainWindow::on_actionSave_filter_triggered()
{
    SavedFilters sf;
    sf.setModal(true);
    sf.exec();
}

void MainWindow::on_pushButton_26_clicked()
{
    Protocol_List pl;
    pl.setModal(true);
    pl.exec();
}

//////////////////////////  START_CAP   //////////////////////////////
void MainWindow::on_pushButton_27_clicked()
{
    if ( sniffer ){
        //clear view
        smodel->clear();
        setUpDataModel();
        delete sniffer;
        sniffer = NULL;
        sniffer = new WinpcapSniffer(this);
    }
    else
        sniffer = new WinpcapSniffer(this);


    getfilters();
    sniffer->StartSniffing();
    std::string filter;
        if(ui->groupBox_3->isChecked())
             filter=ui->lineEdit_3->text().toStdString();
        else
             filter=f.filter_string();

        qDebug()<<"filter is "<<filter.c_str();
    sniffer->SetFilter(filter);
    sniffer->start();


    ui->pushButton_29->setEnabled(true);
    ui->pushButton_27->setEnabled(false);
    ui->listWidget_3->setEnabled(false);
    ui->spinBox->setEnabled(false);
    ui->spinBox_2->setEnabled(false);
    ui->spinBox_3->setEnabled(false);
    ui->spinBox_4->setEnabled(false);
    ui->spinBox_5->setEnabled(false);
    ui->pushButton_30->setEnabled(false);
    ui->tab2->setEnabled(false);
}
//////////////////////Stop Capture///////////////////////////////
void MainWindow::on_pushButton_29_clicked()
{
    //stop
    sniffer->StopSniffing();
    ui->pushButton_29->setEnabled(false);//stopButton
    ui->pushButton_27->setEnabled(true);//startButton
    ui->listWidget_3->setEnabled(true);//selecting device
    ui->spinBox->setEnabled(true);
    ui->spinBox_2->setEnabled(true);
    ui->spinBox_3->setEnabled(true);
    ui->spinBox_4->setEnabled(true);
    ui->spinBox_5->setEnabled(true);
    ui->pushButton_30->setEnabled(true);
    ui->tab2->setEnabled(true);

}



/////////////////   DISK_INFO   ///////////////////////////////////////
void MainWindow::on_pushButton_30_clicked()
{

    //  QString path2=QFileDialog::getExistingDirectory(this,tr("Select Directory"),QDir::currentPath());

    QString filters = "*.pcap";
    QString path2=QFileDialog::getSaveFileName(this,tr("Select Save Directory"),QDir::currentPath(),filters);
    qDebug()<<path2;
    QString path=path2.toLocal8Bit().constData();
    qDebug()<<path;
    ui->lineEdit_24->setText(path2);
    QFileInfo currentPath = path2;
    qDebug()<<QString::fromStdString(currentPath.absolutePath().toStdString());
    QString absolutePath = QString::fromStdString(currentPath.absolutePath().toStdString());
    getDiskInfo(absolutePath);
    sniffer->SetFileName(path2.toStdString());

}

void MainWindow::on_listWidget_3_itemActivated(QListWidgetItem *item)
{
}

/////////////////select Adapter///////////////////////////////
void MainWindow::on_listWidget_3_clicked(const QModelIndex &index)
{
    int adapterNumber = index.row();
    sniffer->SetAdapter(adapterNumber);
    ui->lineEdit_25->setText(QString::fromStdString(sniffer->adapter.GetName()));
    ui->lineEdit_27->setText(QString::fromStdString(sniffer->adapter.GetAddress()));
    ui->lineEdit_28->setText(QString::fromStdString(sniffer->adapter.GetNetmask()));

}

void MainWindow::on_checkBox_8_stateChanged(int arg1)
{
    //arg1 = 2 for checked and 0 for unchecked
    if(ui->checkBox_8->checkState() == Qt::Checked || (arg1 == 2))
        sniffer->SetPromiscMode(1);
    else
        sniffer->SetPromiscMode(0);
}

void MainWindow::on_spinBox_2_valueChanged(int arg1)
{
    //timeOut Value
    sniffer->SetTimeOut(arg1);
}

void MainWindow::on_spinBox_3_valueChanged(int arg1)
{
    //packetlength value
    sniffer->SetPacketLength(arg1);
}

void MainWindow::getDiskInfo(QString &Qpath)
{

    std::string path = Qpath.toStdString();
    TCHAR* str = new TCHAR[path.size()+1];
    std::copy(path.begin(),path.end(),str);
    str[path.size()] = 0;
    manager.CheckFreeSpace(str);

    ui->lineEdit_26->setText(QString::number(manager.GetTotalNumberOfGBytes())+" GB");

    ui->lineEdit->setText(QString::number(manager.GetTotalNumberOfFreeGBytes())+" GB");

    ui->lineEdit_2->setText(QString::number(manager.GetTotalNumberOfGBytes()-
                                            manager.GetTotalNumberOfFreeGBytes())+" GB");

}

void MainWindow::on_actionStart_2_triggered()
{
    on_pushButton_27_clicked();
}

void MainWindow::on_actionStop_2_triggered()
{
    repinfo();
    on_pushButton_29_clicked();
    r.setModal(true);
    r.exec();
}

void MainWindow::on_srcip_stateChanged(int arg1)
{
    if(ui->srcip->isChecked()&&ui->dstip->isChecked()){
        f.srcordstip=false;
        ui->srcordstip->setChecked(false);
        ui->srcordstip->setEnabled(false);
    }
    if(!ui->srcip->isChecked()||!ui->dstip->isChecked()){
        ui->srcordstip->setEnabled(true);
    }
}
void MainWindow::on_dstip_stateChanged(int arg1)
{
    if(ui->srcip->isChecked()&&ui->dstip->isChecked()){
        f.srcordstip=false;
        ui->srcordstip->setChecked(false);
        ui->srcordstip->setEnabled(false);
    }
    if(!ui->srcip->isChecked()||!ui->dstip->isChecked()){
        ui->srcordstip->setEnabled(true);
    }
}
void MainWindow::on_srcordstip_stateChanged(int arg1)
{
    if(ui->srcordstip->isChecked()){
        f.srcip=false;
        f.dstip=false;
        ui->srcip->setChecked(false);
        ui->dstip->setChecked(false);
        ui->srcip->setEnabled(false);
        ui->dstip->setEnabled(false);
    }
    if(!ui->srcordstip->isChecked()){
        ui->srcip->setEnabled(true);
        ui->dstip->setEnabled(true);
    }
}

void MainWindow::on_addip_clicked()
{
    QString ip=ui->ipbyte1->text()+"."+ui->ipbyte2->text()+"."+ui->ipbyte3->text()+"."+ui->ipbyte4->text();
    ui->listip->addItem(ip);
    ui->ipbyte1->setText("");
    ui->ipbyte2->setText("");
    ui->ipbyte3->setText("");
    ui->ipbyte4->setText("");
}

void MainWindow::on_tcp_stateChanged(int arg1)
{
    if(ui->tcp->isChecked()){
        ui->ortcp->setEnabled(true);
        ui->andtcp->setEnabled(true);
    }
    if(!ui->tcp->isChecked()){
        ui->ortcp->setChecked(false);
        ui->ortcp->setEnabled(false);
        ui->andtcp->setEnabled(false);
        ui->andtcp->setChecked(false);
    }
}

void MainWindow::on_dns_clicked()
{
    if(ui->dns->isChecked()){
        ui->ordns->setEnabled(true);
        ui->anddns->setEnabled(true);
    }
    if(!ui->dns->isChecked()){
        ui->ordns->setChecked(false);
        ui->ordns->setEnabled(false);
        ui->anddns->setEnabled(false);
        ui->anddns->setChecked(false);
    }
}

void MainWindow::on_udp_stateChanged(int arg1)
{
    if(ui->udp->isChecked()){
        ui->orudp->setEnabled(true);
        ui->andudp->setEnabled(true);
    }
    if(!ui->udp->isChecked()){
        ui->orudp->setChecked(false);
        ui->orudp->setEnabled(false);
        ui->andudp->setEnabled(false);
        ui->andudp->setChecked(false);
    }
}

void MainWindow::on_rarp_clicked()
{
    if(ui->rarp->isChecked()){
        ui->orrarp->setEnabled(true);
        ui->andrarp->setEnabled(true);
    }
    if(!ui->rarp->isChecked()){
        ui->orrarp->setChecked(false);
        ui->orrarp->setEnabled(false);
        ui->andrarp->setEnabled(false);
        ui->andrarp->setChecked(false);
    }
}

void MainWindow::on_arp_clicked()
{
    if(ui->arp->isChecked()){
        ui->orarp->setEnabled(true);
        ui->andarp->setEnabled(true);
    }
    if(!ui->arp->isChecked()){
        ui->orarp->setChecked(false);
        ui->orarp->setEnabled(false);
        ui->andarp->setEnabled(false);
        ui->andarp->setChecked(false);
    }
}

void MainWindow::on_dhcp_clicked()
{
    if(ui->dhcp->isChecked()){
        ui->ordhcp->setEnabled(true);
        ui->anddhcp->setEnabled(true);
    }
    if(!ui->dhcp->isChecked()){
        ui->ordhcp->setChecked(false);
        ui->ordhcp->setEnabled(false);
        ui->anddhcp->setEnabled(false);
        ui->anddhcp->setChecked(false);
    }
}

void MainWindow::on_http_clicked()
{
    if(ui->http->isChecked()){
        ui->orhttp->setEnabled(true);
        ui->andhttp->setEnabled(true);
    }
    if(!ui->http->isChecked()){
        ui->orhttp->setChecked(false);
        ui->orhttp->setEnabled(false);
        ui->andhttp->setEnabled(false);
        ui->andhttp->setChecked(false);
    }
}

void MainWindow::on_smtp_clicked()
{
    if(ui->smtp->isChecked()){
        ui->orsmtp->setEnabled(true);
        ui->andsmtp->setEnabled(true);
    }
    if(!ui->smtp->isChecked()){
        ui->orsmtp->setChecked(false);
        ui->orsmtp->setEnabled(false);
        ui->andsmtp->setEnabled(false);
        ui->andsmtp->setChecked(false);
    }
}

void MainWindow::on_https_clicked()
{
    if(ui->https->isChecked()){
        ui->orhttps->setEnabled(true);
        ui->andhttps->setEnabled(true);
    }
    if(!ui->https->isChecked()){
        ui->orhttps->setChecked(false);
        ui->orhttps->setEnabled(false);
        ui->andhttps->setEnabled(false);
        ui->andhttps->setChecked(false);
    }
}

void MainWindow::on_ftp_clicked()
{
    if(ui->ftp->isChecked()){
        ui->orftp->setEnabled(true);
        ui->andftp->setEnabled(true);
    }
    if(!ui->ftp->isChecked()){
        ui->orftp->setChecked(false);
        ui->orftp->setEnabled(false);
        ui->andftp->setEnabled(false);
        ui->andftp->setChecked(false);
    }
}

void MainWindow::on_deleteip_clicked()
{
    delete ui->listip->currentItem();
}

void MainWindow::on_pushButton_7_clicked()
{
    ui->port_list->addItem(ui->port_edit->text());
    ui->port_edit->setText("");
}

void MainWindow::on_pushButton_8_clicked()
{
    delete ui->port_list->currentItem();
}

void MainWindow::on_pushButton_9_clicked()
{
    ui->host_list->addItem(ui->host_edit->text());
    ui->host_edit->setText("");
}

void MainWindow::on_pushButton_10_clicked()
{
    delete ui->host_list->currentItem();
}
