#ifndef PRACTICE_5__BINSEARCHTREE_H
#define PRACTICE_5__BINSEARCHTREE_H

#include "FileManager.h"

struct NodeBin {
    int key;
    CarRecord* ptr;

    NodeBin* left;
    NodeBin* right;

    NodeBin(int key, CarRecord* ptr) {
        this->key = key;
        this->ptr = ptr;
        left = nullptr;
        right = nullptr;
    }
};
class BinarySearchTree {
private:
    NodeBin* root;

    NodeBin* insertRecursive(NodeBin* node, int key, CarRecord* ptr) {
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
        if (node == nullptr || node->key == key){
            return node;
        }

        if (key < node->key) {
            return searchRecursive(node->left, key);
        }
        else {
            return searchRecursive(node->right, key);
        }
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
            std::cout << "-> " << node->key << std::endl;
            printTreeRecursive(node->left, level + 1);
        }
    }

public:
    BinarySearchTree() {
        root = nullptr;
    }

    void insert(int key, CarRecord* ptr) {
        root = insertRecursive(root, key, ptr);
    }

    void insert_file(int key, CarRecord* ptr, string binFileName){
        FileManager fileManager;
        fileManager.addRecord(binFileName, *ptr);

        root = insertRecursive(root, key, ptr);
    }

    void search(int key) {
        NodeBin* Found = searchRecursive(root, key);
        if (Found != nullptr)
            cout << Found->ptr->key << " | " << Found->ptr->brand << "\t| " << Found->ptr->owner << endl;
        else {
            cout << "The element with this key does not exist." << endl;
        }
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

        CarRecord record;
        while (file.read(reinterpret_cast<char*>(&record), sizeof(CarRecord))) {
            CarRecord *temp = new CarRecord(record);
            insert(record.key, temp);
        }

        file.close();
    }

};

#endif