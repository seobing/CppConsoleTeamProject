#include "canvas.h"
#include "parabola.h"
#include <conio.h>
#include <time.h>

using namespace std;

void PlayGame(Canvas&);
void printHP(Canvas& , Player& , Player& );
void printgauge(Canvas&, Player&, int, Player&, int );
void checkBomb(Bomb**, int&, Player&, Player&);


int main() {
    Canvas can;
    PlayGame(can);
    cout << ">>>>>>>>>>>>>>>>>>>>>>>>>>>>>Game is Over!!<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<" << endl;
}

void PlayGame(Canvas& can) {
    Player p1(20,10);
    Player p2(80, 10);
    Bomb* bombarr[10];
    int numOfbomb = 0;
    int p1_gauge = 0, p2_gauge = 0;
    bool p1_throw = false, p2_throw = false;
    can.assign(p1.GetX(),p1.GetY(),"A");
    can.assign(p1.GetX(),p1.GetY()-1,"*");
    can.assign(p2.GetX(), p2.GetY(), "B");
    can.assign(p2.GetX(),p2.GetY()-1,"*");
    system("cls");
    can.show();
    clock_t t1 = time(NULL), t2 = time(NULL);
    bool timeset = false;
    while(true) {
        bool key = false;
        if(p1.GetHP() <= 0 || p2.GetHP() <= 0) break; 
        if(timeset == false) {
            t1 = clock();
            timeset = true;
        }
        t2 = clock();
        if(kbhit()) {
            system("cls");
            can.clearCanvas();
            int c = getch();
            if(c == 0) c = getch();
            switch(c) {
            case 72: // up 2p throw
                if(p2.GetB() <= 0) break;
                if(p2_throw == false) {
                    p2_throw = true;
                    p2_gauge = 1;
                    break;
                }
                if(p2_throw) {
                    bombarr[numOfbomb] = p2.throwbomb();
                    if(p2_gauge == 5) bombarr[numOfbomb++] -> setA(1/90.0);
                    else if(p2_gauge == 4)  bombarr[numOfbomb++] -> setA(1/90.0);
                    else if(p2_gauge == 3)  bombarr[numOfbomb++] -> setA(1/90.0);
                    else if(p2_gauge == 2)  bombarr[numOfbomb++] -> setA(1/90.0);
                    else if(p2_gauge == 1)  bombarr[numOfbomb++] -> setA(1/90.0);
                    p2.changeBullet(-1);
                    p2_throw = false;
                    p2_gauge = 0;
                    break;
                }
		    case 80: // down
                break;
		    case 75: // left
                p2.move(0);
                break;
		    case 77: // right
                p2.move(1);
                break;
            case 'a': // 1p left
                p1.move(0);
                break;
            case 'd' : // 1p right
                p1.move(1);
                break;
            case 'w' : // 1p throw
                if(p1.GetB() <= 0) break;
                if(p1_throw == false) {     // ?????? ????????? ???????????? ????????? ??????
                    p1_gauge = 1;
                    p1_throw = true;
                    break;
                }
                if(p1_throw) {      // ????????? ????????? ?????? ???????????? ?????? ??????
                    bombarr[numOfbomb] = p1.throwbomb();
                    if(p1_gauge == 5) bombarr[numOfbomb++] -> setA(1/90.0);
                    else if(p1_gauge == 4)  bombarr[numOfbomb++] -> setA(1/90.0);
                    else if(p1_gauge == 3)  bombarr[numOfbomb++] -> setA(1/90.0);
                    else if(p1_gauge == 2)  bombarr[numOfbomb++] -> setA(1/90.0);
                    else if(p1_gauge == 1)  bombarr[numOfbomb++] -> setA(1/90.0);
                    p1.changeBullet(-1);
                    p1_throw = false;
                    p1_gauge = 0;
                    break;
                }
            }
            for(int i = 0; i < numOfbomb; i++) {    // ????????? ?????????????????? ???????????? ???????????? ?????? ????????? ?????? ?????? ??????
                if(p1.GetX() == bombarr[i]->GetX() && p1.GetY() == bombarr[i]->GetY()) {
                    p1.changeHP(-2);
                    delete bombarr[i];
                    for(int j = i; j < numOfbomb - 1; j++) {
                        bombarr[j] = bombarr[j+1];
                    }
                    numOfbomb--;
                    p2.changeBullet(1);
                }
                else if(p2.GetX() == bombarr[i]->GetX() && p2.GetY() == bombarr[i]->GetY()) {
                    p2.changeHP(-2);
                    delete bombarr[i];
                    for(int j = i; j < numOfbomb - 1; j++) {
                        bombarr[j] = bombarr[j+1];
                    }
                    numOfbomb--;
                    p1.changeBullet(1);
                }
            }
            for(int i = 0; i < numOfbomb; i++) {    // ????????? ???????????? ?????????
                can.assign(bombarr[i]->GetX(), bombarr[i]->GetY(), "*");
            }
            printHP(can, p1, p2);
            printgauge(can, p1, p1_gauge, p2, p2_gauge);
            can.assign(p1.GetX(), p1.GetY(), "A");
            if(p1.GetB() >0) can.assign(p1.GetX(), p1.GetY() -1, "*");
            can.assign(p2.GetX(), p2.GetY(), "B");
            if(p2.GetB() > 0) can.assign(p2.GetX(),p2.GetY()-1,"*");
            can.show();
        }
        if((t2 - t1 > 500)) {
            system("cls");
            can.clearCanvas();
            if(t2 - t1 > 500) timeset = false;
            if(p1_throw) {  // ????????? ????????? ?????? ???????????? ???????????? ??????
                p1_gauge++;
                if(p1_gauge > 5) p1_gauge = 1;
            }
            if(p2_throw) {
                p2_gauge++;
                if(p2_gauge > 5) p2_gauge = 1;
            }
            for(int i = 0; i < numOfbomb; i++) {    // ????????? ?????? 
                bombarr[i]->move();
                parabola(bombarr[i]);
            }
            for(int i = 0; i < numOfbomb; i++) {    // ????????? ?????????????????? ???????????? ???????????? ?????? ????????? ?????? ?????? ??????
                if(p1.GetX() == bombarr[i]->GetX() && p1.GetY() == bombarr[i]->GetY()) {
                    p1.changeHP(-2);
                    delete bombarr[i];
                    for(int j = i; j < numOfbomb - 1; j++) {
                        bombarr[j] = bombarr[j+1];
                    }
                    numOfbomb--;
                    p2.changeBullet(1);
                }
                else if(p2.GetX() == bombarr[i]->GetX() && p2.GetY() == bombarr[i]->GetY()) {
                    p2.changeHP(-2);
                    delete bombarr[i];
                    for(int j = i; j < numOfbomb - 1; j++) {
                        bombarr[j] = bombarr[j+1];
                    }
                    numOfbomb--;
                    p1.changeBullet(1);
                }
            }
            checkBomb(bombarr, numOfbomb, p1, p2);  // ????????? ?????? ??????
            for(int i = 0; i < numOfbomb; i++) {    // ????????? ???????????? ?????????
                can.assign(bombarr[i]->GetX(), bombarr[i]->GetY(), "*");
            }
            printHP(can, p1, p2);
            printgauge(can, p1, p1_gauge, p2, p2_gauge);
            can.assign(p1.GetX(), p1.GetY(), "A");
            if(p1.GetB() >0) can.assign(p1.GetX(), p1.GetY() -1, "*");
            can.assign(p2.GetX(), p2.GetY(), "B");
            if(p2.GetB() > 0) can.assign(p2.GetX(),p2.GetY()-1,"*");
            can.show();
        }
    }
    for(int i = 0; i < numOfbomb; i++) {
        delete bombarr[i];
    }
}

