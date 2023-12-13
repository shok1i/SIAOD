#include <iostream>
#include <vector>
#include <string>

using   std::cin, std::cout, std::string,
        std::vector, std::tuple, std::pair,
        std::getline, std::endl;



int main () {
    vector<tuple<string, string, int>> roads;

    string line, temp;
    getline(cin, line);

    string first = line.substr(0, line.find(' '));
    line = line.substr(line.find(' ') + 1, line.length());

    string second = line.substr(0, line.find(' '));
    line = line.substr(line.find(' ') + 1, line.length());

    int third = stoi( line.substr(0, line.find(' ')) );

    roads.emplace_back(first, second, third);

    for (auto single_elem : roads)
        cout << "First\t" << get<0>(single_elem) << endl
             << "Second\t" << get<1>(single_elem) << endl
             << "Third\t" << get<2>(single_elem) << "\n====\n";
}