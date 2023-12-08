// Вариант №9
// 1) Проверить, является ли дерево деревом выражений.
// 2) Вывести дерево, отобразить его формулу.
// 3) Определить, содержит ли дерево операцию *.
//
//      Создать дерево выражений в соответствии с вводимым выражением. Структура узла дерева включает:
//      информационная часть узла – символьного типа: знак операции +, -, * или цифра; указатель на левое
//      и указатель на правое поддерево. В дереве выражения операнды выражений находятся в листьях дерева.
//
//      Исходное выражение имеет формат: <формула>::=цифра|<формула><знак операции><формула>
//          Примеры: 5; 1+2; 1+2+3*4-5/6.
//      Отобразить дерево на экране, повернув его на экране против часовой стрелки.

#include <iostream>
#include <string>
#include <stack>

using namespace std;

int getPrecedence(char digit){
    if (digit == '+' || digit == '-') return 1;
    else return 2;
}

string convertInfixToPostfix(string infix){
    stack<char> temp;
    string res;

    for (char elem : infix){
        if (isdigit(elem)) res += elem;
        else {
            while (!temp.empty() && getPrecedence(elem) <= getPrecedence(temp.top())){
                res += temp.top();
                temp.pop();
            }
            temp.push(elem);
        }
    }

    while (!temp.empty()){
        res+=temp.top();
        temp.pop();
    }

    return res;
}

struct Node {
    char data;
    Node* left;
    Node* right;

    Node(char data) {
        this->data = data;
        this->left = nullptr;
        this->right = nullptr;
    }
};

//// ================================================================================================================== ////
Node* buildExpressionTree(string postfix) {
        stack<Node*> s;

        for (char elem : postfix) {

            if (isdigit(elem)) {
                Node* newNode = new Node(elem);
                s.push(newNode);
            }
            else if (!isdigit(elem)) {
                Node* newNode = new Node(elem);
                newNode->right = s.top();
                s.pop();
                newNode->left = s.top();
                s.pop();
                s.push(newNode);
            }
        }

        return s.top();
}

// Является ли дерево деревом выражений.
bool isExpressionTree(Node* root) {
    if (root == nullptr) return false;
    // Если текущий узел цифра то левая и правая ветка должны быть nullptr || Если текущий узел операция то его левая и правая ветка должны быть деревьями выражений
    if (isdigit(root->data))
        return root->left == nullptr && root->right == nullptr;
    else
        return root->left != nullptr && root->right != nullptr && isExpressionTree(root->left) &&
               isExpressionTree(root->right);
}

// Вывод дерева, повернутого на экране против часовой стрелки.
void printExpressionTree(Node* root, int level = 0){
    if (root == nullptr) return;

    printExpressionTree(root->right, level + 1);

    for (int i = 0; i < level; i++) std::cout << "   ";

    std::cout << root->data << std::endl;

    printExpressionTree(root->left, level + 1);
}

bool containsMultiplication(Node* root) {
    if (root == nullptr) {
        return false;
    }

    if (root->data == '*') {
        return true;
    }

    return containsMultiplication(root->left) || containsMultiplication(root->right);
}

std::string getExpressionFromTree(Node* root) {
    if (root == nullptr) {
        return "";
    }

    if (isdigit(root->data)) {
        string temp = " ";
        temp[0] = root -> data;
        return temp;
    }

    std::string leftExpression = getExpressionFromTree(root->left);
    std::string rightExpression = getExpressionFromTree(root->right);

    return "(" + leftExpression + root->data + rightExpression + ")";
}

int main() {
    string infixExpression;

    cout << "Enter the expression" << std::endl;
    getline(cin, infixExpression);

    string postfixExpression = convertInfixToPostfix(infixExpression);
    Node* root = buildExpressionTree(postfixExpression);

    cout << "Infix                    ->  " << infixExpression << endl
         << "Postfix                  ->  " << postfixExpression << endl
         << "ExpressionTree           ->  " << endl;
         printExpressionTree(root);

    cout << "Get expression from tree ->  " << getExpressionFromTree(root) << endl
         << "Is Expression tree       ->  " << (isExpressionTree(root) ? "Yes" : "No") << endl
         << "Contains multiplication  ->  " << (containsMultiplication(root) ? "Yes" : "No") << endl;

    return 0;
}