#include <SFML/Graphics.hpp>

#include <conio.h>

#include <vector>

#include <iostream>

#include <windows.h>

#include <cmath>

#include <ctime>

using namespace std;
using namespace sf;
int stolb[3];//порядок столбцов
int nullpole(int field[]) {//обнуляем поле и расставляем блоки
    for (int i = 0; i < 25; i++) {
        field[i] = 0;
    }
    field[1] = field[3] = field[11] = field[13] = field[21] = field[23] = 9;
    return field[25];
}
int proverka(int field[], int orderCubesToBeEnd[]) {//проверка на то, совпали ли столбцы с верхними столбцами
	//если совпали - вернется 1, в обратном случае - 0
    int answer = 0, countMatchCubes = 0;
    int size = 25;
    for (int i = 0; i < 25; i += 5) {
        if (field[i] == field[i + 5] && field[i] == orderCubesToBeEnd[0]) {
            countMatchCubes++;
        }
        if (countMatchCubes == 4) {
            countMatchCubes = 0;
            for (int j = 2; j < 18; j += 5) {
                if (field[j] == field[j + 5] && field[j] == orderCubesToBeEnd[1])
                    countMatchCubes++;
                if (countMatchCubes == 4) {
                    countMatchCubes = 0;
                    for (int m = 4; m < 20; m += 5) {
                        if (field[m] == field[m + 5] && field[m] == (orderCubesToBeEnd[2]))
                            countMatchCubes++;
                        if (countMatchCubes == 4) {
                            answer = 1;
                        }
                    }
                }
            }
        }
    }
    return answer;
}
int arrangement(int field[]) {//случайная расстановка кубиков на поле
    int randIndex, blue = 0, red = 0, yellow = 0;
    while (true) {
        while (blue != 5) {
            randIndex = rand() % 25;
            if (field[randIndex] != 9 && field[randIndex] != 1) {
                field[randIndex] = 1;
                blue++;
            }
        }
        while (red != 5) {
            randIndex = rand() % 25;
            if (field[randIndex] != 9 && field[randIndex] != 1 && field[randIndex] != 2) {
                field[randIndex] = 2;
                red++;
            }
        }
        while (yellow != 5) {
            randIndex = rand() % 25;
            if (field[randIndex] != 9 && field[randIndex] != 1 && field[randIndex] != 2 && field[randIndex] != 3) {
                field[randIndex] = 3;
                yellow++;
            }
        }
        break;
    }
    return field[25];
}
int stolbi(int order[]) {//случайная расстановка порядка столбцов, которые нужно собрать
    srand(time(0));
    int orderCubesToBeEnd[3], rnd;
    orderCubesToBeEnd[0] = rand() % 3;
    orderCubesToBeEnd[1] = rand() % 3;
    while (orderCubesToBeEnd[1] == orderCubesToBeEnd[0]) {
        orderCubesToBeEnd[1] = rand() % 3;
    }
    orderCubesToBeEnd[2] = rand() % 3;
    while (orderCubesToBeEnd[1] == orderCubesToBeEnd[2] || orderCubesToBeEnd[0] == orderCubesToBeEnd[2]) {
        orderCubesToBeEnd[2] = rand() % 3;
    }
    order[0] = orderCubesToBeEnd[0];
    order[1] = orderCubesToBeEnd[1];
    order[2] = orderCubesToBeEnd[2];
    return order[3];
}
int matrixShow(int field[]) {//выводит текущее состояние поля
    for (int i = 0; i < 25; i++) {
        if (i % 5 == 0) {
            cout << endl;
        }
        cout << field[i] << " ";
    }
    return field[25];
}
int ModelBox(int field[], int vibor1, int vibor2) {//тут происходит проверка корректное перемещение блоков, то есть что мы не хотим перейти из клеточки 4 в клеточку 15, в случае если это сделать можно, то мы заменяем значения в матрице и перерисовываем поле
    int temp, complete = 0;
    complete = 0;
    if (vibor1 != 1 && vibor1 != 3 && vibor1 != 11 && vibor1 != 13 && vibor1 != 21 && vibor1 != 23) {
        if (field[vibor2] == 0) {
            if (vibor2 != 1 && vibor2 != 3 && vibor2 != 11 && vibor2 != 13 && vibor2 != 21 && vibor2 != 23) {
                if ((vibor1 == 4 && vibor2 == 5) || (vibor1 == 5 && vibor2 == 4) || (vibor1 == 9 && vibor2 == 10) || (vibor1 == 10 && vibor2 == 9) || (vibor1 == 14 && vibor2 == 15) || (vibor1 == 15 && vibor2 == 14) || (vibor1 == 19 && vibor2 == 20) || (vibor1 == 20 && vibor2 == 19)) {} else {
                    if ((abs(vibor1 - vibor2) == 1 || abs(vibor1 - vibor2) == 5)) {
                        temp = field[vibor1];
                        field[vibor1] = field[vibor2];
                        field[vibor2] = temp;
                        complete = 1;
                    }
                }
            }
        }
    }
    return field[25];
}

