#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
#include <windows.h>
#include <conio.h> // for _getch() code
#include <string.h>

#include "farm_config.h"

// Sağlık barı ve yemek yedikçe iyileşme mekaniği koy
// Gemini da kodlara bak, harvested_item'ı harvested_item_wheat olarak değiştir çünkü apple toplama koyacağız
// pizza yapılamaz satın alınır ama apple juice ve bread yapılabilir

int main (void){
	char field[ROW][COL];
	int process;
	int r,c;
	
	int day=1;
	int water=100;
	int temprature=25;
	int money=0;
	int wheat_harvested_item=0;
	int wheat_seed_count=5;
	int game_hour=7;
	int game_minute=0;
	time_t last_time=time(NULL); // Records real time when game started
	int moves=15;
	
	intro();
	
	startMap(field);
	
	while(1){
				
		process=menu(field,&water,&day,&temprature,&money,&wheat_harvested_item,&wheat_seed_count,&game_hour,&game_minute,&last_time,&moves);
		
		if(process==1 || process==2 || process==5){
		printf("\n\tEnter coordinates(Row,Column)(To exit press -1,-1):\n");
		printf("\t");
			if(scanf("%d%d",&r,&c)!=2){
				while(getchar() != '\n'); // clears wrong user value
				continue;
			}
			
			else if(r==-1){
				continue; // -> To take back last coordinate
			}	
			r--;
			c--;
		}
		else if(process==-1){
			break;
		}
		else if(process==3){
			nextDay(field,&day,&temprature,&water);
			game_hour=7;
			game_minute=0;
			last_time=time(NULL);
			moves=15;
		}
		
		else if(process==4){
			waterWell(field,&water,&moves);
		}
		
		else if(process==6){
			sell(&wheat_harvested_item,&money);
		}
		
		else if(process==7){
			buy(&money,&wheat_seed_count,&moves);
		}
		
		else if(process==9){
			saveGame(field,water,day,money,wheat_harvested_item,wheat_seed_count,game_hour,game_minute,moves);
		}
		
		else if(process==10){
            loadGame(field, &water, &day, &money, &wheat_harvested_item,&wheat_seed_count,&game_hour,&game_minute,&moves);
        }
		
		switch(process){
			case 1:
				plantSeed(field,r,c,&wheat_seed_count,&moves);
				break;
			case 2:
				if(*(*(field+r)+c)=='S'){
					watering(field,r,c,&water,&moves);	
				}
				else if(*(*(field+r)+c)=='D'){
					watering(field,r,c,&water,&moves);	
				}
				else if(*(*(field+r)+c)=='!'){
					watering(field,r,c,&water,&moves);	
				}
				else if(*(*(field+r)+c)=='.'){
					printf("\tBefore watering plant a seed!");
					Sleep(1500);
				}
				else if(*(*(field+r)+c)=='W'){
					printf("\tAlready watered!");
					Sleep(1500);
				}
				break;
			case 5:
				harvest(field,r,c,&wheat_harvested_item,&moves);
				break;
			
			case 8:
				nap(&game_hour,&game_minute,&moves);
		}
		
		if(money>=1000){
			system("cls");
			printf("\n\n\n\n\n\n\n\n\n");
			
			setColor(11);
			printf("\n\n\t---------------------------------------------------------------------------------------------------\n\n");
			
			printf("\t\t\t\t\t\t     ![CONGRATULATIONS]!\n");
			printf("\t\t\t\t\t\t      You finished game!\n");
			printf("\t\t\t\t\t        In total you gained %d dollars ;)\n",money);
			
			printf("\n\n\t---------------------------------------------------------------------------------------------------\n");
			
			printf("\n\n\n\n\n\n\n\n");
			
			setColor(7);
			Sleep(5000);
			break;
		}
	}
	
	return 0;
}

void intro(){
	system("cls");
    setColor(11);
    
    printf("\n\n\n\n\n\n\n\n\n\n\n\n");
    printf("\t\t\t\t\t\tPRESS ENTER TO START");
    
    setColor(7);
    while(getchar() != '\n');
    Sleep(500);
}

void startMap (char map[ROW][COL]){
	int i,j;
	for(i=0;i<ROW;i++){
		for(j=0;j<COL;j++){
			map[i][j]=EMPTY_AREA;
		}
	}
}

