#include "menu.h"

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

void handle_user(char option)
{
	switch(option){
	case 1:
		control_attack();
	}

}

void menu_controller()
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