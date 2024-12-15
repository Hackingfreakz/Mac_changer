#define _GNU_SOURCE
#include<stdio.h>
#include<unistd.h>
#include<string.h>
#include<stdlib.h>
#include<netinet/in.h>
#include<sys/socket.h>
#include<assert.h>
#include<errno.h>
#include<stdbool.h>
#include<sys/ioctl.h>
#include<net/if.h>
#include<net/if_arp.h>
  
typedef unsigned char int8;
typedef unsigned short int int16;
typedef unsigned int int32;
typedef unsigned long int int64;

struct Mac{
    int64 addr:48;
};

bool chmac(char *inf,struct Mac mac){
  struct ifreq ir;

  int fd=socket(AF_INET,SOCK_DGRAM,IPPROTO_IP),ret;
  assert(fd>0);

  strncpy(ir.ifr_ifrn.ifrn_name,(char *)inf, (IFNAMSIZ-1));
  ir.ifr_ifru.ifru_hwaddr.sa_family=ARPHRD_ETHER;
  memcpy(ir.ifr_ifru.ifru_hwaddr.sa_data,&mac,6);
  //printf("%s\n",ir.ifr_ifru.ifru_hwaddr.sa_data);
  ret=ioctl(fd,SIOCSIFHWADDR,&ir);
  close(fd);
  return (!ret)? true : false;
}

struct Mac genMac(){
    int64 a,b;
    struct Mac mac;
    a=(long)random();
    b=(long)random();
    mac.addr=((a*b)%281474976710656);
    return mac;
}

int main(int argc,char *argv[]){
    struct Mac mac;
    //int8 *inf;
    char *inf;
    if(argc<2){
      fprintf(stderr,"Usage : %s INTERFACE\n",*argv);
      return -1;
    }
    else
      inf=argv[1];
      //inf=(int8 *)argv[1];
    srand(getpid());
    mac=genMac();
    if(chmac(inf,mac))
      printf("%lx\n",(long)mac.addr);
    else
      assert_perror(errno);
    return 0;
}
