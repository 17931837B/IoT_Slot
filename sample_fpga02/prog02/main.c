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

int
main(void)
{
    int result;
    int event_dev_fd;
    const char *input_dev_node = INPUT_DEV_NODE;
    struct input_event the_event[MAX_EVENT];

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
        
        if (sw & 0x01) { // SW0の状態 (ビット0)
            printf("  SW0: ON\n");
        } else {
            printf("  SW0: OFF\n");
        }

        if (sw & 0x02) { // SW1の状態 (ビット1)
            printf("  SW1: ON\n");
        } else {
            printf("  SW1: OFF\n");
        }
        
        if (sw & 0x04) { // SW2の状態 (ビット2)
            printf("  SW2: ON\n");
        } else {
            printf("  SW2: OFF\n");
        }

        if (sw & 0x08) { // SW3の状態 (ビット3)
            printf("  SW3: ON\n");
        } else {
            printf("  SW3: OFF\n");
        }
        printf("----------------------------------------\n");
        led_mask = 0x18;
        for (i = 0; i < result/sizeof(struct input_event); i++) {

            printf("type %d, code %d, value %d\n",
                    the_event[i].type, the_event[i].code, the_event[i].value);

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