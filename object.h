#include "RedBird.h"

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
#define KEY_MASK 0x03FF

#define REG_KEYINPUT *(u16 *)0x4000130
#define KEY_DOWN_NOW(key) (~(REG_KEYINPUT) & key))

int playerSwitch=0;
int right=1;

typedef struct Object{
	int x;
	int y;
} Object;

Object p;

void drawPlayer1(Object play){
	if(right){
		for(int i=0;i<REDBIRD_HEIGHT;i++){
			for(int j=0;j<REDBIRD_WIDTH;j++){
				videoBuffer[OFFSET(i+play.y,j+play.x)]=RedBird[(i*REDBIRD_WIDTH)+j];
			}
		}
	}
	else{
		for(int i=0;i<REDBIRD_HEIGHT;i++){
			for(int j=0;j<REDBIRD_WIDTH;j++){
				videoBuffer[OFFSET(i+play.y,j+play.x)]=RedBird[(i*REDBIRD_WIDTH+(REDBIRD_WIDTH-j))];
			}
		}
	}
}

void moveUp(){
	if(p.y>0)
	p.y--;
	drawRect(p.y+REDBIRD_HEIGHT,p.x,REDBIRD_WIDTH,1,0);

}
void moveDown(){
	if(p.y<160-REDBIRD_HEIGHT)
	p.y++;
	drawRect(p.y-1,p.x,REDBIRD_WIDTH,1,0);
	
}
void moveLeft(){
	right=0;
	if(p.x>0)
	p.x--;
	drawRect(p.y,p.x+REDBIRD_WIDTH,1,REDBIRD_HEIGHT,0);
	
}
void moveRight(){
	right=1;
	if(p.x<240-REDBIRD_WIDTH)
	p.x++;
	drawRect(p.y,p.x-1,1,REDBIRD_HEIGHT,0);
}

void buttonPressed(){
	if((KEY_DOWN_NOW(KEY_RIGHT)){
		moveRight();	
		playerSwitch++;
	}
	if((KEY_DOWN_NOW(KEY_LEFT)){
		moveLeft();	
		playerSwitch++;
	}
	if((KEY_DOWN_NOW(KEY_UP)){
		moveUp();	
		playerSwitch++;
	}
	if((KEY_DOWN_NOW(KEY_DOWN)){
		moveDown();
		playerSwitch++;
	}
}