#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <limits.h>
#include <error.h>
#include <errno.h>
#include <unistd.h>
#include <linux/input.h>
#include "sloT.h"

#include <sys/mman.h>
#include "hwlib.h"
#include "socal/socal.h"
#include "socal/hps.h"
#include "socal/alt_gpio.h"
#include "../hps_0.h"

#define INPUT_DEV_NODE "/dev/input/by-path/platform-ffc04000.i2c-event"
#define SYSFS_DEVICE_DIR "/sys/devices/platform/soc/ffc04000.i2c/i2c-0/0-0053/"

#define HW_REGS_BASE (ALT_STM_OFST)
#define HW_REGS_SPAN (0x04000000)
#define HW_REGS_MASK (HW_REGS_SPAN - 1)

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

bool slide[4];

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
                // printf("%d, %d, %d, %d\n",slide[0], slide[1], slide[2], slide[3]);
                sloT[i].stop_requested = true;
            }
        // if (ch == KEYS_MID[COLS]) reset_sloT();
        if (slide[COLS])
            reset_sloT();
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
        // printf("%d, %d, %d, %d\n",slide[0], slide[1], slide[2], slide[3]);
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


static void
write_sysfs_cntl_file(const char *dir_name, const char *file_name,
                      const char *write_str)
{
    char path[PATH_MAX];
    int path_length;
    int file_fd;
    int result;

    // create the path to the file we need to open
    path_length = snprintf(path, PATH_MAX, "%s/%s", dir_name, file_name);
    if (path_length < 0)
        error(1, 0, "path output error");
    if (path_length >= PATH_MAX)
        error(1, 0, "path length overflow");

    // open the file
    file_fd = open(path, O_WRONLY | O_SYNC);
    if (file_fd < 0)
        error(1, errno, "could not open file '%s'", path);
        
    // write the string to the file
    result = write(file_fd, write_str, strlen(write_str));
    if (result < 0)
        error(1, errno, "writing to '%s'", path);
    if ((size_t)(result) != strlen(write_str))
        error(1, errno, "buffer underflow writing '%s'", path);

    // close the file
    result = close(file_fd);
    if (result < 0)
        error(1, errno, "could not close file '%s'", path);
}

#define MAX_EVENT 64

int main(void)
{
    int result;
    int event_dev_fd;
    const char *input_dev_node = INPUT_DEV_NODE;
    struct input_event the_event[MAX_EVENT];
    pthread_t   thread;

    pthread_create(&thread, NULL, main_sub, NULL);

    // enable adxl
    write_sysfs_cntl_file(SYSFS_DEVICE_DIR, "disable", "0");

    // set the sample rate to maximum
    write_sysfs_cntl_file(SYSFS_DEVICE_DIR, "rate", "15");

    // do not auto sleep
    write_sysfs_cntl_file(SYSFS_DEVICE_DIR, "autosleep", "0");

    void *virtual_base;
    int fd;
    int led_mask;
    int sw;
    void *h2p_lw_led_addr;
    void *h2p_lw_sw_addr;

    // open the event device node
    event_dev_fd = open(input_dev_node, O_RDONLY | O_SYNC);
    if (event_dev_fd < 0)
        error(1, errno, "could not open file '%s'", input_dev_node);

    if ((fd = open( "/dev/mem", (O_RDWR|O_SYNC))) == -1) {
        printf("ERROR: could not open \"/dev/mem\"...\n");
        return 1;
    }
    virtual_base = mmap(NULL, HW_REGS_SPAN, (PROT_READ|PROT_WRITE), MAP_SHARED, fd, HW_REGS_BASE);
    if (virtual_base == MAP_FAILED) {
        printf("ERROR: mmap() failed...\n");
        close(fd);
        return 1;
    }

    h2p_lw_led_addr = virtual_base
    + ((unsigned long)(ALT_LWFPGASLVS_OFST + MYPIO_0_BASE)
        & (unsigned long)(HW_REGS_MASK));
    h2p_lw_sw_addr = virtual_base
    + ((unsigned long)(ALT_LWFPGASLVS_OFST + DIPSW_PIO_BASE)
        & (unsigned long)(HW_REGS_MASK));

    while (1) {
        int i;
         
        result = read(event_dev_fd, the_event,
                      sizeof(struct input_event)*MAX_EVENT);
        if (result < 0)
            error(1, errno, "read from '%s'", input_dev_node);
        
        // control led
        *(uint32_t *)h2p_lw_led_addr = led_mask;
        // control sw
        sw = *(uint32_t *)h2p_lw_sw_addr;

        if (sw & 0x01)
            slide[0] = true;
        else
            slide[0] = false;
        if (sw & 0x02)
            slide[1] = true;
        else
            slide[1] = false;
        if (sw & 0x04)
            slide[2] = true;
        else
            slide[2] = false;
        if (sw & 0x08)
            slide[3] = true;
        else
            slide[3] = false;
        // printf("%d, %d, %d, %d\n", slide[0], slide[1], slide[2], slide[3]);
        // printf("--------------\n");
        // if (sw & 0x01) { // SW0の状態 (ビット0)
        //     printf("  SW0: ON\n");
        // } else {
        //     printf("  SW0: OFF\n");
        // }

        // if (sw & 0x02) { // SW1の状態 (ビット1)
        //     printf("  SW1: ON\n");
        // } else {
        //     printf("  SW1: OFF\n");
        // }
        
        // if (sw & 0x04) { // SW2の状態 (ビット2)
        //     printf("  SW2: ON\n");
        // } else {
        //     printf("  SW2: OFF\n");
        // }

        // if (sw & 0x08) { // SW3の状態 (ビット3)
        //     printf("  SW3: ON\n");
        // } else {
        //     printf("  SW3: OFF\n");
        // }
        // printf("----------------------------------------\n");
        led_mask = 0x18;
        for (i = 0; i < result/sizeof(struct input_event); i++) {

            // printf("type %d, code %d, value %d\n",
            //         the_event[i].type, the_event[i].code, the_event[i].value);

            int sw_0 = sw && 0x01;
            if (the_event[i].code == sw_0) {
                int value;
                if (the_event[i].value >= 0) {
                    value = the_event[i].value >> 4;
                    while (value >= 2) {
                        led_mask >>= 1;
                        value >>= 1;
                    }   
                } else {
                    value = -the_event[i].value >> 4;
                    while (value >= 2) {
                        led_mask <<= 1;
                        value >>= 1;
                    }
                }
            }
        }
    }

    // clean up our memory mapping and exit
    if (munmap( virtual_base, HW_REGS_SPAN ) != 0) {
        printf("ERROR: munmap() failed...\n");
        close(fd);
        return 1;
    }
    close(fd);
    return 0;
}