#ifndef REPORT_H
#define REPORT_H

#include <QDialog>
#include <stdio.h>
#include <cstring>
#include <string>
#include <fstream>
#include <QStandardItemModel>

using namespace std;
struct pcapFileHeader {
    string magic_number;   /* magic number */
    uint16_t version_major;  /* major version number */
    uint16_t version_minor;  /* minor version number */
    int32_t  thiszone;       /* GMT to local correction */
    uint32_t sigfigs;        /* accuracy of timestamps */
    uint32_t snaplen;        /* max length of captured packets, in octets */
    uint32_t network;        /* data link type */
};


namespace Ui {
class Report;
}

class Report : public QDialog
{
    Q_OBJECT
    
public:
    explicit Report(QWidget *parent = 0);
    ~Report();

    string pcpfile,savedfile,promis,adaptrname;
    int maxpcktlen,timeout;
    QStandardItemModel *rmodel;
    
private slots:
    void on_pushButton_2_clicked();

    void on_pushButton_clicked();

private:
    Ui::Report *ui;
};

#endif // REPORT_H
