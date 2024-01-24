/*****************************************************************************/
/*                                                                           */
/*                                _mikey.h                                   */
/*                                                                           */
/* Atari Lynx, Mikey chip register hardware structures                       */
/*                                                                           */
/*                                                                           */
/* This software is provided 'as-is', without any expressed or implied       */
/* warranty.  In no event will the authors be held liable for any damages    */
/* arising from the use of this software.                                    */
/*                                                                           */
/* Permission is granted to anyone to use this software for any purpose,     */
/* including commercial applications, and to alter it and redistribute it    */
/* freely, subject to the following restrictions:                            */
/*                                                                           */
/* 1. The origin of this software must not be misrepresented; you must not   */
/*    claim that you wrote the original software. If you use this software   */
/*    in a product, an acknowledgment in the product documentation would be  */
/*    appreciated but is not required.                                       */
/* 2. Altered source versions must be plainly marked as such, and must not   */
/*    be misrepresented as being the original software.                      */
/* 3. This notice may not be removed or altered from any source              */
/*    distribution.                                                          */
/*                                                                           */
/*****************************************************************************/

#ifndef __MIKEY_H
#define __MIKEY_H

// Timer structure 
typedef struct _mikey_timer {
    unsigned char backup;
    unsigned char controla;
    unsigned char count;
    unsigned char controlb;
} _mikey_timer;

typedef struct _mikey_all_timers {
    struct _mikey_timer timer[8];
} _mikey_all_timers;

// Audio channel structure 
typedef struct _mikey_audio {
    unsigned char volume;
    unsigned char feedback;
    unsigned char output;
    unsigned char shift;
    unsigned char backup;
    unsigned char control;
    unsigned char counter;
    unsigned char other;
} _mikey_audio;

// Structure for Mikey register offsets
struct __mikey {
    struct _mikey_timer timer0;  // 0xFD00 aka HCOUNT
    struct _mikey_timer timer1;  // 0xFD04 aka MAG0A
    struct _mikey_timer timer2;  // 0xFD08 aka VCOUNT
    struct _mikey_timer timer3;  // 0xFD0C aka MAG0B
    struct _mikey_timer timer4;  // 0xFD10 aka SERIALRATE
    struct _mikey_timer timer5;  // 0xFD14 aka MAG1A
    struct _mikey_timer timer6;  // 0xFD18
    struct _mikey_timer timer7;  // 0xFD1C aka MAG1B
    struct _mikey_audio audio0;  // 0xFD20
    struct _mikey_audio audio1;  // 0xFD28
    struct _mikey_audio audio2;  // 0xFD30
    struct _mikey_audio audio3;  // 0xFD38
    unsigned char attenreg0;     // 0xFD40  Only available in Lynx 2 hardware
    unsigned char attenreg1;     // 0xFD41      |
    unsigned char attenreg2;     // 0xFD42      |
    unsigned char attenreg3;     // 0xFD43      |
    unsigned char mpan;          // 0xFD44      |
    unsigned char unused0[11];   // 0xFD45 - 0xFD4F  not used
    unsigned char mstereo;       // 0xFD50  stereo control bits, only in Lynx 2 hardware
    unsigned char unused1[47];   // 0xFD51 - 0xFD7F  not used
    unsigned char intrst;        // 0xFD80  interrupt poll 0
    unsigned char intset;        // 0xFD81  interrupt poll 1
    unsigned char unused2[2];    // 0xFD82 - 0xFD83  not used
    unsigned char magrdy0;       // 0xFD84  mag tape channel0 ready bit
    unsigned char magrdy1;       // 0xFD85  mag tape channel1 ready bit
    unsigned char audin;         // 0xFD86  audio in
    unsigned char sysctl1;       // 0xFD87  control bits
    unsigned char mikeyhrev;     // 0xFD88  mikey hardware revision
    unsigned char mikeysrev;     // 0xFD89  mikey software revision
    unsigned char iodir;         // 0xFD8A  parallel i/o data dir
    unsigned char iodat;         // 0xFD8B  parallel data
    unsigned char serctl;        // 0xFD8C  serial control register
    unsigned char serdat;        // 0xFD8D  serial data
    unsigned char unused3[2];    // 0xFD8E - 0xFD8F  not used
    unsigned char sdoneack;      // 0xFD90  suzy done acknowledge
    unsigned char cpusleep;      // 0xFD91  cpu bus request disable
    unsigned char dispctl;       // 0xFD92  video bus request enable, viddma
    unsigned char pbkup;         // 0xFD93  magic 'P' count
    union {
      unsigned char* dispadr;    // 0xFD94 - 0xFD95  start address of video display
      struct {
        unsigned char dispadrlo; // 0xFD94  display address low byte
        unsigned char dispadrhi; // 0xFD95  display address high byte
      };
    };
    unsigned char unused4[6];    // 0xFD96 - 0xFD9B not used
    unsigned char mtest0;        // 0xFD9C
    unsigned char mtest1;        // 0xFD9D
    unsigned char mtest2;        // 0xFD9E
    unsigned char unused5;       // 0xFD9F  not used
    unsigned char palette[32];   // 0xFDA0 - 0xFDBF  palette 32 bytes
    unsigned char unused6[64];   // 0xFDC0 - 0xFDFF  not used
    unsigned char bootrom[504];  // 0xFE00 - 0xFFD8  boot rom
    unsigned char reserved;      // 0xFFD8  reserved for future hardware
    unsigned char mapctl;        // 0xFFF9  map control register
    struct {
        unsigned char *nmi;      // 0xFFFA  NMI vector
        unsigned char *reset;    // 0xFFFB  reset vector
        unsigned char *irq;      // 0xFFFC  IRQ vector
    } vectors;
};

