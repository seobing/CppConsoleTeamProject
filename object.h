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


#endif