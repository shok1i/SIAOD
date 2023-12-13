#include "FileManager.h"
#include "BinSearchTree.h"
#include "RandomizedSearchTree.h"

using namespace std;

void testFM(){
    string  binaryFileName = "binary-test.txt", textFileName = "text-test.txt";

    FileManager fileManager;

    fileManager.createFile(textFileName, binaryFileName);

    cout << "===[  File Manager  ]===" << endl;
    fileManager.printRecords(binaryFileName);
    cout << endl;

    cout << "Add elem with key 919999" << endl;
    CarRecord temp = CarRecord (919999, "BRAND-ADDED", "OWNER-ADDED");
    fileManager.addRecord(binaryFileName, temp);

    cout << "===[  RandomizedBST  ]===" << endl;
    fileManager.printRecords(binaryFileName);
    cout << endl;

    cout << "Search elem with key 910542" << endl;
    fileManager.linearSearch(binaryFileName, 910542);
}

void testBST(){
    string  binaryFileName = "binary-test.txt";

    BinarySearchTree bst;
    bst.Load(binaryFileName);

    cout << "===[ BinarySearchTree ]===" << endl;
    bst.printTree();
    cout << endl;

    cout << "Delete elem with key 538398" << endl;
    bst.remove(538398);

    cout << "===[ BinarySearchTree ]===" << endl;
    bst.printTree();
    cout << endl;

    cout << "Add elem with key 400000" << endl;
    CarRecord* temp = new CarRecord (400000, "BRAND-ADDED", "OWNER-ADDED");
    bst.insert_file(400000, temp, binaryFileName);

    cout << "===[ BinarySearchTree ]===" << endl;
    bst.printTree();
    cout << endl;

    cout << "Search elem with key 910542" << endl;
    bst.search(910542);
}

void testRBST(){
    string  binaryFileName = "binary-test.txt";

    RandomizedBST rbst;
    rbst.Load(binaryFileName);

    cout << "===[  RandomizedBST  ]===" << endl;
    rbst.printTree();
    cout << endl;

    cout << "Delete elem with key 538398" << endl;
    rbst.remove(538398);

    cout << "===[  RandomizedBST  ]===" << endl;
    rbst.printTree();
    cout << endl;

    cout << "Add elem with key 910000" << endl;
    CarRecord* temp = new CarRecord (910000, "BRAND-ADDED", "OWNER-ADDED");
    rbst.insert(910000, temp);

    cout << "===[  RandomizedBST  ]===" << endl;
    rbst.printTree();
    cout << endl;

    cout << "Search elem with key 910542" << endl;
    rbst.search(910542);
}

int main(){

    testFM();
    cout << "\n\n\n";

    testBST();

    cout << "\n\n\n";

    testRBST();

    return 0;
}