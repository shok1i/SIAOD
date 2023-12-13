#include "iostream"
#include "iomanip"
#include "vector"

class Graph{
private:
    int ** _data, _sz;
public:
    Graph(int sz){
        _sz = sz;
        _data = new int * [sz];

        for (int i = 0; i < sz; i++){
            _data[i] = new int [sz];
            for (int j = 0; j < sz; j++){
                _data[i][j] = 0;
            }
        }
    }
    void addEdge(int i, int j, int data){
        _data[i - 1][j - 1] = data;
        _data[j - 1][i - 1] = data;
    }
    void addNode(int add){
        int nsz = _sz + add;
        int ** newData = new int * [nsz];
        for (int i = 0; i < nsz; i++){
            newData[i] = new int [nsz];
            for (int j = 0; j < nsz; j++)
                if (i < _sz && j < _sz)
                    newData[i][j] = _data [i][j];
                else
                    newData[i][j] = 0;
        }
        for (int i = 0; i < _sz; i++)
            delete[] _data[i];
        delete[] _data;
        _data = newData;
        _sz = nsz;
    }
    void findMedian() {
        int median;
        int minDistance = INT_MAX;
        for (int i = 0; i < _sz; ++i) {
            int sumDistance = 0;
            for (int j = 0; j < _sz; ++j) {
                sumDistance += _data[i][j];
            }
            if (sumDistance < minDistance) {
                minDistance = sumDistance;
                median = i;
            }
        }
        std::cout << "The median for the current graph is " << median + 41 << std::endl;
    }
    void pathFinder(int start, int end) {
        std::vector<int> dist(_sz, INT_MAX);
        std::vector<bool> visited(_sz, false);
        std::vector<int> prev(_sz, -1);
        dist[start - 1] = 0;
        for (int count = 0; count < _sz - 1; count++) {
            int minDist = INT_MAX;
            int minIndex = -1;
            for (int i = 0; i < _sz; i++) {
                if (!visited[i] && dist[i] < minDist) {
                    minDist = dist[i];
                    minIndex = i;
                }
            }
            visited[minIndex] = true;
            for (int i = 0; i < _sz; i++) {
                if (!visited[i] && _data[minIndex][i] && dist[minIndex] != INT_MAX && dist[minIndex] + _data[minIndex][i] < dist[i]) {
                    dist[i] = dist[minIndex] + _data[minIndex][i];
                    prev[i] = minIndex;
                }
            }
        }
        std::vector<int> path;
        int current = end - 1;
        while (current != -1) {
            path.insert(path.begin(), current + 1);
            current = prev[current];
        }
        std::cout   << "Weight of the shortest path: " << dist[end - 1] << std::endl;
        std::cout   << "Shortcut: ";
        for (int elem : path)
            std::cout << elem << " ";
    }
    void toString(){
        std::cout << std::setw(5) << "  ";
        for (int i = 0; i < _sz; i++)
            std::cout << " | " << std::setw(5) << i + 1;
        std:: cout << std::endl;

        for (int i = 0; i < _sz; i++){
            std::cout << std::setw(5) << i + 1 << " |";
            for (int j = 0; j < _sz; j++){
                if (_data[i][j] != 0)
                    std::cout << std::setw(6) <<  _data[i][j] << "  ";
                else if (i == j)
                    std::cout << std::setw(8) << "X  ";
                else
                    std::cout << std::setw(8) << " ";
            }
            std::cout << std::endl;
        }
    }
};
void test_1(){
    Graph G (5);
    G.addEdge(1, 2, 1);
    G.addEdge(1, 3, 2);
    G.addEdge(1, 5, 10);
    G.addEdge(2, 5, 6);
    G.addEdge(2, 4, 3);
    G.addEdge(3, 5, 7);
    G.addEdge(3, 4, 4);
    G.addEdge(5, 4, 11);
    G.toString();
    std::cout << std::endl;
    G.findMedian();
    std::cout << std::endl;
    G.pathFinder(1, 4);
}
int main(){
    std::cout << "Graph 1 check:\n";
    test_1();
    std::cout << "\n\n\n";
    std::cout << "Enter the number of faces:" << std::endl;
    int sz;
    std::cin >> sz;
    Graph G(sz);
    int i, j, w, add;
    while (1){
        std::cout   << "======={ TASK }=======\n"
                    << "Current number of faces: " << sz << std::endl
                    << "Current matrix:\n";
        G.toString();
        std::cout   << "======={ MENU }=======\n"
                    << "1. Add a vertex \n"
                    << "2. Add a node \n"
                    << "3. Print matrix \n"
                    << "4. Find median \n"
                    << "5. Find shortest path \n"
                    << "0. Exit \n";
        int choice;
        std::cin >> choice;
        switch (choice) {
            case 0:
                return 0;
            case 1:
                std::cout << "Enter first point\n";
                std::cin  >> i;
                if (i > sz) {
                    std::cout << "Incorrect input\n";
                    break;
                }
                std::cout << "Enter second point\n";
                std::cin  >> j;
                if (j > sz) {
                    std::cout << "Incorrect input\n";
                    break;
                }
                std::cout << "Enter weight point\n";
                std::cin  >> w;
                G.addEdge(i, j, w);
                break;
            case 2:
                std::cout << "Enter the number of nodes to add\n";
                std::cin  >> add;
                sz += add;
                G.addNode(add);
                break;
            case 3:
                std::cout << "Current matrix:\n";
                G.toString();
                break;
            case 4:
                G.findMedian();
                break;
            case 5:
                std::cout << "Enter first point\n";
                std::cin  >> i;
                if (i > sz) {
                    std::cout << "Incorrect input\n";
                    break;
                }
                std::cout << "Enter second point\n";
                std::cin  >> j;
                if (j > sz) {
                    std::cout << "Incorrect input\n";
                    break;
                }
                G.pathFinder(i, j);
                break;
            default:
                std::cout << "Incorrect input\n";
        }
    }
}