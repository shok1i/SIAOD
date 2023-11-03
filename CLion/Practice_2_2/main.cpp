#include <iostream>
#include <string>
#include <fstream>

using namespace std;

struct Bank{
    char Name[256];
    int Code;
    char Address[256];
    char Ownership[8];
};

// Done
void TextToBinary (string TextFilename, string BinaryFilename){
    ifstream InputFile (TextFilename);
    ofstream OutFile   (BinaryFilename, ios::binary);

    if (!InputFile || !OutFile) {
        cout << "Failed to open files\n";
        return;
    }

    Bank bank;
    while (InputFile >> bank.Name >> bank.Code >> bank.Address >> bank.Ownership)
        OutFile.write(reinterpret_cast<const char*>(&bank), sizeof(Bank));

    cout << "Text data converted to binary successfully!" << endl;
    InputFile.close();
    OutFile.close();
}
// Done
void BinaryToText (string TextFilename, string BinaryFilename){
    ifstream InputFile(BinaryFilename, ios::binary);
    ofstream OutFile  (TextFilename);

    if (!InputFile || !OutFile) {
        cout << "Failed to open files\n";
        return;
    }

    Bank bank;
    while (InputFile.read(reinterpret_cast<char*>(&bank), sizeof(Bank)))
        OutFile << bank.Name << " \\ " << bank.Code << " \\ " << bank.Address << " \\ " << bank.Ownership << endl;

    cout << "Binary data converted to text successfully!" << endl;
    InputFile.close();
    OutFile.close();
}
// Done
void PrintBinary  (string BinaryFilename){
    ifstream InputFile(BinaryFilename, ios::binary);

    if (!InputFile) {
        cout << "Failed to open files\n";
        return;
    }

    Bank bank;

    cout << "========================[ Print binary ]========================" << endl;
    while (InputFile.read(reinterpret_cast<char*>(&bank), sizeof(Bank)))
        cout << "Name:: " << bank.Name << " Code:: " << bank.Code << " Address:: " << bank.Address << " Ownership:: " << bank.Ownership << endl;
    cout << "================================================================" << endl;

    InputFile.close();
}
// Done
void BankAtIndex  (string BinaryFilename, int Index){
    ifstream InputFile(BinaryFilename, ios::binary);

    if (!InputFile) {
        cout << "Failed to open files\n";
        return;
    }

    Bank bank;
    InputFile.seekg(Index * sizeof(Bank));

    cout << "=======================[ Bank at index ]=======================" << endl;
    if (InputFile.read(reinterpret_cast<char*>(&bank), sizeof(Bank)))
        cout << "Name:: " << bank.Name << " ||Code:: " << bank.Code << " ||Address:: " << bank.Address << " ||Ownership:: " << bank.Ownership << endl;
    else
        cout << "The bank with the" << Index << "does not exist" << endl;
    cout << "===============================================================" << endl;

    InputFile.close();
}
// Done
void OverwritingBank(string BinaryFilename, int Code){
    Bank bank, last;

    fstream BinaryFile(BinaryFilename, ios::in | ios::binary);

    while (BinaryFile.read(reinterpret_cast<char*>(&last), sizeof(last)));
    BinaryFile.close();

    BinaryFile.open(BinaryFilename, ios::in | ios::binary);
    ofstream temp("temp.txt", ios::out | ios::binary);

    while (BinaryFile.read(reinterpret_cast<char*>(&bank), sizeof(bank))) {
        if (bank.Code == Code)
            temp.write(reinterpret_cast<char*>(&last), sizeof(last));
        else if (last.Code != bank.Code)
            temp.write(reinterpret_cast<char*>(&bank), sizeof(bank));
    }

    BinaryFile.close();
    remove(BinaryFilename.c_str());
    temp.close();
    rename("temp.txt", BinaryFilename.c_str());
}
// Done
void AllCommercial(string BinaryFilename){
    ifstream InputFile(BinaryFilename, ios::binary);
    Bank bank;

    if (!InputFile) {
        cout << "Failed to open files\n";
        return;
    }


    cout << "======================[ Commercial banks ]======================" << endl;
    while (InputFile.read(reinterpret_cast<char*>(&bank), sizeof(Bank)))
        if (bank.Ownership[0] == 'c' && bank.Ownership[1] == 'o' && bank.Ownership[2] ==  'm')
            cout << "Name:: " << bank.Name << " ||Code:: " << bank.Code << " ||Address:: " << bank.Address << " ||Ownership:: " << bank.Ownership << endl;
    cout << "================================================================" << endl;

    InputFile.close();
}
// Done
void ChangeOwnership(string BinaryFilename, int index){
    fstream InputFile(BinaryFilename, ios::binary | ios::in | ios::out);
    Bank bank;

    if (!InputFile) {
        cout << "Failed to open files\n";
        return;
    }

    while (InputFile.read(reinterpret_cast<char*>(&bank), sizeof(Bank)))
        if (bank.Code == index){
            cout << "Name:: " << bank.Name << " ||Code:: " << bank.Code << " ||Address:: " << bank.Address << " ||Ownership:: " << bank.Ownership << endl;
            if (bank.Ownership[0] == 'g')
            { bank.Ownership[0] = 'c'; bank.Ownership[1] = 'o'; bank.Ownership[2] =  'm'; }
            else
            { bank.Ownership[0] = 'g'; bank.Ownership[1] = 'o'; bank.Ownership[2] =  'v'; }
            InputFile.write(reinterpret_cast<char*>(&bank), sizeof(Bank));
            break;
        }

    InputFile.close();
}

