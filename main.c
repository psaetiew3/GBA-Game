#include "mylib.h"


int main(void)
{
	int titlePage = 1;
	int gameover = 0;
	REG_DISPCTL=MODE3|BG2_ENABLE;
    
	Object *p = malloc(sizeof *p);
	Object *f = malloc(sizeof *f);
    Object *f2 = malloc(sizeof *f2);
    Object *f3 = malloc(sizeof *f3);
    Object *ob = malloc(sizeof *ob);
    Object *ob2 = malloc(sizeof *ob2);
    Object *ob3 = malloc(sizeof *ob3);

    int xStartPos = 7;
    int yStartPos = 12;
    
	p->x = xStartPos;
	p->y = yStartPos+10;
    
	f->y = 100-yStartPos;
	f->x = 210-xStartPos;
   	f2->y = 80-yStartPos;
	f2->x = 80-xStartPos; 
    f3->y = 140-yStartPos;
	f3->x = 140-xStartPos;
    
    ob->x = 60-xStartPos;
    ob->y = 60-yStartPos;
    ob2->x = 120-xStartPos;
    ob2->y = 100-yStartPos;
    ob3->x = 40-xStartPos;
    ob3->y = 140-yStartPos;

	while(1)
	{
		sync();
		if(titlePage && !gameover){
			drawTitle();
			if((KEY_DOWN_NOW(KEY_START))
				{
					titlePage = 0;
					drawBackground();
				}
		}
		else if(!titlePage && !gameover)
		{
            checkTokenHit(p, ob, ob2, ob3);
            if (tokenNum1Hit(ob)) {
                drawRect(ob->y,ob->x,21,17, SKY);
            }
            if (tokenNum2Hit(ob2)) {
                drawRect(ob2->y,ob2->x,21,17, SKY);
            }
            if (tokenNum3Hit(ob3)) {
                drawRect(ob3->y,ob3->x,21,17, SKY);
            }
            
			drawPlayer(p);
			drawFoe(f, f2, f3);
            drawToken(ob, ob2, ob3);
			updateFoe1(f);
			updateFoe2(f2);
			updateFoe3(f3);

			buttonPressed(p);
			if(winPage(p)){
				gameover = 1;
			}
			if(checkHitFoe(p, f, f2, f3)){
				if(afterHitFoe(p)){
                    gameover = 1;
				}
			}

		}
        else
        {
			if((KEY_DOWN_NOW(KEY_SELECT))
			{
			titlePage = 1;
			gameover = 0;
			}
		}
	}
	return 0;
}