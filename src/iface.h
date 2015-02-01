#ifndef IFACE_H
#define IFACE_H

#define _GNU_SOURCE     /* To get defns of NI_MAXSERV and NI_MAXHOST */
#include <stdio.h>
#include <stdlib.h>
#include <ifaddrs.h>
#include <netdb.h>
#include <linux/if.h>
#include <sys/socket.h>
#include <sys/ioctl.h>
#include <linux/if_link.h>

#define HW_ADDR_LENGTH 18
#define IFACE_NAME_LENGTH 10
#define MAX_IFACE 10

struct iface{
    char *name;
    char *inet_addr;
    char *inet6_addr;
    char *hw_addr;
    char *broad_addr;
    char *inet_mask;
    char *inet6_mask;
    unsigned char running;
    unsigned char updown;
    unsigned int flags;
    unsigned int mtu;
    unsigned int metric;
    unsigned int tx_bytes;
    unsigned int rx_bytes;
    unsigned int tx_packets;
    unsigned int rx_packets;
};

void free_iface(struct iface *ifa);
void init_iface(struct iface *ifa);
int get_info_interface(struct iface* ifa, const char *name_iface);
char ** get_list_interfaces();
char * get_mac(const char *name_iface);

#endif
