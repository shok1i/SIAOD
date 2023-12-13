#ifndef ABOBA_HASH_H
#define ABOBA_HASH_H

#include <iostream>
#include <vector>

#include "Bin.h"

class HashTable {
private:
    static const int BASE_TABLE = 4;
    std::vector<int> table;
    int size = 0;

    int hash1(int accountNumber) { return accountNumber % table.size(); }

    int hash2(int accountNumber) { return (accountNumber % (table.size() - 1)) + 1; }

    void resizeAndRehash() {
        int newTableSize = table.size() * 2;
        std::vector<int> newTable(newTableSize);

        for (const int account : table) {
            if (account != 0) {
                int index = hash1(account);
                int step = hash2(account);

                while (newTable[index] != 0) {
                    index = (index + step) % newTableSize;
                }

                newTable[index] = account;
            }
        }

        table = newTable;
    }

public:
// Done
    HashTable(){
        table = std::vector<int>(BASE_TABLE);
    }
// Done
    void Insert(int pos) {
        if(size == table.size()-1){
            resizeAndRehash();
        }

        int index = hash1(pos);
        int step = hash2(pos);

        while (table[index] != 0) {
            if (table[index] == pos) {
                std::cout << "An account with this number already exists. Data update." << std::endl;
                table[index] = pos;
                return;
            }
            index = (index + step) % table.size();
        }

        table[index] = pos;
        size++;
    }
// Done
    int Search(int accountNumber) {
        int index = hash1(accountNumber);
        int step = hash2(accountNumber);

        while (table[index] != 0) {
            if (table[index] == accountNumber) {
                return table[index];
            }
            index = (index + step) % table.size();
        }

        return 0; // Счет не найден
    }
// Done
    void Remove(int accountNumber) {
        int index = hash1(accountNumber);
        int step = hash2(accountNumber);

        while (table[index] != 0) {
            if (table[index] == accountNumber) {
                table[index] = 0; // Очищаем ячейку
                return;
            }
            index = (index + step) % table.size();
        }
        size--;
    }
// Done
    void PrintHash() {
        cout << "========================[ Print hash ]========================" << endl;
        for (int i = 0; i < table.size(); ++i) {
            if (table[i] != 0) {
                std::cout << "Hash " << i << ": (" << table[i] << ")" << std::endl;
            }
        }
    }

// Сделать HashTest
    void testHeshT() {
        HashTable table;
        int bankAccount;
        table.Insert(1);
        table.Insert(2);
        table.Insert(3);
        table.Insert(4);
        table.PrintHash();
        cout << "Add elem" << endl;
        table.Insert(5);
        table.PrintHash();
        cout << "delete elem with key 4" << endl;
        table.Remove(4);
        table.PrintHash();
        bankAccount = table.Search(3);
        std::cout << "Hash " << 3 << " was found on pos: (" << bankAccount - 1<< ")" << std::endl;
    }

};

#endif //ABOBA_HASH_H