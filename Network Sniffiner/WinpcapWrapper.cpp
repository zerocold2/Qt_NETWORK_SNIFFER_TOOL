#include"WinpcapWrapper.h"
#include <iostream>
using namespace NetworkWrapper;

//////////////////////////////////////////////////////////////////////////
int WinpcapWrapper::datalink ;//datalink
std::string WinpcapWrapper::attachedDevice;//the name of the running adapter
int WinpcapWrapper::packetCounter;//packet counter for stop after
std::string WinpcapWrapper::FileName;//file name for save
int WinpcapWrapper::BufferSize;//buffer size
int WinpcapWrapper::FileSize;//file size
std::string WinpcapWrapper::FilterString;//filter string
pcap_if_t* WinpcapWrapper::alldevs;//pointer for all devices
pcap_if_t* WinpcapWrapper::d;//pointer for the device
pcap_dumper_t* WinpcapWrapper::dumpfile;//pointer for the dumpfile
pcap_t* WinpcapWrapper::adhandle;//handler for the session
char WinpcapWrapper::errbuf[PCAP_ERRBUF_SIZE];
bpf_program WinpcapWrapper::fcode;//struct
bpf_u_int32 WinpcapWrapper::NetMask;
pcap_pkthdr* WinpcapWrapper::header;//struct
const u_char* WinpcapWrapper::pkt_data;
int WinpcapWrapper::timeOut=TIME_OUT_ONE;//driver time out
int WinpcapWrapper::packetlength= MAX_SNAPLEN;//packet length
int WinpcapWrapper::promiscMode = PCAP_OPEN_FLAG_PROMISCUOUS;
//////////////////////////////////////////////////////////////////////////
//convert ip address to string////////////////////////////////////////////
char *WinpcapWrapper::iptostring(u_long in) {

    char output[IPTOSBUFFERS][3*4+3+1];
    short which=0;
    u_char *p;

    p = (u_char *)&in;
    which = (which + 1 == IPTOSBUFFERS ? 0 : which + 1);
    sprintf(output[which], "%d.%d.%d.%d", p[0], p[1], p[2], p[3]);
    return output[which];

}

