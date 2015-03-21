#pragma once
#ifndef ADAPTER_H
#define ADAPTER_H
#include <string>

namespace NetworkWrapper {

class Adapter
{
private:
	
    std::string _name;//for example "\Device\NPF_{xxxxx}"
    std::string _description;//for example "3com ethernete pci"
    std::string _address;//ip-address "192.168.1.1"
    std::string _netmask;// 255.255.255.255
public:
    Adapter();
    ~Adapter(void);
    Adapter(std::string name, std::string description, std::string address, std::string netmask);
    void SetName( std::string name);
    std::string GetName();
    void SetDescription(std::string description);
    std::string GetDescription();
    void SetAddress(std::string address);
    std::string GetAddress();
    void SetNetmask(std::string netmask);
    std::string GetNetmask();
};

}
#endif
