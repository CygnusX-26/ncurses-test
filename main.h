 
#include <ncurses.h>
#include <stdlib.h>
#include <string.h>

#define MAP_WIDTH 14
#define MAP_HEIGHT 30
#define PLAYER_START_X MAP_WIDTH/2
#define PLAYER_START_Y MAP_HEIGHT/2
#define PLAYER_SPEED 1
#define INFO_BOARD_SIZE_X 5
#define INFO_BOARD_SIZE_Y 18
#define DIG_WIN 1337


typedef enum {
    EMPTY,
    OCCUPIED,
} TileType;

typedef enum {
    UP,
    DOWN,
    LEFT,
    RIGHT
} Direction;

typedef struct {
    int x;
    int y;
    int dug;
    TileType type;
} Tile;

void drawPlayer(Direction);
void drawMap(WINDOW*, int, int, Direction, int, int);

void initMap();
void initGame();

void dig(int, int);
void getFlag();

Direction handleKeyPressed(char, int*, int*);