//https://www.cnblogs.com/mowangshiyiyi316/p/6661541.html

#include <iostream>
#include <fstream>
#include <vector>
#include <queue>
#include <limits>
#include <iomanip>
using namespace std;

struct Vertex {
    char color; // 'w' for white, 'g' for gray, 'b' for black
    int pi; // Parent vertex
    int time; // Discovery time for DFS
    int d; // Distance from source for BFS
    vector<int> adj; // Adjacent vertices
};

void DFS_Visit(vector<Vertex>& G, int u, int& time) {
    time++;
    G[u].time = time;
    G[u].color = 'g'; // Mark u as visited (gray)

    // Visit all adjacent vertices of u
    for (int v : G[u].adj) {
        if (G[v].color == 'w') {
            G[v].pi = u; // Set parent of v as u
            DFS_Visit(G, v, time);
        }
    }

    G[u].color = 'b'; // Mark u as finished (black)
}

void DFS(vector<Vertex>& G) {
    int time = 0;

    // Initialize all vertices as white
    for (int i = 0; i < G.size(); ++i) {
        G[i].color = 'w';
        G[i].pi = -1; // Null parent
    }

    // Visit all vertices
    for (int i = 0; i < G.size(); ++i) {
        if (G[i].color == 'w') {
            DFS_Visit(G, i, time);
        }
    }
}

void BFS(vector<Vertex>& G, int s) {
    // Initialize all vertices
    for (int i = 0; i < G.size(); ++i) {
        G[i].color = 'w';
        G[i].pi = -1; // Null parent
        G[i].d = numeric_limits<int>::max(); // Infinite distance
    }

    // Initialize source vertex
    G[s].color = 'g'; // Mark s as visited (gray)
    G[s].pi = -1; // Null parent
    G[s].d = 0; // Distance from source is 0

    // Initialize queue
    queue<int> Q;
    Q.push(s);

    // Breadth-first search
    while (!Q.empty()) {
        int u = Q.front();
        Q.pop();

        // Visit all adjacent vertices of u
        for (int v : G[u].adj) {
            if (G[v].color == 'w') {
                G[v].color = 'g'; // Mark v as visited (gray)
                G[v].d = G[u].d + 1; // Update distance from source
                G[v].pi = u; // Set parent of v as u
                Q.push(v); // Enqueue v
            }
        }

        G[u].color = 'b'; // Mark u as finished (black)
    }
}

// Function to generate a random undirected graph
vector<vector<int>> generateRandomGraph(int n, int e) {
    // Initialize adjacency matrix with all zeros
    vector<vector<int>> adjMatrix(n, vector<int>(n, 0));

    // Initialize random seed
    srand(time(0));

    // Ensure e <= (n choose 2) / 2
    int maxEdges = (n * (n - 1)) / 2;
    if (e > maxEdges / 2) {
        cout << "Error: Too many edges requested." << endl;
        return adjMatrix;
    }

    // Generate random edges
    int edgesAdded = 0;
    while (edgesAdded < e) {
        int u = rand() % n;
        int v = rand() % n;
        if (u != v && adjMatrix[u][v] == 0) {
            // Add edge between u and v
            adjMatrix[u][v] = 1;
            adjMatrix[v][u] = 1;
            edgesAdded++;
        }
    }

    return adjMatrix;
}

// Function to print adjacency matrix to CSV file
void printAdjacencyMatrixCSV(const vector<vector<int>>& adjMatrix, const string& filename) {
    ofstream file(filename);
    if (!file.is_open()) {
        cerr << "Error: Unable to open file " << filename << endl;
        return;
    }

    for (const auto& row : adjMatrix) {
        for (int val : row) {
            file << val << ",";
        }
        file << endl;
    }

    file.close();
}

// Function to print adjacency list to CSV file
void printAdjacencyListCSV(const vector<vector<int>>& adjMatrix, const string& filename) {
    ofstream file(filename);
    if (!file.is_open()) {
        cerr << "Error: Unable to open file " << filename << endl;
        return;
    }

    for (int i = 0; i < adjMatrix.size(); ++i) {
        file << i << ",";
        for (int j = 0; j < adjMatrix[i].size(); ++j) {
            if (adjMatrix[i][j] == 1) {
                file << j << ",";
            }
        }
        file << endl;
    }

    file.close();
}

// Function to print DFS tree to CSV file
void printDFSTreeCSV(const vector<Vertex>& G, const string& filename) {
    ofstream file(filename);
    if (!file.is_open()) {
        cerr << "Error: Unable to open file " << filename << endl;
        return;
    }

    file << "Vertex,Discovery Time,Parent" << endl;
    for (int i = 0; i < G.size(); ++i) {
        file << i << "," << G[i].time << "," << G[i].pi << endl;
    }

    file.close();
}

// Function to print BFS tree to CSV file
void printBFSTreeCSV(const vector<Vertex>& G, const string& filename) {
    ofstream file(filename);
    if (!file.is_open()) {
        cerr << "Error: Unable to open file " << filename << endl;
        return;
    }

    file << "Vertex,Distance,Parent" << endl;
    for (int i = 0; i < G.size(); ++i) {
        file << i << "," << G[i].d << "," << G[i].pi << endl;
    }

    file.close();
}

int main() {
    int n, e;
    cout << "Enter the number of nodes (n): ";
    cin >> n;
    cout << "Enter the number of edges (e <= " << (n * (n - 1)) / 2 << "): ";
    cin >> e;
    
    vector<vector<int>> adjMatrix = generateRandomGraph(n, e);
    string adjacencyMatrixFile = "/Users/macbookpro/Downloads/未命名檔案夾/AdjacencyMatrix.csv";
    printAdjacencyMatrixCSV(adjMatrix, adjacencyMatrixFile);
    printAdjacencyListCSV(adjMatrix, "/Users/macbookpro/Downloads/未命名檔案夾/AdjacencyList.csv");
    
    // Create Vertex vector for DFS and BFS
    vector<Vertex> G(n);
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            if (adjMatrix[i][j] == 1) {
                G[i].adj.push_back(j);
            }
        }
    }
    
    // Perform DFS on the graph
    DFS(G);
    printDFSTreeCSV(G, "/Users/macbookpro/Downloads/未命名檔案夾/DFSTree.csv");
    
    // Perform BFS on the graph starting from vertex 0
    BFS(G, 0);
    printBFSTreeCSV(G, "/Users/macbookpro/Downloads/未命名檔案夾/BFSTree.csv");
    
    cout << "CSV files have been generated." << endl;
    
    return 0;
}
