#ifndef ABOBA_HASH_H
#define ABOBA_HASH_H

#include <iostream>
#include <vector>

#include "Bin.h"

class HashTable {
private:
    static const int BASE_TABLE = 4;
    std::vector<BankAccount> table;
    int size = 0;

    int hash1(int accountNumber) { return accountNumber % table.size(); }

    int hash2(int accountNumber) { return (accountNumber % (table.size() - 1)) + 1; }

    void resizeAndRehash() {
        int newTableSize = table.size() * 2;
        std::vector<BankAccount> newTable(newTableSize);

        for (const BankAccount& account : table) {
            if (account.accountNumber != 0) {
                int index = hash1(account.accountNumber);
                int step = hash2(account.accountNumber);

                while (newTable[index].accountNumber != 0) {
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
        table = std::vector<BankAccount>(BASE_TABLE);
    }
// Done
    void Insert(BankAccount account) {
        if(size == table.size()-1){
            resizeAndRehash();
        }

        int index = hash1(account.accountNumber);
        int step = hash2(account.accountNumber);

        while (table[index].accountNumber != 0) {
            if (table[index].accountNumber == account.accountNumber) {

                std::cout << "An account with this number already exists. Data update." << std::endl;
                table[index] = account;
                return;
            }
            index = (index + step) % table.size();
        }

        table[index] = account;
        size++;
    }
// Done
    BankAccount Search(int accountNumber) {
        int index = hash1(accountNumber);
        int step = hash2(accountNumber);

        while (table[index].accountNumber != 0) {
            if (table[index].accountNumber == accountNumber) {
                return table[index];
            }
            index = (index + step) % table.size();
        }

        return BankAccount(0, "", ""); // Счет не найден
    }

    void TimeS(int accountNumber){
        int index = hash1(accountNumber);
        int step = hash2(accountNumber);

        auto begin = std::chrono::steady_clock::now();

        while (table[index].accountNumber != 0) {
            if (table[index].accountNumber == accountNumber) {
                auto end = std::chrono::steady_clock::now();
                auto elapsed_ms = std::chrono::duration_cast<std::chrono::nanoseconds>(end - begin);

                std::cout << "The time: " << elapsed_ms.count() << " ns\n";
            }
            index = (index + step) % table.size();
        }
    }
// Done
    void Remove(int accountNumber) {
        int index = hash1(accountNumber);
        int step = hash2(accountNumber);

        while (table[index].accountNumber != 0) {
            if (table[index].accountNumber == accountNumber) {
                table[index] = BankAccount(0, "", ""); // Очищаем ячейку
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
            if (table[i].accountNumber != 0) {
                std::cout << "Hash " << i << ": (" << table[i].accountNumber << ", " << table[i].fullName << ", " << table[i].address << ")" << std::endl;
            }
        }
    }

// Сделать HashTest
    void testHeshT() {
        HashTable table;
        BankAccount bankAccount;
        bankAccount.accountNumber = 1;
        table.Insert(bankAccount);
        bankAccount.accountNumber += 1;
        table.Insert(bankAccount);
        bankAccount.accountNumber += 1;
        table.Insert(bankAccount);
        bankAccount.accountNumber += 1;
        table.Insert(bankAccount);
        table.PrintHash();
        cout << "Add elem" << endl;
        bankAccount.accountNumber += 1;
        table.Insert(bankAccount);
        table.PrintHash();
        cout << "delete elem with key 4" << endl;
        table.Remove(4);
        table.PrintHash();
        bankAccount = table.Search(3);
        std::cout << "Hash " << 4 << ": (" << bankAccount.accountNumber << ", " << bankAccount.fullName << ", " << bankAccount.address << ")" << std::endl;
    }

};

#endif //ABOBA_HASH_H