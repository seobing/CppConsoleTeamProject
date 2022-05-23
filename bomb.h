#ifndef __BOMB_H__
#define __BOMB_H__
#include"object.h"
#include"player.h"

class Bomb : public Object {
private:
    double a;
public:
    Bomb(Player p): Object(0,0){ //player의 위치가 던져질때의 시작점
        this -> v[0] = p.GetX();
        this -> v[1] = p.GetY();
    }
    void move(Player p){
        if(p.GetX() > 60) this -> v[0] -= 1;
        else if(p.GetX() < 30) this -> v[1] += 1;
    }
};
#endif