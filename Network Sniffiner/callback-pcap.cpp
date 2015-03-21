#ifdef _MSC_VER
/*
 * we do not want the warnings about the old deprecated and unsecure CRT functions
 * since these examples can be compiled under *nix as well
 */
#define _CRT_SECURE_NO_WARNINGS
#endif

#define HAVE_REMOTE
//#include <QtCore/QCoreApplication>
#include "CallbackHandle.h"

using namespace std;
int cnt=0;

c_back::c_back(QObject *parent):QObject(parent)
{
}

QString c_back::call_back(u_char *param, const pcap_pkthdr *header, const u_char *pkt_data){
    QStringList list;
    QString srcmac="",dstmac="",srcip,desip,srcport,desport,pcol="",pktlen,n,tim,icmptype,icmpcode,icmpid,icmpseq;
    cnt++;
    struct tm *ltime;
    char timestr[16];
    const struct sniff_ip *ip;
    const struct sniff_tcp *tcp;
    const struct sniff_ethernet *ethernet;
    udp_header *uh;
    icmpheader *icmp;
    arphdr_t *arpheader = NULL;
    u_short u_sport,u_dport,t_sport,t_dport,id,seq;
    const char *payload;
    u_int ip_len;
    u_int tcp_len;
    u_int payload_len;
    time_t local_tv_sec;
    char srcm[15],dstm[15];
    (VOID)(param);
    local_tv_sec=header->ts.tv_sec;
    ltime=localtime(&local_tv_sec);
    strftime(timestr,sizeof timestr,"%H:%M:%S",ltime);
    ethernet=(struct sniff_ethernet*)(pkt_data);            //ether
    ip=(struct sniff_ip*)(pkt_data+SIZE_ETHERNET);          //ip
    ip_len=IP_HL(ip)*4;                                     //iplen
    tcp=(struct sniff_tcp*)(pkt_data+SIZE_ETHERNET+ip_len); //tcp
    tcp_len=TH_OFF(tcp)*4;                                  //tcpLen
    uh = (udp_header*)((u_char*)ip+ip_len);                 //udp
    arpheader = (struct arphdr*)(pkt_data+SIZE_ETHERNET);   //arp
    icmp=(icmpheader *)(pkt_data);                          //ICMP
    u_sport = ntohs( uh->sport );                           //"ntohs BigEndian" src_port for udp
    u_dport = ntohs( uh->dport );                           //dest_port for udp
    t_sport=ntohs(tcp->th_sport);                           //src_port for tcp
    t_dport=ntohs(tcp->th_dport);                           //dest_port for tcp
    memcpy(&id,icmp+4,2);                                   //icmp id
    memcpy(&seq,icmp+6,2);                                  //icmp seq
    for(int i=0;i<6;i++){
        sprintf(srcm,"%02X:", arpheader->sha[i]);
        srcmac+=srcm;                                       //srcmac for arp
        sprintf(dstm,"%02X:",arpheader->tha[i]);
        dstmac+=dstm;                                       //destmac for arp
    }
    /*
     * CASTING
     */
    n=QString::number(cnt); //count
    tim=timestr;
    pktlen=QString::number(header->len);    //packet length
    srcip=QString::number(ip->ip_src2.byte1)+"."+QString::number(ip->ip_src2.byte2)+"."+QString::number(ip->ip_src2.byte3)+"."+QString::number(ip->ip_src2.byte4);
    desip=QString::number(ip->ip_dst2.byte1)+"."+QString::number(ip->ip_dst2.byte2)+"."+QString::number(ip->ip_dst2.byte3)+"."+QString::number(ip->ip_dst2.byte4);
    icmptype=QString::number(icmp->type);
    icmpcode=QString::number(icmp->code);
    icmpid=QString::number(ntohs(id));
    icmpseq=QString::number(ntohs(seq));


    if(ethernet->ether_type==htons(ETHERTYPE_IP)){
        if(ip->ip_p==IPPROTO_TCP){  //TCP
            if(t_sport==21||t_sport==20||t_dport==21||t_dport==20)pcol="FTP";
            if(t_sport==25||t_sport==587||t_dport==25||t_dport==587)pcol="SMTP";
            if(t_sport==43||t_dport==43)pcol="WHOIS";
            if(t_sport==53||t_dport==53)pcol="DNS";
            if(t_sport==57||t_dport==57)pcol="MTP";
            if(t_sport==70||t_dport==70)pcol="GOPHER";
            if((t_sport>=71&&t_sport<=74)||(t_dport>=71&&t_dport<=74))pcol="NETRJS";
            if(t_sport==79||t_dport==79)pcol="FP";
            if(t_sport==80||t_sport==8080||t_dport==80||t_dport==8080)pcol="HTTP";
            if(t_sport==101||t_dport==101)pcol="NIC";
            if(t_sport==102||t_dport==102)pcol="ISO-TSAP";
            if(t_sport==107||t_dport==107)pcol="R-TELNET";
            if(t_sport==110||t_dport==110)pcol="POP3";
            if(t_sport==115||t_dport==115)pcol="SFTP";
            if(t_sport==119||t_dport==119)pcol="NNTP";
            if(t_sport==143||t_dport==143)pcol="IMAP";
            if(t_sport==443||t_dport==443)pcol="HTTPS";
            if(t_sport==445||t_dport==445)pcol="SMB";
            if(t_sport==512||t_dport==512)pcol="REXEC";
            if(t_sport==513||t_dport==513)pcol="RLOGIN";
            if(t_sport==514||t_dport==514)pcol="SHELL";
            if(t_sport==540||t_dport==540)pcol="UUCP";
            if(t_sport==548||t_dport==548)pcol="AFP";
            if(t_sport==648||t_dport==648)pcol="RRP";
            if(t_sport==700||t_dport==700)pcol="EPP";
            if(t_sport==701||t_dport==701)pcol="LMP";
            if(t_sport==702||t_dport==702)pcol="IRIS";
            if(t_sport==706||t_dport==706)pcol="SILC";
            if(t_sport==711||t_dport==711)pcol="CISCO";
            if(t_sport==712||t_dport==712)pcol="TBRPF";
            if(t_sport==847||t_dport==847)pcol="DHCP";
            if(t_sport==903||t_sport==904)pcol="VMWARE";
            if(t_sport==993||t_dport==993)pcol="IMAPS";
            if(t_sport==995||t_dport==995)pcol="POP3S";
            //
            if(pcol=="")pcol="TCP";
            srcport=QString::number(t_sport);
            desport=QString::number(t_dport);
            list<<n<<tim.toUtf8().data()<<pktlen<<srcip<<srcport<<pcol<<desip<<desport;
        }//UDP
        if(ip->ip_p==IPPROTO_UDP){
            if(u_sport==1900||u_dport==1900)pcol="SSDP";
            if(u_sport==67||u_sport==68)pcol="BOOTP/DHCP";
            if(u_sport==69||u_dport==69)pcol="TFTP";
            if(u_sport==123||u_dport==123)pcol="NTP";
            if(u_sport==161||u_dport==161)pcol="SNMP";
            if(u_sport==513||u_dport==513)pcol="WHO";
            if(u_sport==520||u_dport==520)pcol="RIP";
            if(u_sport==901)pcol="VMWARE";
            if(u_sport==53||u_dport==53)pcol="DNS";
            if(u_sport==137||u_dport==137)pcol="NBNS";
            if(u_sport==138||u_dport==138)pcol="NBDS";
            if(u_sport==139||u_dport==139)pcol="NBSS";
            if(u_sport==1900||u_dport==1900)pcol="SSDP";
            if(u_sport==5355||u_dport==5355)pcol="LLMNR";
            if(u_sport==5678||u_dport==5678)pcol="MNDP";
            //
            if(pcol=="")pcol="UDP";
            srcport=QString::number(u_sport);
            desport=QString::number(u_dport);
            list<<n<<tim.toUtf8().data()<<pktlen<<srcip<<srcport<<pcol<<desip<<desport;

        }
        //ICMP
        if(ip->ip_p==IPPROTO_ICMP){
            pcol="ICMP";
            list<<n<<tim.toUtf8().data()<<pktlen<<srcip<<icmpid<<pcol<<desip<<icmpseq;
        }
    }
    else if(ethernet->ether_type==htons(ETHERTYPE_ARP)){
        pcol="ARP";
        list<<n<<tim.toUtf8().data()<<pktlen<<srcmac.toUtf8().data()<<" "<<pcol<<dstmac.toUtf8().data()<<" ";
    }
    else if (ethernet->ether_type==htons(ETHERTYPE_REVARP)){
        pcol="RARP";
        list<<n<<tim.toUtf8().data()<<pktlen<<srcmac.toUtf8().data()<<" "<<pcol<<dstmac.toUtf8().data()<<" ";
    }


    QString itm=list.join("\t");
    if(pcol!=""){
        qDebug()<<itm;
        return itm;
    }
}