/////////////////////convert ip6 to string/////////////////////////////////////////////////////
#ifndef __MINGW32__ /* Cygnus doesn't have IPv6 */
char* WinpcapWrapper::ip6tostring(struct sockaddr *sockaddr, char *address, int addrlen) {
    socklen_t sockaddrlen;

#ifdef WIN32
    sockaddrlen = sizeof(struct sockaddr_in6);
#else
    sockaddrlen = sizeof(struct sockaddr_storage);
#endif


    if(getnameinfo(sockaddr,
                   sockaddrlen,
                   address,
                   addrlen,
                   NULL,
                   0,
                   NI_NUMERICHOST) != 0) address = NULL;

    return address;
}
#endif /* __MINGW32__ */
////////////////// get all devices//////////////////////////////////////////////////
std::vector<Adapter>WinpcapWrapper::FindAllDevs() {
    Adapter device;
    std::vector<Adapter>deviceList;



    /* Retrieve the device list */
    if(pcap_findalldevs(&alldevs, errbuf) == -1)
    {

        qDebug()<<QString::fromStdString(errbuf);
        fprintf(stderr,"Error in pcap_findalldevs: %s\n", errbuf);
    }

    ////////////////printing devs////////////////////////////////////////////////////////////
    for(d=alldevs; d; d=d->next)
    {

        pcap_addr_t *a;//address of pcap contains ipaddress , netmask and others
        char ip6str[128];

        /* Name */
        printf("%s\n",d->name);
        device.SetName(d->name);
        /* Description */
        if (d->description) {
            printf("\tDescription: %s\n",d->description);
            device.SetDescription(d->description);
        }


        /* IP addresses */
        for(a=d->addresses; a; a=a->next) {
            printf("\tAddress Family: #%d\n",a->addr->sa_family);

            switch(a->addr->sa_family)
            {
            case AF_INET:
                printf("\tAddress Family Name: AF_INET\n");
                if (a->addr) {
                    //                    printf("\tAddress: %s\n",WinpcapWrapper::getInstance()->iptostring(((struct sockaddr_in *)a->addr)->sin_addr.s_addr));
                    device.SetAddress(WinpcapWrapper::getInstance()->iptostring(((struct sockaddr_in *)a->addr)->sin_addr.s_addr));
                }
                if (a->netmask) {
                    //                    printf("\tNetmask: %s\n",WinpcapWrapper::iptostring(((struct sockaddr_in *)a->netmask)->sin_addr.s_addr));
                    device.SetNetmask(WinpcapWrapper::getInstance()->iptostring(((struct sockaddr_in *)a->netmask)->sin_addr.s_addr));
                }
                if (a->broadaddr)
                    //                    printf("\tBroadcast Address: %s\n",WinpcapWrapper::iptostring(((struct sockaddr_in *)a->broadaddr)->sin_addr.s_addr));
                    if (a->dstaddr)
                        //                    printf("\tDestination Address: %s\n",WinpcapWrapper::iptostring(((struct sockaddr_in *)a->dstaddr)->sin_addr.s_addr));
                        break;

            case AF_INET6:
                printf("\tAddress Family Name: AF_INET6\n");
                if (a->addr) {
                    //printf("\tAddress: %s\n", WinpcapWrapper::ip6tostring(a->addr, ip6str, sizeof(ip6str)));
                    //                    device.SetAddress( WinpcapWrapper::getInstance()->ip6tostring(a->addr, ip6str, sizeof(ip6str)));
                }
                break;

            default:
                printf("\tAddress Family Name: Unknown\n");
                break;
            }
        }
        deviceList.push_back(device);
    }
    pcap_freealldevs(alldevs);
    return deviceList;
}
///////////////////select device ///////////////////////////////////////////////////////
Adapter	WinpcapWrapper::FindDev(int inum) {
    // std::size_t inum_tmp=inum;
    Adapter device;
    std::vector<Adapter>deviceList= WinpcapWrapper::FindAllDevs();

    //    if((size_t)inum < 1 ||(size_t) inum >deviceList.size())
    //    {
    ////        printf("\nInterface number out of range.\n");
    //        qDebug()<<"Interface number out of range";
    //       inum = 1;
    //    }

    for (std::vector<Adapter>::iterator it = deviceList.begin(); it != deviceList.end() && inum >= 0; ++it,--inum)
        device = *it;

    qDebug()<<QString::fromStdString(device.GetDescription());
    return device;

}
//////////////////////////////////////////////////////////////////////////
void		WinpcapWrapper::Loop() {

    pcap_loop(WinpcapWrapper::adhandle, packetCounter,WinpcapWrapper::packet_handler, (unsigned char *)dumpfile);
}
/////////////////* save into file till we find a way *///////////////////////////////////////////////////////////
void		WinpcapWrapper::packet_handler(u_char *param, const struct pcap_pkthdr *header, const u_char *pkt_data) {

    static int packetCount=0;
    std::cout<<"packet number"<<++packetCount<<std::endl;
    WinpcapWrapper::DumpPacket((unsigned char *)dumpfile,header,pkt_data);
    ////////////Decoding Part/////////////////////////////////////////////////
    QString packet = getInstance()->decoder->call_back(param,header,pkt_data);
    emit WinpcapWrapper::getInstance()->packetArived(packet);
}
//////////////////////////////////////////////////////////////////////////
bool		WinpcapWrapper::OpenLive(std::string dev,int snaplen,int promisc,int read_timeout) {
    /* Open the adapter */
    if ((adhandle= pcap_open_live(dev.c_str(),	// name of the device
                                  snaplen,			// portion of the packet to capture.
                                  // 65536 grants that the whole packet will be captured on all the MACs.
                                  promisc,				// promiscuous mode (nonzero means promiscuous)
                                  read_timeout,			// read timeout
                                  errbuf			// error buffer
                                  )) == NULL)
    {
        fprintf(stderr,"\nUnable to open the adapter. %s is not supported by WinPcap\n", d->name);
        /* Free the device list */
        pcap_freealldevs(alldevs);
        return false;
    } else {
        return true;
    }
}
////////////////////capture packet with callback function//////////////////////////////////////////////////////
void	WinpcapWrapper::StartCaptureWithCallBack(std::string adapterName){
    /*if (WinpcapWrapper::IsEthernet())
    {*/

    WinpcapWrapper::OpenLive(adapterName, packetlength,promiscMode, timeOut);
    WinpcapWrapper::StartDump();
//    WinpcapWrapper::Loop();
    /*}
    else
    {
        printf("LinkLayer is not ethernet !!!");
    }*/
}
//////////////////////capture packet without callback function////////////////////////////////////////////////////
void WinpcapWrapper::StartCaptureWithoutCallBack(std::string adapterName){

    WinpcapWrapper::OpenLive(adapterName, packetlength,promiscMode, timeOut);
    WinpcapWrapper::StartDump();
    int res;
    /* Retrieve packets*/
    static int packetCount=0;

    while((res = pcap_next_ex( adhandle, &header, &pkt_data)) >= 0 && WinpcapWrapper::packetCounter >0)
    {
        WinpcapWrapper::DumpPacket((unsigned char *)dumpfile,header,pkt_data);
        std::cout<<"packet number"<<++packetCount<<std::endl;
        WinpcapWrapper::packetCounter--;
    }


    if (res == -1)
    {
        printf("Error reading the packets: %s\n", pcap_geterr(adhandle));
    }
}

