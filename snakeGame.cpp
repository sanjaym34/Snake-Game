#include<iostream>
#include<conio.h>
#include<stdlib.h>
using namespace std;

#define A 75
#define W 72
#define S 80
#define D 77

bool gameOver;
const int width = 30;
const int height = 30;
int x,y,foodX,foodY,score;
int tailX[100],tailY[100],tailLength;
enum eDirection {STOP = 0,UP,DOWN,LEFT,RIGHT};
eDirection dir;

void Setup(){
    gameOver = false;
    dir = STOP;
    x = width / 2;
    y = height / 2;
    foodX = rand() % width;
    foodY = rand() % height;
    score = 0;
}

void Draw(){
    system("cls");
    cout << "Use arrow keys" << endl;
    cout << "If you hit the borders or yourself, you die" << endl;
    cout << "For every fruit you eat, your score increases by 10" << endl;
    cout << "S --> Snake && F --> Fruit" << endl;
    for(int i=0;i<width+2;i++){
        cout << "* ";
    }
    cout << endl;

    for(int i = 0 ;i<height;i++){
        for(int j=0;j<width;j++){
            if(j == 0)
                cout << "* ";
                if(i == y && j == x)
                    cout << "S ";
                else if(i == foodY && j == foodX)
                    cout << "F ";
                else{
                    bool isPrinted = false;
                    for(int k=0;k<tailLength;k++){
                        if(tailX[k] == j && tailY[k] == i){
                            cout << "S ";
                            isPrinted = true;
                        }
                    }

                        if(isPrinted == false){
                            cout << "  ";
                        }
                }
            if(j == (width - 1)){
                cout << "* ";
            }

        }
        cout << endl;
    }

    for(int i=0;i<width+2;i++){
        cout << "* ";
    }
    cout << endl;
    cout << "Score: " << score;
}

void Input(){
    while(_kbhit()){
        switch(_getch()){
        case 'a':case A:
            dir = LEFT;
            break;
        case 'w':case W:
            dir = UP;
            break;
        case 's':case S:
            dir = DOWN;
            break;
        case 'd':case D:
            dir = RIGHT;
            break;
        case 'x':
            gameOver = true;
            break;
        }
    }
}

void Logic(){
    int prevX = tailX[0];
    int prevY = tailY[0];
    int prev2X;
    int prev2Y;
    tailX[0] = x;
    tailY[0] = y;
    for(int i=1;i<tailLength;i++){
        prev2X = tailX[i];
        prev2Y = tailY[i];
        tailX[i] = prevX;
        tailY[i] = prevY;
        prevX = prev2X;
        prevY = prev2Y;
    }
    switch(dir){
    case LEFT:
        x--;
        break;
    case RIGHT:
        x++;
        break;
    case UP:
        y--;
        break;
    case DOWN:
        y++;
        break;
    default:
        break;
    }
    if(x<0 || x>width || y<0 || y>height){
        gameOver=true;
    }
    for(int i=0;i<tailLength;i++){
        if(tailX[i] == x && tailY[i] == y){
            gameOver = true;
        }
    }
    if(x == foodX && y == foodY){
        score += 10;
        foodX = rand() % width;
        foodY = rand() % height;
        tailLength++;
    }
}

int main(){
    Setup();
    while(!gameOver){
        Draw();
        Input();
        Logic();
    }
    return 0;
}
