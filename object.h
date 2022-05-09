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
public:
    Player(int x, int y) : Object(x, y), HP(0) { 
        if(x > 60) where = 1;
        else if(x < 30) where = 0;
        else {
            cout << "Player x is out of range!" << endl;
            exit(0);
        }
    }
    Player(vector<int> vv) : Object(v), HP(0) { 
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
};

#endif