//    void dijkstra(int startVertex, int endVertex) {
//        std::vector<int> distance(V, std::numeric_limits<int>::max());
//        std::vector<int> parent(V, -1);
//        std::vector<bool> visited(V, false);
//
//        distance[startVertex] = 0;
//
//        for (int i = 0; i < V - 1; i++) {
//            int u = -1;
//            // Находим вершину с минимальным расстоянием из еще не посещенных вершин
//            for (int j = 0; j < V; j++) {
//                if (!visited[j] && (u == -1 || distance[j] < distance[u])) {
//                    u = j;
//                }
//            }
//
//            visited[u] = true;
//
//            // Обновляем расстояния до соседних вершин
//            for (int v = 0; v < V; v++) {
//                if (!visited[v] && adjacencyMatrix[u][v] && distance[u] != std::numeric_limits<int>::max() &&
//                    distance[u] + adjacencyMatrix[u][v] < distance[v]) {
//                    distance[v] = distance[u] + adjacencyMatrix[u][v];
//                    parent[v] = u;
//                }
//            }
//        }
//
//        // Выводим найденный кратчайший путь
//        std::cout << "Shortcut: ";
//        std::cout << distance[endVertex];
//        printPath(parent, endVertex);
//        std::cout << std::endl;
//    }
//
//    void printPath(const std::vector<int>& parent, int vertex) {
//        if (vertex == -1) {
//            return;
//        }
//        printPath(parent, parent[vertex]);
//        std::cout << vertex << " ";
//    }
//};

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

        std::cout << "The median for the current graph is " << median - 1 << std::endl;
    }

    void dijkstra__1(int start, int end) {
        const int INF = INT_MAX;

        std::vector<int> dist(_sz, INF);
        std::vector<bool> visited(_sz, false);
        std::vector<int> prev(_sz, -1);

        dist[start - 1] = 0;

        for (int count = 0; count < _sz - 1; count++) {
            int minDist = INF;
            int minIndex = -1;

            for (int i = 0; i < _sz; i++) {
                if (!visited[i] && dist[i] < minDist) {
                    minDist = dist[i];
                    minIndex = i;
                }
            }

            visited[minIndex] = true;

            for (int i = 0; i < _sz; i++) {
                if (!visited[i] && _data[minIndex][i] && dist[minIndex] != INF &&
                    dist[minIndex] + _data[minIndex][i] < dist[i]) {
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


    void dijkstrasAlgorithm(int start, int end) {
        // Create a vector to store the shortest distances from the start node to all other nodes
        std::vector<int> shortestDistances(_sz, INT_MAX);

        // Create a vector to store the visited status of each node
        std::vector<bool> visited(_sz, false);

        std::vector<int> prev(_sz, -1);

        // Set the distance of the start node to 0
        shortestDistances[start - 1] = 0;

        // Iterate through all nodes
        for (int i = 0; i < _sz - 1; ++i) {
            // Find the node with the minimum distance that is not visited
            int minDistance = INT_MAX;
            int minIndex = -1;
            for (int j = 0; j < _sz; ++j) {
                if (!visited[j] && shortestDistances[j] <= minDistance) {
                    minDistance = shortestDistances[j];
                    minIndex = j;
                }
            }

            // Mark the found node as visited
            visited[minIndex] = true;

            // Update the distances of the adjacent nodes
            for (int j = 0; j < _sz; ++j) {
                if (!visited[j] && _data[minIndex][j] && shortestDistances[minIndex] != INT_MAX &&
                    shortestDistances[minIndex] + _data[minIndex][j] < shortestDistances[j]) {
                    shortestDistances[j] = shortestDistances[minIndex] + _data[minIndex][j];

                    prev[i] = minIndex;
                }
            }
        }

        // Print the shortest distance from the start node to the end node
        std::cout << "The shortest distance from node " << start << " to node " << end << " is " << shortestDistances[end - 1] << std::endl;


        std::vector<int> path;

        int current = end - 1;
        while (current != -1) {
            path.insert(path.begin(), current + 1);
            current = prev[current];
        }

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

int main(){
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
    G.dijkstra__1(1, 4);

}