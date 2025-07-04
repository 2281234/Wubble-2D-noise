#include <iostream>
#include <string>
#include <map>
#include <vector>
#include "lodepng.h"

int X;
int Y;
int Z;
std::vector<std::vector<std::vector<char>>>* Map = nullptr;

int pointz = 0;
int pointy = 0;
int pointx = 0;

int const LEFT_UP = 1;
int const UP = 2;
int const RIGHT_UP = 3;
int const LEFT = 4;
int const CENTER = 5;
int const RIGHT = 6;
int const LEFT_DOWN = 7;
int const DOWN = 8;
int const RIGHT_DOWN = 9;

char emptySpace = ' ';
char aCell = '=';
char bCell = '#';

int envir = 0; // environment
std::map<char, unsigned char> rchannel = { {emptySpace, 0}, {aCell, 127}, {bCell, 255} };
std::map<char, unsigned char> gchannel = { {emptySpace, 0}, {aCell, 127}, {bCell, 255} };
std::map<char, unsigned char> bchannel = { {emptySpace, 0}, {aCell, 127}, {bCell, 255} };

void startMap() {
    for (int iz = 0; iz < Z; iz++) {
        for (int iy = 0; iy < Y; iy++) {
            for (int ix = 0; ix < X; ix++) {
                (*Map)[iz][iy][ix] = emptySpace;
            }
        }
    }
}

void randMap(int a, int b) {
    srand(time(0));
    int r = 0;
    for (int iy = 0; iy < Y; iy++) {
        for (int ix = 0; ix < X; ix++) {
            r = rand() % 100;
            if (r <= a) {
                (*Map)[pointz][iy][ix] = bCell;
            }
            else if (r <= a + b) {
                (*Map)[pointz][iy][ix] = aCell;
            }
            else {
                (*Map)[pointz][iy][ix] = emptySpace;
            }
        }
    }
}

char readChar(int a) {
    if (a == LEFT_UP and (pointx != 0 and pointy != 0)) {
        return (*Map)[pointz - 1][pointy - 1][pointx - 1];
    }
    else if (a == UP and pointy != 0) {
        return (*Map)[pointz - 1][pointy - 1][pointx];
    }
    else if (a == RIGHT_UP and (pointx != 0 and pointy != 0)) {
        return (*Map)[pointz - 1][pointy - 1][pointx + 1];
    }
    else if (a == LEFT and pointx != 0) {
        return (*Map)[pointz - 1][pointy][pointx - 1];
    }
    else if (a == CENTER) {
        return (*Map)[pointz - 1][pointy][pointx];
    }
    else if (a == RIGHT and pointx != X - 1) {
        return (*Map)[pointz - 1][pointy][pointx + 1];
    }
    else if (a == LEFT_DOWN and (pointx != 0 and pointy != Y - 1)) {
        return (*Map)[pointz - 1][pointy + 1][pointx - 1];
    }
    else if (a == DOWN and pointy != Y - 1) {
        return (*Map)[pointz - 1][pointy + 1][pointx];
    }
    else if (a == RIGHT_DOWN and (pointx != X - 1 and pointy != Y - 1)) {
        return (*Map)[pointz - 1][pointy + 1][pointx + 1];
    }
    return 0;
}

bool envirContains(char cell) {
    for (int i = 1; i <= 9; i++) {
        if (readChar(i) == cell) {
            return 1;
        }
    }
    return 0;
}

void checkEnvir() {
    envir = 0;
    //a:

    if (envirContains(bCell)) {
        envir++;
    }

    //b:
    if (readChar(CENTER) == aCell) {
        envir++;
    }
    if (readChar(LEFT_UP) == aCell) {
        if (readChar(RIGHT_UP) == aCell) {
            envir++;
        }
        if (readChar(LEFT_DOWN) == aCell) {
            envir++;
        }
        if (readChar(RIGHT_DOWN) == aCell) {
            envir++;
        }
    }
    if (readChar(RIGHT_UP) == aCell) {
        if (readChar(LEFT_DOWN) == aCell) {
            envir++;
        }
        if (readChar(RIGHT_DOWN) == aCell) {
            envir++;
        }
    }
    if (readChar(LEFT_DOWN) == aCell) {
        if (readChar(RIGHT_DOWN) == aCell) {
            envir++;
        }
    }
}
void creatPNG() {
    std::vector<unsigned char> image(X * Y * 4);
    unsigned int index = 0;
    bool a = 0;
    int r = 0;
    int g = 0;
    int b = 0;
    for (int iz = 0; iz < Z; iz++) {
        a = iz == 0;
        std::cout << '\r' << (iz + 1) * 100 / Z << "% of image is created/изображения сделано"<< std::flush;
        for (int iy = 0; iy < Y; iy++) {
            for (int ix = 0; ix < X; ix++) {
                index = (iy * X + ix) * 4;
                image[index + 3] = 255;
                if ((*Map)[iz][iy][ix] == emptySpace) {
                    r = rchannel[emptySpace];
                    g = gchannel[emptySpace];
                    b = bchannel[emptySpace];
                }
                else if ((*Map)[iz][iy][ix] == aCell) {
                    r = rchannel[aCell];
                    g = gchannel[aCell];
                    b = bchannel[aCell];
                }
                if ((*Map)[iz][iy][ix] == bCell) {
                    r = rchannel[bCell];
                    g = gchannel[bCell];
                    b = bchannel[bCell];
                }
                if (a == 1) {
                    image[index + 0] = r; // Красный (Red)
                    image[index + 1] = g; // Зеленый (Green)
                    image[index + 2] = b; // Синий (Blue)
                }
                else {
                    image[index + 0] = (image[index + 0] * 2 + r * 3) / 5; // Красный (Red)
                    image[index + 1] = (image[index + 1] * 2 + g * 3) / 5; // Зеленый (Green)
                    image[index + 2] = (image[index + 2] * 2 + b * 3) / 5; // Синий (Blue)
                }
            }
        }
    }
    std::string fileName = "Noise.png";
    unsigned int error = lodepng::encode(fileName.c_str(), image, X, Y);
    if (error) {
        std::cout << "\nerror creating impage/ошибка при создании изображения\n";
    }
    else {
        std::cout << "\nnoise saved in Noise.png/шум сохранён в Noise.png\n";
    }
}
int main() {
    setlocale(LC_ALL, "russian");
    std::cout << "Enter width, height and number of iterations (the more iterations, the longer the program runs, but the better the noise)\nВведите ширену, высоту и количество итераций(чем больше итераций, тем дольше работа программы, но лучше шум)\n";
    std::cin >> X >> Y >> Z;
    Map = new std::vector<std::vector<std::vector<char>>>(
        Z, std::vector<std::vector<char>>(
            Y, std::vector<char>(X)
        )
    );
    startMap();
    for (pointz = 0; pointz < Z; pointz++) {
        std::cout << '\r' << (pointz + 1) * 100 / Z << "% of Wubble simulation done/от Wubble симуляции сделанно" << std::flush;
        if (pointz == 0) {
            randMap(1, 0);
        }
        else {
            for (pointy = 0; pointy < Y; pointy++) {
                for (pointx = 0; pointx < X; pointx++) {
                    checkEnvir();
                    if (envir == 1) {
                        (*Map)[pointz][pointy][pointx] = aCell;
                    }
                    else if (envir == 2) {
                        (*Map)[pointz][pointy][pointx] = bCell;
                    }
                }
            }
        }
    }
    std::cout << '\n';
    creatPNG();
    std::string waitEnter;
    std::cin >> waitEnter;
}
