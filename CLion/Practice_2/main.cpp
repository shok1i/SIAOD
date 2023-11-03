#include <iostream>
#include <string>
#include <fstream>
#include <vector>

using std::cin, std::cout, std::string, std::ofstream, std::ifstream, std::getline;

// Функция для создания текстового файла, содержащего десятичные числа
void createFile(string filename){
    ofstream file(filename);

    if (file.is_open())
        file << "1 2 3 4 5 6\n"
             << "7 8 9 10\n"
             << "11 12\n";
    else
        cout << "File opening error\n";

    file.close();
}

// Функция для вывода содержимого текстового файла
void printFile(string filename){
    ifstream file(filename);
    string line;

    if (file.is_open())
        while (getline(file, line))  cout << line << std::endl;

    else
        cout << "File opening error\n";

    file.close();
}

// Добавление новой строки в конец файла
void addLine(string filename, string line){
    ofstream file (filename, std::ios_base::app);

    if (file.is_open())
        file << line << std::endl;
    else
        cout << "File opening error\n";

    file.close();
}

// Вывести эллемент под индексов введенным пользователем
int readIndex(string filename, int index){
    ifstream file(filename);
    int count = 0;
    string line;

    if (file.is_open())
        while (getline(file, line)){
            string temp;
            count++;
            for (char unit : line) {
                if (isdigit(unit))
                    temp += unit;
                else
                {
                    if (count == index) return stoi(temp);
                    count++;
                    temp="";
                }

            }
        }
    else
        cout << "File opening error\n";

    file.close();
}

// Определить кол-во чисел в файле
int numberCount(string filename){
    ifstream file(filename);
    int count = 0;
    string line;

    if (file.is_open())
        while (getline(file, line)){
            count++;
            for (char unit : line) {
                if (!isdigit(unit)) count++;
            }
        }
    else
        cout << "File opening error\n";

    return count;
}

// Задние по вариантам Вариант №29
std::vector <int> fibonacciSeries(int count) {
    std::vector <int> temp = {0, 1};
    int i_first = 0, i_second = 1;

    while (count >= i_second){
        temp.push_back(i_first + i_second);
        i_first = i_second;
        i_second = temp.back();
    }

    return temp;
}

void task(string filename, string task_filename){
    ifstream file(filename);
    string line, temp;

    if (file.is_open())
        while (getline(file, temp))
            line += temp + " ";
    else
        cout << "File opening error\n";

    string tmp;
    int count = 0;
    std::vector <int> digit;
    for (char unit : line){
        if (isdigit(unit))
            tmp += unit;
        else{
            digit.push_back(stoi(tmp));
            count++;
            tmp="";
        }
    }

    ofstream task_file (task_filename, std::ios_base::in);
    if (task_file.is_open()) {
        int index = 0;
        for (int unit: fibonacciSeries(count)) {
            for (int i = 0; i < unit && index < digit.size(); i++) {
                task_file << digit.at(index) << " ";
                index++;
            }
            if (index < digit.size()) task_file << "\n";
        }
    }
    else
        cout << "File opening error\n";

    file.close();
    task_file.close();
}

int main() {
    string filename;
    cout << "Enter filename: ";
    cin  >> filename;

    int choice;
    cout << "1. Create file\n"
         << "2. Print the contents of the file\n"
         << "3. Add a new line to the file\n"
         << "4. Read the value of the number\n"
         << "5. Determine the number of numbers in the file\n"
         << "6. Change file name\n"
         << "7. Do task\n"
         << "0. Exit\n";



    while (choice != 0)
    {
        cout << "Select action: ";
        cin  >> choice;
        switch (choice) {
            case 1:
                createFile(filename);
                break;
            case 2:
                printFile(filename);
                break;
            case 3: {
                string line;
                cout << "Enter a new line: ";
                cin.ignore();
                getline(cin, line);
                addLine(filename, line);
                break;
            }
            case 4: {
                int index;
                cout << "Enter the number of the number: ";
                cin  >> index;
                cout << "The number is: " << readIndex(filename, index) << "\n";
                break;
            }
            case 5:
                cout << "The number of numbers: " << numberCount(filename) << "\n";
                break;
            case 6: {
                cout << "Enter new filename: ";
                cin >> filename;
                break;
            }
            case 7:{
                string task_filename;
                cout << "Enter name to task file: ";
                cin  >> task_filename;
                ofstream task_file (task_filename);
                task(filename, task_filename);
                break;
            }

            case 0:
                cout << "Exit\n";
                break;
            default:
                cout << "Wrong choice!\n";
                break;
        }

    }
// Добавить отработку переполнения и то функция отработана

    task(filename, "task_filename");
    printFile("task_filename");

    return 0;
}