int main() {
    string TextFilename, BinaryFilename;

    cout << "Enter the name of file:\n";
    cin  >> TextFilename;
    cout << "Enter the file name for the binary file:\n";
    cin  >> BinaryFilename;

    ofstream TextFile   (TextFilename);
    TextFile << "Name--1 0 Address--0 com" << endl
             << "Name--2 1 Address--1 gov" << endl
             << "Name--3 2 Address--2 gov" << endl
             << "Name--4 3 Address--3 gov" << endl
             << "Name--5 4 Address--4 com" << endl
             << "Name--6 5 Address--5 gov" << endl
             << "Name--7 6 Address--6 com" << endl
             << "Name--8 7 Address--7 gov" << endl
             << "Name--9 8 Address--8 com" << endl;
    TextFile.close();
    ifstream BinaryFile (BinaryFilename);
    BinaryFile.close();

    int choice = -1, index;
    cout << "=======================================[ SELECTIONS ]=======================================\n"
         << "1. Converting test data from a text file to a binary file;\n"
         << "2. Converting data from a binary file to a text file;\n"
         << "3. Output all records of the binary file;\n"
         << "4. Access to a record by its sequence number in the file;\n"
         << "5. Deleting a record with a specified key value;\n"
         << "6. Generate information on the banks of the city, with commercial form of ownership;\n"
         << "7. Replace the ownership form of the bank with the given code with the opposite one;\n"
         << "0. Exiting the programme;\n"
         << "=============================================================================================\n";
    while (choice != 0){
        cout << "Your choice:\n";
        cin  >> choice;
        switch (choice) {
            case 0:
                return 0;
            case 1:
                TextToBinary(TextFilename, BinaryFilename);
                break;
            case 2:
                BinaryToText(TextFilename, BinaryFilename);
                break;
            case 3:
                PrintBinary(BinaryFilename);
                break;
            case 4:
                cout << "Enter the index:\n";
                cin >> index;
                BankAtIndex(BinaryFilename, index);
                break;
            case 5:
                cout << "Enter the index:\n";
                cin >> index;
                OverwritingBank(BinaryFilename, index - 1);
                break;
            case 6:
                AllCommercial(BinaryFilename);
                break;
            case 7:
                cout << "Enter the index:\n";
                cin >> index;
                ChangeOwnership(BinaryFilename, index);
                break;
            default:
                cout << "Incorrect value\n";
                break;
        }
    }
}
