#ifndef OTAKU_SABER_H
#define OTAKU_SABER_H

typedef signed char     c;
typedef unsigned char   uc;
typedef signed int      i;
typedef unsigned int    ui;
typedef signed long     l;
typedef unsigned long   ul;

#define PUSH_L          uc(0b10000)
#define PUSH_C          uc(0b01000)
#define PUSH_R          uc(0b00100)
#define PUSH_A          uc(0b00010)
#define PUSH_B          uc(0b00001)
#define PUSH_NONE       uc(0b0000)

#endif