#include "Bin.h"
#include "Hash.h"
#include "BinHash.h"

int main() {
    Bin bin;
    HashBin hashBin;
    HashTable hashTable;

    int i = 0;
    int key = 0;

    while (1){
        cout << "Enter the number of the operation" << endl
             << "1 -> testBinT    ||  2 -> testHashT" << endl
             << "3 -> CreateBin   ||  4 -> PrintBin"  << endl
             << "5 -> LinkingHash ||  6 -> Deleting"  << endl
             << "7 -> Search      ||  8 -> DisplayAll"   << endl
             << "-1 -> Exit" << endl;
        cin  >> i;

        cout << "\n\n";
        if (i == -1) return 0;
        else if (i == 1) bin.testBinT();
        else if (i == 2) hashTable.testHeshT();
        else if (i == 3) bin.TextToBinary("text.txt", "bin.txt");
        else if (i == 4) bin.PrintBinary("bin.txt");
        else if (i == 5) hashBin.Linking("bin.txt");
        else if (i == 6){
            cout << "Enter the number of the key to be deleted" << endl;
            cin  >> key;
            hashBin.Deleting("bin.txt", key);
        }
        else if (i == 7){
            cout << "Enter the key number to search for" << endl;
            cin  >> key;
            BankAccount temp = hashBin.Search(key);
            cout << "Your key is " << key << endl
                    << " || AccountNumber || " << temp.accountNumber
                    << " || Name || " << temp.fullName
                    << " || Address || " << temp.address << endl;
        }
        else if (i == 8) hashBin.Display("bin.txt");
        else cout << "Wrong number" << endl;

        cout << "\n\n";
    }

}