//////////////////////////////////////////////////////////////////////////
void	WinpcapWrapper::SetFilter(std::string filter) {
    if (!filter.empty())
    {
        /* Retrieve the mask of the first address of the interface */
        //WinpcapWrapper::NetMask=((struct sockaddr_in *)(d->addresses->netmask))->sin_addr.S_un.S_addr;
        //  we suppose to be in a C class network ;-)
//        if(d->addresses != NULL)
//            /* Retrieve the mask of the first address of the interface */
//            WinpcapWrapper::NetMask=((struct sockaddr_in *)(d->addresses->netmask))->sin_addr.S_un.S_addr;
//        else
//            /* If the interface is without addresses we suppose to be in a C class network */
            WinpcapWrapper::NetMask=0xffffff;


        //compile the filter
        if(pcap_compile(WinpcapWrapper::adhandle, &(WinpcapWrapper::fcode), filter.c_str(), 1, WinpcapWrapper::NetMask) < 0)
        {
            fprintf(stderr,"\nError compiling filter: wrong syntax.\n");

            pcap_close(WinpcapWrapper::adhandle);
        }

        //set the filter
        if(pcap_setfilter(WinpcapWrapper::adhandle, &(WinpcapWrapper::fcode))<0)
        {
            fprintf(stderr,"\nError setting the filter\n");

            pcap_close(WinpcapWrapper::adhandle);

        }
    }

  ///////filters/////////////////////////////////////////////////////////



//    //compile the filter
//    if (pcap_compile(adhandle, &fcode, packet_filter, 1, netmask) <0 )
//    {
//        fprintf(stderr,"\nUnable to compile the packet filter. Check the syntax.\n");
//        /* Free the device list */
//        pcap_freealldevs(alldevs);
//        return -1;
//    }

//    //set the filter
//    if (pcap_setfilter(adhandle, &fcode)<0)
//    {
//        fprintf(stderr,"\nError setting the filter.\n");
//        /* Free the device list */
//        pcap_freealldevs(alldevs);
//        return -1;
//    }


}
//////////////////////////////////////////////////////////////////////////
//void	WinpcapWrapper::MonitorDump()
//{

