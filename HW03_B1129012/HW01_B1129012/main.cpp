//https://www.cnblogs.com/mowangshiyiyi316/p/6661541.html
#include <iostream>
#include <fstream>
#include <vector>
#include <queue>
#include <limits>
#include <iomanip>
using namespace std;

struct Vertex{
    char color;
    int pi;
    int time;
    int d;
    vector<int> adj;
};

void DFS_Visit(vector<Vertex>& G, int u, int& time){
    time++;
    G[u].time = time;
    G[u].color = 'g';
    for (int v : G[u].adj){
        if (G[v].color == 'w'){
            G[v].pi = u;
            DFS_Visit(G, v, time);
        }
    }
    G[u].color = 'b';
}

void DFS(vector<Vertex>& G){
    int time = 0;
    for (int i = 0; i < G.size(); ++i){
        G[i].color = 'w';
        G[i].pi = -1;
    }
    for (int i = 0; i < G.size(); ++i){
        if (G[i].color == 'w') {
            DFS_Visit(G, i, time);
        }
    }
}

void BFS(vector<Vertex>& G, int s) {
    for (int i = 0; i < G.size(); ++i){
        G[i].color = 'w';
        G[i].pi = -1;
        G[i].d = numeric_limits<int>::max();
    }
    G[s].color = 'g';
    G[s].pi = -1;
    G[s].d = 0;
    queue<int> Q;
    Q.push(s);
    while (!Q.empty()){
        int u = Q.front();
        Q.pop();

        for (int v : G[u].adj){
            if (G[v].color == 'w'){
                G[v].color = 'g';
                G[v].d = G[u].d + 1;
                G[v].pi = u;
                Q.push(v);
            }
        }
        G[u].color = 'b';
    }
}

vector<vector<int>> generateRandomGraph(int n, int e){
    vector<vector<int>> adjMatrix(n, vector<int>(n, 0));
    srand(time(0));

    int maxEdges = (n * (n - 1)) / 2;
    if (e > maxEdges / 2){
        cout << "Error" << endl;
        return adjMatrix;
    }
    // Generate edges
    int edgesAdded = 0;
    while (edgesAdded < e){
        int u = rand() % n;
        int v = rand() % n;
        if (u != v && adjMatrix[u][v] == 0){
            adjMatrix[u][v] = 1;
            adjMatrix[v][u] = 1;
            edgesAdded++;
        }
    }
    return adjMatrix;
}

void printAdjacencyMatrixCSV(const vector<vector<int>>& adjMatrix, const string& filename){
    ofstream file(filename);
    if (!file.is_open()){
        cerr << "Error: Unable to open file " << filename << endl;
        return;
    }
    for (const auto& row : adjMatrix){
        for (int val : row){
            file << val << ",";
        }
        file << endl;
    }
    file.close();
}

void printAdjacencyListCSV(const vector<vector<int>>& adjMatrix, const string& filename){
    ofstream file(filename);
    if (!file.is_open()){
        cerr << "Error: Unable to open file " << filename << endl;
        return;
    }
    for (int i = 0; i < adjMatrix.size(); ++i){
        file << i << ",";
        for (int j = 0; j < adjMatrix[i].size(); ++j){
            if (adjMatrix[i][j]==1){
                file << j << ",";
            }
        }
        file << endl;
    }
    file.close();
}

void printDFSTreeCSV(const vector<Vertex>& G, const string& filename) {
    ofstream file(filename);
    if (!file.is_open()){
        cerr << "Error: Unable to open file " << filename << endl;
        return;
    }
    file << "Vertex,Discovery Time,Parent" << endl;
    for (int i = 0; i < G.size(); ++i){
        file << i << "," << G[i].time << "," << G[i].pi << endl;
    }
    file.close();
}

// Function to print BFS tree to CSV file
void printBFSTreeCSV(const vector<Vertex>& G, const string& filename){
    ofstream file(filename);
    if (!file.is_open()){
        cerr << "Error: Unable to open file " << filename << endl;
        return;
    }
    file << "Vertex,Distance,Parent" << endl;
    for (int i = 0; i < G.size(); ++i){
        file << i << "," << G[i].d << "," << G[i].pi << endl;
    }
    file.close();
}

int main() {
    int n, e;
    cout << "Enter the number of nodes (n): ";
    cin >> n;
    cout << "Enter the number of edges (e): ";
    cin >> e;
    
    vector<vector<int>> adjMatrix = generateRandomGraph(n, e);
    printAdjacencyMatrixCSV(adjMatrix, "/Users/macbookpro/Downloads/未命名檔案夾/AdjacencyMatrix.csv");
    printAdjacencyListCSV(adjMatrix, "/Users/macbookpro/Downloads/未命名檔案夾/AdjacencyList.csv");
    vector<Vertex> G(n);
    for (int i = 0; i < n; ++i){
        for (int j = 0; j < n; ++j){
            if (adjMatrix[i][j] == 1){
                G[i].adj.push_back(j);
            }
        }
    }
    DFS(G);
    printDFSTreeCSV(G, "/Users/macbookpro/Downloads/未命名檔案夾/DFSTree.csv");
    BFS(G, 0);
    printBFSTreeCSV(G, "/Users/macbookpro/Downloads/未命名檔案夾/BFSTree.csv");
    return 0;
}
