/*****************************************************************************/
/*                                                                           */
/*                                _suzy.h                                    */
/*                                                                           */
/* Atari Lynx, Suzy chip register hardware structures                        */
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

#ifndef __SUZY_H
#define __SUZY_H

// Sprite control block (SCB) defines

// SPRCTL0 bit definitions
enum {
    BITS_MASK          = 0xC0,
    FOUR_PER_PIXEL     = 0xC0,
    THREE_PER_PIXEL    = 0x80,
    TWO_PER_PIXEL      = 0x40,
    ONE_PER_PIXEL      = 0x00,
    HFLIP              = 0x20,
    VFLIP              = 0x10,
    SHADOW_SPRITE      = 0x07,
    XOR_SPRITE         = 0x06,
    NONCOLL_SPRITE     = 0x05,
    NORMAL_SPRITE      = 0x04,
    BOUNDARY_SPRITE    = 0x03,
    BSHADOW_SPRITE     = 0x02,
    BACKNONCOLL_SPRITE = 0x01,
    BACKGROUND_SPRITE  = 0x00
};

// SPRCTL1 bit definitions
enum {
    LITERAL       = 0x80,
    PACKED        = 0x00,
    ALGO_3        = 0x40,  // Do not use algo 3 shifter (buggy) 
    RELOAD_MASK   = 0x30,
    RELOAD_NONE   = 0x00,
    RELOAD_HV     = 0x10,
    RELOAD_HVS    = 0x20,
    RELOAD_HVST   = 0x30,
    REUSE_PALETTE = 0x08,
    SKIP_SPRITE   = 0x04,
    DRAW_UP       = 0x02,
    DRAW_LEFT     = 0x01
};

// Sprite control block  with all attributes
typedef struct scb_hvst_pal4 {  
    unsigned char sprctl0; // set RELOAD_HVST
    unsigned char sprctl1;
    unsigned char sprcoll;
    unsigned char *next;
    unsigned char *data;
    signed int hpos;
    signed int vpos;
    unsigned int hsize;
    unsigned int vsize;
    unsigned int stretch;
    unsigned int tilt;
    unsigned char penpal[8];
} scb_hvst_pal4;

// Sprite control block with all attributes except penpal
typedef struct scb_hvst {
    unsigned char sprctl0; // set RELOAD_HVST | REUSE_PALETTE
    unsigned char sprctl1;
    unsigned char sprcoll;
    unsigned char *next;
    unsigned char *data;
    signed int hpos;
    signed int vpos;
    unsigned int hsize;
    unsigned int vsize;
    unsigned int stretch;
    unsigned int tilt;
} scb_hvst;

// Sprite control block without stretch, tilt and penpal
typedef struct scb_hv {
    unsigned char sprctl0; // set RELOAD_HV | REUSE_PALETTE
    unsigned char sprctl1;
    unsigned char sprcoll;
    unsigned char *next;
    unsigned char *data;
    signed int hpos;
    signed int vpos;
    unsigned int hsize;
    unsigned int vsize;
} scb_hv;

// Sprite control block with palette and without stretch, tilt
typedef struct scb_hv_pal4 {             
    unsigned char sprctl0; // set RELOAD_HV 
    unsigned char sprctl1;
    unsigned char sprcoll;
    char *next;
    unsigned char *data;
    signed int hpos;
    signed int vpos;
    unsigned int hsize;
    unsigned int vsize;
    unsigned char penpal[8];
} scb_hv_pal4;

// Sprite control block without tilt and palette
typedef struct scb_hvs {
    unsigned char sprctl0;
    unsigned char sprctl1;
    unsigned char sprcoll;
    char *next;
    unsigned char *data;
    signed int hpos;
    signed int vpos;
    unsigned int hsize;
    unsigned int vsize;
    unsigned int stretch;
} scb_hvs;

// Sprite control block with palette and without tilt
typedef struct scb_hvs_pal4 {
    unsigned char sprctl0; // set RELOAD_HVS
    unsigned char sprctl1;
    unsigned char sprcoll;
    char *next;
    unsigned char *data;
    signed int hpos;
    signed int vpos;
    unsigned int hsize;
    unsigned int vsize;
    unsigned int stretch;
    unsigned char penpal[8];
} scb_hvs_pal4;

// Sprite control block without stretch, tilt, palette
typedef struct scb_none {
    unsigned char sprctl0; // set RELOAD_NONE | REUSE_PALETTE
    unsigned char sprctl1;
    unsigned char sprcoll;
    char *next;
    unsigned char *data;
    signed int hpos;
    signed int vpos;
} scb_none;

