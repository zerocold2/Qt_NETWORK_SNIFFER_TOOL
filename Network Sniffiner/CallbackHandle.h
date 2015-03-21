#ifndef CALLBACKHANDLE_H
#define CALLBACKHANDLE_H
#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

#define SIZE_ETHERNET       14
#define ETHER_ADDR_LEN      6
#define ARP_REQUEST         1            /* ARP Request */
#define ARP_REPLY           2            /* ARP Reply   */
#define IP_HL(ip)               (((ip)->ip_vhl) & 0x0f) // & 0x0f) - is a logical 'AND' with 15 (0x0f) that only returns the lowest 4 bits.
#define IP_V(ip)                (((ip)->ip_vhl) >> 4)
#define ETHERTYPE_IP        0X0800
#define ETHERTYPE_ARP       0X0806
#define	ETHERTYPE_REVARP	0x8035
#ifdef __cplusplus
}
#endif

#include <QtCore>
#include <pcap.h>
#include "CallbackHandle.h"
#include <vector>
#include <stdio.h>
#include <string.h>
#include <winsock2.h>
#include <QStringList>
#include <QDebug>
#include <time.h>
#include <qlist.h>

/* Ethernet header */
struct sniff_ethernet {
       u_char  ether_dhost[ETHER_ADDR_LEN];    /* destination host address */
       u_char  ether_shost[ETHER_ADDR_LEN];    /* source host address */
       u_short ether_type;                     /* IP? ARP? RARP? etc */
};
/* 4 bytes IP address */
typedef struct ip_address
{
u_char byte1;
u_char byte2;
u_char byte3;
u_char byte4;
}ip_address;

/* IP header */
struct sniff_ip {
       u_char  ip_vhl;                 /* version << 4 | header length >> 2 */
       u_char  ip_tos;                 /* type of service */
       u_short ip_len;                 /* total length */
       u_short ip_id;                  /* identification */
       u_short ip_off;                 /* fragment offset field */
       #define IP_RF 0x8000            /* reserved fragment flag */
       #define IP_DF 0x4000            /* dont fragment flag */
       #define IP_MF 0x2000            /* more fragments flag */
       #define IP_OFFMASK 0x1fff       /* mask for fragmenting bits */
       u_char  ip_ttl;                 /* time to live */
       u_char  ip_p;                   /* protocol */
       u_short ip_sum;                 /* checksum */
       //struct  in_addr ip_src,ip_dst;  /* source and dest address */
       ip_address ip_src2,ip_dst2;
};
/* ARP Header, (assuming Ethernet+IPv4)            */
typedef struct arphdr {
   u_int16_t htype;    /* Hardware Type           */
   u_int16_t ptype;    /* Protocol Type           */
   u_char hlen;        /* Hardware Address Length */
   u_char plen;        /* Protocol Address Length */
   u_int16_t oper;     /* Operation Code          */
   u_char sha[6];      /* Sender hardware address */
   u_char spa[4];      /* Sender IP address       */
   u_char tha[6];      /* Target hardware address */
   u_char tpa[4];      /* Target IP address       */
}arphdr_t;

   /*ICMP*/
typedef struct icmpheader
{
 u_char  type;
 u_char  code;
 u_short checksum;
 u_short id;
 u_short sequence;
 u_short data;
} icmpheader;


/* TCP header */
typedef u_int tcp_seq;
struct sniff_tcp {
       u_short th_sport;               /* source port */
       u_short th_dport;               /* destination port */
       tcp_seq th_seq;                 /* sequence number */
       tcp_seq th_ack;                 /* acknowledgement number */
       u_char  th_offx2;               /* data offset, rsvd */
       #define TH_OFF(th)      (((th)->th_offx2 & 0xf0) >> 4)
       u_char  th_flags;
       #define TH_FIN  0x01
       #define TH_SYN  0x02
       #define TH_RST  0x04
       #define TH_PUSH 0x08
       #define TH_ACK  0x10
       #define TH_URG  0x20
       #define TH_ECE  0x40
       #define TH_CWR  0x80
       #define TH_FLAGS        (TH_FIN|TH_SYN|TH_RST|TH_ACK|TH_URG|TH_ECE|TH_CWR)
       u_short th_win;                 /* window */
       u_short th_sum;                 /* checksum */
       u_short th_urp;                 /* urgent pointer */
};

/* UDP header*/
typedef struct udp_header
{
   u_short sport;			// Source port
   u_short dport;			// Destination port
   u_short len;			// Datagram length
   u_short crc;			// Checksum
}udp_header;




class c_back:public QObject{

public:
    c_back(QObject *parent=0);
    QString call_back(u_char *param, const struct pcap_pkthdr *header, const u_char *pkt_data);
signals:
    void packetArived(QString);
};

#endif // CALLBACKHANDLE_H
