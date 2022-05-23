#ifndef __DERIVED_H__
#define __DERIVED_H__
#include "object.h"

class Bomb : public Object {
private:
    int where;
    double a;
public:
    Bomb(int x, int y, int mywhere): Object(x,y),where(mywhere){} //player의 위치가 던져질때의 시작점
    void move(){
        if(this -> where == 0) this -> v[0] += 1;
        else if(this -> where == 1) this -> v[0] -= 1;
    }
};

class Player : public Object {
private:
    int HP;
    int where;  //0이면 왼쪽, 1이면 오른쪽에 위치
    int bullet; // 가지고 있는 총알의 개수
public:
    Player(int x, int y) : Object(x, y), HP(20), bullet(5) { 
        if(x > 60) where = 1;
        else if(x < 30) where = 0;
        else {
            cout << "Player x is out of range!" << endl;
            exit(0);
        }
    }
    Player(vector<int> vv) : Object(v), HP(20), bullet(5) { 
        if(vv[0] > 60) where = 1;
        else if(vv[0] < 30) where = 0;
        else {
            cout << "Player x is out of range!" << endl;
            exit(0);
        }
    }

    int GetB() {
        return bullet;
    }

    int GetHP() {
        return HP;
    }

    void move(int n) { // n이 0이면 왼쪽으로 이동, 1이면 오른쪽으로 이동
        if(where == 0) {
            if(n == 0) {
                if(v[0] - 1 == -1) return;
                v[0] -= 1;
            }
            else if(n == 1) {
                if(v[0] + 1 == 40) return;
                v[0] += 1;
            }
        }
        else if(where == 1) {
            if(n == 0) {
                if(v[0] - 1 == 60) return;
                v[0] -= 1;
            }
            else if(n == 1) {
                if(v[0] + 1 == 100) return;
                v[0] += 1;
            }
        }
    }

    bool isAlive() {
        if(HP > 0) return true;
        else return false;
    }

    void changeHP(int n) {
        HP += n;
    }

    Bomb* throwbomb() {           // 탄환을 만들어 반환, 플레이어의 x좌표와 y좌표+1에서 생성
        Bomb* p;
        if(this -> v[0] > 60) p = new Bomb(this -> v[0], (this -> v[1])-1,1);
        else p = new Bomb(this -> v[0], (this -> v[1])-1,0);
        return p;
    }

    void changeBullet(int n) {
        bullet += n;
    }
};


#endif