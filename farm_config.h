// Game's rules will be written here

#ifndef FARM_CONFIG_H 
#define FARM_CONFIG_H

#define ROW 10
#define COL 10
#define EMPTY_AREA '.'
#define SEED 'S'
#define CROP 'G'
#define DRIED_SEED 'D'
#define WATERED_DRIED '?'
#define DEATH_SEED 'X'
#define WATERED 'W'
#define DRIED_WHEAT '!'

#define UP 72
#define DOWN 80
#define LEFT 75
#define RIGHT 77
#define ENTER 13
#define ESC 27

void startMap (char map[ROW][COL]);
void drawMap (char map[ROW][COL]);
void plantSeed (char map[ROW][COL],int x,int y,int* seed);
void watering (char map[ROW][COL],int x,int y,int* water);
void nextDay (char map[ROW][COL],int* day,int* temprature,int* water);
int menu (char map[ROW][COL],int* water,int* day,int* temprature,int* money, int* harvested_item,int* seed);
void waterWell (char map[ROW][COL],int* water);
void harvest (char map[ROW][COL],int x,int y,int* harvested_item);
void sell (int* harvested_item,int* money);
void buy (int* money, int* seed);
void setColor(int color){
//	7: White, 9: Blue, 10: Green, 12: Red, 14: Yellow
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), color);
}
void intro();
void saveGame(char map[ROW][COL], int water, int day, int money, int item,int seed);
void loadGame(char map[ROW][COL], int* water, int* day, int* money, int* item,int* seed);

#endif