void drawMap (char map[ROW][COL],int moves){
	int i,j;
	
	printf("\t\t\t         ");
	for(j=0;j<COL;j++){ //column number
		printf("%d ",j+1);
	}
	
	printf("\t   --- Meaning of Symbols ---");
	printf("\n");
	
	for(i=0;i<ROW;i++){
		if(i==2){
			printf("\t  Energy Bar=%02d     %2d | ",moves, i+1);
		}else{
			if(i<2 || i>=8) printf("\t\t\t    %2d | ",i+1); // row number
			else if(i>2 && i<8){
				int required_moves=(7-i)*3+1;
				int base_moves=(7-i)*3;
				int local_moves=moves-base_moves;
				printf("\t       |");
				if(moves>=required_moves){
					if(local_moves>=3) printf("===");
					else if(local_moves==2) printf(" ==");
					else if(local_moves==1) printf("  =");
				}else{
					printf("   ");
				}
				printf("|\t    %2d | ",i+1);
			}
		}
		for(j=0;j<COL;j++){
					
			char cell = map[i][j];
				
			if(cell == 'W') setColor(9);       // Blue (Watered)
  			else if(cell == 'G') setColor(10); // Green (Wheat)
	    	else if(cell == 'S') setColor(14); // Yellow (Seed)
    		else if(cell == 'X') setColor(12); // Red (Dead)
    		else if(cell == 'D') setColor(6);  // Orange/Brown (Dried)
			else if(cell == '?') setColor(11); // Light Blue (Saved)
			else if(cell == '!') setColor(6);
			    
   			printf("%c ", cell);
  			setColor(7); //turns collor to white
		}
		printf("\t\t");		
		if(i==1){
			setColor(14); 
			printf("   S : Seed"); setColor(7);
		}
		else if(i==2){
			setColor(9); 
			printf("   W : Watered"); 
			setColor(7);
		}
		else if(i==3){
			setColor(10);
			printf("   G : Grown"); 
			setColor(7);
		}
		else if(i==4){
			setColor(6);  
			printf("   D : Dried Seed"); 
			setColor(7);
		}
		else if(i==5){
			setColor(11);
			printf("   ? : Saved"); 
			setColor(7);
		}
		else if(i==6){
			setColor(12); 
			printf("   X : Dead");
			setColor(7);
		}
		else if(i==7){
			setColor(6);
			printf("   ! : Dried Wheat");
			setColor(7);
		}
		else if(i==8){
			printf("   . : Empty Area");
		}
		
		printf("\n");
	}
	
}

void plantSeed (char map[ROW][COL],int x,int y,int* wheat_seed,int* moves){
	if(x>=0 && x<ROW && y>=0 && y<COL && *wheat_seed>0){
		if(*(*(map+x)+y)=='.'){
			*(*(map+x)+y)='S';
			(*wheat_seed)--;
			(*moves)--;
		}
		else if(*(*(map+x)+y)=='G' || *(*(map+x)+y)=='W' || *(*(map+x)+y)=='?' || *(*(map+x)+y)=='S' || *(*(map+x)+y)=='D' || *(*(map+x)+y)=='!'){
			printf("\tThis area isn't empty.");
			Sleep(1500);
		}
		else if(*(*(map+x)+y)=='X' || *(*(map+x)+y)=='G'){
			printf("\tThis area needs to be harvested.");
			Sleep(1500);
		}
	}
	else if(*wheat_seed<=0){
		printf("Buy some wheat seed!");
		Sleep(1500);
	}
	else{
		printf("\tError:Enter values between 1 and %d",COL);
		Sleep(1500); // -> To see warning, freeze program for one and half second
	}
}

