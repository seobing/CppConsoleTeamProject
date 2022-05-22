#include "canvas.h"
#include "object.h"
#include <conio.h>

using namespace std;

void PlayGame(Canvas& can);

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
    can.assign(p2.GetX(), p2.GetY(), "B");
    system("cls");
    can.show();
    while(true) {
        if(kbhit()) {
            system("cls");
            can.clearCanvas();
            int c = getch();
            switch(c) {
            case 72: // up
                break;
		    case 80: // down
                
                break;
		    case 75: // left
                p2.move(0);
                break;
		    case 77: // right
                p2.move(1);
                break;
            case 100: // fall
                
                break;
            }
            for(int i = 0; i < numOfbomb; i++) {
                can.assign(bombarr[i]->GetX(), bombarr[i]->GetY(), "*");
            }
            can.assign(p1.GetX(), p1.GetY(), "A");
            can.assign(p2.GetX(), p2.GetY(), "B");
            can.show();
        }
    }
    for(int i = 0; i < numOfbomb; i++) {
        delete bombarr[i];
    }
}