// TIM_CONTROLA control bit definitions
#define ENABLE_INT       0x80
#define RESET_DONE       0x40
#define ENABLE_RELOAD    0x10
#define ENABLE_COUNT     0x08

// AUD_CONTROL control bit definitions
#define FEEDBACK_7       0x80
#define ENABLE_INTEGRATE 0x20

// Audio and timer clock settings for source period 
#define AUD_LINKING      0x07
#define AUD_64           0x06
#define AUD_32           0x05
#define AUD_16           0x04
#define AUD_8            0x03
#define AUD_4            0x02
#define AUD_2            0x01
#define AUD_1            0x00

// TIM_CONTROLB control bit definitions
#define TIMER_DONE       0x08
#define LAST_CLOCK       0x04
#define BORROW_IN        0x02
#define BORROW_OUT       0x01

// MPAN and MSTEREO registers bit definitions
#define LEFT3_SELECT     0x80
#define LEFT2_SELECT     0x40
#define LEFT1_SELECT     0x20
#define LEFT0_SELECT     0x10
#define RIGHT3_SELECT    0x08
#define RIGHT2_SELECT    0x04
#define RIGHT1_SELECT    0x02
#define RIGHT0_SELECT    0x01
#define LEFT_ATTENMASK   0xF0
#define RIGHT_ATTENMASK  0x0F

// Interrupt Reset and Set bit definitions
#define TIMER7_INT       0x80
#define TIMER6_INT       0x40
#define TIMER5_INT       0x20
#define TIMER4_INT       0x10
#define TIMER3_INT       0x08
#define TIMER2_INT       0x04
#define TIMER1_INT       0x02
#define TIMER0_INT       0x01
#define SERIAL_INT       TIMER4_INT
#define VERTICAL_INT     TIMER2_INT
#define HORIZONTAL_INT   TIMER0_INT

// SYSCTL1 bit definitions
#define POWERON          0x02
#define CART_ADDR_STROBE 0x01

//  IODIR and IODAT bit definitions
#define AUDIN_BIT        0x10 // different from AUDIN address
#define READ_ENABLE      0x10 // same bit for AUDIN_BIT
#define RESTLESS         0x08
#define NOEXP            0x04 // if set, redeye is not connected
#define CART_ADDR_DATA   0x02 //
#define CART_POWER_OFF   0x02 // same bit for CART_ADDR_DATA
#define EXTERNAL_POWER   0x01 //

// SERCTL bit definitions for write operations
#define TXINTEN          0x80
#define RXINTEN          0x40
#define PAREN            0x01
#define RESETERR         0x08
#define TXOPEN           0x04
#define TXBRK            0x02
#define PAREVEN          0x01

// SERCTL bit definitions for read operations
#define TXRDY            0x80
#define RXRDY            0x40
#define TXEMPTY          0x20
#define PARERR           0x10
#define OVERRUN          0x08
#define FRAMERR          0x04
#define RXBRK            0x02
#define PARBIT           0x01

// DISPCTL bit definitions
#define DISP_COLOR       0x08 // must be set to 1
#define DISP_FOURBIT     0x04 // must be set to 1
#define DISP_FLIP        0x02 //
#define DMA_ENABLE       0x01 // must be set to 1

// MTEST0 bit definitions
#define AT_CNT16         0x80
#define AT_TEST          0x40
#define XCLKEN           0x20
#define UART_TURBO       0x10
#define ROM_SEL          0x08
#define ROM_TEST         0x04
#define M_TEST           0x02
#define CPU_TEST         0x01

// MTEST1 bit definitions
#define P_CNT16          0x40
#define REF_CNT16        0x20
#define VID_TRIG         0x10
#define REF_TRIG         0x08
#define VID_DMA_DIS      0x04
#define REF_FAST         0x02
#define REF_DIS          0x01

// MTEST2 bit definitions
#define V_STROBE         0x10
#define V_ZERO           0x08
#define H_120            0x04
#define H_ZERO           0x02
#define V_BLANKEF        0x01

// MAPCTL flag definitions
#define TURBO_DISABLE    0x80
#define VECTOR_SPACE     0x08
#define ROM_SPACE        0x04
#define MIKEY_SPACE      0x02
#define SUZY_SPACE       0x01

#endif

