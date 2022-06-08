#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
//#include <Windows.h>
#define MAP 16
// Function
#define MONEY_LIMIT 100000
int Dice();
int PM(int a);
void Local();
void User_turn(int userIndex);
void Buy_hotel();
void print_map();
// global variable
char local[MAP][30] = {"Start","Korea","USA","Japan","China","England","**Island**","Germany","Argentina","Greece","France","Sweden","Australia","Turkey","Switzerland","Egypt"};
int own_local[MAP] = {3,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};
int own_hotel[MAP] = {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};
int* p = &own_local[0];
int* pht = &own_hotel[0];
char own[30], loc[30];
int dice1,dice2,temp;
int money = 10000;
int i=0,uj=0,cj=0;
int cho,cho2,cho3;
int ure;
int pass_money;
int moneyLimit = 100000;
int islandCount[2] = {0,0};
int userPosition[2] = {0,0};
int userMoney[2] = {10000,10000};
char showUser1Pos[MAP][30] = {"0",};
char showUser2Pos[MAP][30] = {"0",};

int main(void)
{
	printf("** BlueMarble **\n\nPress Any Key to Game Start");
	getchar();
	srand(time(NULL));

	while(1){
		dice1 = dice2 = 0;
		system("cls");
		print_map();
		User_turn(0);
		print_map();
		User_turn(1);
	}
	return 0;
}
int Dice() {
	int a;
	a = rand()%6+1;
	return a;
}
int PM(int a) {
	int result;
	if (a == 1) {
		result = uj*150+(uj*pht[uj]*350)*1.5;
	} else if (a == 2) {
		result = cj*150+(uj*pht[cj]*350)*1.5;
	} else {
		result = i*150+(uj*pht[i]*350)*1.5;
	}
	return result;
}
void Local() {
	strcpy(loc, local[uj]);
}

void Buy_hotel() {
	system("cls");
	puts("=================================================");
	if(money >= uj*150) {
		pht[uj] = 1;
		money -= uj*150;
		printf("          You Build Hotel!\n         Remained Money : %d won\n",money);
	} else {
		puts("       You don't have enough money!");
		ure = 1;
	}
	puts("=================================================");
	getchar();
}

void print_map()
{
	for (int jj=0; jj < MAP; jj++){
		strcpy(showUser1Pos[jj], " ");
		strcpy(showUser2Pos[jj], " ");
	}
	strcpy(showUser1Pos[userPosition[0]], "1");
	strcpy(showUser2Pos[userPosition[1]], "2");
	printf("========================================================================================================\n");
	printf("##  %s[%s][%s]      %s[%s][%s]        %s[%s][%s]       %s[%s][%s]         %s[%s][%s]  ##\n",
	local[8],  showUser1Pos[8],showUser2Pos[8], local[9], showUser1Pos[9],showUser2Pos[9],
	local[10], showUser1Pos[10],showUser2Pos[10], local[11],showUser1Pos[11],showUser2Pos[11],
	local[12], showUser1Pos[12],showUser2Pos[12]);
	printf("##                                                                                                    ##\n");
	printf("##    %s[%s][%s]                                                                     %s[%s][%s]  ##\n",
	local[7], showUser1Pos[7],showUser2Pos[7], local[13], showUser1Pos[13],showUser2Pos[13]);
	printf("##                                                                                                    ##\n");
	printf("## %s[%s][%s]                                                                %s[%s][%s]  ##\n",
	local[6], showUser1Pos[6],showUser2Pos[6], local[14], showUser1Pos[14],showUser2Pos[14]);
	printf("##                                                                                                    ##\n");
	printf("##    %s[%s][%s]                                                                      %s[%s][%s]  ##\n",
	local[5], showUser1Pos[5],showUser2Pos[5], local[15], showUser1Pos[15],showUser2Pos[15]);
	printf("##                                                                                                    ##\n");
	printf("##      %s[%s][%s]        %s[%s][%s]       %s[%s][%s]           %s[%s][%s]             %s[%s][%s]  ##\n",
		local[4],showUser1Pos[4],showUser2Pos[4], local[3],showUser1Pos[3],showUser2Pos[3],
		local[2],showUser1Pos[2],showUser2Pos[2], local[1],showUser1Pos[1],showUser2Pos[1],
		local[0],showUser1Pos[0],showUser2Pos[0]);
	printf("========================================================================================================\n");
}

