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
void drawMap (char map[ROW][COL],int moves);
void inventory (char map[ROW][COL], int* water, int* day, int* temprature);
void plantSeed (char map[ROW][COL],int x,int y,int* wheat_seed,int* moves);
void watering (char map[ROW][COL],int x,int y,int* water,int* moves);
void nextDay (char map[ROW][COL],int* day,int* temprature,int* water);
int menu (char map[ROW][COL],int* water,int* day,int* temprature,int* money, int* wheat_harvested_item,int* wheat_seed,int* game_hour,int* game_minute, time_t* last_time,int* moves);
void waterWell (char map[ROW][COL],int* water,int* moves);
void harvest (char map[ROW][COL],int x,int y,int* wheat_harvested_item,int* moves);
void sell (int* wheat_harvested_item,int* money);
void nap (int* game_hour,int* game_minute,int* moves);
void buy (int* money, int* wheat_seed,int* moves);
void setColor(int color){
//	7: White, 9: Blue, 10: Green, 12: Red, 14: Yellow
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), color);
}
void intro();
void updateTime(int* hour, int* minute, time_t* last_time);
void saveGame(char map[ROW][COL], int water, int day, int money, int wheat_harvested_item,int wheat_seed,int game_hour,int game_minute,int moves);
void loadGame(char map[ROW][COL], int* water, int* day, int* money, int* wheat_harvested_item,int* wheat_seed,int* game_hour,int* game_minute,int* moves);

#endif
