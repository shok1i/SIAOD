
#include "iostream"
#include "fstream"
#include "random"

using namespace std;

int Random_Func(int min, int max){
    random_device rd; // obtain a random number from hardware
    mt19937 gen(rd()); // seed the generator
    uniform_int_distribution<> RANDOM(min, max); // define the range
    return RANDOM(gen);
}
void createText(const string& textFileName, int size){
    ofstream out;
    out.open(textFileName);
    for (int i = 0; i < size; i++) {
        out << Random_Func(100000000, 1000000000) << " BRAND-" << i << " OWNER-" << i << endl;
    }
    out.close();
}

// 97 lines
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

// 127 lines
struct NodeBin {
    int key;
    CarRecord ptr;

    NodeBin* left;
    NodeBin* right;

    NodeBin(int key, CarRecord ptr) {
        this->key = key;
        this->ptr = ptr;
        left = nullptr;
        right = nullptr;
    }
};
class BinarySearchTree {
private:
    NodeBin* root;

    NodeBin* insertRecursive(NodeBin* node, int key, CarRecord ptr) {
        if (node == nullptr) {
            return new NodeBin(key, ptr);
        }

        if (key < node->key) {
            node->left = insertRecursive(node->left, key, ptr);
        } else if (key > node->key) {
            node->right = insertRecursive(node->right, key, ptr);
        }

        return node;
    }

    NodeBin* searchRecursive(NodeBin* node, int key) {
        if (node == nullptr || node->key == key) {
            return node;
        }

        if (key < node->key) {
            return searchRecursive(node->left, key);
        }

        return searchRecursive(node->right, key);
    }

    NodeBin* deleteRecursive(NodeBin* node, int key) {
        if (node == nullptr) {
            return node;
        }

        if (key < node->key) {
            node->left = deleteRecursive(node->left, key);
        } else if (key > node->key) {
            node->right = deleteRecursive(node->right, key);
        } else {
            if (node->left == nullptr) {
                NodeBin* temp = node->right;
                delete node;
                return temp;
            } else if (node->right == nullptr) {
                NodeBin* temp = node->left;
                delete node;
                return temp;
            }

            NodeBin* minValueNode = getMinValueNode(node->right);
            node->key = minValueNode->key;
            node->ptr = minValueNode->ptr;
            node->right = deleteRecursive(node->right, minValueNode->key);
        }

        return node;
    }

    NodeBin* getMinValueNode(NodeBin* node) {
        NodeBin* current = node;
        while (current && current->left != nullptr) {
            current = current->left;
        }
        return current;
    }

    void printTreeRecursive(NodeBin* node, int level) {
        if (node != nullptr) {
            printTreeRecursive(node->right, level + 1);
            for (int i = 0; i < level; i++) {
                std::cout << "   ";
            }
            cout << level;
            std::cout << "-> " << node->key << "\\" << node->ptr.brand << std::endl;
            printTreeRecursive(node->left, level + 1);
        }
    }

public:
    BinarySearchTree() {
        root = nullptr;
    }

    void insert(int key, CarRecord ptr) {
        root = insertRecursive(root, key, ptr);
    }

    void search(int key) {
        NodeBin* FoundBin = searchRecursive(root, key);
        cout << FoundBin->ptr.key << " | " << FoundBin->ptr.brand << "\t| " << FoundBin->ptr.owner << endl;
    }

    void remove(int key) {
        root = deleteRecursive(root, key);
    }

    void printTree() {
        printTreeRecursive(root, 0);
    }

    void Load(const string& binaryFileName){
        fstream file;
        file.open(binaryFileName, ios::in | ios::binary);

        int line = 0;
        CarRecord record;
        while (file.read(reinterpret_cast<char*>(&record), sizeof(CarRecord))) {
            insert(record.key, record);
            line++;
        }
    }
};

// 125 lines
struct Node {
    int key;
    CarRecord ptr;

    int priority;
    Node* left;
    Node* right;

    Node(int key, CarRecord ptr) {
        this->key = key;
        this->ptr = ptr;

        priority = Random_Func(0, 1000);
        left = nullptr;
        right = nullptr;
    }
};
class RandomizedBST {
private:
    Node* root;

    Node* rotateRight(Node* node) {
        Node* newRoot = node->left;
        node->left = newRoot->right;
        newRoot->right = node;
        return newRoot;
    }

