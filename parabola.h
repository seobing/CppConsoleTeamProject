#ifndef __PARABOLA_H__
#define __PARABOLA_H__
#include "derived.h"

int parabola(Bomb* b, int gauge){
    b -> setA(gauge/3); 
    b -> move();
    b -> go(a*(b -> GetX())*(b -> GetX()), b-> GetY());
}

#endif