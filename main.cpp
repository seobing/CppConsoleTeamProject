#include "canvas.h"
#include "parabola.h"
#include <conio.h>

using namespace std;

void PlayGame(Canvas&);
void printHP(Canvas& , Player& , Player& );
void printGague(Canvas&, Player&, int, Player&, int );
void checkBomb(Bomb**, int&, Player&, Player&);


int main() {
    Canvas can;
    PlayGame(can);
}

void PlayGame(Canvas& can) {
    Player p1(20,10);
    Player p2(80, 10);
    Bomb* bombarr[10];
    int numOfbomb = 0;
    int p1_gague = 1, p2_gague = 1;
    bool p1_throw = false, p2_throw = false;
    can.assign(p1.GetX(),p1.GetY(),"A");
    can.assign(p1.GetX(),p1.GetY()-1,"*");
    can.assign(p2.GetX(), p2.GetY(), "B");
    can.assign(p2.GetX(),p2.GetY()-1,"*");
    system("cls");
    can.show();
    while(true) {
        if(kbhit()) {
            system("cls");
            can.clearCanvas();
            int c = getch();
            if(c == 224) c = getch();
            switch(c) {
            case 72: // up 2p throw
                if(p2.GetB() <= 0) break;
                if(p2_throw == false) {
                    p2_throw = true;
                    break;
                }
                if(p2_throw) {
                    bombarr[numOfbomb] = p2.throwbomb();
                    bombarr[numOfbomb++] -> setA(p2_gague/450);
                    p2.changeBullet(-1);
                    p2_throw = false;
                    p2_gague = 1;
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
                if(p1_throw == false) {     // 한번 누르면 게이지를 모으기 시작
                    p1_throw = true;
                    break;
                }
                if(p1_throw) {      // 두번째 누르게 되면 게이지에 따라 던짐
                    bombarr[numOfbomb] = p1.throwbomb();
                    bombarr[numOfbomb++] -> setA(p1_gague/450);
                    /*if(p1_gague == 5) {
                        bombarr[numOfbomb++] -> setA(1/90);
                    }*/
                    p1.changeBullet(-1);
                    p1_throw = false;
                    p1_gague = 1;
                    break;
                }
            }
            if(p1_throw) {  // 시간이 지남에 따라 게이지가 늘어나는 역할
                p1_gague++;
                if(p1_gague > 5) p1_gague = 1;
            }
            if(p2_throw) {
                p2_gague++;
                if(p2_gague > 5) p2_gague = 1;
            }
            for(int i = 0; i < numOfbomb; i++) {    // 탄환의 이동 
                bombarr[i]->move();

                parabola(bombarr[i]);
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
            checkBomb(bombarr, numOfbomb, p1, p2);  // 탄환의 범위 확인
            for(int i = 0; i < numOfbomb; i++) {    // 탄환을 캔버스에 찍어줌
                can.assign(bombarr[i]->GetX(), bombarr[i]->GetY(), "*");
            }
            printHP(can, p1, p2);
            printGague(can, p1, p1_gague, p2, p2_gague);
            can.assign(p1.GetX(), p1.GetY(), "A");
            can.assign(p1.GetX(),p1.GetY()-1,"*");
            can.assign(p2.GetX(), p2.GetY(), "B");
            can.assign(p2.GetX(),p2.GetY()-1,"*");
            can.show();
        }
    }
    for(int i = 0; i < numOfbomb; i++) {
        delete bombarr[i];
    }
}

void printHP(Canvas& can, Player& p1, Player& p2) { // p1과 p2를 입력받아 각자의 HP만큼 캔버스에 찍어주는 함수
    for(int i = 0; i < p1.GetHP(); i++) {
        can.assign(i, 13, "O");
    }
    for(int i = 0; i < p2.GetHP(); i++) {
        can.assign(99-i, 13, "O");
    }
}

void printGague(Canvas& can, Player& p1, int p1_gague, Player& p2, int p2_gague) { // p1과 p2의 좌표 아래에 게이지를 캔버스에 찍어주는 함수
    for(int i = 0; i < p1_gague; i++) {
        can.assign(p1.GetX()+i, p1.GetY() + 2, ">>");
    }
    for(int i = 0; i < p2_gague; i++) {
        can.assign(p2.GetX()-i, p2.GetY() + 2, "<<");
    }
}

void checkBomb(Bomb** arr, int& numOfBomb, Player& p1, Player& p2) {  // Bomb이 화면 밖으로 나가는 경우 이를 제거해주고 플레이어의 탄환 수 등을 조정
    for(int i = 0; i < numOfBomb; i++) {
        if(arr[i]->GetX() < 0 || arr[i]->GetX() > 99 || arr[i]->GetY() > 13 || arr[i]->GetY() < 0) {
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