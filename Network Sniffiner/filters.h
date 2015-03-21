#ifndef FILTERS_H
#define FILTERS_H

#include <stdio.h>
#include <qlist.h>
#include <cstring>
#include <string>
#include <cstdlib>
#include <utility>
#include <set>
#include <algorithm>
#include <map>
using namespace std;

#define mp(x,y) make_pair((x),(y))
typedef map<string, bool> msb;

class Filters
{

public:
    std::string ip, n_port,dsthost;
    bool tcp,udp,arp,smtp,rarp,ftp,http,https,dhcp,dns,srcip,dstip,srcordstip,
          ortcp,andtcp,orudp,andudp,orsmtp,andsmtp,orftp,andftp,orhttp,andhttp,
          orhttps,andhttps,ordns,anddns,ordhcp,anddhcp,orarp,andarp,orrarp,andrarp,
            tcpport,udpport,srcport,dstport,srcordstport;


    Filters();
    std::string filter_string();
};

#endif // FILTERS_H