void User_turn(int userIndex) {
	do
	{
		uj = userPosition[userIndex];
		money = userMoney[userIndex];
		Local();
		puts("=================================================");
		printf(
			"[Player %d Your turn.]\n\n"
			"Your Money : %d원\n"
			"You are in : %s(%d)\n",
			userIndex+1, money,loc,uj
		);
		puts("=================================================");
		puts("Press any key to try dice.");
		getchar();
		dice1 = Dice();
		dice2 = Dice();
		puts("=================================================");
		printf("                = Dice Result=\n"
		  "               [%d]+[%d] = [%d]\n",dice1,dice2,dice1+dice2);
		puts("=================================================");
		getchar();

		if (dice1 == dice2){
		    puts("=================================================");
    		puts("Dice Double, You can try one more time!");
			if (islandCount[userIndex] != 0 ){
				islandCount[userIndex] = 0;
				puts("You can get away from island!.");
			}
    		getchar();
    		puts("=================================================");
		}
		else if (islandCount[userIndex] != 0) {
			puts("=================================================");
    		printf("You are in island. You must refresh %d turn.\n", islandCount[userIndex]--);
    		getchar();
    		puts("=================================================");
			return;
		}
		temp = dice1+dice2;
		uj += temp;

    	if( uj > MAP-1 ) {
			uj = uj%MAP;
    		puts("=================================================");
    		printf("  You passed the starting poine. You got 700 won .\n");
    		puts("=================================================");
    		money += 700;
    		getchar();
    	}
    	Local();
		userPosition[userIndex] = uj;
		userMoney[userIndex] = money;
	} while(dice1 == dice2);

	print_map();
	if ( uj == 6 ){
		islandCount[userIndex] = 3;
		puts("=================================================");
		puts("You are in island now. you should refresh 3 turn by now.");
		getchar();
		puts("=================================================");
		getchar();
		return;
	}

	// 통행료 지불
	// 혹은 내땅
	if (userIndex == 0 && p[uj] == 2){
		// pay money to User 2
		puts("=================================================");
		printf("%s is for Player %d.\n\n",loc, userIndex+2);
		pass_money = PM(1);
		printf(
			"Land Price : %d won\n"
			"Hotel Price : %d won\n"
			"Total Charge((Land Price+Hotel Price)*1.5) : %d won\n\n"
			,uj*100, uj*pht[uj]*350, pass_money);

		userMoney[0] -= pass_money;
		userMoney[1] += pass_money;
		money = userMoney[userIndex];

		printf("Total Charge %d.\n Remained Money : [%d won]\n",pass_money,money);
		puts("=================================================");
		getchar();

	}
	else if (userIndex == 1 && p[uj] == 1){
		// pay money to User 1
		puts("=================================================");
		printf("%s is for Player %d\n\n",loc, userIndex);
		pass_money = PM(1);
		printf(
			"Land Price : %d won\n"
			"Hotel Price : %d won\n"
			"Total Charge((Land Price+Hotel Price)*1.5) : %d won\n\n"
			,uj*100, uj*pht[uj]*350, pass_money);

		userMoney[1] -= pass_money;
		userMoney[0] += pass_money;
		money = userMoney[userIndex];
		printf("Total Charge %d.\n Remained Money : [%d won]\n",pass_money,money);
		puts("=================================================");
		getchar();
	}
	if(money <= 0) {
		system("cls");
		puts("=================================================");
		printf("** Game Over **\n Player %d You are broken!\n", userIndex+1);
		puts("=================================================");
		//Sleep(3000);
		exit(0);
	}

	if (money >= MONEY_LIMIT) {
		system("cls");
		puts("=================================================");
		printf("** Game Win **\n Player %d You Win.!\n", userIndex+1);
		puts("=================================================");
		//Sleep(3000);
		exit(0);
	}
	do {
		ure = 0;
		system("cls");
		if(p[uj] == 0) {
			strcpy(own,"Empty Land");
		} else if(p[uj] == 1) {
			strcpy(own,"Player1's Land");
		} else if(p[uj] == 2) {
			strcpy(own,"Player2's Land");
		} else {
			strcpy(own,"Neutral Area");
		}
		printf(
			"Player %d Your Money : %d won\n"
			"Player %d You're in : %s(%d)\n"
			"-------------------------\n"
			"1. Buy this Land\n"
			"2. Check Who's Land\n"
			"3. Turn over\n"
			"Owner : %s\n"
			"Number of Hotel : %d개\n"
			"-------------------------\n"
			"  Select : [ ]\b\b",
			userIndex+1, money, userIndex+1, loc, uj, own, pht[uj]
		);
		scanf("%d",&cho);
		switch(cho){
		case 1:
			system("cls");
			puts("=================================================");
			printf(
				"Land Price : %d원\n"
				"Hotel Price : %d원\n"
				"Player %d Your Money : %d원\n"
				,uj*100, uj*150, userIndex+1, money);
			puts("=================================================");
			printf("1. Buy Only Land\n"
				   "2. Buy Hotel\n"
				   "Select : [ ]\b\b" );
			scanf("%d",&cho2);

			if(cho2 == 1) {
				puts("=================================================");
				if(money >= uj*100 && p[uj] == 0) {
					money -= uj*100;
					p[uj]=userIndex+1;
					printf("You got %s succesively!\n Remained Money : %d won\n",loc,money);
					puts("=================================================");
					getchar();
					break;
				} else if(money < uj*100) {
					printf("            Can't afford it!\n");
					puts("=================================================");
					getchar();
					ure = 1;
					break;
				}else if (p[uj] == 3) {
					printf(" You can't buy this %s cause it's neutral area!\n",loc);
					puts("=================================================");
					getchar();
					ure = 1;
					break;
				} else {
					printf("  %s is already owned by another!\n",loc);
					puts("=================================================");
					getchar();
					ure = 1;
					break;
				}
			} else if(cho2 == 2) {
				if (userIndex == 0 && p[uj] == 2){
					puts("=================================================");
					printf("      %s is not your Land!\n",loc);
					puts("=================================================");
					getchar();
					ure = 1;
					break;
				}
				else if (userIndex == 1 && p[uj] == 1){
					puts("=================================================");
					printf("      %s is not your Land!\n",loc);
					puts("=================================================");
					getchar();
					ure = 1;
					break;
				}
				else if( pht[uj] > 0 ) {
					puts("=================================================");
					printf("     You have to build Hotel only One!\n");
					puts("=================================================");
					getchar();
					ure = 1;
					break;
				} else {
					Buy_hotel();
				}
			}
			else {
				puts(
				"=================================================\n"
				"               Press Wrong Character!, Check your number\n"
				"=================================================\n"
				);
				getchar();
				ure = 1;
				break;
			}
			break;

		case 2: // 소유권 확인
			system("cls");
			printf(
				"Player 1's Land\n"
				"--------------------------------------------\n"
			);
			for(i=0; i<MAP; i++) {
				pass_money = PM(3);
				if(p[i] == 1) {
					printf("%s(%d) - Charge : %d won\n",local[i],i,pass_money);
				}
			}
			puts("--------------------------------------------\n\n");
			printf(
				"Player 2's Land\n"
				"--------------------------------------------\n"
			);
			for(i=0; i<MAP; i++) {
				pass_money = PM(3);
				if(p[i] == 2) {
					printf("%s(%d) - Charge : %d won\n",local[i],i,pass_money);
				}
			}
			puts("--------------------------------------------");
			getchar();
			system("cls");
			ure = 1;
			break;
		case 3:
			system("cls");
			puts("=================================================");
			puts("             Turn over.");
			puts("=================================================");
			getchar();
			system("cls");
			break;
		}
	} while (ure == 1);
	userMoney[userIndex] = money;
}