#include <stdio.h>      
#include <sys/types.h>
#include <ifaddrs.h>
#include <netinet/in.h> 
#include <string.h> 
#include <arpa/inet.h>
#include <string>

using namespace std;

string find_ip_addr() {
    struct ifaddrs * ifAddrStruct=NULL;
    struct ifaddrs * ifa=NULL;
    void * tmpAddrPtr=NULL;

    getifaddrs(&ifAddrStruct);
    string rej="127.0.0.1";
    for (ifa = ifAddrStruct; ifa != NULL; ifa = ifa->ifa_next) {
        if (!ifa->ifa_addr) {
            continue;
        }
        if (ifa->ifa_addr->sa_family == AF_INET) { // check it is IP4
            // is a valid IP4 Address
            tmpAddrPtr=&((struct sockaddr_in *)ifa->ifa_addr)->sin_addr;
            char addressBuffer[INET_ADDRSTRLEN];
            inet_ntop(AF_INET, tmpAddrPtr, addressBuffer, INET_ADDRSTRLEN);
            
            if(rej.compare(string(addressBuffer)) == 0)
                continue;
            else{
                rej=string(addressBuffer);
                //printf("%s IP Address %s\n", ifa->ifa_name, addressBuffer); 
                break;    
            }
            
        }
    }
    if (ifAddrStruct!=NULL) freeifaddrs(ifAddrStruct);
    return rej;
}