//    if ( pcap_live_dump_ended(WinpcapWrapper::adhandle, 1)!= 0)
//        printf("the Dumping is stopped ");
//    else
//        printf("Dumping is in progress");
//}
//////////////////////////////////////////////////////////////////////////
void		WinpcapWrapper::DumpPacket(u_char *param, const struct pcap_pkthdr *header, const u_char *pkt_data) {
    pcap_dump((unsigned char *)dumpfile, header, pkt_data);

}
//////////////////////////////////////////////////////////////////////////
void		WinpcapWrapper::StopDump() {
    if (dumpfile != NULL)
    {
        pcap_dump_close(dumpfile);
        dumpfile = NULL;
    }

}
//////////////////////////////////////////////////////////////////////////
void		WinpcapWrapper::StartDump() {
    ////////////generate local time //////////////////////////////////////////////////////////////
    time_t rawtime;
    struct tm * timeinfo;
    char buffer [80];

    time ( &rawtime );
    timeinfo = localtime ( &rawtime );

    strftime (buffer,80,"%Y%m%d%H%M%S",timeinfo);
    //////////////////////////////////////////////////////////////////////////

    if(WinpcapWrapper::FileName.empty())
        WinpcapWrapper::FileName="Carnivore_"+static_cast<std::string>(buffer)+".pcap";//add time to file make it unique

    dumpfile = pcap_dump_open(adhandle,WinpcapWrapper::FileName.c_str());

    if(dumpfile==NULL)
    {
        fprintf(stderr,"\nError opening output file\n");
    }

}
//////////////////////////////////////////////////////////////////////////
int		WinpcapWrapper::GetDataLink() {
    datalink = pcap_datalink(adhandle);
    return datalink;
}
//////////////////////////////////////////////////////////////////////////
bool WinpcapWrapper::IsEthernet(){

    /* Check the link layer. We support only Ethernet for simplicity. */
    if(WinpcapWrapper::GetDataLink() != DLT_EN10MB)
    {
        fprintf(stderr,"\nThis program works only on Ethernet networks.\n");
        /* Free the device list */
        pcap_freealldevs(alldevs);
        return false;
    }
    else
    {
        return true;
    }
}
//////////////////////////////////////////////////////////////////////////
bool		WinpcapWrapper::SetMinToCopy(int size) {

    //sets the minimum number of bytes required to be received by the driver before
    //OnReceivePacket fires. Lowering this can increase response time,
    //but increases system calls which lowers program efficiency.

    if (pcap_setmintocopy(adhandle, size) == 0)
        return true;
    return false;
}
//////////////////////////////////////////////////////////////////////////
void		WinpcapWrapper::SetKernelBuffer(int bytes) {
    if (pcap_setbuff(adhandle, bytes) == 0)
        std::cout<<"buffer has be set to"<<bytes <<std::endl;
}

//////////////////////////////////////////////////////////////////////////
void		WinpcapWrapper::Close() {
    WinpcapWrapper::StopDump();
    attachedDevice.clear();
    if (adhandle != NULL)
    {
        pcap_breakloop(adhandle);
        pcap_close(adhandle);
        adhandle = NULL;
    }
}
//////////////////////////////////////////////////////////////////////////
std::string WinpcapWrapper::GetAttachedDevice() {
    return attachedDevice;
}
//////////////////////////////////////////////////////////////////////////
void	WinpcapWrapper::SetPacketCounter(int num){
    WinpcapWrapper::packetCounter = num;
}
//////////////////////////////////////////////////////////////////////////
void	WinpcapWrapper::SetFileName(std::string fileName){
    WinpcapWrapper::FileName = fileName;
}
//////////////////////////////////////////////////////////////////////////
void	WinpcapWrapper::SetFileSize(int fileSize){
    WinpcapWrapper::FileSize =fileSize;
}
//////////////////////////////////////////////////////////////////////////
void	WinpcapWrapper::SetBuffer(int bufferSize){
    WinpcapWrapper::BufferSize = bufferSize;
}

void WinpcapWrapper::SetPacketLength(int pLength)
{
    if(pLength > MIN_SNAPLEN && pLength < MAX_SNAPLEN )
        packetlength = pLength;
    else
        packetlength =MAX_SNAPLEN;
}

void WinpcapWrapper::SetTimeOut(int time)
{
    if(time > TIME_OUT_ZERO && time <TIME_OUT_TWENTY)
        timeOut=time;
    else
        timeOut = TIME_OUT_ONE;
}

void WinpcapWrapper::SetPromiscMode(int promiscFlag)
{
    if(promiscFlag == PCAP_CLOSE_FLAG_PROMISCUOUS)
        promiscMode =promiscFlag;
    else if(promiscFlag == PCAP_OPEN_FLAG_PROMISCUOUS)
        promiscMode =promiscFlag;
    else
        promiscMode = PCAP_OPEN_FLAG_PROMISCUOUS;
}
//WinpcapWrapper::WinpcapWrapper(QObject *parent):QObject(parent)
//{
////    decoder = new c_back(this);
//}

WinpcapWrapper *WinpcapWrapper::getInstance()
{
    static WinpcapWrapper* wpcap = 0;
    if (wpcap == 0) {
        wpcap = new WinpcapWrapper();
    }
    return wpcap;
}

//////////////////////////////////////////////////////////////////////////

