#include "protocol_list.h"
#include "ui_protocol_list.h"

Protocol_List::Protocol_List(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Protocol_List)
{
    ui->setupUi(this);
    QListWidget *item=ui->listWidget;
        item->addItem("ip");
        item->addItem("tcp");
        item->addItem("arp");
        item->addItem("udp");
        item->addItem("smtp");
        item->addItem("http");
        item->addItem("dns");
        item->addItem("ftp");
        item->addItem("rarp");
        item->addItem("https");
        item->addItem("mllp");
        item->addItem("ssdp");
        item->addItem("mndp");
        item->addItem("pop3");
        item->addItem("dhcp");
}

Protocol_List::~Protocol_List()
{
    delete ui;
}
