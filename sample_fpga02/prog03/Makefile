TARGET = sloT

SOCEDS_DEST_ROOT = /mnt/c/intelFPGA/22.1/embedded
SRCS = main.c
OBJS = $(SRCS:.c=.o)
CROSS_COMPILE = arm-linux-gnueabihf-
CFLAGS = -Dsoc_cv_av -static -g -Wall  -I${SOCEDS_DEST_ROOT}/ip/altera/hps/altera_hps/hwlib/include -I${SOCEDS_DEST_ROOT}/ip/altera/hps/altera_hps/hwlib/include/soc_cv_av
LDFLAGS =  -g -Wall -lpthread
CC = $(CROSS_COMPILE)gcc
ARCH= arm

build: $(TARGET)

$(TARGET): $(OBJS)
	$(CC) $(OBJS) $(LDFLAGS) -o $(TARGET)

%.o : %.c
	$(CC) $(CFLAGS) -c $< -o $@

.PHONY: clean
	rm -f $(TARGET) *.a *~
