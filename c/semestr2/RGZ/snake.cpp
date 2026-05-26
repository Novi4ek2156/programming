#include <iostream>
#include <ncurses.h>
#include <unistd.h>
#include <cstdlib>
#include <ctime>

using namespace std;

bool gameOver;
bool gameWin;  // Флаг победы
int height;
int width;
int x, y, fruitX, fruitY, superfX, superfY, score;
int speed = 1;
int key;
enum eDirection {STOP=0, UP, DOWN, LEFT, RIGHT};
eDirection dir;
int tailX[100], tailY[100], nTail;

void SaveScoreToFile() {
    FILE *f = fopen("Score.txt", "w+");
    if (f != NULL) {
        if (gameWin) {
            printw("YOU WIN!!!\n");
            fprintf(f, "VICTORY! Final Score: %d\n", score);
        } else {
            printw("\nYOU LOSE!!!\n");
            fprintf(f, "Game Over! Final Score: %d\n", score);
        }
        fprintf(f, "Tail length: %d\n", nTail);
        fprintf(f, "Date: ");
        
        time_t now = time(NULL);
        fprintf(f, "%s", ctime(&now));
        
        fclose(f);
        printw("\nScore saved to Score.txt\n");
        refresh();
        napms(2000);
    } else {
        printw("\nError: Cannot save file!\n");
        refresh();
        napms(2000);
    }
}

bool checkWin() {
    int maxCells = (width - 2) * height;
    if (nTail + 1 >= maxCells) {
        return true;
    }
    return false;
}

bool isFreeCell(int checkX, int checkY) {
    if (checkX <= 0 || checkX >= width - 1 || checkY < 0 || checkY >= height) {
        return false;
    }
    
    if (checkX == x && checkY == y) {
        return false;
    }
    
    for(int i = 0; i < nTail; i++) {
        if (checkX == tailX[i] && checkY == tailY[i]) {
            return false;
        }
    }
    
    return true;
}

void generateFruit() {
    int freeCells = 0;
    for(int i = 0; i < height; i++) {
        for(int j = 1; j < width - 1; j++) {
            if (isFreeCell(j, i)) {
                freeCells++;
            }
        }
    }
    
    if (freeCells == 0) {
        gameWin = true;
        gameOver = true;
        return;
    }
    
    int target = rand() % freeCells;
    int counter = 0;
    
    for(int i = 0; i < height; i++) {
        for(int j = 1; j < width - 1; j++) {
            if (isFreeCell(j, i)) {
                if (counter == target) {
                    fruitX = j;
                    fruitY = i;
                    return;
                }
                counter++;
            }
        }
    }
}

void generateSuperFruit() {
    if (nTail % 2 != 0) return;
    
    int freeCells = 0;
    for(int i = 0; i < height; i++) {
        for(int j = 1; j < width - 1; j++) {
            if (isFreeCell(j, i) && !(j == fruitX && i == fruitY)) {
                freeCells++;
            }
        }
    }
    
    if (freeCells == 0) return;
    
    int target = rand() % freeCells;
    int counter = 0;
    
    for(int i = 0; i < height; i++) {
        for(int j = 1; j < width - 1; j++) {
            if (isFreeCell(j, i) && !(j == fruitX && i == fruitY)) {
                if (counter == target) {
                    superfX = j;
                    superfY = i;
                    return;
                }
                counter++;
            }
        }
    }
}

void Setup() {
    gameOver = false;
    gameWin = false;
    dir = STOP;
    score = 0;
    nTail = 0;
    x = (width / 2) -2;
    y = (height / 2) -2;
    
    generateFruit();
    generateSuperFruit();
}

void MapSize() {
    printw("Input size map(Format: 20 20): ");
    scanw("%d %d", &height, &width);
}

void Draw() {
    clear();
    printw("\n+++++SNAKE GAME+++++\n");
    printw("Score: %d\nTail: %d\n", score, nTail);
    
    if (gameWin) {
        printw("*** VICTORY! ***\n");
    }
    
    for(int i=0; i < width; i++) {
        printw("#");
    }
    printw("\n");

    for(int i=0; i < height; i++){
        for(int j=0; j < width; j++) {
            if(j == 0 || j == width - 1) {
                printw("#");
            } else if (i == y && j == x){
                printw("o");
            } else if (i == fruitY && j == fruitX){
                printw("*");
            } else if ((i == superfY && j == superfX) && nTail % 2 == 0) {
                printw("+");
            } else{
                bool print = false;
                for(int k = 0; k < nTail; k++) {
                    if (i == tailY[k] && j == tailX[k]) {
                        printw(".");
                        print = true;
                    }
                }
                if(!print) printw(" ");
            }
        }
        printw("\n");
    }

    for(int i=0; i < width; i++) {
        printw("#");
    }
    printw("\n");
}

void Input() {
    key = getch();
    if (key != ERR) {
        switch(key) {
            case 'w':
                if (dir != DOWN) dir = UP;
                break;
            case 's':
                if(dir != UP) dir = DOWN;
                break;
            case 'a':
                if(dir != RIGHT) dir = LEFT;
                break;
            case 'd':
                if (dir != LEFT) dir = RIGHT;
                break;
            case 'q':
                gameOver = true;
                break;
            default:
                break;
        }
    }
}

void Logic() {
    int prevX = tailX[0];
    int prevY = tailY[0];
    tailX[0] = x;
    tailY[0] = y;
    int prev2X, prev2Y;
    for(int i = 1; i < nTail; i++ ) {
        prev2X = tailX[i];
        prev2Y = tailY[i];
        tailX[i] = prevX;
        tailY[i] = prevY;
        prevX = prev2X;
        prevY = prev2Y;
    }

    switch (dir) {
    case UP:
        y--;
        break;
    case DOWN:
        y++;
        break;
    case LEFT:
        x--;
        break;
    case RIGHT:
        x++;
        break;
    default:
        break;
    }
    
    if (x <= 0 || x >= width - 1 || y < 0 || y >= height) {
        gameOver = true;
    }

    for(int i = 0; i < nTail; i++) {
        if(x == tailX[i] && y == tailY[i]) {
            gameOver = true;
        }
    }
    
    if (x == superfX && y == superfY) {
        score += 50;
        generateSuperFruit();
        
        if (checkWin()) {
            gameWin = true;
            gameOver = true;
        }
    }
    
    for(int i = 0; i < nTail; i++) {
        if (fruitX == tailX[i] && fruitY == tailY[i]) {
            generateFruit();
        }
        if (superfX == tailX[i] && superfY == tailY[i]) {
            generateSuperFruit();
        }
    }

    if (x == fruitX && y == fruitY) {
        score += 10;
        nTail++;
        generateFruit();
        generateSuperFruit();
        
        if (checkWin()) {
            gameWin = true;
            gameOver = true;
        }
    }
}

int main() {
    srand(time(NULL));
    
    initscr();
    
    MapSize();
    Setup();

    nodelay(stdscr, TRUE);  // ДОБАВЛЕНО: для неблокирующего ввода
    // ДОБАВЛЕНО: задаем начальное направление, чтобы змейка двигалась сама
    dir = RIGHT;
    
    while(!gameOver) {
        Draw();
        Input();
        Logic();
        usleep(125000);
    }
    
    SaveScoreToFile();
    
    endwin();
    return 0;
}