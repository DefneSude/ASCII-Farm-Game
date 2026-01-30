#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
#include <windows.h>
#include <conio.h> // for _getch() code
#include <string.h>

#include "farm_config.h"

int main (void){
	char field[ROW][COL];
	int process;
	int r,c;
	
	int day=1;
	int water=100;
	int temprature=25;
	int money=0;
	int harvested_item=0;
	int seed_count=5;
	
	intro();
	
	startMap(field);
	
	while(1){
				
		process=menu(field,&water,&day,&temprature,&money,&harvested_item,&seed_count);
		
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
		}
		else if(process==-1){
			break;
		}
		else if(process==3){
			nextDay(field,&day,&temprature,&water);
		}
		
		else if(process==4){
			waterWell(field,&water);
		}
		
		else if(process==6){
			sell(&harvested_item,&money);
		}
		
		else if(process==7){
			buy(&money,&seed_count);
		}
		
		else if(process==8){
			saveGame(field,water,day,money,harvested_item,seed_count);
		}
		
		else if(process==9){
            loadGame(field, &water, &day, &money, &harvested_item,&seed_count);
        }
		
		switch(process){
			case 1:
				plantSeed(field,r,c,&seed_count);
				break;
			case 2:
				if(*(*(field+r)+c)=='S'){
					watering(field,r,c,&water);	
				}
				else if(*(*(field+r)+c)=='D'){
					watering(field,r,c,&water);	
				}
				else if(*(*(field+r)+c)=='!'){
					watering(field,r,c,&water);	
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
				harvest(field,r,c,&harvested_item);
				break;
		}	
		
		if(money>=200){
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

void drawMap (char map[ROW][COL]){
	int i,j;
	
	printf("\t\t\t        ");
	for(j=0;j<COL;j++){ //column number
		printf("%d ",j);
	}
	
	printf("\t   --- Meaning of Symbols ---");
	printf("\n");
	
	for(i=0;i<ROW;i++){
		printf("\t\t\t    %d | ",i); // row number
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

void plantSeed (char map[ROW][COL],int x,int y,int* seed){
	if(x>=0 && x<ROW && y>=0 && y<COL && *seed>0){
		if(*(*(map+x)+y)=='.'){
			*(*(map+x)+y)='S';
			(*seed)--;
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
	else if(*seed<=0){
		printf("Buy some seed!");
		Sleep(1500);
	}
	else{
		printf("\tError:Enter values between 0 and %d",COL);
		Sleep(1500); // -> To see warning, freeze program for one and half second
	}
}

void watering (char map[ROW][COL],int x,int y,int* water){
	
	if(*water<=0){
		printf("There is no water left!");
		Sleep(1500);
	}
	else{
		if(x>=0 && x<ROW && y>=0 && y<COL){
			if(*(*(map+x)+y)=='S'){
				*(*(map+x)+y)='W';
				*(water)-=1;	
			}
			
			else if(*(*(map+x)+y)=='!'){
				*(*(map+x)+y)='G';
				*(water)-=1;
			}
		
			else if(*(*(map+x)+y)=='D'){
				*(*(map+x)+y)='?';
				*water-=1;
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
			printf("\tError:Enter values between 0 and %d",COL);
			Sleep(1500); // -> To see warning, freeze program for one amd half second
		}
	}
	
}

void nextDay (char map[ROW][COL],int* day,int* temprature,int* water){
	int i,j;
	
	srand(time(NULL));
	
	printf("\n\t Day ends... Seeds are growing...\n");
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

void waterWell (char map[ROW][COL],int* water){
	int x;
	
	if(*water==100){
		printf("\tWater is already fulled");
		Sleep(1500);
	}
	else if(*water<=90){
		*water+=10;
		printf("\t-> +10");
		Sleep(1500);
	}
	else{
		x=100-*water;
		*water=100;
		printf("\t-> +%d",x);
		Sleep(1500);
	}
}

void harvest (char map[ROW][COL],int x,int y,int* harvested_item){

            if(*(*(map+x)+y)=='G'){
                *(*(map+x)+y)='.'; 
                (*harvested_item)++;
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
			}
			else if(*(*(map+x)+y)=='?'){
				printf("\tDried areas can be saved, water them.");
			}
}

void sell (int* harvested_item,int* money){
	int i;
	int sell_value=25;
	
	if(*(harvested_item)<=0){
		printf("\tBefore harvest some wheat!");
		Sleep(2000);
	}
	else{
		printf("\tHow money wheat you want to sell:");
		scanf("%d",&i);
		
		if(i>*(harvested_item)){
			printf("\tThere is no enough wheat.");
			Sleep(2000);
		}
		else if(i==0){
			printf("\tInvalid amount.");
			Sleep(2000);
		}
		else{
			(*money)+=(sell_value)*i;
			(*harvested_item)-=i;
		}
	}
}

void buy (int* money, int* seed){
	int i;
	int buy_value=20;
	if(*money==0){
		printf("\tThere is no money!");
		Sleep(1500);
	}
	else{
		printf("\tEnter how many seeds you want:");
		scanf("%d",&i);
		if(i>0){
			if(*money>=i*(buy_value)){
			(*money)-=i*(buy_value);
			(*seed)+=i;
		}
			else{
				printf("\tThere is no enough money!");
				Sleep(1500);
			}
		}
		else{
			printf("\tEnter a value more than zer0.");
			Sleep(1500);
		}
		
	}
}

int menu (char map[ROW][COL],int* water,int* day,int* temprature,int* money, int* harvested_item,int* seed){
	int choice=1;
	int key;
	
	while(1){
		system("cls"); // It clears screen
		
		printf("\n\t\t\t\t	-*- ASCII FARM - Day: %-3d-*-\n",*day);
		
		printf("\n\t---------------------------------------------------------------------------------------------------\n");
		
		printf("\t\t\t\t  Water Level: %-3d | Temprature: %-3d | Money: %-3d ",*water,*temprature,*money);
		
		printf("\n\t---------------------------------------------------------------------------------------------------\n");
		
		printf("\t\t\t\t\tHarvested wheat: %-3d |   Seed: %-3d",*harvested_item,*seed);
		
		printf("\n\t---------------------------------------------------------------------------------------------------\n\n");
		
		drawMap(map);
		
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
		
		if(choice==8) printf(" [Save Game] ");
		else		  printf(" save game ");
		
		if(choice==9) printf(" [Load Game] ");
        else          printf("  load game ");
		
		printf("\n\n\t---------------------------------------------------------------------------------------------------\n");
		printf("\t[To move bar: <- ->][To select: Enter][To exit: ESC]\n");
		
		key=_getch(); // for -> and <- keys
		
		if(key==224){
			key = _getch();
			
			if(key==LEFT){
				choice--;
				if(choice==0) choice=9;
			}
			else if(key==RIGHT){
				choice++;
				if(choice==10) choice=1;
			}
		}	
		else if(key==ENTER) return choice;
		
		else if(key==ESC) return -1;
	}
}

void saveGame(char map[ROW][COL], int water, int day, int money, int item,int seed){
	FILE* farm_file=fopen("farm_save.txt","w");
	
	if(farm_file==NULL){
		printf("\tWARNING:Save failed!");
		return;
	}
	
	fprintf(farm_file,"%d %d %d %d %d\n", water, day, money, item,seed);
	
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

void loadGame(char map[ROW][COL], int* water, int* day, int* money, int* item,int* seed){
	FILE* farm_file = fopen("farm_save.txt", "r");
	
	if(farm_file == NULL){
        printf("\tSave file not found!\n");
        Sleep(1500);
        return;
    }
    
    fscanf(farm_file, "%d %d %d %d %d\n", water, day, money, item, seed);
    
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



