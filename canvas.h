#ifndef __CANVAS_H__
#define __CANVAS_H__
#include <vector>
#include <iostream>         
#include <string>  

using namespace std;

class Canvas {
private:
    vector<vector<string>> y;       // 좌표를 벡터로 표현하기 위해서 이차원 벡터를 사용
public:
    Canvas() : y(14, vector<string>(100, " ")) { //세로 14, 가로 100
        for(int i = 13; i > 10; i--) {
            for(int j = 0; j < 100; j++) {
                if(i==12) {
                    assign(j,i," ");
                    if(j == 0 || j == 39 || j == 61 || j == 99) assign(j, i, "|");
                }
                else if(j <40 || j > 60) assign(j, i,"=");
            }
        }
    }

    string gets(int x1, int y1) {       // 캔버스의 x1, y1의 위치에 존재하는 문자를 반환
        string s = y[y1][x1];
        return s;
    }

    string gets(vector<int> v) {        // 위 함수의 오버로딩
        string s = y[v[1]][v[0]];
        return s;
    }

    void show() {                                       // 캔버스를 출력하는 함수
        for(int i = 0; i < y.size(); i++) {
            for(int j = 0; j < y[i].size(); j++) {
                vector<int> v = {j, i};
                cout << y[i][j];             // 그 외에는 캔버스에 담긴 것을 출력한다
            }
            cout << endl;
        }
    }

    
    void assign(int x1, int y1, string s) {     // 캔버스 상 x1, y1 위치에 s를 집어넣는다
        y[y1][x1] = s;
    }

    void clearCanvas() {        // 캔버스 전체를 지워버리는 함수
        for(int i = 0; i < y.size(); i++) {
            for(int j = 0; j < y[i].size(); j++) {
                if((i > 10) && (j < 40 || j > 60)) continue;
                y[i][j] = " ";
            }
        }
    }
};

#endif