void watering (char map[ROW][COL],int x,int y,int* water,int* moves){
	
	if(*water<=0){
		printf("There is no water left!");
		Sleep(1500);
	}
	else{
		if(x>=0 && x<ROW && y>=0 && y<COL){
			if(*(*(map+x)+y)=='S'){
				*(*(map+x)+y)='W';
				(*water)--;
				(*moves)--;	
			}
			
			else if(*(*(map+x)+y)=='!'){
				*(*(map+x)+y)='G';
				(*water)--;
			}
		
			else if(*(*(map+x)+y)=='D'){
				*(*(map+x)+y)='?';
				(*water)--;
				(*moves)--;
			}
		
			else if(*(*(map+x)+y)=='X'){
				printf("\n\tIt is dead...\n");
				Sleep(1500);	
			}
			else if(*(*(map+x)+y)=='G'){
				printf("\tIt is already grown.");
				Sleep(1500);
			}
		}
		else{
			printf("\tError:Enter values between 1 and %d",COL);
			Sleep(1500); // -> To see warning, freeze program for one amd half second
		}
	}
	
}

void nextDay (char map[ROW][COL],int* day,int* temprature,int* water){
	int i,j;
	
	srand(time(NULL));
	
	printf("\n\tDay ends... Seeds are growing...\n");
	Sleep(1500);
	
	for(i = 0; i < ROW; i++) {
        for(j = 0; j < COL; j++) {
            
            char* area=(*(map + i) + j);

            if(*area=='W'){
                *area='G'; 
            }
            else if(*area=='S'){
            	*area='D'; // dried
			}
			else if(*area=='?'){
				*area='S';
			}
            else if(*area=='D'){
            	*area='X'; // dead seed
			}
			else if(*area=='G'){
				*area='!';
			}
			else if(*area=='!'){
				*area='X';
			}
        }
    }
    
    *day+=1;
    
    *temprature=rand()%25+15+1;
    
    int weatherChance=rand() % 100;
    
    if(weatherChance<20) { 
        printf("\n\t [!] IT IS RAINNING! Water well is fulled, seeds are watered.\n");
        *water=100; 
        
        int i,j;
        for(i=0;i<ROW;i++){
            for(j=0;j<COL;j++){
                if(*(*(map+i)+j)=='S') map[i][j]='W';
                if(*(*(map+i)+j)=='D') map[i][j]='?';         	
			}
		}
                
        Sleep(2000);
    }
    
    else if(*temprature > 35) {
        printf("\n\t [!] IT IS TOO HOT! Water is evaporating...\n");
        *water -= 20; 
        if(*water < 0) *water = 0;
        Sleep(2000);
    }
}

void waterWell (char map[ROW][COL],int* water,int* moves){
	int x;
	
	if(*water==100){
		printf("\tWater is already fulled");
		Sleep(1500);
	}
	else if(*water<=90){
		*water+=10;
		printf("\t-> +10");
		Sleep(1500);
		(*moves)--;
	}
	else{
		x=100-*water;
		*water=100;
		printf("\t-> +%d",x);
		Sleep(1500);
		(*moves)--;
	}
}

void harvest (char map[ROW][COL],int x,int y,int* wheat_harvested_item,int* moves){

            if(*(*(map+x)+y)=='G'){
                *(*(map+x)+y)='.'; 
                (*wheat_harvested_item)++;
                (*moves)--;
            }
            else if(*(*(map+x)+y)=='.'){
            	printf("\tEmpty areas can't be harvested.\n");
            	Sleep(1500);
			}
            else if(*(*(map+x)+y)=='S'){
            	printf("\tSeeds can't be harvested.\n");
            	Sleep(1500);
			}
			else if(*(*(map+x)+y)=='W'){
				printf("\tWatered areas can't be harvested.\n");
				Sleep(1500);
			}
            else if(*(*(map+x)+y)=='X'){
            	*(*(map+x)+y)='.';
            	(*moves)--;
			}
			else if(*(*(map+x)+y)=='?'){
				printf("\tDried areas can be saved, water them.");
			}
}

void sell (int* wheat_harvested_item,int* money){
	int i;
	int sell_value=25;
	
	if(*(wheat_harvested_item)<=0){
		printf("\tBefore harvest some wheat!");
		Sleep(2000);
	}
	else{
		printf("\tHow money wheat you want to sell:");
		scanf("%d",&i);
		
		if(i>*(wheat_harvested_item)){
			printf("\tThere is no enough wheat.");
			Sleep(2000);
		}
		else if(i==0){
			printf("\tInvalid amount.");
			Sleep(2000);
		}
		else{
			(*money)+=(sell_value)*i;
			(*wheat_harvested_item)-=i;
		}
	}
}

