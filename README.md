# RTStreamHub
RTStreamHub: A headless GNSS data streaming hub with NTRIP TLS support

The forwarding, caching, and transmission of real-time data streams are crucial components of GNSS data processing. Various communication protocols, such as the transmission control protocol (TCP), the networked transport of RTCM via internet protocol (NTRIP), and serial ports, play a significant role in data reception and transmission. Receiver data is transmitted to the server through a data transfer unit (DTU) via the TCP. The server then forwards or pushes the data stream to an NTRIP caster, or alternatively, real-time precise products are delivered to users by organizations such as the International GNSS Service (IGS) through the NTRIP. Particularly, the adoption of NTRIP TLS (transport layer security) enhances data confidentiality for users. However, the reception of NTRIP TLS data on the user side involves more complex procedures. 

RTStreamHub, an open-source, headless C/C++ software that operates on Linux servers, facilitates the forwarding, caching, and transmission of real-time data streams. Built on RTKLIB, RTStreamHub has been further upgraded to support NTRIP, with enhanced compatibility for NTRIP TLS and the use of port 443 for TCP encryption, ensuring secure data reception. This development enables users to conveniently receive real-time satellite products, such as the high accuracy service (HAS) provided by European Galileo.

CONTRIBUTOR

   Core developers:

   * Runzhi Zhang (zhangrunzhi@ntsc.ac.cn)
   * Rui Tu ( turui-2004@126.com)
   * Xiaochun Lu (luxc@ntsc.ac.cn)

CONTACT
   QQ Groups: 651080705 (HASPPP)
   Emails: zhangrunzhi@ntsc.ac.cn; turui-2004@126.com; luxc@ntsc.ac.cn
