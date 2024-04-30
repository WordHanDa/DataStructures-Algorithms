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
    int maxEdges = ((n * (n - 1)) / 2);
    if (e > maxEdges){
        cout << "Error" << endl;
        return adjMatrix;
    }
    int edgesAdded = 0;
    while (edgesAdded < e){
        int u = rand() % n;
        int v = rand() % n;
        if (u!=v && adjMatrix[u][v]==0){
            adjMatrix[u][v] = 1;
            adjMatrix[v][u] = 1;
            edgesAdded++;
        }
    }
    return adjMatrix;
}

void printAdjacencyMatrixCSV(const vector<vector<int>>& adjMatrix, const string& filename){
    ofstream file(filename);
    file << ",";
    for (int i = 0; i < adjMatrix.size(); ++i) {
        file << i << ",";
    }
    file << endl;
    for (int i = 0; i < adjMatrix.size(); ++i){
        file << i << ",";
        for (int j = 0; j < adjMatrix[i].size(); ++j){
            file << adjMatrix[i][j] << ",";
        }
        file << endl;
    }
    file.close();
}

void printAdjacencyListCSV(const vector<Vertex>& G, const string& filename){
    ofstream file(filename);
    for (int i = 0; i < G.size(); ++i){
        file << i << ",";
        for (int j = 0; j < G[i].adj.size(); ++j){
            file << G[i].adj[j] << ",";
        }
        file << endl;
    }
    file.close();
}

void printDFSTreeCSV(const vector<Vertex>& G, const string& filename) {
    ofstream file(filename);
    for (int i = 0; i < G.size(); ++i){
        if(G[i].time!=G.size()){
            file << i << "," << G[i].time << endl;
        }else{
            file << i << "," << i << endl;
        }
    }
    file.close();
}

void printBFSTreeCSV(const vector<Vertex>& G, const string& filename){
    ofstream file(filename);
    for (int i = 0; i < G.size(); ++i){
        file << i << "," << G[i].d << endl;
    }
    file.close();
}

int main(){
    int n, e;
    cout << "Enter the number of nodes & edges (n,e): ";
    cin >> n >> e;
    vector<vector<int>> adjMatrix = generateRandomGraph(n, e);
    vector<Vertex> G(n);
    for (int i = 0; i < n; ++i){
        for (int j = 0; j < n; ++j){
            if (adjMatrix[i][j] == 1){
                G[i].adj.push_back(j);
            }
        }
    }
    printAdjacencyMatrixCSV(adjMatrix, "/Users/macbookpro/Downloads/未命名檔案夾/AdjacencyMatrix.csv");
    printAdjacencyListCSV(G, "/Users/macbookpro/Downloads/未命名檔案夾/AdjacencyList.csv");
    DFS(G);
    BFS(G, 0);
    printDFSTreeCSV(G, "/Users/macbookpro/Downloads/未命名檔案夾/DFSTree.csv");
    printBFSTreeCSV(G, "/Users/macbookpro/Downloads/未命名檔案夾/BFSTree.csv");
    return 0;
}
