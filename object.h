#ifndef __OBJECT_H__
#define __OBJECT_H__
#include <vector>
#include <iostream>

using namespace std;

class Object {
protected:
    vector<int> v;
public:
    Object(int x, int y) : v(2, 0) {
        v[0] = x;
        v[1] = y;
    }

    Object(vector<int> vv) : v(vv) { }

    int GetX() {
        return v[0];
    }

    int GetY() {
        return v[1];
    }

    void move(int xx, int yy) {
        v[0] += xx;
        v[1] += yy;
    }

    void go(int xx, int yy) {
        v[0] = xx;
        v[1] = yy;
    }
};

class Player : public Object {
private:
    int HP;
    int where;  //0이면 왼쪽, 1이면 오른쪽에 위치
    int bullet; // 가지고 있는 총알의 개수
public:
    Player(int x, int y) : Object(x, y), HP(20) { 
        if(x > 60) where = 1;
        else if(x < 30) where = 0;
        else {
            cout << "Player x is out of range!" << endl;
            exit(0);
        }
    }
    Player(vector<int> vv) : Object(v), HP(20) { 
        if(vv[0] > 60) where = 1;
        else if(vv[0] < 30) where = 0;
        else {
            cout << "Player x is out of range!" << endl;
            exit(0);
        }
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

    bool isHit(Bomb** arr, int bombcnt) {       // Bomb*를 가지고 있는 배열과 그 배열의 원소의 개수를 인자로 받음
        for(int i = 0; i < bombcnt; i++) {      // 탄환과 플레이어의 좌표가 같은지 확인 하는 함수. 같으면 탄에 맞은 것이므로 true를 반환하고 아니면 false 반환
            if(this->GetX() == arr[i]->GetX() && this->GetY() == arr[i]->GetY()) return true;
        }
        return false;
    }

    /*Bomb* throwbomb() {           // 탄환을 만들어 반환, 플레이어의 x좌표와 y좌표+1에서 생성
        Bomb* p = new Bomb(this->GetX(), this->GetY()+1);
        return p;
    }*/
    
};

class Bomb : public Object {

};
class Bomb : public Object {
private:
    double a;
public:
    //Bomb(Player p): {
    //}
    void move(){
    }
};


#endif