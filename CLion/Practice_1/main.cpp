#include <iostream>
#include "string"

// Практика №1
// Вариант №10

std::string cout_2sc(unsigned int x){
    std::string str;
    int n = sizeof (int) * 8;
    unsigned mask = (1<<(n-1));
    for(int i = 1; i <= n; i++){
        str += std::to_string(((x & mask)>>(n-i)));
        mask = mask>>1;
    }
    return str;
}

// Задание №1
// Четыре младших разряда
int Number_1(int x){
    int mask = 0x000F; // => 1111 в 2с.с. => F  16с.с.
    return x | mask;
}

// Задание №2
// 3-ий 5-ый 11-ый
int Number_2(int x){
    int mask = ~0x0828; // => 1 0 0 0 0 0 1 0 1 0 0 0 в 2с.с. => 585 в 16 с.с.
    return x & mask;
}

// Задание №3
// 16 => 2^4
int Number_3(int x){
    return x << 4;
}

// Задание №4
// 16 => 2^4
int Number_4(int x){
    return x >> 4;
}

// Задание №5
// Установить n-ый бит в 1, используя маску 2
int Number_5(int x, int n){
    unsigned int mask_2 = 0x80000000 >> 31 - n;
    return mask_2 | x;
}

int main() {
    int x, n;
    setlocale(LC_ALL, "ru");
    system("chcp 65001");
    std::cout   << "Поле для ввода:" << std::endl;
    std::cin    >> x;
    std::cout   << "Введите значение n для пятого задания:" << std::endl;
    std::cin    >> n;
    std::cout << "№     | " << "Число в 2 с.с." << "\t\t\t\t| " << "Число в 10 с.с." << std::endl
              << "ИСХОД | " << cout_2sc(x) << "\t| " << x << std::endl
              << "1     | " << cout_2sc(Number_1(x)) << "\t| " << Number_1(x) << std::endl
              << "2     | " << cout_2sc(Number_2(x)) << "\t| " << Number_2(x) << std::endl
              << "3     | " << cout_2sc(Number_3(x)) << "\t| " << Number_3(x) << std::endl
              << "4     | " << cout_2sc(Number_4(x)) << "\t| " << Number_4(x) << std::endl
              << "5     | " << cout_2sc(Number_5(x, n)) << "\t| " << Number_5(x, n) << std::endl;
}
