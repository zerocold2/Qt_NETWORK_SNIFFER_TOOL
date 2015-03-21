#include "report.h"
#include "ui_report.h"
#include <QMessageBox>
#include <QVariant>

ofstream os;
pcapFileHeader fileHeader;

Report::Report(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Report)
{
    os.open("report.rep");
    fileHeader.magic_number = "0xa1b2c3d4";
    fileHeader.version_major = 2;
    fileHeader.version_minor = 4;
    fileHeader.thiszone = 0;
    fileHeader.sigfigs = 0;
    fileHeader.snaplen = 65535;
    fileHeader.network = 1;     //Ethernet
    ui->setupUi(this);
    rmodel =new QStandardItemModel(11,2,this);
    rmodel->setHeaderData(0,Qt::Horizontal,QObject::tr("Propertiy"));
    rmodel->setHeaderData(1,Qt::Horizontal,QObject::tr("Value"));
    QModelIndex index=rmodel->index(0,0);
    rmodel->setData(index,"Saved captured file");
    QModelIndex index0=rmodel->index(0,1);
    rmodel->setData(index0,"D:\E\ahmed\computer_science\G_Projects\GP Network anlysis\implemmentations\Carnivore v1.9\Carnivore");
    QModelIndex index1=rmodel->index(1,0);
    rmodel->setData(index1,"report file name");
    QModelIndex index2=rmodel->index(1,1);
    rmodel->setData(index2,"report.rep");
    QModelIndex index3=rmodel->index(2,0);
    rmodel->setData(index3,"magic number");
    QModelIndex index4=rmodel->index(2,1);
    rmodel->setData(index4,fileHeader.magic_number.c_str());
    QModelIndex index5=rmodel->index(3,0);
    rmodel->setData(index5,"version major");
    QModelIndex index6=rmodel->index(3,1);
    rmodel->setData(index6,"2");
    QModelIndex index7=rmodel->index(4,0);
    rmodel->setData(index7,"version minor");
    QModelIndex index8=rmodel->index(4,1);
    rmodel->setData(index8,(char)fileHeader.version_minor);
    QModelIndex index9=rmodel->index(5,0);
    rmodel->setData(index9,"this zone");
    QModelIndex index91=rmodel->index(5,1);
    rmodel->setData(index91,"0");
    QModelIndex index92=rmodel->index(6,0);
    rmodel->setData(index92,"max packet length");
    QModelIndex index93=rmodel->index(6,1);
    rmodel->setData(index93,maxpcktlen);
    QModelIndex index94=rmodel->index(7,0);
    rmodel->setData(index94,"Data link type");
    QModelIndex index95=rmodel->index(7,1);
    rmodel->setData(index95,"Ethernet");
    QModelIndex index96=rmodel->index(8,0);
    rmodel->setData(index96,"Promiscis mode");
    QModelIndex index97=rmodel->index(8,1);
    rmodel->setData(index97,"true");
    QModelIndex index99=rmodel->index(9,1);
    rmodel->setData(index99,"1000 ms");
    QModelIndex index98=rmodel->index(9,0);
    rmodel->setData(index98,"capture Time out");
    QModelIndex index991=rmodel->index(10,0);
    rmodel->setData(index991,"Sniffing driver");
    QModelIndex index981=rmodel->index(10,1);
    rmodel->setData(index981,QString(adaptrname.c_str()));


    ui->tableView->setModel(rmodel);
    ui->tableView->setEditTriggers(QAbstractItemView::NoEditTriggers);
    ui->tableView->resizeColumnsToContents();
    ui->tableView->resizeRowsToContents();
}

Report::~Report()
{
    delete ui;
}

void Report::on_pushButton_2_clicked()
{
    os << "Saved captured file\t\t"<<pcpfile<<
          "\nreport file name\t\t"<<savedfile<<
          "\nmagic_number\t\t"<<fileHeader.magic_number <<
          "\nversion_major\t\t"<<fileHeader.version_major <<
          "\nversion_minor\t\t" <<fileHeader.version_minor <<
          "\nthiszone\t" << fileHeader.thiszone <<
             "\nsigfigs\t\t"<<   fileHeader.sigfigs <<
          "\nmax packet length\t\t"<< fileHeader.snaplen <<
          "\nData link type = Ethernet = \t\t" <<fileHeader.network
        <<"\ncapture time out\t\t"<<timeout
       <<"\npromisciss mode\t\t"<<promis<<
         "\nNetwork driver name\t\t"<<adaptrname;



    //os.write(reinterpret_cast<const char*>(&fileHeader),sizeof fileHeader);
    os.close();
    QMessageBox::information(this,"save data","Data saved in report.rep file in the same direcory");
}

void Report::on_pushButton_clicked()
{
    this->close();
}
