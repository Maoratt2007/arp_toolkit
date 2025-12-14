#pragma once 
#include <stdio.h>
#include <stdint.h>// uint8_t, uint16_t
#include <string.h>
#include <stdlib.h>
#include <unistd.h> //read close write
#include <sys/socket.h> //socket, bind, liste, accept
#include <arpa/inet.h>//htons
#include <linux/if_ether.h>//ETH_P_ARP- ETHER TYPE ARP IN LINUX
#include <linux/if_packet.h>// struct sockaddr_ll
#include <net/if.h>// if_nametoindex()


#define MAC_LEN (6)
#define IP_LEN (4)
#define ARP_HTYPE (1)
#define ARP_PTYPE (0x0800)
#define ARP_HLEN (6)
#define ARP_PLEN (4)
#define ARP_REPLY (2)
#define ARP_PACKET_SIZE (60)
#define PACKET_SEND_COUNT (10000)

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
	uint8_t source_mac[MAC_LEN];
	uint8_t source_ip[IP_LEN]; 
	uint8_t target_mac[MAC_LEN];
	uint8_t target_ip[IP_LEN];

} arp_addrs_t;

void arp_attack_banner();
void show_arp_attack_menu();
void usage();
void cleanup(int sock);
arp_addrs_t init_addrs();
int open_socket();
void set_ether_headers(arp_addrs_t arp_addrs, uint8_t *reply_arp);
void set_arp_headers( arp_header_t *arp, arp_addrs_t arp_addrs );
void set_socket(struct sockaddr_ll * addr, arp_addrs_t arp_addrs);
void send_arp_packets(int sock,uint8_t* reply_arp,struct sockaddr_ll addr, int count);
void control_attack();
void arp_attack_handle_user(int option_int);
void arp_attack_menu_controller();