// Sprite control block with palette without size, stretch, tilt
typedef struct scb_none_pal4 {
    unsigned char sprctl0; // set RELOAD_NONE
    unsigned char sprctl1;
    unsigned char sprcoll;
    char *next;
    unsigned char *data;
    signed int hpos;
    signed int vpos;
    unsigned char penpal[8];
} scb_none_pal4;

// Miscellaneous Mikey definitions

// SPRGO bit definitions
enum {
    SPRITE_GO = 0x01,  // sprite process start bit
    EVER_ON   = 0x04   // everon detector enable
};

// SPRSYS bit definitions for write operations
enum {
    SIGNMATH        = 0x80,  // signed math
    ACCUMULATE      = 0x40,  // accumulate multiplication results
    NO_COLLIDE      = 0x20,  // do not collide with any sprites (also SPRCOLL bit definition)
    VSTRETCH        = 0x10,  // stretch v
    LEFTHAND        = 0x08,
    UNSAFEACCESSRST = 0x04,  // unsafe access reset
    SPRITESTOP      = 0x02  // request to stop sprite process
};

// SPRSYS bit definitions for read operations
enum {
    MATHWORKING   = 0x80,  // math operation in progress
    MATHWARNING   = 0x40,  // accumulator overflow on multiple or divide by zero
    MATHCARRY     = 0x20,  // last carry bit
    VSTRETCHING   = 0x10,
    LEFTHANDED    = 0x08,
    UNSAFEACCESS  = 0x04,  // unsafe access performed
    SPRITETOSTOP  = 0x02,  // requested to stop 
    SPRITEWORKING = 0x01  // sprite process is active
};

// JOYSTICK bit definitions
enum {
    JOY_RIGHT      = 0x10,
    JOY_LEFT       = 0x20,
    JOY_DOWN       = 0x40,
    JOY_UP         = 0x80,
    OPTION1_BUTTON = 0x08,
    OPTION2_BUTTON = 0x04,
    INNER_BUTTON   = 0x02,
    OUTER_BUTTON   = 0x01,
    A_BUTTON       = OUTER_BUTTON,
    B_BUTTON       = INNER_BUTTON
};

// SWITCHES bit definitions
enum {
    CART1_IO_INACTIVE = 0x04,
    CART0_IO_INACTIVE = 0x02,
    BUTTON_PAUSE      = 0x01
};

// Structure for unsigned multiplications math registers
struct _math_unsigned_multiply {
    unsigned int factor1;         // 0xFC52 - 0xFC53
    unsigned int factor2;         // 0xFC54 - 0xFC55  write starts multiply
    unsigned char unused2[10];    // 0xFC56 - 0xFC5F  do not use
    unsigned long product;        // 0xFC60 - 0xFC63
    unsigned char unused3[8];     // 0xFC64 - 0xFC6B  do not use
    unsigned long accumulate;     // 0xFC6C - 0xFC6F
};

struct _math_signed_multiply {
    int factor1;                  // 0xFC52 - 0xFC53
    int factor2;                  // 0xFC54 - 0xFC55  write starts multiply
    unsigned char unused2[10];    // 0xFC56 - 0xFC5F  do not use
    long product;                 // 0xFC60 - 0xFC63
    unsigned char unused3[8];     // 0xFC64 - 0xFC6B  do not use
    long accumulate;              // 0xFC6C - 0xFC6F
};

struct _math_divide {
    unsigned long quotient;       // 0xFC52 - 0xFC53
    unsigned int divisor;         // 0xFC54 - 0xFC55
    unsigned char unused2[8];     // 0xFC56 - 0xFC5F  do not use
    unsigned int dividend2;       // 0xFC60 - 0xFC61
    unsigned int dividend1;       // 0xFC62 - 0xFC63 write starts divide
    unsigned char unused3[8];     // 0xFC64 - 0xFC6B  do not use
    unsigned long remainder;      // 0xFC6C - 0xFC6F
};

