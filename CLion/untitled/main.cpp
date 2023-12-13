#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <map>
#include <queue>
#include <algorithm>

using namespace std;

/*=============================================[ RLE ]=============================================*/
void RLE(const string& Input) {
    string temp = Input, out;
    char elem = Input[0];
    temp += "$";
    int count = -1;
    for (char i : temp)
        if (elem == i) count++;
        else {
            count++;
            out += to_string(count);
            out += elem;
            elem  = i;
            count = 0;
        }

    double Compression = (double)Input.length() / (double)out.length();
    cout << "==[ RLE ]==" << endl
         << "Input:  " << Input << endl
         << "Output: " << out << endl
         << "==> Compression ratio: " << Input.length() << " / " <<  out.length() << " = " << Compression << endl;
}
/*=============================================[ LZ77 ]=============================================*/
struct LZ77Token {
    int offset, length;
    char next;
};
void LZ77(const string& Input) {
    string temp = Input, out;

    int index = 0;
    while (index < temp.length()) {
        LZ77Token token;
        token.offset = 0;
        token.length = 0;
        token.next = temp[index];

        for (int i = index - 1; i >= 0; i--) {
            int j = 0;
            while (index + j < temp.length() && temp[i + j] == temp[index + j]) {
                j++;
            }

            if (j > token.length) {
                token.offset = index - i - 1;
                token.length = j;
                token.next = temp[index + j];
            }
        }

        out += to_string(token.offset) + to_string(token.length) + token.next + " ";
//        out += to_string(token.offset) + " " + to_string(token.length) + " " + token.next + " ";
        index += (token.length + 1);
    }

    double Compression = (double)Input.length() / (double)out.length();
    cout << "==[ LZ77 ]==" << endl
         << "Input:  " << Input << endl
         << "Output: " << out << endl
         << "==> Compression ratio: " << Input.length() << " / " <<  out.length() << " = " << Compression << endl;
}
/*=============================================[ LZ78 ]=============================================*/
void LZ78(const string& Input) {
    string temp = Input, out;

    map<string, int> storage;
    vector<pair<int, char>> compressed_data;
    string current_symbol;


    int index = 1;

    for (char character: temp) {
        current_symbol += character;
        if (storage.find(current_symbol) == storage.end()) {
            storage[current_symbol] = index;
            compressed_data.push_back
                    (make_pair(storage[current_symbol.substr(0, current_symbol.length() - 1)], character));
            index += 1;
            current_symbol = "";
        }
    }

    for (auto elem: compressed_data)
        out += to_string(elem.first) + elem.second + ' ';
//            out += to_string(elem.first) + " " + elem.second + ' ';

    storage.clear();
    compressed_data.clear();

    double Compression = (double) Input.length() / (double) out.length();
    cout << "==[ LZ78 ]==" << endl
         << "Input:  " << Input << endl
         << "Output: " << out << endl
         << "==> Compression ratio: " << Input.length() << " / " << out.length() << " = " << Compression << endl;
}
/*=============================================[ HUFFMAN ]============================================= NOT FILE */
struct HUFFMAN {
    char data;
    int freq;
    HUFFMAN* left, * right;
    HUFFMAN(char data, int freq) : data(data), freq(freq), left(nullptr), right(nullptr) {}
};
struct compare {
    bool operator()(HUFFMAN* l, HUFFMAN* r) {
        return l->freq > r->freq;
    }
};
void GenerateCodes(HUFFMAN* root, string code, map<char, string>& huffmanCodes) {
    if (root == nullptr)
        return;
    if (!root->left && !root->right) {
        huffmanCodes[root->data] = code;
    }
    GenerateCodes(root->left, code + "0", huffmanCodes);
    GenerateCodes(root->right, code + "1", huffmanCodes);
}
void Huffman(const string& OutputName, const string& InputName) {

    ifstream Output;
    ofstream Input;

    Output.open(OutputName);
    Input.open(InputName);

    string line;
    while (getline(Output, line)) {
        if (line == "") { Input << "\n"; continue; }

        map<char, int> freq;
        for (char c: line) {
            freq[c]++;
        }

        priority_queue<HUFFMAN *, vector<HUFFMAN *>, compare> pq;
        for (auto pair: freq) {
            pq.push(new HUFFMAN(pair.first, pair.second));
        }

        while (pq.size() != 1) {
            HUFFMAN *left = pq.top();
            pq.pop();
            HUFFMAN *right = pq.top();
            pq.pop();

            int sumFreq = left->freq + right->freq;
            HUFFMAN *newHUFFMAN = new HUFFMAN('\0', sumFreq);
            newHUFFMAN->left = left;
            newHUFFMAN->right = right;
            pq.push(newHUFFMAN);
        }

        HUFFMAN *root = pq.top();
        map<char, string> huffmanCodes;
        GenerateCodes(root, "", huffmanCodes);

        for (char c : line)
            for (auto elem: huffmanCodes) {
                if (c == elem.first) {
                    Input << elem.second << " "; // << elem.first <<") ";
                    continue;
                }
            }

        Input << "\n";

        huffmanCodes.clear();
    }

    Output.close();
    Input.close();
}
/*=============================================[ SHANON-FANO ]============================================= FILE + NAME */
struct Node {
    char symbol;
    int frequency;
    string code;
    Node* left;
    Node* right;

    Node(char symbol, int frequency) : symbol(symbol), frequency(frequency), left(nullptr), right(nullptr) {}
};
void buildTree(vector<Node*>& nodes, int start, int end) {
    if (start >= end) {
        return;
    }

    if (start + 1 == end) {
        nodes[start]->code += '0';
        nodes[end]->code += '1';
        return;
    }

    int totalFrequency = 0;
    for (int i = start; i <= end; ++i) {
        totalFrequency += nodes[i]->frequency;
    }

    int currentFrequency = 0;
    int mid = start;
    while (currentFrequency <= totalFrequency / 2) {
        currentFrequency += nodes[mid]->frequency;
        ++mid;
    }

    for (int i = start; i < mid; ++i) {
        nodes[i]->code += '0';
    }

    for (int i = mid; i <= end; ++i) {
        nodes[i]->code += '1';
    }

    buildTree(nodes, start, mid - 1);
    buildTree(nodes, mid, end);
}
void ShannonFano(const string& OutputName, const string& InputName) {
    ifstream Output;
    ofstream Input;

    Output.open(OutputName);
    Input.open(InputName);

    vector<Node*> nodes;

    string line;
    while (getline(Output, line)) {
        vector<int> frequencies(256, 0);

        for (char c: line) {
            frequencies[c]++;
        }

        for (int i = 0; i < 256; ++i) {
            if (frequencies[i] > 0) {
                nodes.push_back(new Node(i, frequencies[i]));
            }
        }

        sort(nodes.begin(), nodes.end(), [](Node *a, Node *b) {
            return a->frequency > b->frequency;
        });

        buildTree(nodes, 0, nodes.size() - 1);

        for (char c: line)
            for (auto elem : nodes){
                if (c == elem->symbol) {
                    Input << elem->code << " "; // << elem->symbol << "|" << elem->frequency << ") ";
                }
            }
        Input << "\n";

        frequencies.clear();
        nodes.clear();
    }

    Output.close();
    Input.close();
}

int main() {
    string OutputName = "_OutputName.txt";

    RLE ("abacabadabacabae");
    cout << endl;
    LZ77("abacabadabacabae");
    cout << endl;
    LZ78("abacabadabacabae");
    cout << endl;
    Huffman(OutputName, "4Huffman.txt");
    ShannonFano(OutputName, "5ShannonFano.txt");
}
