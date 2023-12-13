#ifndef ABOBA_BINHASH_H
#define ABOBA_BINHASH_H

#include "Bin.h"
#include "Hash.h"

class HashBin{
    Bin bin;
    HashTable hashTable;
public:
    void Linking(string BinaryFilename) {
        ifstream InputFile(BinaryFilename, ios::binary);

        if (!InputFile) { cout << "Failed to open files\n"; return; }

        BankAccount bank;
        int i = 0;
        while (InputFile.read(reinterpret_cast<char*> (&bank), sizeof(BankAccount))){
            i++;
            hashTable.Insert(i);
        }

        cout << "The bonding was successful!" << endl;
        InputFile.close();
    }

    void Deleting(string BinaryFilename, int key){
        bin.Remove(BinaryFilename, key);
        hashTable.Remove(key);
    }

    int Search(int key){
        return hashTable.Search(key);
    }

    void TimeS(int code){
        hashTable.TimeS(code);
    }

    void Display(string BinaryFilename){
        // bin.PrintBinary(BinaryFilename);
        hashTable.PrintHash();
    }
};

#endif //ABOBA_BINHASH_H
