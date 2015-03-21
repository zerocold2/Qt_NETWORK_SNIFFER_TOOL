# Qt_NETWORK_SNIFFER_TOOL
This project written in c++ using qt gui library cross platform application, allowing capture network packets and analysis it depending on set of filters

Readable code written in June, 2013
reviewed by PHD acadamic professors into Sh.A "Sherouk academy"
Allowing cpature the whole packets passed throw the network card 
The main features is:
- Capture all network packets
- Decoding packets
- Filter incoming or outcoming packets according to set of filters such that ip, protocol, port.
- Save captured sessions
- Saved files compatible with wireshark network monitoring application
- Text searching inside the packet (Good Feature)
- Analysis the network traffic
- and many other features
 
Using LibPcap to deal with network card capture the packets 
control which packets are what we need

This application buitl on MVC technique the divide the application onto three parts
1- Model -> the drivers. compiling libraries, wrapper files
2- View -> the UI design and controls
3- Controls 