void buy (int* money, int* wheat_seed,int* moves){
	int i;
	int key;
	int redraw=1;
	int choice=1;
	int buy_value_wheat=20;
	int buy_value_energy_drink=100;
	
	if(*money==0){
		printf("\tThere is no money!");
		Sleep(1500);
		return;
	}
	while(1){
		if(redraw){
			system("cls");
			printf("\n\n\t--- MARKET ---\n");
			printf("\tMoney: %d\n\n", *money);
			
			printf("\t");
			if(choice==1) printf(" [Wheat 20$] ");
			else		  printf(" wheat ");
		
			if(choice==2) printf(" [Energy Drink 100$] ");
			else		  printf(" energy drink ");
			printf("\n\n\t[To move: <- ->][To select: Enter][To exit: ESC]\n");
			
			redraw=0;
		}
		Sleep(30);
	
		if(kbhit()){
				key=_getch(); // for -> and <- keys
				
				if(key==224){
					key = _getch();
				
					if(key==LEFT){
						choice--;
						if(choice==0) choice=2;
						redraw=1;
					}
					else if(key==RIGHT){
						choice++;
						if(choice==3) choice=1;
							redraw=1;
					}
				}	
				else if(key==ENTER){
					switch(choice){
						case 1:
							printf("\tEnter how many seeds you want:");
							scanf("%d",&i);
							if(i>0){
								if(*money>=i*(buy_value_wheat)){
								(*money)-=i*(buy_value_wheat);
								(*wheat_seed)+=i;
								}else{
									printf("\tThere is no enough money!");
									Sleep(1500);
								}
							}else{
								printf("\tEnter a value more than zer0.");
								Sleep(1500);
							}
							break;
						case 2:
							if(*money>=buy_value_energy_drink){
								(*money)-=buy_value_energy_drink;
								if(*moves<10) *moves+=5;
								else *moves=15;
								printf("\t+ENERGY");
								Sleep(1000);
							}else{
								printf("\tThere is no enough money! No energy!");
								Sleep(1500);
							}
							break;
					}
					
					redraw=1;	
				}
				
				else if(key==ESC) return;
		}
	}
}


void nap (int* game_hour,int* game_minute,int* moves){
	if(*game_hour<=21 || *game_hour<7){
		*game_hour+=3;
		*game_minute+=rand()%21;
		if(*moves<10) *moves+=5;
		else *moves=15;
		printf("\tMy eyelids are...\n");
		Sleep(1000);
		printf("\tI will wake up in 3 hours and ... ... minutes...");
		Sleep(2000);
	}else{
		printf("\tI should sleep... not nap...");
		Sleep(2000);
	}
}

