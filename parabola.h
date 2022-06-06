#ifndef __PARABOLA_H__
#define __PARABOLA_H__
#include "derived.h"
#include<cmath>

// y = (gauge/3)*(x2-x1)^2 + 10 

int parabola(Bomb* b, double gauge){
                                                    double a = 10.0/9;
    b -> setA(5.0/450);
    //cout << a << endl;
    //cout << b -> GetX() << endl;
    cout << b -> getA() << endl; 
    //b -> move();
    int bottom = b-> GetX();
    //double height = (b->getA())*pow(bottom,2) - 100*(b->getA())*bottom + 27.7;
    double height = (b->getA())*pow(2*bottom - 130, 2);
    if(height < 0) height = 0;
    b -> go(bottom, height);
}
         
#endif