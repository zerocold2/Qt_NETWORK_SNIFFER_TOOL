#include "WinpcapSniffer.h"

using namespace NetworkWrapper;

//constructor
WinpcapSniffer::WinpcapSniffer(QObject *parent) :
    QThread(parent)
{
    wpcap = WinpcapWrapper::getInstance();
}
//destructor
WinpcapSniffer::~WinpcapSniffer() {
    wait();
    StopSniffing();
    qDebug()<<"winpcapsniffer closed";
}

void WinpcapSniffer::run()
{
//    StartSniffing();
    startLoop();
}

void WinpcapSniffer::StartSniffing() {
    printf("Sniffing is On .....\n");
    if (WinpcapSniffer::adapter.GetName().empty())
    {
        if(GetAdapters().size()>= 0){
            adapter = WinpcapSniffer::SetAdapter(0);
            WinpcapSniffer::wpcap->StartCaptureWithCallBack(WinpcapSniffer::adapter.GetName());
        }
    }
    else{
        WinpcapSniffer::wpcap->StartCaptureWithCallBack(WinpcapSniffer::adapter.GetName());
    }
}

void WinpcapSniffer::startLoop()
{
    WinpcapSniffer::wpcap->Loop();
}

void WinpcapSniffer::StopSniffing() {

    WinpcapSniffer::wpcap->Close();
}

void WinpcapSniffer::SetPacketLength(int PL)
{
    //packet length
    wpcap->SetPacketLength(PL);
}

void WinpcapSniffer::SetTimeOut(int TO)
{
    //timeout
    wpcap->SetTimeOut(TO);
}

void WinpcapSniffer::SetPromiscMode(int Promisc)
{
    //set promisc mode 1 for true and 0 for false
    if(Promisc == 0 || Promisc == 1)
        wpcap->SetPromiscMode(Promisc);
    else
        wpcap->SetPromiscMode(1);

}

void WinpcapSniffer::SetMaxNumOfPacket(int PC){
    WinpcapSniffer::wpcap->SetPacketCounter(PC);
}
void WinpcapSniffer::SetFileName(std::string FN){
    WinpcapSniffer::wpcap->SetFileName(FN);
}
void WinpcapSniffer::SetFileSize(int FS){
    WinpcapSniffer::wpcap->SetFileSize(FS);
}
void WinpcapSniffer::SetBuffer(int BS){
    WinpcapSniffer::wpcap->SetBuffer(BS);
}
void WinpcapSniffer::SetFilter(std::string F){
    WinpcapSniffer::wpcap->SetFilter(F);
}

std::string WinpcapSniffer::GetAdapterInfo() {
    std::string info;
    info ="winpcap: "+adapter.GetDescription();

    //if (!adapter.GetAddress().empty() && adapter.GetAddress().length > 6)
    //{
    info+= "(" + adapter.GetAddress() + ")";
    //}
    info += " " + adapter.GetName() ;
    std::cout<<info<<std::endl;
    return info;
}
Adapter WinpcapSniffer::SetAdapter(int inum ) {
    WinpcapSniffer::adapter = wpcap->FindDev(inum);
    return adapter;
}
//check this out
std::vector<Adapter> WinpcapSniffer::GetAdapters() {

       return wpcap->FindAllDevs();
}

