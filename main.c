#include "main.h"
#include <curses.h>

Tile MAP[MAP_WIDTH][MAP_HEIGHT] = {};

int playerx = PLAYER_START_X;
int playery = PLAYER_START_Y;

int main() {
    initGame();

    if (has_colors() == FALSE) {
        endwin();
        printf("Your terminal does not support color\n");
        exit(1);
    }

    int offsetx = 0;
    int offsety = 0;
    int startx = (LINES - MAP_WIDTH)/2;
    int starty = (COLS - MAP_HEIGHT)/2;
    Direction d = UP;
    WINDOW *win = newwin(MAP_WIDTH, MAP_HEIGHT, startx, starty);
    WINDOW *info = newwin(INFO_BOARD_SIZE_X, INFO_BOARD_SIZE_Y, 0, (COLS-INFO_BOARD_SIZE_Y)/2);

    box(stdscr, 5, 0);
    box(win, 0, 0);
    wprintw(info, " Current Tile: %x\n", MAP[PLAYER_START_X-offsetx-2][PLAYER_START_Y-offsety-2].type);
    wprintw(info, " Times Dug: %d\n", MAP[PLAYER_START_X-offsetx-2][PLAYER_START_Y-offsety-2].dug);
    
    refresh();
    wrefresh(win); 
    wrefresh(info);
    
    while (true) {
        drawMap(win, offsetx, offsety, d, startx, starty);
        d = handleKeyPressed(getch(), &offsetx, &offsety);

        werase(info);
        werase(win);
        
        wprintw(info, " Current Tile: %x\n", MAP[PLAYER_START_X-offsetx-2][PLAYER_START_Y-offsety-2].type);
        wprintw(info, " Times Dug: %d\n", MAP[PLAYER_START_X-offsetx-2][PLAYER_START_Y-offsety-2].dug);

        wrefresh(win);
        wrefresh(info);
        refresh();
        if (MAP[PLAYER_START_X-offsetx-2][PLAYER_START_Y-offsety-2].type == OCCUPIED && MAP[PLAYER_START_X-offsetx-2][PLAYER_START_Y-offsety-2].dug == DIG_WIN) {
            getFlag();
        }
    }
	endwin();	
}

/* in use */
void drawMap(WINDOW* win, int offsetx, int offsety, Direction d, int startx, int starty) {
    drawPlayer(d);
    mvwin(win, startx-offsetx, starty-offsety);
    box(win, 0, 0);
    wrefresh(win);
}

/* in use */
void drawPlayer(Direction dir) {
    attron(COLOR_PAIR(1));
    switch (dir) {
        case UP:
            mvaddch(LINES/2, COLS/2, ACS_UARROW);
            break;
        case DOWN:
            mvaddch(LINES/2, COLS/2, ACS_DARROW);
            break;
        case LEFT:
            mvaddch(LINES/2, COLS/2, ACS_LARROW);
            break;
        case RIGHT:
            mvaddch(LINES/2, COLS/2, ACS_RARROW);
            break;
        default:
            break;
    }
    attroff(COLOR_PAIR(1));
}

/* in use */
void initMap() {
    int location_x = rand() % (MAP_WIDTH-2);
    int location_y = rand() % (MAP_HEIGHT-2);
    for (int i = 0; i < MAP_WIDTH-2; i++) {
        for (int j = 0; j < MAP_HEIGHT-2; j++) {
            MAP[i][j].x = i;
            MAP[i][j].y = j;
            if (i == location_x && j == location_y) {
                MAP[i][j].type = OCCUPIED;
            }
            else {
                MAP[i][j].type = EMPTY;
            }
        }
    }
}

/* in use */
void initGame() {
    initscr();
    start_color();
    curs_set(0);
    init_pair(1, COLOR_GREEN, COLOR_BLACK);
    initMap();
}

/* in use*/
Direction handleKeyPressed(char key, int* offsetx, int* offsety) {
    switch (key) {
        case 'w':
            (*offsetx)-=PLAYER_SPEED;
            return UP;
        case 'a':
            (*offsety)-=PLAYER_SPEED;
            return LEFT;
        case 's':
            (*offsetx)+=PLAYER_SPEED;
            return DOWN;
        case 'd':
            (*offsety)+= PLAYER_SPEED;
            return RIGHT;
        case ' ':
            dig(*offsetx, *offsety);
            return UP;
        case 'q':
            exit(0);
        default:
            return UP;
    }
}

/* in use */
void dig(int offsetx, int offsety) {
    MAP[PLAYER_START_X-offsetx-2][PLAYER_START_Y-offsety-2].dug++;
}

/* in use */
void getFlag() {
    endwin();
    printf("You won!");
    /* add flag system here */
    exit(0);
}