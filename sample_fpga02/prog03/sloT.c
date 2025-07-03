#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>
#include <unistd.h>
#include <termios.h>
#include <fcntl.h>
#include <string.h>
#include "sloT.h"
#include <unistd.h>
#include <stdbool.h>
#include <pthread.h>

#define SYMBOL_TYPES 4
#define ROWS 3 // odd num
#define COLS 3
#define SYMBOL_HEIGHT 5
#define SYMBOL_WIDTH 10
#define FRAME_HEIGHT 2
#define FRAME_WIDTH 3

typedef struct {
    int symbols[ROWS+1];
    int offset;
    bool is_stopped;
    bool stop_requested; // A S D key pushed
} SloTColumn;

SloTColumn sloT[COLS];
bool finished;
const int display_height = (SYMBOL_HEIGHT+FRAME_HEIGHT) *ROWS -FRAME_HEIGHT;
const int display_width = (SYMBOL_WIDTH+FRAME_WIDTH) *COLS +FRAME_WIDTH;
bool bitmap[(SYMBOL_HEIGHT+FRAME_HEIGHT) *ROWS -FRAME_HEIGHT][(SYMBOL_WIDTH+FRAME_WIDTH) *COLS +FRAME_WIDTH];

const char* SYMBOL_BITMAPS[SYMBOL_TYPES][SYMBOL_HEIGHT] = {{
    "   #####  ",
    "  #      ",
    "   ####   ",
    "       #  ",
    "  #####   "},{
    "    ##    ",
    "   #  #   ",
    "   #  #   ",
    "    ##  # ",
    " ###  ## "},{
    "   ####   ",
    "  #    #  ",
    " #      # ",
    "  #    #  ",
    "   ####   "},{
    " ######## ",
    "     #    ",
    "     #    ",
    "    #     ",
    "    #     "}
};
const char FRAME_BITMAP[FRAME_WIDTH] = " # ";
const char KEYS_MID[9] = "asdfghjkl";

void enable_raw_mode() {
    struct termios t;
    tcgetattr(0, &t);
    t.c_lflag &= ~(ICANON | ECHO);
    tcsetattr(0, TCSANOW, &t);
    fcntl(0, F_SETFL, O_NONBLOCK);
}

void reset_sloT() {
    for (int c = 0; c < COLS; ++c) {
        sloT[c].symbols[0] = rand() % SYMBOL_TYPES;
        for (int r = 0; r < ROWS; ++r)
            do sloT[c].symbols[r] = rand() % SYMBOL_TYPES; // avoid duplicates
                while (sloT[c].symbols[r+1] == sloT[c].symbols[r]);
        sloT[c].offset = rand() % (SYMBOL_HEIGHT+FRAME_HEIGHT);
        sloT[c].is_stopped = false;
        sloT[c].stop_requested = false;
    }
    finished = false;
}

void update_symbols(SloTColumn* col) {
    for (int i = ROWS; i > 0; --i)
        col->symbols[i] = col->symbols[i-1];
    while (col->symbols[0] == col->symbols[1])
        col->symbols[0] = rand() % SYMBOL_TYPES;
}

void update_offset(SloTColumn* col, int i) {
    col->offset--;
    if (col->offset <= 0) {
        if (col->stop_requested) {
            col->is_stopped = true;
            col->stop_requested = false;
        } else {
            update_symbols(col);
            col->offset = SYMBOL_HEIGHT+FRAME_HEIGHT;
        }
    }
}

void generate_bitmap() {
    memset(bitmap, false, display_height*display_width);
    int x, y;
    for (int c = 0; c < COLS; ++c) {
        int top = sloT[c].offset;
        for (int r = 0; r <= ROWS; ++r) {
            int symbol_id = sloT[c].symbols[r];
            for (int i = 0; i < SYMBOL_HEIGHT; ++i) {
                const char* line = SYMBOL_BITMAPS[symbol_id][i];
                y = (SYMBOL_HEIGHT+FRAME_HEIGHT) *r -top +i;
                if (y < 0 || y >= display_height) continue;
                for (int s = 0; s < SYMBOL_WIDTH; ++s) {
                    x = (SYMBOL_WIDTH+FRAME_WIDTH) *c +FRAME_WIDTH +s;
                    bitmap[y][x] = (line[s] == '#');
                }
            }
        }
    }
    for (y = 0; y < display_height; y++) { // frame
        for (int c = 0; c < COLS +1; ++c) {
            for (int f = 0; f < FRAME_WIDTH; f++) {
                x = (SYMBOL_WIDTH+FRAME_WIDTH) *c +f; 
                bitmap[y][x] = (FRAME_BITMAP[f] == '#');
            }            
        }
    }
}

void render_to_terminal() {
    // printf("\033[2J\033[H"); // clear
    // for (int i = 0; i < display_height; ++i) {
    //     for (int j = 0; j < display_width; j++) 
    //         printf(bitmap[i][j] ? "#" : " ");
    //     printf("\n");
    // }
}

void handle_input() {
    char ch;
    while (read(0, &ch, 1) > 0) {
        for (int i = 0; i < COLS; i++) 
            // if (ch == KEYS_MID[i])
            if (slide[i])
            {
                printf("%d, %d, %d, %d\n",slide[0], slide[1], slide[2], slide[3]);
                sloT[i].stop_requested = true;
            }
        if (ch == KEYS_MID[COLS]) reset_sloT();
    }
}

int get_symbol(const SloTColumn* col, int place) {
    return col->symbols[place]; // symbol at center
}
bool check_result() {
    int center = ROWS /2 ;
    for (int i = 1; i < COLS; i++) 
        if (get_symbol(&sloT[0], center) != get_symbol(&sloT[i], center))
            return false;
    return true;
}

void    *main_sub() {
    // while(1)
    // {
    //     printf("%d, %d, %d, %d\n", slide[0], slide[1], slide[2], slide[3]);
    //     printf("--------------\n");
    // }
    srand(time(NULL));
    enable_raw_mode();
    reset_sloT();

    while (1) {
        handle_input();
        for (int i = 0; i < COLS; ++i)
            if (!sloT[i].is_stopped)
                update_offset(&sloT[i], i);
        generate_bitmap();
        render_to_terminal();

        if (finished) {
            printf("\n>>> %s <<<\n", check_result() ? "SUCCESS" : "FAIL");
            sleep(1);
        } else {
            finished = true;
            for (int i = 0; i < COLS; i++) {
                if (!sloT[i].is_stopped) {
                    finished = false;
                    break;
                }
            }
        }

        usleep(1 *1000); // ms
    }
    return (NULL);
}