// Structure for Suzy register offsets 
struct __suzy {
    unsigned char *tmpadr;        // 0xFC00* temporary address 
    unsigned int  tiltacum;       // 0xFC02* accumulator for tilt value
    unsigned int  hoff;           // 0xFC04  offset to H edge of screen
    unsigned int  voff;           // 0xFC06  offset to V edge of screen
    unsigned char *vidbas;        // 0xFC08  base address of video build buffer
    unsigned char *collbas;       // 0xFC0A  base address of collision buffer
    unsigned char *vidadr;        // 0xFC0C* current video build address
    unsigned char *colladr;       // 0xFC0E* current collision buffer address
    unsigned char *scbnext;       // 0xFC10  address of next SCB
    unsigned char *sprdline;      // 0xFC12  start of sprite data line address
    unsigned int  hposstrt;       // 0xFC14  start hpos
    unsigned int  vposstrt;       // 0xFC16  start vpos
    unsigned int  sprhsiz;        // 0xFC18  sprite h size
    unsigned int  sprvsiz;        // 0xFC1A  sprite v size
    unsigned int  stretch;        // 0xFC1C  H size adder
    unsigned int  tilt;           // 0xFC1E  H position adder
    unsigned int  sprdoff;        // 0xFC20  offset to next sprite data line
    unsigned int  sprvpos;        // 0xFC22  current vpos
    unsigned int  colloff;        // 0xFC24  offset to collision depository
    unsigned int  vsizacum;       // 0xFC26  vertical size accumulator
    unsigned int  hsizoff;        // 0xFC28  horizontal size offset
    unsigned int  vsizoff;        // 0xFC2A  vertical size offset
    unsigned char *scbadr;        // 0xFC2C  address of current SCB
    unsigned char *procadr;       // 0xFC2E  address of current sprite data proc
    unsigned char unused0[32];    // 0xFC30 - 0xFC4F  reserved
    unsigned char unused1[2];     // 0xFC50 - 0xFC51  do not use
    union {
        struct {
            unsigned char mathd;      // 0xFC52
            unsigned char mathc;      // 0xFC53
            unsigned char mathb;      // 0xFC54
            unsigned char matha;      // 0xFC55  write starts a multiply operation
            unsigned char mathp;      // 0xFC56
            unsigned char mathn;      // 0xFC57
            unsigned char unused2[8]; // 0xFC58 - 0xFC5F  do not use
            unsigned char mathh;      // 0xFC60
            unsigned char mathg;      // 0xFC61
            unsigned char mathf;      // 0xFC62
            unsigned char mathe;      // 0xFC63  write starts a divide operation
            unsigned char unused3[8]; // 0xFC64 - 0xFC6B  do not use
            unsigned char mathm;      // 0xFC6C
            unsigned char mathl;      // 0xFC6D
            unsigned char mathk;      // 0xFC6E
            unsigned char mathj;      // 0xFC6F
        };
        struct _math_unsigned_multiply math_unsigned_multiply;
        struct _math_signed_multiply math_signed_multiply;
        struct _math_divide math_divide;
    };
    unsigned char unused4[16];        // 0xFC70 - 0xFC7F  do not use
    unsigned char sprctl0;            // 0xFC80  sprite control bits 0
    unsigned char sprctl1;            // 0xFC81  sprite control bits 1
    unsigned char sprcoll;            // 0xFC82  sprite collision number
    unsigned char sprinit;            // 0xFC83  sprite initialization bits
    unsigned char unused5[4];         // 0xFC84 - 0xFC87  unused
    unsigned char suzyhrev;           // 0xFC88  suzy hardware revision
    unsigned char suzysrev;           // 0xFC89  suzy software revision
    unsigned char unused6[6];         // 0xFC8A - 0xFC8F  unused
    unsigned char suzybusen;          // 0xFC90  suzy bus enable
    unsigned char sprgo;              // 0xFC91  sprite process start bit
    unsigned char sprsys;             // 0xFC92  sprite control bits
    unsigned char unused7[29];        // 0xFC93 - 0xFCAF  unused
    unsigned char joystick;           // 0xFCB0  joystick and buttons
    unsigned char switches;           // 0xFCB1  other switches
    unsigned char rcart0;             // 0xFCB2  cart0 read/write
    unsigned char rcart1;             // 0xFCB3  cart1 read/write
    unsigned char unused8[8];         // 0xFCB4 - 0xFCBF  unused
    unsigned char leds;               // 0xFCC0  leds
    unsigned char unused9;            // 0xFCC1  unused
    unsigned char iostatus;           // 0xFCC2  parallel IO port status
    unsigned char iodata;             // 0xFCC3  parallel IO port data
    unsigned char howie;              // 0xFCC4  howie 
                                      // 0xFCC5 - 0xFCFF  unused
};

#endif