int menu (char map[ROW][COL],int* water,int* day,int* temprature,int* money, int* wheat_harvested_item,int* wheat_seed,int* game_hour,int* game_minute, time_t* last_time,int* moves){
	int choice=1;
	int key;
	int redraw=1;
	int last_seen_min=-1;
	
	while(1){
		updateTime(game_hour,game_minute,last_time);
		
		if(*game_hour==2 && *game_minute==15 || *moves==0){
			printf("\tYou are getting tired... unconscious... goodnight...\n");
			Sleep(2500);
			printf("\tI wish you can stay alive while you are vulnerable...");
			Sleep(1500);
			return 3;
		}
		
		
		if(*game_minute!=last_seen_min){
			redraw=1;
			last_seen_min=*game_minute;
		}
		
		if(redraw){
			system("cls"); // It clears screen
			
			printf("\n\t\t\t\t\t");
			printf("    -*-  ASCII FARM - Day: %-3d-*-\n",*day);
		
			printf("\n\t---------------------------------------------------------------------------------------------------\n");
		
			printf("\t\t\t\t  Water Level: %-3d | Temprature: %-3d | Money: %-3d ",*water,*temprature,*money);
		
			printf("\n\t---------------------------------------------------------------------------------------------------\n");
		
			printf("\t\t\t\t\tHarvested wheat: %-3d |   Seed: %-3d",*wheat_harvested_item,*wheat_seed);
		
			printf("\n\t---------------------------------------------------------------------------------------------------\n");
		
			printf("\t\t\t\t\t\t    Time : %02d:%02d", *game_hour, *game_minute);
			
			printf("\n\t---------------------------------------------------------------------------------------------------\n\n");
		
			drawMap(map,*moves);
		
			printf("\n\t---------------------------------------------------------------------------------------------------\n\n");
		
			printf("\t");
			if(choice==1) printf(" [Plant Seed] ");
			else		  printf(" plant seed ");
		
			if(choice==2) printf(" [Water Seed] ");
			else		  printf(" water seed ");
		
			if(choice==3) printf(" [Sleep] ");
			else		  printf(" sleep ");
		
			if(choice==4) printf(" [Collect Water] ");
			else		  printf(" collect water ");
			
			if(choice==5) printf(" [Harvest] ");
			else		  printf(" harvest ");
		
			if(choice==6) printf(" [Sell] ");
			else		  printf(" sell ");
		
			if(choice==7) printf(" [Buy] ");
			else		  printf(" buy ");
			
			if(choice==8) printf(" [Nap] ");
	        else          printf("  nap ");
	        
	    	if(choice==9) printf(" [Save Game] ");
			else		  printf(" save game ");
		
			if(choice==10) printf(" [Load Game] ");
	        else          printf("  load game ");
	        
			printf("\n\n\t---------------------------------------------------------------------------------------------------\n");
			printf("\t[To move bar: <- ->][To select: Enter][To exit: ESC]\n");
		
			redraw=0;
		}
		
		Sleep(30);
		
		if(kbhit()){
			key=_getch(); // for -> and <- keys
			
			if(key==224){
				key = _getch();
			
				if(key==LEFT){
					choice--;
					if(choice==0) choice=10;
					redraw=1;
				}
				else if(key==RIGHT){
					choice++;
					if(choice==11) choice=1;
					redraw=1;
				}
			}	
			else if(key==ENTER) return choice;
		
			else if(key==ESC) return -1;
		}
	}
}

void updateTime(int* hour, int* minute, time_t* last_time){
	time_t current_time=time(NULL);
	double diff=difftime(current_time,*last_time);
	
	if(diff>=10.0){
		int passed_minutes=(int)(diff/1.0);
		*minute+=passed_minutes;
		
		*last_time+=passed_minutes;
		
		if(*minute>=60){
			*hour+=(*minute/60);
			*minute=*minute%60;
		}
		
		if(*hour>=24){
			*hour=*hour%24;
		}
	}
}

void saveGame(char map[ROW][COL], int water, int day, int money, int wheat_harvested_item,int wheat_seed,int game_hour,int game_minute,int moves){
	FILE* farm_file=fopen("farm_save.txt","w");
	
	if(farm_file==NULL){
		printf("\tWARNING:Save failed!");
		return;
	}
	
	fprintf(farm_file,"%d %d %d %d %d %d %d %d\n", water, day, money, wheat_harvested_item,wheat_seed,game_hour,game_minute,moves);
	
	int i,j;
	for(i=0; i<ROW; i++){
        for(j=0; j<COL; j++){
            fputc(map[i][j], farm_file);
        }
        fputc('\n', farm_file); 
    }
    
    fclose(farm_file);
    printf("\tGame Saved Successfully!\n");
    Sleep(1500);
}

void loadGame(char map[ROW][COL], int* water, int* day, int* money, int* wheat_harvested_item,int* wheat_seed,int* game_hour,int* game_minute,int* moves){
	FILE* farm_file = fopen("farm_save.txt", "r");
	
	if(farm_file == NULL){
        printf("\tSave file not found!\n");
        Sleep(1500);
        return;
    }
    
    fscanf(farm_file, "%d %d %d %d %d %d %d %d\n", water, day, money, wheat_harvested_item, wheat_seed,game_hour,game_minute,moves);
    
    int i, j;
    char temp; // Temporary variable to absorb the end-of-line character (\n)
    
    for(i=0; i<ROW; i++){
    	for(j=0;j<COL;j++){
    		map[i][j] = fgetc(farm_file);
		}
		temp = fgetc(farm_file);
	}
	fclose(farm_file);
    printf("\tGame Loaded Successfully!\n");
    Sleep(1500);
}
