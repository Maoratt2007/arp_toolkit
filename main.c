#include <stdio.h>

void banner()
{
	printf("------------------------------------\n");
	printf("         ARP FORGE TOOLKIT         \n");
	printf("------------------------------------\n");
}

void show_menu()
{
	printf("1 - Offensive Mode\n");
	printf("2 - ARP Monitor\n");
	printf("3 - Exit\n");
}


int main()
{
	char option = 0;
	banner();

	while(option != '3')
	{
		show_menu();
		option = getchar();
		getchar();
		printf("User entered: %c\n",option);
	}

	return 0;
}