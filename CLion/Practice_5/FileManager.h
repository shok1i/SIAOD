#ifndef PRACTICE__5_FILEMANAGER_H
#define PRACTICE__5_FILEMANAGER_H

#include "random"
#include "iostream"
#include "fstream"

using namespace std;

int Random_Func(int min, int max){
    random_device rd;
    mt19937 gen(rd());
    uniform_int_distribution<> RANDOM(min, max);
    return RANDOM(gen);
}
void createText(const string& textFileName, int size){
    ofstream out;
    out.open(textFileName);
    for (int i = 0; i < size; i++) {
        out << Random_Func(100000, 1000000) << " BRAND-" << i << " OWNER-" << i << endl;
    }
    out.close();
}

struct CarRecord{
    int  key;
    char brand[64];
    char owner[64];
};
class FileManager {
private:
    fstream file;

public:
    void createFile(const string& textFileName, const string& binaryFileName) {
        ifstream textFile(textFileName);
        file.open(binaryFileName, ios::out | ios::binary);

        if (!textFile || !file) {
            cout << "Failed to open files." << endl;
            return;
        }

        CarRecord record;
        while (textFile >> record.key >> record.brand >> record.owner) {
            file.write(reinterpret_cast<const char*>(&record), sizeof(CarRecord));
        }

        textFile.close();
        file.close();
    }

    void linearSearch(const string& binaryFileName, int carNumber) {
        file.open(binaryFileName, ios::in | ios::binary);

        if (!file) {
            std::cout << "Failed to open file." << std::endl;
            return;
        }

        CarRecord record;
        bool found = false;
        while (file.read(reinterpret_cast<char*>(&record), sizeof(CarRecord))) {
            if (record.key == carNumber) {
                cout << "Record found." << endl;
                cout << "KEY       | Brand\t| Owner Info" << endl;
                cout << record.key << " | " << record.brand << "\t| " << record.owner << endl;
                found = true;
                break;
            }
        }

        if (!found) {
            cout << "Record not found." << endl;
        }

        file.close();
    }

    void printRecord(const string& binaryFileName, int address) {
        file.open(binaryFileName, std::ios::in | std::ios::binary);

        if (!file) {
            cout << "Failed to open file." << endl;
            return;
        }

        CarRecord record;
        file.seekg(address * sizeof(CarRecord));
        file.read(reinterpret_cast<char*>(&record), sizeof(CarRecord));

        cout << "ADDRESS\t| KEY       | Brand\t| Owner Info" << endl;
        cout << address << "\t| " << record.key << " | " << record.brand << "\t| " << record.owner << endl;

        file.close();
    }

    void printRecords(const string& binaryFileName){
        file.open(binaryFileName, ios::in | ios::binary);
        CarRecord record;
        cout << "KEY       | Brand\t| Owner Info" << endl;
        while (file.read(reinterpret_cast<char*>(&record), sizeof(CarRecord))) {
            cout << record.key << " | " << record.brand << "\t| " << record.owner << endl;
        }
        file.close();
    }

    void addRecord(const string& binaryFileName, const CarRecord& newRecord) {
        file.open(binaryFileName, ios::out | ios::app | ios::binary);

        if (!file) {
            cout << "Failed to open file." << endl;
            return;
        }

        file.write(reinterpret_cast<const char*>(&newRecord), sizeof(CarRecord));

        file.close();
    }
};


#endif //PRACTICE__5_FILEMANAGER_H
