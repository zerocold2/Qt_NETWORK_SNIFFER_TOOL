#include "Adapter.h"
using namespace NetworkWrapper;
Adapter::Adapter()
{
    _name = GetName();
    _description = GetDescription();
    _address = GetAddress();
    _netmask = GetNetmask();
}
Adapter::~Adapter(void) {
    //close();
}
Adapter::Adapter(std::string name, std::string description, std::string address, std::string netmask)
{
    _name = name;
    _description = description;
    _address = address;
    _netmask = netmask;
}
void Adapter::SetName( std::string name) {
    _name = name;
}
std::string Adapter::GetName() {
    return _name;
}
void Adapter::SetDescription(std::string description) {
    _description=description;
}
std::string Adapter::GetDescription() {
    return _description;
}
void Adapter::SetAddress(std::string address) {
    _address=address;
}
std::string Adapter::GetAddress() {
    return _address;
}
void Adapter::SetNetmask(std::string netmask) {
    _netmask=netmask;
}
std::string Adapter::GetNetmask() {
    return _netmask;
}
