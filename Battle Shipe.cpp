#include <iostream>
#include <cstdlib>
#include <ctime>
#include <string>

using namespace std;

const int BOARD = 7; //размер доски
const int EMPTY = 0; //пустые ячейки
const int SINGLE = 1;
const int DOUBLE = 2;//корабли
const int TRIPLE = 3;

void clearScreen() {
    system("cls");          // команда для очистки консоля
}

bool isValidPlacement(int arr[][BOARD], int x, int y, int size, int orientation, int n) {//x,y координнаты,а n размер доски
    if ((orientation == 0 && y + size > n) || (orientation == 1 && x + size > n)) {      // проверяет можно ли разместить там корабль и не выходит ли он за доску
        return false;
    }

    for (int i = x; i < x + size; ++i) {
        for (int j = y; j < y + size; ++j) {
            if (i >= 0 && i < n && j >= 0 && j < n && arr[i][j] != EMPTY) {
                return false;
            }
        }
    }

    return true;
}

void placeShip(int arr[][BOARD], int size, int shipType, int n) { //рандомная постоновка по х и у
    int x, y, orientation;
    do {
        x = rand() % n;
        y = rand() % n;
        orientation = rand() % 2; // и рандомная ориентфция
    } while (!isValidPlacement(arr, x, y, size, orientation, n));

    for (int i = 0; i < size; ++i) { // заполнение ячейек
        if (orientation == 0) {
            arr[x][y + i] = shipType;
        }
        else {
            arr[x + i][y] = shipType;
        }
    }
}

void printBoard(int arr[][BOARD], int n) {
    cout << " ";
    for (int i = 1; i <= n; i++) {   // состояния доски почле хода и очищения
        cout << i << " ";
    }
    cout << endl;

    for (int i = 0; i < n; i++) {
        cout << i + 1 << " ";
        for (int j = 0; j < n; j++) {
            cout << arr[i][j] << " ";
        }
        cout << endl;
    }
}

bool Destroyed(int arr[][BOARD], int shipType, int n) {
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {   // проверка уничтожен ли корабль
            if (arr[i][j] == shipType) {
                return false;
            }
        }
    }
    return true;
}

int main() {
    string playerName;
    cout << "Enter your name: ";
    getline(cin, playerName);       //вывод имени

    int arr[BOARD][BOARD] = { EMPTY };  //создается двухмерный массив 

    srand(time(0)); // вывод рандомных чисел и они с каждым перезапуском не повторяются

    placeShip(arr, 3, TRIPLE, BOARD);
    placeShip(arr, 2, DOUBLE, BOARD);
    placeShip(arr, 1, SINGLE, BOARD);               //размещение кораблей разных раазмеров на доске
    placeShip(arr, 1, SINGLE, BOARD);
    placeShip(arr, 1, SINGLE, BOARD);
    placeShip(arr, 1, SINGLE, BOARD);

    int sunked = 0;
    while (sunked < 9) {     // повтор покаа не будет потоплено 9 кораблей
        clearScreen();     //очищение консоли после каждой попытки
        printBoard(arr, BOARD); // росле очищения выводит текущее состояние доски

        int r, c;
        cout << playerName << ", enter coordinates (row column): ";
        cin >> r >> c;

        if (r < 1 || r > BOARD || c < 1 || c > BOARD) {
            cout << "Invalid coordinates. Try again." << endl;
            continue;
        }

        if (arr[r - 1][c - 1] == EMPTY) {
            cout << "Miss" << endl;
        }
        else {
            cout << "Hit!" << endl;
            int Type = arr[r - 1][c - 1];    // проверяет пустая ли ячейка если нет то заменяет на ноль и выводит то что попал
            arr[r - 1][c - 1] = EMPTY;
            sunked++;

            if (Destroyed(arr, Type, BOARD)) {
                if (Type == SINGLE) {
  
                  cout << "Sunk! You destroyed a single-masted ship!" << endl;
                }
                else if (Type == DOUBLE) {
                    cout << "Sunk! You destroyed a double-masted ship!" << endl;   
                }
                else if (Type == TRIPLE) {
                    cout << "Sunk! You destroyed a triple-masted ship!" << endl;
                }
            }
        }

        cout << "Press Enter to continue...";
        cin.ignore(); // игнорирует другте значения перед нажатием enter
        cin.get();// ожидвет нажатия enter
    }

    clearScreen();
    printBoard(arr, BOARD);
    cout << "You win the game, " << playerName << "! Congrats!" << endl;

    return 0;
}