void printHP(Canvas& can, Player& p1, Player& p2) { // p1??? p2??? ???????????? ????????? HP?????? ???????????? ???????????? ??????
    for(int i = 0; i < p1.GetHP(); i++) {
        can.assign(i, 13, "O");
    }
    for(int i = 0; i < p2.GetHP(); i++) {
        can.assign(99-i, 13, "O");
    }
}

void printgauge(Canvas& can, Player& p1, int p1_gauge, Player& p2, int p2_gauge) { // p1??? p2??? ?????? ????????? ???????????? ???????????? ???????????? ??????
    for(int i = 0; i < p1_gauge; i++) {
        can.assign(p1.GetX()+i, p1.GetY() + 2, ">");
    }
    for(int i = 0; i < p2_gauge; i++) {
        can.assign(p2.GetX()-i, p2.GetY() + 2, "<");
    }
}

void checkBomb(Bomb** arr, int& numOfBomb, Player& p1, Player& p2) {  // Bomb??? ?????? ????????? ????????? ?????? ?????? ??????????????? ??????????????? ?????? ??? ?????? ??????
    for(int i = 0; i < numOfBomb; i++) {
        if(arr[i]->GetX() < 0 || arr[i]->GetX() > 99 || arr[i]->GetY() > 13 || arr[i]->GetY() < 0 || arr[i]->GetY() > 10) {
            if(arr[i]->GetW() == 0) {
                delete arr[i];
                for(int j = i; j < numOfBomb - 1; j++) {
                    arr[j] = arr[j+1];
                }
                numOfBomb--;
                p1.changeBullet(1);
            }
            else if(arr[i]->GetW() == 1) {
                delete arr[i];
                for(int j = i; j < numOfBomb - 1; j++) {
                    arr[j] = arr[j+1];
                }
                numOfBomb--;
                p2.changeBullet(1);
            }
        }
    }
}