#ifndef PRACTICE_5__RANDOMIZEDSEARCHTREE_H
#define PRACTICE_5__RANDOMIZEDSEARCHTREE_H

#include "FileManager.h"

struct Node {
    int key;
    CarRecord* ptr;

    int priority;
    Node* left;
    Node* right;

    Node(int key, CarRecord* ptr) {
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

    Node* insertNode(Node* node, int key, CarRecord* ptr) {
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

    void printTreeRecursive(Node* node, int level) {
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
    void insert(int key, CarRecord* ptr) {
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
        if (Found != nullptr)
            cout << Found->ptr->key << " | " << Found->ptr->brand << "\t| " << Found->ptr->owner << endl;
        else {
            cout << "The element with this key does not exist." << endl;
        }
    }

    void Load(const string& binaryFileName){
        fstream file;
        file.open(binaryFileName, ios::in | ios::binary);

        CarRecord record;
        while (file.read(reinterpret_cast<char*>(&record), sizeof(CarRecord))) {
            CarRecord* temp = new CarRecord(record);
            insert(record.key, temp);
        }

        file.close();
    }

};

#endif