; Lynx system hardware includes
; Shawn Jefferson
; June 18th, 2004
;
; Reference:
;  Bastian Schick's Lynx Documentation
;  http://www.geocities.ws/SiliconValley/Byte/4242/lynx/
;

; ***
; *** Suzy Addresses
; ***

; SUZY registers from $FC00-$FC7F (both sprite and MATH) clear the upper byte
; when the lower byte is stored to.

; Sprite engine registers - *'ed values are used internally by SUZY and
; cannot be usefully initialized externally.

SUZY_BASE   = $FC00

TMPADRL     = $FC00 ; *
TMPADRH     = $FC01 ; *
TILTACUML   = $FC02 ; *
TILTACUMH   = $FC03 ; *
HOFFL       = $FC04
HOFFH       = $FC05
VOFFL       = $FC06
VOFFH       = $FC07
VIDBASL     = $FC08
VIDBASH     = $FC09
COLLBASL    = $FC0A
COLLBASH    = $FC0B
VIDADRL     = $FC0C ; *
VIDADRH     = $FC0D ; *
COLLADRL    = $FC0E ; *
COLLADRH    = $FC0F ; *
SCBNEXTL    = $FC10
SCBNEXTH    = $FC11
SPRDLINEL   = $FC12 ; *
SPRDLINEH   = $FC13 ; *
HPOSSTRTL   = $FC14 ; *
HPOSSTRTH   = $FC15 ; *
VPOSSTRTL   = $FC16 ; *
VPOSSTRTH   = $FC17 ; *
SPRHSIZL    = $FC18
SPRHSIZH    = $FC19
SPRVSIZL    = $FC1A
SPRVSIZH    = $FC1B
STRETCHL    = $FC1C ; *
STRETCHH    = $FC1D ; *
TILTL       = $FC1E ; *
TILTH       = $FC1F ; *
SPRDOFFL    = $FC20 ; *
SPRDOFFH    = $FC21 ; *
SPRVPOSL    = $FC22 ; *
SPRVPOSH    = $FC23 ; *
COLLOFFL    = $FC24
COLLOFFH    = $FC25
VSIZACUML   = $FC26 ; *
VSIZACUMH   = $FC27 ; *
HSIZOFFL    = $FC28
HSIZOFFH    = $FC29
VSIZOFFL    = $FC2A
VSIZOFFH    = $FC2B
SCBADRL     = $FC2C ; *
SCBADRH     = $FC2D ; *
PROCADRL    = $FC2E ; *
PROCADRH    = $FC2F ; *

; Math engine registers

MATHD       = $FC52
MATHC       = $FC53
MATHB       = $FC54
MATHA       = $FC55
MATHP       = $FC56
MATHN       = $FC57
MATHH       = $FC60
MATHG       = $FC61
MATHF       = $FC62
MATHE       = $FC63
MATHM       = $FC6C
MATHL       = $FC6D
MATHK       = $FC6E
MATHJ       = $FC6F

; More SUZY control registers

SPRCTL0            = $FC80
; Sprite control 0 bit definitions
BITS_MASK          = %11000000 ; Mask for settings bits per pixel
; Sprite bits-per-pixel definitions
ONE_PER_PIXEL      = %00000000
TWO_PER_PIXEL      = %01000000
THREE_PER_PIXEL    = %10000000
FOUR_PER_PIXEL     = %11000000
; More sprite control 0 bit definitions
HFLIP              = %00100000
VFLIP              = %00010000
; Sprite types - redefined to reflect the reality caused by the shadow error
SHADOW_SPRITE      = %00000111
XOR_SPRITE         = %00000110
NONCOLL_SPRITE     = %00000101 ; Non-colliding
NORMAL_SPRITE      = %00000100
BOUNDARY_SPRITE    = %00000011
BSHADOW_SPRITE     = %00000010 ; Background shadow
BACKNONCOLL_SPRITE = %00000001 ; Background non-colliding
BACKGROUND_SPRITE  = %00000000

SPRCTL1          = $FC81
; Sprite control 1 bit definitions
LITERAL          = %10000000
PACKED           = %00000000
ALGO_3           = %01000000 ; Broken, do not set this bit!
; Sprite reload mask definitions
RELOAD_MASK      = %00110000
RELOAD_NONE      = %00000000 ; Reload nothing
RELOAD_HV        = %00010000 ; Reload hsize, vsize
RELOAD_HVS       = %00100000 ; Reload hsize, vsize, stretch
RELOAD_HVST      = %00110000 ; Reload hsize, vsize, stretch, tilt
; More sprite control 1 bit definitions
REUSE_PALETTE    = %00001000
SKIP_SPRITE      = %00000100
DRAW_UP          = %00000010
DRAW_LEFT        = %00000001

