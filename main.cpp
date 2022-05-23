#include "canvas.h"
#include "derived.h"
#include <conio.h>

using namespace std;

void PlayGame(Canvas&);
void printHP(Canvas& , Player& , Player& ); 

int main() {
    Canvas can;
    PlayGame(can);
}

void PlayGame(Canvas& can) {
    Player p1(15,10);
    Player p2(75, 10);
    Bomb* bombarr[10];
    int numOfbomb = 0;
    can.assign(p1.GetX(),p1.GetY(),"A");
    can.assign(p2.GetX(), p2.GetY(),"B");
    system("cls");
    can.show();
    while(true) {
        if(kbhit()) {
            system("cls");
            can.clearCanvas();
            int c = getch();
            switch(c) {
            case 72: // up 2p throw
                if(p2.GetB() < 0) break;
                bombarr[numOfbomb++] = p2.throwbomb();
                p2.changeBullet(-1);
                break;
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
                if(p1.GetB() < 0) break;
                bombarr[numOfbomb++] = p1.throwbomb();
                p1.changeBullet(-1);
                break;
            }
            for(int i = 0; i < numOfbomb; i++) {    // 탄환의 이동
                bombarr[i]->move();
                bombarr[i]->move();
            }
            for(int i = 0; i < numOfbomb; i++) {    // 탄환이 플레이어에게 맞았는지 확인하고 맞은 탄환은 제거 하는 과정
                if(p1.GetX() == bombarr[i]->GetX() && p1.GetY() == bombarr[i]->GetY()) {
                    p1.changeHP(-2);
                    delete bombarr[i];
                    for(int j = i; j < numOfbomb - 1; j++) {
                        bombarr[j] = bombarr[j+1];
                    }
                    numOfbomb--;
                    p1.changeBullet(1);
                }
                else if(p2.GetX() == bombarr[i]->GetX() && p2.GetY() == bombarr[i]->GetY()) {
                    p2.changeHP(-2);
                    delete bombarr[i];
                    for(int j = i; j < numOfbomb - 1; j++) {
                        bombarr[j] = bombarr[j+1];
                    }
                    numOfbomb--;
                    p2.changeBullet(1);
                }
            }
            for(int i = 0; i < numOfbomb; i++) {    // 탄환을 캔버스에 찍어줌
                can.assign(bombarr[i]->GetX(), bombarr[i]->GetY(), "*");
            }
            printHP(can, p1, p2);
            can.assign(p1.GetX(), p1.GetY(), "A");
            can.assign(p2.GetX(), p2.GetY(), "B");
            can.show();
        }
    }
    for(int i = 0; i < numOfbomb; i++) {
        delete bombarr[i];
    }
}

void printHP(Canvas& can, Player& p1, Player& p2) { // p1과 p2를 입력받아 각자의 HP만큼 캔버스에 찍어주는 함수
    for(int i = 0; i < p1.GetHP(); i++) {
        can.assign(i, 14, "O");
    }
    for(int i = 0; i < p2.GetHP(); i++) {
        can.assign(99-i, 14, "O");
    }
}