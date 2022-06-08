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
char local[MAP][30] = {"시작지점","한국","미국","일본","중국","영국","무인도","독일","아르헨티나","그리스","프랑스","스웨덴","오스트레일리아","터키","스위스","이집트"};
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
		printf("          호텔을 성공적으로 구입했습니다!\n         남은 돈 : %d원\n",money);
	} else {
		puts("       돈이 부족하거나 잘못 입력했습니다!");
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
	printf("##  %s[%s][%s]      %s[%s][%s]      %s[%s][%s]     %s[%s][%s]       %s[%s][%s]  ##\n",
	local[8],  showUser1Pos[8],showUser2Pos[8], local[9], showUser1Pos[9],showUser2Pos[9],
	local[10], showUser1Pos[10],showUser2Pos[10], local[11],showUser1Pos[11],showUser2Pos[11],
	local[12], showUser1Pos[12],showUser2Pos[12]);
	printf("##                                                                                                    ##\n");
	printf("##  %s[%s][%s]                                                                            %s[%s][%s]  ##\n",
	local[7], showUser1Pos[7],showUser2Pos[7], local[13], showUser1Pos[13],showUser2Pos[13]);
	printf("##                                                                                                    ##\n");
	printf("##  %s[%s][%s]                                                                        %s[%s][%s]  ##\n",
	local[6], showUser1Pos[6],showUser2Pos[6], local[14], showUser1Pos[14],showUser2Pos[14]);
	printf("##                                                                                                    ##\n");
	printf("##  %s[%s][%s]                                                                          %s[%s][%s]  ##\n",
	local[5], showUser1Pos[5],showUser2Pos[5], local[15], showUser1Pos[15],showUser2Pos[15]);
	printf("##                                                                                                    ##\n");
	printf("##  %s[%s][%s]          %s[%s][%s]         %s[%s][%s]          %s[%s][%s]             %s[%s][%s]  ##\n",
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
			"[플레이어 %d 당신의 차례입니다.]\n\n"
			"현재 당신의 돈 : %d원\n"
			"현재 당신의 장소 : %s(%d)\n",
			userIndex+1, money,loc,uj
		);
		puts("=================================================");
		puts("아무키나 누르면 주사위를 던집니다.");
		getchar();
		dice1 = Dice();
		dice2 = Dice();
		puts("=================================================");
		printf("                =주사위 결과=\n"
		  "               [%d]+[%d] = [%d]\n",dice1,dice2,dice1+dice2);
		puts("=================================================");
		getchar();

		if (dice1 == dice2){
		    puts("=================================================");
    		puts("더블입니다 주사위를 한번더 굴립니다. 한번에 이동합니다");
			if (islandCount[userIndex] != 0 ){
				islandCount[userIndex] = 0;
				puts("무인도를 탈출합니다.");
			}
    		getchar();
    		puts("=================================================");
		}
		else if (islandCount[userIndex] != 0) {
			puts("=================================================");
    		printf("당신은 무인도입니다. 남은 횟수는 %d 입니다.\n", islandCount[userIndex]--);
    		getchar();
    		puts("=================================================");
			return;
		}
		temp = dice1+dice2;
		uj += temp;

    	if( uj > MAP-1 ) {
			uj = uj%MAP;
    		puts("=================================================");
    		printf("  당신은 한바퀴를 돌아서 700원을 받습니다.\n");
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
		puts("당신은 무인도입니다. 3턴동안 휴식합니다.");
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
		printf("%s은(는) 플레이어 %d 의 영토입니다.\n\n",loc, userIndex+2);
		pass_money = PM(1);
		printf(
			"토지 가격 : %d원\n"
			"호텔 가격 : %d원\n"
			"합계통행료((토지가격+호텔가격)*1.5) : %d원\n\n"
			,uj*100, uj*pht[uj]*350, pass_money);

		userMoney[0] -= pass_money;
		userMoney[1] += pass_money;
		money = userMoney[userIndex];

		printf("통행료 %d원을 지불합니다.\n남은 돈 : [%d원]\n",pass_money,money);
		puts("=================================================");
		getchar();

	}
	else if (userIndex == 1 && p[uj] == 1){
		// pay money to User 1
		puts("=================================================");
		printf("%s은(는) 플레이어 %d 의 영토입니다.\n\n",loc, userIndex);
		pass_money = PM(1);
		printf(
			"토지 가격 : %d원\n"
			"호텔 가격 : %d원\n"
			"합계통행료((토지가격+호텔가격)*1.5) : %d원\n\n"
			,uj*100, uj*pht[uj]*350, pass_money);

		userMoney[1] -= pass_money;
		userMoney[0] += pass_money;
		money = userMoney[userIndex];
		printf("통행료 %d원을 지불합니다.\n남은 돈 : [%d원]\n",pass_money,money);
		puts("=================================================");
		getchar();
	}
	if(money <= 0) {
		system("cls");
		puts("=================================================");
		printf("** Game Over **\n 플레이어 %d 당신은 파산했습니다!\n", userIndex+1);
		puts("=================================================");
		//Sleep(3000);
		exit(0);
	}

	if (money >= MONEY_LIMIT) {
		system("cls");
		puts("=================================================");
		printf("** Game Win **\n 플레이어 %d 당신은 이겼습니다.!\n", userIndex+1);
		puts("=================================================");
		//Sleep(3000);
		exit(0);
	}
	do {
		ure = 0;
		system("cls");
		if(p[uj] == 0) {
			strcpy(own,"빈 영토");
		} else if(p[uj] == 1) {
			strcpy(own,"플레이어1 의 영토");
		} else if(p[uj] == 2) {
			strcpy(own,"플레이어2 의 영토");
		} else {
			strcpy(own,"중립 영토");
		}
		printf(
			"현재 플레이어 %d 당신의 돈 : %d원\n"
			"현재 플레이어 %d 당신의 장소 : %s(%d)\n"
			"-------------------------\n"
			"1. 현재 영토 구입\n"
			"2. 영토소유권 확인\n"
			"3. 턴 넘기기\n"
			"영토소유자 : %s\n"
			"호텔 갯수 : %d개\n"
			"-------------------------\n"
			"  선택 : [ ]\b\b",
			userIndex+1, money, userIndex+1, loc, uj, own, pht[uj]
		);
		scanf("%d",&cho);
		switch(cho){
		case 1:
			system("cls");
			puts("=================================================");
			printf(
				"토지 가격 : %d원\n"
				"호텔 가격 : %d원\n"
				"현재 플레이어 %d 당신의 돈 : %d원\n"
				,uj*100, uj*150, userIndex+1, money);
			puts("=================================================");
			printf("1. 토지 구입\n"
				   "2. 호텔 구입\n"
				   "입력 : [ ]\b\b" );
			scanf("%d",&cho2);

			if(cho2 == 1) {
				puts("=================================================");
				if(money >= uj*100 && p[uj] == 0) {
					money -= uj*100;
					p[uj]=userIndex+1;
					printf("%s을(를) 성공적으로 구입했습니다!\n남은 돈 : %d원\n",loc,money);
					puts("=================================================");
					getchar();
					break;
				} else if(money < uj*100) {
					printf("            돈이 부족합니다!\n");
					puts("=================================================");
					getchar();
					ure = 1;
					break;
				}else if (p[uj] == 3) {
					printf("   %s은(는) 구입하지 못 하는 영토입니다!\n",loc);
					puts("=================================================");
					getchar();
					ure = 1;
					break;
				} else {
					printf("  %s은(는) 이미 소유권이 있는 영토입니다!\n",loc);
					puts("=================================================");
					getchar();
					ure = 1;
					break;
				}
			} else if(cho2 == 2) {
				if (userIndex == 0 && p[uj] == 2){
					puts("=================================================");
					printf("      %s은(는) 당신의 영토가 아닙니다!\n",loc);
					puts("=================================================");
					getchar();
					ure = 1;
					break;
				}
				else if (userIndex == 1 && p[uj] == 1){
					puts("=================================================");
					printf("      %s은(는) 당신의 영토가 아닙니다!\n",loc);
					puts("=================================================");
					getchar();
					ure = 1;
					break;
				}
				else if( pht[uj] > 0 ) {
					puts("=================================================");
					printf("     호텔은 1개까지만 건설할 수 있습니다!\n");
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
				"               잘못 입력했습니다!\n"
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
				"현재 플레이어1 의 소유 영토\n"
				"--------------------------------------------\n"
			);
			for(i=0; i<MAP; i++) {
				pass_money = PM(3);
				if(p[i] == 1) {
					printf("%s(%d) - 통행료 : %d원\n",local[i],i,pass_money);
				}
			}
			puts("--------------------------------------------\n\n");
			printf(
				"현재 플레이어2 의 소유 영토\n"
				"--------------------------------------------\n"
			);
			for(i=0; i<MAP; i++) {
				pass_money = PM(3);
				if(p[i] == 2) {
					printf("%s(%d) - 통행료 : %d원\n",local[i],i,pass_money);
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
			puts("             당신의 턴을 마칩니다.");
			puts("=================================================");
			getchar();
			system("cls");
			break;
		}
	} while (ure == 1);
	userMoney[userIndex] = money;
}