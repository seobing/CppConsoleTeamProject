#ifndef __PARABOLA_H__
#define __PARABOLA_H__
#include "derived.h"
#include<cmath>

// y = (gauge/3)*(x2-x1)^2 + 10 

int parabola(Bomb* b){
    double a = 10.0/9;
    if(b->fset == false) {
        b->fset = true;
        b->bot = b->GetX();
    }
    //b -> setA(5.0/450);
    double height;
    if(b -> GetW() == 1)    height = (b->getA())*pow(b->GetX() - 50 -(b->bot - 80), 2);
    else    height = (b->getA())*pow(b->GetX() - 50 -(20 - b->bot), 2);
    if(height < 0) height = 0;
    b -> go(b->GetX(), height);
}
         
#endif