    Node* rotateLeft(Node* node) {
        Node* newRoot = node->right;
        node->right = newRoot->left;
        newRoot->left = node;
        return newRoot;
    }

    Node* insertNode(Node* node, int key, CarRecord ptr) {
        if (node == nullptr)
            return new Node(key, ptr);

        if (key < node->key) {
            node->left = insertNode(node->left, key, ptr);
            if (node->left->priority > node->priority)
                node = rotateRight(node);
        } else {
            node->right = insertNode(node->right, key, ptr);
            if (node->right->priority > node->priority)
                node = rotateLeft(node);
        }

        return node;
    }

    Node* deleteNode(Node* node, int key) {
        if (node == nullptr)
            return nullptr;

        if (key < node->key)
            node->left = deleteNode(node->left, key);
        else if (key > node->key)
            node->right = deleteNode(node->right, key);
        else {
            if (node->left == nullptr) {
                Node* temp = node->right;
                delete node;
                node = temp;
            } else if (node->right == nullptr) {
                Node* temp = node->left;
                delete node;
                node = temp;
            } else {
                if (node->left->priority > node->right->priority) {
                    node = rotateRight(node);
                    node->right = deleteNode(node->right, key);
                } else {
                    node = rotateLeft(node);
                    node->left = deleteNode(node->left, key);
                }
            }
        }

        return node;
    }

    Node* searchRecursive(Node* node, int key) {
        if (node == nullptr || node->key == key) {
            return node;
        }

        if (key < node->key) {
            return searchRecursive(node->left, key);
        }

        return searchRecursive(node->right, key);
    }

    void printTreeRecursive(Node* node, int level) {
        if (node != nullptr) {
            printTreeRecursive(node->right, level + 1);
            for (int i = 0; i < level; i++) {
                std::cout << "   ";
            }
            cout << level;
            std::cout << "-> " << node->key << "\\" << node->ptr.brand << std::endl;
            printTreeRecursive(node->left, level + 1);
        }
    }

public:
    void insert(int key, CarRecord ptr) {
        root = insertNode(root, key, ptr);
    }

    void remove(int key) {
        root = deleteNode(root, key);
    }

    void printTree() {
        printTreeRecursive(root, 0);
    }

    void search(int key) {
        Node* Found = searchRecursive(root, key);
        cout << Found->ptr.key << " | " << Found->ptr.brand << "\t| " << Found->ptr.owner << endl;
    }

    void Load(const string& binaryFileName){
        fstream file;
        file.open(binaryFileName, ios::in | ios::binary);

        int line = 0;
        CarRecord record;
        while (file.read(reinterpret_cast<char*>(&record), sizeof(CarRecord))) {
            insert(record.key, record);
            line++;
        }
    }
};

int main(){
    string  textFileName = "text.txt", binaryFileName = "binary.txt";
    int size = 10;

    // createText(textFileName, size);

    FileManager fileManager;
    fileManager.createFile(textFileName, binaryFileName);

    BinarySearchTree bst;
    bst.Load(binaryFileName);

    cout << "===[ BinarySearchTree ]===" << endl;
    bst.printTree();
    cout << endl;

    cout << "Delete elem with key 327010303" << endl;
    bst.remove(327010303);

    cout << "===[ BinarySearchTree ]===" << endl;
    bst.printTree();
    cout << endl;

    cout << "Add elem with key 100100376" << endl;
    bst.insert(100100376, CarRecord(100100376, "BRAND-ADDED", "OWNER-ADDED"));
    cout << "===[ BinarySearchTree ]===" << endl;
    bst.printTree();
    cout << endl;

    cout << "Search elem with key 962142361" << endl;
    bst.search(962142361);

    cout << " \n=============================================\n";
    RandomizedBST rbst;
    rbst.Load(binaryFileName);

    cout << "===[  RandomizedBST  ]===" << endl;
    rbst.printTree();
    cout << endl;

    cout << "Delete elem with key 327010303" << endl;
    rbst.remove(327010303);

    cout << "===[  RandomizedBST  ]===" << endl;
    rbst.printTree();
    cout << endl;

    cout << "Add elem with key 100100376" << endl;
    rbst.insert(100100376, CarRecord(100100376, "BRAND-ADDED", "OWNER-ADDED"));
    cout << "===[  RandomizedBST  ]===" << endl;
    rbst.printTree();
    cout << endl;

    cout << "Search elem with key 962142361" << endl;
    rbst.search(962142361);

    return 0;
}