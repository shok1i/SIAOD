#ifndef ABOBA_BIN_H
#define ABOBA_BIN_H

#include <iostream>
#include <string>
#include <fstream>

#include <chrono>

using namespace std;

struct BankAccount {
    int accountNumber;
    char fullName[256] = {'n', 'a', 'm', 'e'};
    char address[256]  = {'a', 'd', 'd', 'r', 'e', 's', 's'};
};

class Bin {
public:
// Done
    void TextToBinary(string TextFilename, string BinaryFilename) {
        ifstream InputFile(TextFilename);
        ofstream OutFile(BinaryFilename, ios::binary);

        if (!InputFile || !OutFile) { cout << "Failed to open files\n"; return; }

        BankAccount bank;
        while (InputFile >> bank.accountNumber >> bank.fullName >> bank.address)
            OutFile.write(reinterpret_cast<const char *>(&bank), sizeof(BankAccount));

        cout << "Text data converted to binary successfully!" << endl;
        InputFile.close();
        OutFile.close();
    }
// Done
    void PrintBinary(string BinaryFilename) {
        ifstream InputFile(BinaryFilename, ios::binary);

        if (!InputFile) { cout << "Failed to open files\n"; return; }

        BankAccount bank;

        cout << "========================[ Print binary ]========================" << endl;
        while (InputFile.read(reinterpret_cast<char*> (&bank), sizeof(BankAccount)))
            cout << " Code:: " << bank.accountNumber << " Name:: " << bank.fullName << " Address:: " << bank.address << endl;

        InputFile.close();
    }
// Done
    void Remove (string BinaryFilename, int Code){
        fstream BinaryFile(BinaryFilename, ios::in | ios::binary);
        ofstream temp("temp.txt", ios::out | ios::binary);
        BankAccount bank;

        while (BinaryFile.read(reinterpret_cast<char*>(&bank), sizeof(bank)))
            if (bank.accountNumber != Code)
                temp.write(reinterpret_cast<char*>(&bank), sizeof(bank));

        BinaryFile.close();
        remove(BinaryFilename.c_str());
        temp.close();
        rename("temp.txt", BinaryFilename.c_str());
    }
    void Search (int Code){
        fstream BinaryFile("text.txt", ios::binary);
        BankAccount bank;

        auto begin = std::chrono::steady_clock::now();

        cout << Code << "\t| ";
        while (BinaryFile.read(reinterpret_cast<char*> (&bank), sizeof(BankAccount)))
            if (bank.accountNumber == Code) {
                cout << " Code:: " << bank.accountNumber << " Name:: " << bank.fullName << " Address:: " << bank.address << endl;
                break;
            }

        auto end = std::chrono::steady_clock::now();
        auto elapsed_ms = std::chrono::duration_cast<std::chrono::nanoseconds>(end - begin);

        std::cout << "The time: " << elapsed_ms.count() << " ns\n";
        BinaryFile.close();
    }

// Сделать BinTest
    void testBinT() {
        Bin bin;
        bin.TextToBinary("text-test.txt", "bin-test.txt");
        bin.PrintBinary("bin=test.txt");
        bin.Remove("bin-test.txt", 5);
        bin.PrintBinary("bin-test.txt");
    }

};
#endif //ABOBA_BIN_H
