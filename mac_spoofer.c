#define _GNU_SOURCE
#include<stdio.h>
#include<unistd.h>
#include<string.h>
#include<stdlib.h>
#include<assert.h>
#include<errno.h>

typedef unsigned char int8;
typedef unsigned short int int16;
typedef unsigned int int32;
typedef unsigned long int int64;

struct Mac{
    int64 addr:48;
};
    
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
    srand(getpid());
    mac=genMac();
    printf("%lx\n",(long)mac.addr);
    return 0;
}
    
