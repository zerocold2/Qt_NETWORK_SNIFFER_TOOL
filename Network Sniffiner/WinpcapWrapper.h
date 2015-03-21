
#ifndef WINPCAPWRAPPER_H
#define WINPCAPWRAPPER_H
#ifdef _MSC_VER
#define _CRT_SECURE_NO_WARNINGS
#endif
#define MAX_SNAPLEN  65536
#define MIN_SNAPLEN  64
#define TIME_OUT_ONE 1000
#define TIME_OUT_ZERO 0
#define TIME_OUT_TWENTY 20000
#define PCAP_CLOSE_FLAG_PROMISCUOUS   0
#define PCAP_OPEN_FLAG_PROMISCUOUS   1
#define IPTOSBUFFERS	12		/* From tcptraceroute, convert a numeric IP address to a string */
#include <cstdio>
#include <ctime>
///////////used to make c run in c++ ///////////////////////////////////////////////////////////////
#ifdef __cplusplus
extern "C" {
#endif
////////to be continued//////////////////////////////////////////////////////////////////
#define PCAP_VERSION_MAJOR 2
#define PCAP_VERSION_MINOR 4
#include <pcap.h>
////the rest of c //////////////////////////////////////////////////////////////////////
#ifdef __cplusplus
}
#endif
//////////////////////////////////////////////////////////////////////////

#include <QtCore>
#include <string>
#include <vector>
#include "Adapter.h"
#include "CallbackHandle.h"
#include<time.h>

namespace NetworkWrapper {

class WinpcapWrapper :public QObject{

    Q_OBJECT
    //    private:
    //        WinpcapWrapper(QObject *parent = 0);

signals:
    void packetArived(QString);

public:
    c_back *decoder;
    static WinpcapWrapper *getInstance();
    static  int timeOut;//driver time out
    static int packetlength;//packet length
    static  int promiscMode;//Promisc Mode for capture
    static  int datalink ;//datalink
    static std::string attachedDevice;//the name of the running adapter
    static int packetCounter;
    static std::string FileName;
    static int BufferSize;
    static int FileSize;
    static std::string FilterString;
    static  pcap_if_t *alldevs;//pointer for all devices
    static  pcap_if_t *d;//pointer for the device
    static  pcap_dumper_t *dumpfile;//pointer for the dumpfile
    static  pcap_t *adhandle;//handler for the session
    static  char errbuf[PCAP_ERRBUF_SIZE];
    static  struct bpf_program fcode;
    static   bpf_u_int32 NetMask;
    //////////////packet Data////////////////////////////////////////////////////////////
    static  struct pcap_pkthdr *header;
    static const u_char *pkt_data;
    //////////////////////////////////////////////////////////////////////////
    /*static*/ char*				iptostring(u_long in);
    //static char*				ip6tostring(struct sockaddr *sockaddr, char *address, int addrlen);
    static std::vector<Adapter>	FindAllDevs();
    /*static*/ Adapter		        FindDev(int inum);
    /*static*/ void				    Loop();
    static void				    packet_handler(u_char *param, const struct pcap_pkthdr *Myheader, const u_char *Mypkt_data);
    /*static*/ bool				    OpenLive(std::string dev,int snaplen=MAX_SNAPLEN,int promisc=PCAP_OPEN_FLAG_PROMISCUOUS,int read_timeout=1000);
    /*static*/ void				    SetFilter(std::string filter);
    //static void				    MonitorDump();
    static void				    DumpPacket(u_char *param, const struct pcap_pkthdr *header, const u_char *pkt_data);
    /*static*/ void					StartCaptureWithCallBack(std::string adapterName);
    /*static*/ void					StartCaptureWithoutCallBack(std::string adapterName);
    /*static*/ void				    StopDump();
    /*static*/ void			        StartDump();
    /*static*/ int				    GetDataLink();
    /*static*/ bool					IsEthernet();
    /*static*/ bool				    SetMinToCopy(int size);
    /*static*/ void				    SetKernelBuffer(int bytes);
    /*static*/ void				    Close();
    /*static*/ std::string			GetAttachedDevice();
    /*static*/ void					SetPacketCounter(int);
    /*static*/ void					SetFileName(std::string);
    /*static*/ void					SetFileSize(int);
    /*static*/ void					SetBuffer(int);
    /*static*/ void                 SetPacketLength(int);
    /*static*/ void                 SetTimeOut(int);
    /*static*/ void                 SetPromiscMode(int);


};
}
#endif // !WINPCAPWRAPPER_H
