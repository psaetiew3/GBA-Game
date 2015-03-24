#include "DMA.h"
#include "title.h"
#include "Player.h"
#include "GreenPig.h"
#include "YellowBird.h"
#include "BlueBird.h"
#include "RedBird.h"
#include "background.h"
#include "gameover.h"
#include <stdlib.h>
#include <stdio.h>

#define RGB(r,g,b) ((r)|((g)<<5)|((b)<<10))
#define OFFSET(row,col) ((row)*240+(col))
#define SETMODE(mode) REG_DISPCTL = (mode)
#define GREEN RGB(0,31,0)
#define PINK RGB(31, 27, 28)
#define SKY RGB(19, 27, 29)
#define BLUE RGB(0,0,31)
#define RED RGB(31,0,0)
#define WHITE RGB(31,31,31)

#define REG_DISPCTL *(u16 *)0x4000000 
#define BG2_ENABLE 0x400
#define MODE3 3

#define KEY_A 1
#define KEY_B 2
#define KEY_SELECT 4
#define KEY_START 8
#define KEY_RIGHT 16
#define KEY_LEFT 32
#define KEY_UP 64
#define KEY_DOWN 128
#define KEY_R 256
#define KEY_L 512

#define KEY *(u16 *)0x4000130
#define KEY_DOWN_NOW(key) (~(KEY) & key))


#define recalc(num) (num%360)


#define REG_VCOUNT *(vu16 *)0x4000006

typedef unsigned short u16;
typedef volatile unsigned short vu16;

typedef struct Object{
	int x;
	int y;
} Object;



void setPixel(int r, int c, u16 color);
void drawRect(int r, int c, int width, int height, u16 color);
void sync();
void drawPlayer(Object *player);
void drawFoe(Object *foe, Object *foe2, Object *foe3);
void drawToken(Object *ob, Object *ob2, Object *ob3);
void drawTitle();
void drawBackground();
void drawWinPage();
int winPage(Object *player);
void upPressed(Object *player);
void downPressed(Object *player);
void leftPressed(Object *player);
void rightPressed(Object *player);
void drawImage3(int r, int c, int width, int height, const u16* image);
void drawImage3mirror(int r, int c, int width, int height, const u16* image);
void buttonPressed(Object *player);
int checkHitFoe(Object *player, Object *foe, Object *foe2, Object *foe3);
int afterHitFoe(Object *player);
void checkTokenHit(Object *player, Object *ob, Object *ob2, Object *ob3);
int tokenNum1Hit(Object *ob);
int tokenNum2Hit(Object *ob2);
int tokenNum3Hit(Object *ob3);
void updateFoe1(Object *foe);
void updateFoe2(Object *foe2);
void updateFoe3(Object *foe3);
