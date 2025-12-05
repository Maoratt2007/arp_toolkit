int sock;

void usage()
{
  puts("usage:\t./arp-poison <interface> <gateway ip> <mac addr>");
  puts("ex:\t./arp-poison eth0 10.1.1.1 aa:bb:cc:dd:ee:ff");
  exit(1);
}

void cleanup()
{
	close(sock)
	exit(0)

}


