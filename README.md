# MAC Address Spoofer

## Project Overview
This project provides a tool to spoof (change) the MAC address of your network interface on a Linux system. The MAC (Media Access Control) address is a unique identifier assigned to network interfaces for communications at the data link layer of a network segment. Changing the MAC address can be useful for privacy, security testing, and other purposes.

## How It Works
The program generates a random MAC address and changes the MAC address of the specified network interface using system calls and ioctl operations. Here’s an overview of the main components:

### Key Concepts
- **MAC Address**: A unique identifier assigned to network interfaces for communications at the data link layer.
- **Random MAC Generation**: The tool generates a random MAC address using the random number generator.
- **Socket Programming**: The program opens a socket to communicate with the network interface.
- **ioctl Operations**: The `ioctl` system call is used to set the MAC address of the network interface.

### Project Files
- **mac_spoofer.c**: The main source file containing the logic for generating and changing the MAC address.
- **Makefile**: A makefile to compile the project.

### Code Breakdown
#### mac_spoofer.c
```c
#define _GNU_SOURCE
#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>
#include <netinet/in.h>
#include <sys/socket.h>
#include <assert.h>
#include <errno.h>
#include <stdbool.h>
#include <sys/ioctl.h>
#include <net/if.h>
#include <net/if_arp.h>

typedef unsigned char int8;
typedef unsigned short int int16;
typedef unsigned int int32;
typedef unsigned long int int64;

struct Mac {
    int64 addr : 48;
};

bool chmac(char *inf, struct Mac mac) {
    struct ifreq ir;
    int fd = socket(AF_INET, SOCK_DGRAM, IPPROTO_IP), ret;
    assert(fd > 0);

    strncpy(ir.ifr_name, inf, IFNAMSIZ - 1);
    ir.ifr_hwaddr.sa_family = ARPHRD_ETHER;
    memcpy(ir.ifr_hwaddr.sa_data, &mac, 6);

    ret = ioctl(fd, SIOCSIFHWADDR, &ir);
    close(fd);
    return (!ret) ? true : false;
}

struct Mac genMac() {
    int64 a, b;
    struct Mac mac;
    a = random();
    b = random();
    mac.addr = ((a * b) % 281474976710656);
    return mac;
}

int main(int argc, char *argv[]) {
    struct Mac mac;
    char *inf;
    if (argc < 2) {
        fprintf(stderr, "Usage: %s INTERFACE\n", *argv);
        return -1;
    } else {
        inf = argv[1];
    }
    srand(getpid());
    mac = genMac();
    if (chmac(inf, mac)) {
        printf("New MAC address: %012lx\n", (long)mac.addr);
    } else {
        perror("Failed to change MAC address");
        assert(0);
    }
    return 0;
}
```
###Usage
##To compile
```
make
```
##To Execute
```
sudo ./altermac <interface>
```

