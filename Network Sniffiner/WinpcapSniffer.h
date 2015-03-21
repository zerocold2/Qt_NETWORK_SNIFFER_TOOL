#pragma once
#ifndef WINPCAPSNIFFER_H
#define  WINPCAPSNIFFER_H
#include "WinpcapWrapper.h"
#include"Adapter.h"
#include<string>
#include<vector>
#include <iostream>
#include<QThread>
namespace NetworkWrapper {

class WinpcapSniffer :public QThread
{
    Q_OBJECT
private:


public:
    QPointer<WinpcapWrapper> wpcap;
    Adapter adapter;

    explicit WinpcapSniffer(QObject *parent = 0);
    ~WinpcapSniffer(void);
    void run();
    void SetMaxNumOfPacket(int);
    void SetFileName(std::string);
    void SetFileSize(int);
    void SetBuffer(int);
    void StartSniffing();
    void startLoop();
    void StopSniffing();
    void SetPacketLength(int);
    void SetTimeOut(int);
    void SetPromiscMode(int);
    void SetFilter(std::string filter);
    std::string GetAdapterInfo();
    Adapter		SetAdapter(int inum = 1);
    std::vector<Adapter> GetAdapters();
};

}
#endif //WINPCAPSNIFFER_H
