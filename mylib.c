#include "mylib.h"

u16 *videoBuffer=(u16 *) 0x6000000;

int counterF=0;
int advance=2;
int foeTurn=0;

int tokenNum1 = 0;
int tokenNum2 = 0;
int tokenNum3 = 0;

int life = 3;

int xStartPos = 15;
int yStartPos = 20;


void setPixel(int r, int c, u16 color) 
{ 
	videoBuffer[OFFSET(r,c)] = color;
}

void drawRect(int r, int c, int width, int height, u16 
color) 
{ 
	for (int i = 0; i < height; i++)
    {
		for (int j = 0; j < width; j++)
        {
			videoBuffer[OFFSET(r + i, c + j)] = color;
		}
	} 
}

void sync()
{
    while(REG_VCOUNT >= 160); 
    while(REG_VCOUNT < 160);   
}

void drawPlayer(Object *player){
	drawImage3(player->y, player->x, PLAYER_WIDTH, PLAYER_HEIGHT, Player);
}

void drawFoe(Object *foe, Object *foe2, Object *foe3){
    if(foeTurn){
        drawImage3(foe->y, foe->x, REDBIRD_WIDTH, REDBIRD_HEIGHT, RedBird);
        drawImage3(foe2->y, foe2->x, YELLOWBIRD_WIDTH, YELLOWBIRD_HEIGHT, YellowBird);
        drawImage3(foe3->y, foe3->x, BLUEBIRD_WIDTH, BLUEBIRD_HEIGHT, BlueBird);
    }
    else{
        drawImage3mirror(foe->y, foe->x, REDBIRD_WIDTH, REDBIRD_HEIGHT, RedBird);
        drawImage3mirror(foe2->y, foe2->x, YELLOWBIRD_WIDTH, YELLOWBIRD_HEIGHT, YellowBird);
        drawImage3mirror(foe3->y, foe3->x, BLUEBIRD_WIDTH, BLUEBIRD_HEIGHT, BlueBird);
    }
}

void drawToken(Object *ob, Object *ob2, Object *ob3) {
    if (!tokenNum1Hit(ob)) {
	drawImage3(ob->y,ob->x,GREENPIG_WIDTH,GREENPIG_HEIGHT,GreenPig);
	}
    if (!tokenNum2Hit(ob2)) {
    drawImage3(ob2->y,ob2->x,GREENPIG_WIDTH,GREENPIG_HEIGHT,GreenPig);
	}
    if (!tokenNum3Hit(ob3)) {
    drawImage3(ob3->y,ob3->x,GREENPIG_WIDTH,GREENPIG_HEIGHT,GreenPig);
    }
}
void drawBackground(){
	drawImage3(0, 0, BACKGROUND_WIDTH, BACKGROUND_HEIGHT, background);
}

void drawWinPage(){
	drawImage3(0, 0, GAMEOVER_WIDTH, GAMEOVER_HEIGHT, gameover);
}

void drawTitle(){
	drawImage3(0, 0, TITLE_WIDTH, TITLE_HEIGHT, title);
}

int winPage(Object *player){
	if(player->x==240-xStartPos-PLAYER_WIDTH && player->y==160-yStartPos-PLAYER_HEIGHT) {
		drawWinPage();
		return 1;
	}
	else{
		return 0;
	}
}