SPRCOLL          = $FC82
; SPRCOLL bit definitions
; NO_COLLIDE     = %00100000 ; Also defined for SPRSYS

SPRINIT     = $FC83
SUZYHREV    = $FC88
SUZYSREV    = $FC89
SUZYBUSEN   = $FC90

SPRGO       = $FC91
; SPRGO bit definitions
SPRITE_GO   = $01   ; sprite process start bit
EVER_ON     = $04   ; everon detector enable

SPRSYS          = $FC92
; SPRSYS bit definitions for write operations
SIGNMATH        = $80  ; signed math
ACCUMULATE      = $40  ; accumulate multiplication results
NO_COLLIDE      = $20  ; do not collide with any sprites (also SPRCOLL bit definition)
VSTRETCH        = $10  ; stretch v
LEFTHAND        = $08
UNSAFEACCESSRST = $04  ; unsafe access reset
SPRITESTOP      = $02  ; request to stop sprite process
; SPRSYS bit definitions for read operations
MATHWORKING     = $80  ; math operation in progress
MATHWARNING     = $40  ; accumulator overflow on multiple or divide by zero
MATHCARRY       = $20  ; last carry bit
VSTRETCHING     = $10
LEFTHANDED      = $08
UNSAFEACCESS    = $04  ; unsafe access performed
SPRITETOSTOP    = $02  ; requested to stop
SPRITEWORKING   = $01  ; sprite process is active

JOYSTICK       = $FCB0
; JOYSTICK bit definitions
JOY_RIGHT      = $10
JOY_LEFT       = $20
JOY_DOWN       = $40
JOY_UP         = $80
OPTION1_BUTTON = $08
OPTION2_BUTTON = $04
INNER_BUTTON   = $02
OUTER_BUTTON   = $01
A_BUTTON       = OUTER_BUTTON
B_BUTTON       = INNER_BUTTON

SWITCHES    = $FCB1
; SWITCHES bit definitions
CART1_IO_INACTIVE = $04
CART0_IO_INACTIVE = $02
BUTTON_PAUSE      = $01

RCART0      = $FCB2
RCART1      = $FCB3
; LEDS output register only exists on early wire-wrap prototypes
LEDS        = $FCC0
; Parallel IO port only exists on early wire-wrap prototypes
IOSTATUS    = $FCC2
IODATA      = $FCC3
HOWIE       = $FCC4


; ***
; *** Mikey Addresses
; ***

MIKEY_BASE  = $FD00

; Mikey Timers

TIMER0      = $FD00
TIMER1      = $FD04
TIMER2      = $FD08
TIMER3      = $FD0C
TIMER4      = $FD10
TIMER5      = $FD14
TIMER6      = $FD18
TIMER7      = $FD1C
HCOUNT      = TIMER0             ; horizontal line timer (timer 0)
VCOUNT      = TIMER2             ; vertical blank timer (timer 2)
SERIALRATE  = TIMER4             ; serial timer (timer 4)

; Timer offsets
TIM_BACKUP       = 0
TIM_CONTROLA     = 1
TIM_COUNT        = 2
TIM_CONTROLB     = 3

; TIM_CONTROLA control bit definitions
ENABLE_INT       = $80
RESET_DONE       = $40
ENABLE_RELOAD    = $10
ENABLE_COUNT     = $08

; AUD_CONTROL control bit definitions
FEEDBACK_7       = $80
ENABLE_INTEGRATE = $20

; Audio and timer clock settings for source period
AUD_LINKING      = $07
AUD_64           = $06
AUD_32           = $05
AUD_16           = $04
AUD_8            = $03
AUD_4            = $02
AUD_2            = $01
AUD_1            = $00

; TIM_CONTROLB control bit definitions
TIMER_DONE       = $08
LAST_CLOCK       = $04
BORROW_IN        = $02
BORROW_OUT       = $01


; Mikey Audio

AUDIO0      = $FD20             ; audio channel 0
AUDIO1      = $FD28             ; audio channel 1
AUDIO2      = $FD30             ; audio channel 2
AUDIO3      = $FD38             ; audio channel 3

; Audio channel offsets
AUD_VOLCNTRL = 0
AUD_FEEDBACK = 1
AUD_OUTPUT   = 2
AUD_SHIFT    = 3
AUD_BACKUP   = 4
AUD_CONTROL  = 5
AUD_COUNTER  = 6
AUD_OTHER    = 7

; Stereo control registers follow
; Stereo capability does not exist in all Lynxes
; Left and right may be reversed, and if so will be corrected in a later release

