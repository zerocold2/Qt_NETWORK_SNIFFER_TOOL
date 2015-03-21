#include "filters.h"

Filters::Filters()
{
    /*
      initial assign all variables to false
    */
    tcp=udp=arp=smtp=rarp=ftp=http=https=dhcp=dns=srcip=dstip=srcordstip=
    ortcp=andtcp=orudp=andudp=orsmtp=andsmtp=orftp=andftp=orhttp=andhttp=
    orhttps=andhttps=ordns=anddns=ordhcp=anddhcp=orarp=andarp=orrarp=andrarp=
            tcpport=udpport=srcport=dstport=srcordstport=false;
}

std::string Filters::filter_string()
{
    msb ortst,andtst,tst;   // initialize tree structure (STL) for standard ports
    int cnt=0;  //counter to know how many packets for each port
    string sfilter="",stst="",sortst="",sortst1="",sandtst="",sandtst1="",sip="",sport="";

    // assign variables to tree structure from string,bool types
    ortst["ftp"]=orftp;
    ortst["smtp"]=orsmtp;
    ortst["http"]=orhttp;
    ortst["https"]=orhttps;
    ortst["dhcp"]=ordhcp;
    ortst["udp"]=orudp;
    ortst["dns"]=ordns;
    ortst["arp"]=orarp;
    ortst["rarp"]=orrarp;
    ortst["tcp"]=ortcp;

    // assign variables to tree structure from string,bool types
    andtst["ftp"]=andftp;
    andtst["smtp"]=andsmtp;
    andtst["udp"]=andudp;
    andtst["http"]=andhttp;
    andtst["https"]=andhttps;
    andtst["dns"]=anddns;
    andtst["dhcp"]=anddhcp;
    andtst["arp"]=andarp;
    andtst["rarp"]=andrarp;
    andtst["tcp"]=andtcp;

    // assign variables to tree structure from string,bool types
    tst["ftp"]=ftp;
    tst["smtp"]=smtp;
    tst["udp"]=udp;
    tst["http"]=http;
    tst["https"]=https;
    tst["dns"]=dns;
    tst["dhcp"]=dhcp;
    tst["arp"]=arp;
    tst["rarp"]=rarp;
    tst["tcp"]=tcp;

    //loop over var type of "or ports"
    for(msb::const_iterator it=ortst.begin();it!=ortst.end();++it){
        if(it->second==true){
           if(it->first=="udp"||it->first=="arp"||it->first=="tcp"||it->first=="rarp"||it->first=="dns")
               sortst1+=" or "+it->first;
           else
               sortst+=" or port "+it->first;
        }
    }

    for(msb::const_iterator it=andtst.begin();it!=andtst.end();++it){
        if(it->second==true){
           if(it->first=="udp"||it->first=="arp"||it->first=="tcp"||it->first=="rarp"||it->first=="dns")
               sandtst1+=" and "+it->first;
           else
               sandtst+=" and port "+it->first;
        }
    }

    for(msb::const_iterator it=tst.begin();it!=tst.end();++it){
        if(it->second==true&&!andtst[it->first]&&!ortst[it->first]){
            if(it->first=="udp"||it->first=="arp"||it->first=="tcp"||it->first=="rarp"||it->first=="dns"){
                cnt++;
                stst=it->first;
            }else{
                cnt++;
                stst="port "+it->first;
            }
            if(cnt>1)break;
        }
    }

    if(!srcip&&!dstip&&!srcordstip&&cnt==1)sip=stst;
    if(sip=="dns")sip="port 53";
    if(srcip&&!dstip)sip="src "+ip;     //src ip;
    if(dstip&&!srcip)sip="dst "+ip;
    if(srcordstip)sip=ip;
    if(dsthost!="")sip+" and dst "+dsthost;

    if((srcport)&&tcpport)
        sport="tcp src port "+n_port;
    else if((dstport)&&tcpport)
        sport="tcp dst port "+n_port;
    else if (srcordstport&&tcpport)
        sport="port "+n_port;
    else if(srcordstport&&udpport)
        sport="udp port "+n_port;
    else if(srcport&&udpport)
        sport="udp src "+n_port;
    else if (dstport&&udpport)
        sport="udp dst "+n_port;

    if(sfilter==" ")
        sfilter=sport;
    else if(sport!="")
        sfilter=" "+sip+sortst+sortst1+sandtst+sandtst1+" and "+sport;
    else
        sfilter=" "+sip+sortst+sortst1+sandtst+sandtst1;

    return sfilter;
}