void buttonPressed(Object *player){
	if((KEY_DOWN_NOW(KEY_UP)){
		upPressed(player);	
	}
	if((KEY_DOWN_NOW(KEY_DOWN)){
		downPressed(player);
	}
    if((KEY_DOWN_NOW(KEY_LEFT)){
		leftPressed(player);	
	}
	if((KEY_DOWN_NOW(KEY_RIGHT)){
		rightPressed(player);	
	}
}

void upPressed(Object *player){
	if(player->y > yStartPos){
		player->y--;
		drawRect(player->y + PLAYER_HEIGHT, player->x, PLAYER_WIDTH, 1, SKY);
	}
}

void downPressed(Object *player){
	if(player->y < 160-yStartPos-PLAYER_HEIGHT){
		player->y++;
		drawRect(player->y - 1, player->x, PLAYER_WIDTH, 1, SKY);	
	}
}

void leftPressed(Object *player){
	if(player->x > xStartPos){
		player->x--;
		drawRect(player->y,player->x+PLAYER_WIDTH,1,PLAYER_HEIGHT,SKY);
	}
}

void rightPressed(Object *player){
	if(player->x < 240-xStartPos-PLAYER_WIDTH){
		player->x++;
		drawRect(player->y,player->x-1,1,PLAYER_HEIGHT,SKY);
	}
}


int checkHitFoe(Object *player, Object *foe, Object *foe2, Object *foe3){
	int xpos=(player->x)-(foe->x);
	int ypos=(player->y)-(foe->y);
    
    int xpos2=(player->x)-(foe2->x);
	int ypos2=(player->y)-(foe2->y);
    
    int xpos3=(player->x)-(foe3->x);
	int ypos3=(player->y)-(foe3->y);
    
	if ((xpos<20 && xpos>(-PLAYER_WIDTH) && ypos<20 && ypos>(-PLAYER_HEIGHT))
    || (xpos2<20 && xpos2>(-PLAYER_WIDTH) && ypos2<20 && ypos2>(-PLAYER_HEIGHT))
    || (xpos3<20 && xpos3>(-PLAYER_WIDTH) && ypos3<20 && ypos3>(-PLAYER_HEIGHT))) {
		life--;
        return 1;
	} else {
        return 0;
    }
}

int afterHitFoe(Object *player){
	player->x = xStartPos;
	player->y = yStartPos;
    if (life == 0) {
        drawBackground();
        return 1;
    }
	drawBackground();
	return 0;
}


void checkTokenHit(Object *player, Object *ob, Object *ob2, Object *ob3) {
    int xpos = (player->x)-(ob->x);
	int ypos = (player->y)-(ob->y);
    
    int xpos2 = (player->x)-(ob2->x);
	int ypos2 = (player->y)-(ob2->y);
    
    int xpos3 = (player->x)-(ob3->x);
	int ypos3 = (player->y)-(ob3->y);
    
	if (xpos<20 && xpos>(-PLAYER_WIDTH) && ypos<20 && ypos>(-PLAYER_HEIGHT)) {
		tokenNum1 = 1;
    }
	if (xpos2<20 && xpos2>(-PLAYER_WIDTH) && ypos2<20 && ypos2>(-PLAYER_HEIGHT)) {
		tokenNum2 = 1;
    }
    if (xpos3<20 && xpos3>(-PLAYER_WIDTH) && ypos3<20 && ypos3>(-PLAYER_HEIGHT)) {
		tokenNum3 = 1;
    }
}

int tokenNum1Hit(Object *ob) {
    if (tokenNum1 == 1) {
        drawImage3(0,50,GREENPIG_WIDTH,GREENPIG_HEIGHT,GreenPig);
        return 1;
    } else {
        return 0;
    }
}
int tokenNum2Hit(Object *ob2) {
    if (tokenNum2 == 1) {
        drawImage3(0,80,GREENPIG_WIDTH,GREENPIG_HEIGHT,GreenPig);
        return 1;
    } else {
        return 0;
    }
}
int tokenNum3Hit(Object *ob3) {
    if (tokenNum3 == 1) {
        drawImage3(0,110,GREENPIG_WIDTH,GREENPIG_HEIGHT,GreenPig);
        return 1;
    } else {
        return 0;
    }
}

void drawImage3(int r, int c, int width, int height, const u16* image){
	for(int i = 0; i< height; i++){
		DMA[3].src = &image[width * i];
		DMA[3].dst = &videoBuffer[OFFSET(r + i, c)];
		DMA[3].cnt = (width) | DMA_ON;
	}
}

void drawImage3mirror(int r, int c, int width, int height, const u16* image){
	for(int i=0;i<height;i++){
		DMA[3].src = &image[width * i];
		DMA[3].dst = &videoBuffer[OFFSET(r + i, c)];
		DMA[3].cnt = (width) | DMA_ON | DMA_SOURCE_DECREMENT;
	}
}
void updateFoe1(Object *foe){
	counterF = recalc(counterF);
	if(counterF > 20 && counterF < 190){
		foeTurn = 0;
		foe->x-=advance;
		drawRect(foe->y,foe->x+REDBIRD_WIDTH,advance,REDBIRD_HEIGHT, SKY);
    }
	if(counterF > 190 && counterF < 380){
		foeTurn = 1;
		foe->x+=advance;
		drawRect(foe->y,foe->x-advance,advance,REDBIRD_HEIGHT, SKY);
    }
	counterF+=advance;
}

void updateFoe2(Object *foe2){
	counterF = recalc(counterF);
	if(counterF > 20 && counterF < 190){
		foeTurn = 0;
        foe2->x-=advance;
		drawRect(foe2->y,foe2->x+YELLOWBIRD_WIDTH,advance,YELLOWBIRD_HEIGHT, SKY);
    }
	if(counterF > 190 && counterF < 380){
		foeTurn = 1;
        foe2->x+=advance;
		drawRect(foe2->y,foe2->x-advance,advance,YELLOWBIRD_HEIGHT, SKY);
    }
	counterF+=advance;

}
void updateFoe3(Object *foe3){
	counterF = recalc(counterF);
	if(counterF > 20 && counterF < 190){
		foeTurn = 0;
        foe3->x-=advance;
		drawRect(foe3->y, foe3->x + BLUEBIRD_WIDTH, advance, BLUEBIRD_HEIGHT, SKY);
    }
	if(counterF > 190 && counterF < 380){
		foeTurn = 1;
        foe3->x+=advance;
		drawRect(foe3->y, foe3->x - advance, advance, BLUEBIRD_HEIGHT, SKY);
    }
	counterF+=advance;

}