void vivodporyadka(int orderCubesToBeEnd[]) {//вывод порядка столбцов можно использовать для документации
    for (int i = 0; i < 3; i++)
        cout << orderCubesToBeEnd[i] << "   ";
}

void selectCheck(int matrica[], int poslvidel) {//если выделен ящичек, и последний клик был не по нему, то ящик перестанет быть выделенным
    for (int i = 0; i < 25; i++) {
        if (matrica[i] == 4 || matrica[i] == 5 || matrica[i] == 6) {
            if (i != poslvidel) {
                switch (matrica[i]) {
                case 4:
                    matrica[i] = 1;
                    break;
                case 5:
                    matrica[i] = 2;
                    break;
                case 6:
                    matrica[i] = 3;
                    break;
                }
            }
        }
    }
}
void determineHit(int* x, int* y, int pozx, int pozy){//узнаем куда попали курсором
	if ((pozx > 100.0) && (pozx < 164.0)) {
        *x = 0;
    }
    if ((pozx > 184) && (pozx < 248)) {
        *x = 1;
    }
    if ((pozx > 268) && (pozx < 332)) {
        *x = 2;
    }
    if ((pozx > 352) && (pozx < 416)) {
        *x = 3;
    }
    if ((pozx > 436) && (pozx < 500)) {
        *x = 4;
    }
    if ((pozy > 100.0) && (pozy < 164.0)) {
        *y = 0;
    }
    if ((pozy > 184) && (pozy < 248)) {
        *y = 1;
    }
    if ((pozy > 268) && (pozy < 332)) {
        *y = 2;
    }
    if ((pozy > 352) && (pozy < 416)) {
        *y = 3;
    }
    if ((pozy > 436) && (pozy < 500)) {
        *y = 4;
    }
}
int main() {
    RenderWindow window(VideoMode(600, 550), "CourseWork");
    int field[25];//игровое поле
    int orderCubesToBeEnd[3];

    bool win = false;

	//txt and sprite loading
    Image fon;
    fon.loadFromFile("bg-igra.png");
    Texture fontex;
    fontex.loadFromImage(fon);
    Sprite fonspr;
    fonspr.setTexture(fontex);
    Image restartbg;
    restartbg.loadFromFile("bg-restart.png");
    Texture resbgtex;
    resbgtex.loadFromImage(restartbg);
    Sprite restartspr;
    restartspr.setTexture(resbgtex);
    Image buttonRest;
    buttonRest.loadFromFile("button-restart.png");
    Texture buttonRestTex;
    buttonRestTex.loadFromImage(buttonRest);
    Sprite buttonRestSpr;
    buttonRestSpr.setTexture(buttonRestTex);
    Image redbox;
    redbox.loadFromFile("red.png");
    Texture redboxtex;
    redboxtex.loadFromImage(redbox);
    Sprite redboxspr;
    redboxspr.setTexture(redboxtex);
    Image bluebox;
    bluebox.loadFromFile("blue.png");
    Texture blueboxtex;
    blueboxtex.loadFromImage(bluebox);
    Sprite blueboxspr;
    blueboxspr.setTexture(blueboxtex);
    Image yellowbox;
    yellowbox.loadFromFile("yellow.png");
    Texture yellowboxtex;
    yellowboxtex.loadFromImage(yellowbox);
    Sprite yellowboxspr;
    yellowboxspr.setTexture(yellowboxtex);
    Image blockbox;
    blockbox.loadFromFile("block.png");
    Texture blockboxtex;
    blockboxtex.loadFromImage(blockbox);
    Sprite blockboxspr;
    blockboxspr.setTexture(blockboxtex);
    Image bluevidelbox;
    bluevidelbox.loadFromFile("bluevidel.png");
    Texture bluevidelboxtex;
    bluevidelboxtex.loadFromImage(bluevidelbox);
    Sprite bluevidelboxspr;
    bluevidelboxspr.setTexture(bluevidelboxtex);
    Image yellowvidelbox;
    yellowvidelbox.loadFromFile("yellowvidel.png");
    Texture yellowvidelboxtex;
    yellowvidelboxtex.loadFromImage(yellowvidelbox);
    Sprite yellowvidelboxspr;
    yellowvidelboxspr.setTexture(yellowvidelboxtex);
    Image redvidelbox;
    redvidelbox.loadFromFile("redvidel.png");
    Texture redvidelboxtex;
    redvidelboxtex.loadFromImage(redvidelbox);
    Sprite redvidelboxspr;
    redvidelboxspr.setTexture(redvidelboxtex);
 
    do {

        Event event;
        win = false;
        int firstSelect = 26;
        yellowboxtex.setSmooth(true);
        window.clear();
        int x = 0, y = 0, countSelected = 0;
        float dX = 0, dY = 0;
        stolbi(orderCubesToBeEnd);
        nullpole(field);
        bool videl = false, otvidel = true;
        int indexvidel;
        int *x1 = &x, *y1 = &y;
		
        int lastSelect = 26;
		//пред финальное состояние, можно раскомментировать эти 6 строчек и закомментировать строчку ниже
        /*field[0]=field[5]=field[10]=field[15]=field[20]=1;
        field[2]=field[7]=field[12]=field[17]=field[22]=2;
        field[4]=field[8]=field[14]=field[19]=field[24]=3;
        orderCubesToBeEnd[0]=0;
        orderCubesToBeEnd[1]=1;
        orderCubesToBeEnd[2]=2;*/

        arrangement(field);//случайным образом мы расставляем по полю наши кубики

        matrixShow(field);//выводим матрицу поля
        while (window.isOpen() && win == false) {
            Vector2i pixelPos = Mouse::getPosition(window);
            Vector2f pos = window.mapPixelToCoords(pixelPos);
            bool fclick = false;
            bool picked = false;
            while (window.pollEvent(event)) {
                if (event.type == Event::Closed) {
                    window.close();
                    win = true;
                }
                if (event.type == Event::MouseButtonPressed)
                    if (event.key.code == Mouse::Left) {
                        while (fclick == false) {
                            int modi;
                            int divi;

                            for (int i = 0; i < 25; i++) {
                                divi = i / 5;
                                modi = i % 5;
                                int index;
                                if ((pos.x > 100 + 84 * modi) && (pos.x < 100 + 84 * modi + 64) && (pos.y > 100 + 84 * divi) && (pos.y < 100 + 84 * divi + 64)) {

                                    float pozx, pozy;

                                    pozx = pos.x;
                                    pozy = pos.y;
									//узнаем по какому кубику мы попали
									determineHit(x1,y1,pozx,pozy);

                                    index = *y1 * 5 + *x1;
                                    firstSelect = index;

                                    fclick = true;
                                    videl = true;
                                    if (field[index] == 0 || field[index] == 9) {//если мы кликнули лкмом по заблокированному блоку или пустому, то выделение пред. блока снимется
                                        switch (field[lastSelect]) {
                                        case 4:
                                            field[lastSelect] = 1;
                                            break;
                                        case 5:
                                            field[lastSelect] = 2;
                                            break;
                                        case 6:
                                            field[lastSelect] = 3;
                                            break;
                                        }
                                    }
                                    countSelected++;
                                    picked = true;
                                    if (countSelected > 1) {//если количество выделенных кубиков больше чем 1, то мы предыдущий кубик сделаем не выделенным
                                        if (field[firstSelect] == 1 || field[firstSelect] == 2 || field[firstSelect] == 3) {
                                            switch (field[indexvidel]) {
                                            case 4:
                                                field[indexvidel] = 1;
                                                break;
                                            case 5:
                                                field[indexvidel] = 2;
                                                break;
                                            case 6:
                                                field[indexvidel] = 3;
                                                break;
                                            }
                                            countSelected = 1;
                                        }
                                    }
                                } else {
                                    fclick = true;
                                }
                            }
                        }
                    }
                bool sclick = false, videl = false;
                if (field[firstSelect] != 0) {//если мы ещё ничего не выделяли то, кубик, на который мы нажали выделится
                    if (countSelected == 1)

                    {
                        indexvidel = firstSelect;
                        switch (field[firstSelect]) {
                        case 1:
                            field[firstSelect] = 4;
                            lastSelect = firstSelect;
                            break;
                        case 2:
                            field[firstSelect] = 5;
                            lastSelect = firstSelect;
                            break;
                        case 3:
                            field[firstSelect] = 6;
                            lastSelect = firstSelect;
                            break;
                        }
                    }
                }
                if (event.type == Event::MouseButtonPressed)
                    if (event.key.code == Mouse::Right) {
                        if (firstSelect != 1 || firstSelect != 3 || firstSelect != 11 || firstSelect != 13 || firstSelect != 21 || firstSelect != 23) {

                            int modi;
                            int divi;
                            for (int i = 0; i < 25; i++) {

                                divi = i / 5;
                                modi = i % 5;
                                int index;
								//
                                if ((pos.x > 100 + 84 * modi) && (pos.x < 100 + 84 * modi + 64) && (pos.y > 100 + 84 * divi) && (pos.y < 100 + 84 * divi + 64)) {
                                    float pozx, pozy;
                                    pozx = pos.x;
                                    pozy = pos.y;
									//узнаем по какому кубику мы попали
									determineHit(x1, y1, pozx, pozy);
                                    index = *y1 * 5 + *x1;

									//если мы попали курсором не по заблокированному блоку и второй клик не равен первому клику, то мы передвигаем ящикек первого клика в свободное поле
                                    if (index != firstSelect && index != 1 && index != 3 && index != 11 && index != 13 && index != 21 && index != 23) {
                                        ModelBox(field, firstSelect, index);
                                        sclick = true;
                                        picked = true;
                                        switch (field[index]) {
                                        case 4:
                                            field[index] = 1;
                                            break;
                                        case 5:
                                            field[index] = 2;
                                            break;
                                        case 6:
                                            field[index] = 3;
                                            break;
                                        }
                                        videl = false;
                                        countSelected = 1;
                                    }


                                }
                            }
                        }
                    }
                if (picked == true) {
                    system("cls");
                    matrixShow(field);
                    picked = false;
                }
            }
            window.clear();
            fonspr.setPosition(0, 0);
            window.draw(fonspr);
            for (int i = 0; i < 25; i++) {
                x = i % 5;
                y = i / 5;
				//рисование ящичков, которые находятся выше игрового поля
                blueboxspr.setPosition(100 + 168 * orderCubesToBeEnd[0], 20);
                window.draw(blueboxspr);

                yellowboxspr.setPosition(100 + 168 * orderCubesToBeEnd[1], 20);
                window.draw(yellowboxspr);

                redboxspr.setPosition(100 + 168 * orderCubesToBeEnd[2], 20);
                window.draw(redboxspr);
				////

                stolb[orderCubesToBeEnd[0]] = 1;
                stolb[orderCubesToBeEnd[1]] = 2;
                stolb[orderCubesToBeEnd[2]] = 3;
				//рисование всех игровых ящичков
                switch (field[i]) {
                case 1:
                    blueboxspr.setPosition(100 + x * 84, 100 + y * 84);
                    window.draw(blueboxspr);
                    break;
                case 2:
                    yellowboxspr.setPosition(100 + x * 84, 100 + y * 84);
                    window.draw(yellowboxspr);
                    break;
                case 3:
                    redboxspr.setPosition(100 + x * 84, 100 + y * 84);
                    window.draw(redboxspr);
                    break;
                case 4:
                    bluevidelboxspr.setPosition(96 + x * 84, 96 + y * 84);
                    window.draw(bluevidelboxspr);
                    break;
                case 5:
                    yellowvidelboxspr.setPosition(96 + x * 84, 96 + y * 84);
                    window.draw(yellowvidelboxspr);
                    break;
                case 6:
                    redvidelboxspr.setPosition(96 + x * 84, 96 + y * 84);
                    window.draw(redvidelboxspr);
                    break;
                case 9:
                    blockboxspr.setPosition(100 + x * 84, 100 + y * 84);
                    window.draw(blockboxspr);
                    break;
                }

            }
            window.display();

            if (proverka(field, stolb) == 1) {//если собраны все столбики в нужном порядке, то мы заходим в этот цикл
				//вырисовываем бекграунд, потому что так как игра остановилась, нужно прорисовать прошлый кадр
                window.clear();
                window.draw(fonspr);
                for (int i = 0; i < 25; i++) {
                    x = i % 5;
                    y = i / 5;

                    blueboxspr.setPosition(100 + 168 * orderCubesToBeEnd[0], 20);
                    window.draw(blueboxspr);

                    yellowboxspr.setPosition(100 + 168 * orderCubesToBeEnd[1], 20);
                    window.draw(yellowboxspr);

                    redboxspr.setPosition(100 + 168 * orderCubesToBeEnd[2], 20);
                    window.draw(redboxspr);
                    stolb[orderCubesToBeEnd[0]] = 1;
                    stolb[orderCubesToBeEnd[1]] = 2;
                    stolb[orderCubesToBeEnd[2]] = 3;

                    switch (field[i]) {
                    case 1:
                        blueboxspr.setPosition(100 + x * 84, 100 + y * 84);
                        window.draw(blueboxspr);
                        break;
                    case 2:
                        yellowboxspr.setPosition(100 + x * 84, 100 + y * 84);
                        window.draw(yellowboxspr);
                        break;
                    case 3:
                        redboxspr.setPosition(100 + x * 84, 100 + y * 84);
                        window.draw(redboxspr);
                        break;
                    case 9:
                        blockboxspr.setPosition(100 + x * 84, 100 + y * 84);
                        window.draw(blockboxspr);
                        break;
                    }
                }

                bool restclick = false, exit = false;
                restartspr.setPosition(0, 0);
                window.draw(restartspr);
                buttonRestSpr.setPosition(225, 275);
                window.draw(buttonRestSpr);
                window.display();

                while (restclick == false) {//ждем пока нажмут на кнопку рестарта, а потом перезапускаем игру
                    Vector2i pixelPos = Mouse::getPosition(window);
                    Vector2f pos = window.mapPixelToCoords(pixelPos);
                    system("cls");
                    Event event1;
                    while (window.pollEvent(event1)) {

                        if (event1.type == Event::MouseButtonPressed)
                            if (event1.key.code == Mouse::Left)
								//если попали лкмом по спрайту кнопки, то будет перезагрузка игры
                                if (buttonRestSpr.getGlobalBounds().contains(pos.x, pos.y)) {
                                    restclick = true;
                                    win = false;
                                    break;
                                }
                    }
                    window.clear();

                }
                if (win == false)
                    break;
            }

        }
        selectCheck(field, indexvidel);
    }
    while (win == false);
    return 0;
}