MPAN            = $FD44 ; Stereo attenuation select register
MSTEREO         = $FD50 ; Stereo channel disable register
ATTENREG0       = $FD40 ; Stereo attenuation registers
ATTENREG1       = $FD41
ATTENREG2       = $FD42
ATTENREG3       = $FD43

; Bit definitions for MPAN and MSTEREO registers
LEFT3_SELECT    = %10000000
LEFT2_SELECT    = %01000000
LEFT1_SELECT    = %00100000
LEFT0_SELECT    = %00010000
RIGHT3_SELECT   = %00001000
RIGHT2_SELECT   = %00000100
RIGHT1_SELECT   = %00000010
RIGHT0_SELECT   = %00000001
LEFT_ATTENMASK  = %11110000
RIGHT_ATTENMASK = %00001111

; Mikey Misc

INTRST      = $FD80
INTSET      = $FD81
; Interrupt bits in INTRST and INTSET
TIMER0_INT = $01
TIMER1_INT = $02
TIMER2_INT = $04
TIMER3_INT = $08
TIMER4_INT = $10
TIMER5_INT = $20
TIMER6_INT = $40
TIMER7_INT = $80

HORIZONTAL_INT = TIMER0_INT
VERTICAL_INT = TIMER2_INT
SERIAL_INT = TIMER4_INT

MAGRDY0        = $FD84
MAGRDY1        = $FD85
AUDIN          = $FD86
SYSCTL1        = $FD87
MIKEYHREV      = $FD88
MIKEYSREV      = $FD89

IODIR          = $FD8A
IODAT          = $FD8B
; IODIR and IODAT bit definitions
AUDIN_BIT      = %00010000 ; note that there is also the address AUDIN
READ_ENABLE    = %00010000 ; same bit for AUDIN_BIT
RESTLESS       = %00001000
NOEXP          = %00000100 ; If set, redeye is not connected
CART_ADDR_DATA = %00000010
CART_POWER_OFF = %00000010 ; same bit for CART_ADDR_DATA
EXTERNAL_POWER = %00000001

SERCTL      = $FD8C
SERDAT      = $FD8D
; SERCTL bit definitions for write operations
TXINTEN  = $80
RXINTEN  = $40
PAREN    = $01
RESETERR = $08
TXOPEN   = $04
TXBRK    = $02
PAREVEN  = $01
; SERCTL bit definitions for read operations
TXRDY   = $80
RXRDY   = $40
TXEMPTY = $20
PARERR  = $10
OVERRUN = $08
FRAMERR = $04
RXBRK   = $02
PARBIT  = $01

SDONEACK    = $FD90 ; Suzy done ack
CPUSLEEP    = $FD91 ; zzz

DISPCTL     = $FD92 ; Display control
; DISPCTL bit definitions
DISP_COLOR   = $08 ; must be set to 1
DISP_FOURBIT = $04 ; must be set to 1
DISP_FLIP    = $02
DMA_ENABLE   = $01 ; must be set to 1

PBKUP       = $FD93 ; Display's magic 'P' count
DISPADRL    = $FD94 ; Start of display
DISPADRH    = $FD95

; System test vectors, see spec for bits
MTEST0      = $FD9C
; MTEST0 bit definitions
AT_CNT16   = $80
AT_TEST    = $40
XCLKEN     = $20
UART_TURBO = $10
ROM_SEL    = $08
ROM_TEST   = $04
M_TEST     = $02
CPU_TEST   = $01

MTEST1      = $FD9D
; MTEST1 bit definitions
P_CNT16     = $40
REF_CNT16   = $20
VID_TRIG    = $10
REF_TRIG    = $08
VID_DMA_DIS = $04
REF_FAST    = $02
REF_DIS     = $01

MTEST2      = $FD9E
; MTEST2 bit definitions
V_STROBE  = $10
V_ZERO    = $08
H_120     = $04
H_ZERO    = $02
V_BLANKEF = $01

PALETTE     = $FDA0                 ; hardware rgb palette
GCOLMAP     = $FDA0                 ; hardware rgb palette (green)
RBCOLMAP    = $FDB0                 ; hardware rgb palette (red-blue)


; ***
; *** Misc Hardware + 6502 vectors
; ***

MAPCTL      = $FFF9 ; Map Control register
; MAPCTL flag definitions
TURBO_DISABLE = $80
VECTOR_SPACE  = $08
ROM_SPACE     = $04
MIKEY_SPACE   = $02
SUZY_SPACE    = $01

VECTORS     = $FFFB
INTVECTL    = $FFFE
INTVECTH    = $FFFF
RSTVECTL    = $FFFC
RSTVECTH    = $FFFD
NMIVECTL    = $FFFA
NMIVECTH    = $FFFB

