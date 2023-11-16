#include "iostream"
#include "iomanip"

class Graph{
private:
    int **_data, _sz;
public:
    Graph(int sz){
        _sz = sz;
        _data = new int * [sz];

        for (int i = 0; i < sz; i++){
            _data[i] = new int [sz];
            for (int j = 0; j < sz; j++){
                _data[i][j] = -1;
            }
        }
    }

    void addEdge(int i, int j, int data){
        _data[i][j] = data;
    }

    void toString(){
        std::cout << std::setw(5) << "  ";
        for (int i = 0; i < _sz; i++)
            std::cout << " | " << std::setw(5) << i;
        std:: cout << std::endl;

        for (int i = 0; i < _sz; i++){
            std::cout << std::setw(5) << i << " |";
            for (int j = 0; j < _sz; j++){
                if (_data[i][j] != -1)
                    std::cout << std::setw(6) <<  _data[i][j] << "  ";
                else
                    std::cout << std::setw(8) << " ";
            }
            std::cout << std::endl;
        }
    }
};

int main(){
    Graph G (9);

    G.addEdge(1, 1, 56);
    G.addEdge(4, 5, 486);
    G.addEdge(3, 6, 41);
    G.addEdge(4, 1, 413);

    G.toString();
}
