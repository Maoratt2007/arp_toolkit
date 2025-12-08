#pragma once 
#include <stdio.h>
#include <stdint.h>// uint8_t, uint16_t
#include <string.h>
#include <stdlib.h>
#include <unistd.h> //read close write
#include <sys/socket.h> //socket, bind, liste, accept
#include <arpa/inet.h>//htons
#include <linux/if_ether.h>//ETH_P_ARP- ETHER TYPE ARP IN LINUX


#define MAC_LEN (6)
#define IP_LEN (4)

typedef struct arp_header_s {
	uint16_t htype;
	uint16_t ptype;
	uint8_t hlen;
	uint8_t plen;
	uint16_t opcode;
	uint8_t sender_mac[MAC_LEN];
	uint8_t sender_ip[IP_LEN];
	uint8_t target_mac[MAC_LEN];
	uint8_t target_ip[IP_LEN];
} arp_header_t;

typedef struct arp_addrs_s {
	uint8_t source_mac[6];
	uint8_t source_ip[4]; 
	uint8_t target_mac[6];
	uint8_t target_ip[4];

} arp_addrs_t;

void usage();
void cleanup(int sock);
arp_addrs_t init_addrs();
int open_socket();
void set_ether_headers(arp_addrs_t arp_addrs, uint8_t *reply_arp);
void control_attack();