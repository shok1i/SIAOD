#include <iostream>
#include <fstream>
#include <string>
#include <vector>

using namespace std;

void RLE(const string& OutputName, const string& InputName) {
    ifstream Output;
    ofstream Input;

    Output.open(OutputName);
    Input.open(InputName);

    string line;
    while (getline(Output, line)){
        char elem = line[0];
        line += "$";
        int count = -1;

        for (char i : line)
            if (elem == i) count++;
            else {
                count++;
                Input << count << elem;
                elem  = i;
                count = 0;
            }

        Input << "\n";
    }

    Output.close();
    Input.close();
}

struct LZ77Token {
    int offset, length;
    char next;
};

void LZ77(const string& OutputName, const string& InputName) {
    ifstream Output;
    ofstream Input;

    Output.open(OutputName);
    Input.open(InputName);

    string line;
    while (getline(Output, line)) {

        int index = 0;
        while (index < line.length()) {
            LZ77Token token;
            token.offset = 0;
            token.length = 0;
            token.next = line[index];

            // 1 -> BUFFER
            for (int i = index - 1; i >= 0; i--) {
                int j = 0;
                while (index + j < line.length() && line[i + j] == line[index + j]) {
                    j++;
                }

                if (j > token.length) {
                    token.offset = index - i - 1;
                    token.length = j;
                    token.next = line[index + j];
                }
            }

            Input << " (" << token.offset << ", " << token.length << ", " << token.next << ") ";
            index += (token.length + 1);
        }

        Input << "\n";
    }

    Output.close();
    Input.close();
}


int main() {
    string OutputName = "_OutputName.txt", InputName = "_InputName.txt";

    LZ77(OutputName, InputName);
}
