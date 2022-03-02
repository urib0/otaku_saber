#ifndef OTAKU_SABER_H
#define OTAKU_SABER_H

typedef signed char     c;
typedef unsigned char   uc;
typedef signed int      i;
typedef unsigned int    ui;
typedef signed long     l;
typedef unsigned long   ul;

#define PUSH_NONE       uc(0b000000)
#define PUSH_LONG       uc(0b100000)
#define PUSH_L          uc(0b010000)
#define PUSH_C          uc(0b001000)
#define PUSH_R          uc(0b000100)
#define PUSH_A          uc(0b000010)
#define PUSH_B          uc(0b000001)

enum MODE{
    MODE_SLEEP,
    MODE_NORMAL,
    MODE_DEBUG
};

#endif