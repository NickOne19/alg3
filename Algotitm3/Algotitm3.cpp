#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <algorithm>

using namespace std;

struct pos { // Информацию о платформе храним в структуре pos, которая содержит ее координаты (x, y) и количество монет coins на ней.
    long long x, y, coins;
} c[50];

int maxCoins(int v, int g, int n) { // Начиная с последней платформы (наивысшей, которая имеет наибольшую y - координату), вычисляем значения ячеек opt[i].
    int i, j, res = 0;
    int opt[50] = { 0 };
    for (i = n - 1; i >= 0; i--) {
        //Если мы начинаем сбор монет с i-ой платформы и в ней же сбор заканчиваем, то положим opt[i] = c[i].coins.
        opt[i] = c[i].coins;

        for (j = i + 1; j < n; j++) {
            //Если с j-ой платформы можно прыгнуть на i-ую платформу (i < j), и при этом сумма opt[j] + c[i].coins будет больше opt[i], то пересчитываем значение opt[i].
            if ((opt[j] + c[i].coins > opt[i]) &&
                (g * (c[i].x - c[j].x) * (c[i].x - c[j].x) <= (c[j].y - c[i].y) * 2 * v * v)) {
                opt[i] = opt[j] + c[i].coins;
            }
        }
        if (opt[i] > res) res = opt[i];
    }
    return res;
}
int f(pos a, pos b) { //Функция сортировки – платформы сортируются по возрастанию y - координат.
    return a.y < b.y;
}

int main() { // После считывания входнх данных сортируем платформы по возрастанию их ординат. Вычисляем и выводим результат.
    int n, v, g, res;
    setlocale(LC_ALL, "Russian");
    while (cin >> n >> v >> g) {
        for (int i = 0; i < n; i++) {
            cin >> c[i].x >> c[i].y >> c[i].coins;
        }
        sort(c, c + n, f);
        res = maxCoins(v, g, n);
        cout <<" Вывод " << res << " " << endl;
    }
    return 0;
}