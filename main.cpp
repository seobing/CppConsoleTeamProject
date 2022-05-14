#include "canvas.h"
#include "object.h"
#include <conio.h>

using namespace std;

int main() {
    Canvas can;
    //can.show();
    Player p1(75, 10);
    system("cls");
    can.assign(p1.GetX(), p1.GetY(), "1");
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
                p1.move(0);
                break;
		    case 77: // right
                p1.move(1);
                break;
            case 100: // fall
                
                break;
            }
            can.assign(p1.GetX(), p1.GetY(), "1");
            can.show();
        }
    }
    
}