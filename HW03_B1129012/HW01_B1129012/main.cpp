#include <iostream>
#include <fstream>
#include <vector>
#include <ctime>
#include <cstdlib>
#include <algorithm>
#include <queue>
#include <limits>
using namespace std;

struct Vertex {
    char color; // 'w' for white, 'g' for gray, 'b' for black
    int pi; // Parent vertex
    int d; // Distance from source (for BFS)
    int time; // Discovery time (for DFS)
    vector<int> adj; // Adjacent vertices
};

// Function to generate a random number between 0 and n-1
int randomNode(int n) {
    return rand() % n;
}

// Function to generate a random undirected graph using adjacency matrix
vector<vector<int>> generateRandomUndirectedGraph_Matrix(int n, int e, string filename) {
    // Initialize adjacency matrix with all zeros
    vector<vector<int>> graph(n, vector<int>(n, 0));
    int edgeCount = 0;

    while (edgeCount < e) {
        int node1 = randomNode(n);
        int node2 = randomNode(n);
        
        // Ensure node1 and node2 are different and there is no edge between them
        if (node1 != node2 && graph[node1][node2] == 0) {
            graph[node1][node2] = 1;
            graph[node2][node1] = 1;
            edgeCount++;
        }
    }

    // Save adjacency matrix to CSV file
    ofstream outfile(filename);
    if (outfile.is_open()) {
        for (const auto& row : graph) {
            for (int val : row) {
                outfile << val << ",";
            }
            outfile << endl;
        }
        outfile.close();
        cout << "Adjacency matrix saved to: " << filename << endl;
    } else {
        cout << "Error: Unable to open file for writing!" << endl;
    }

    return graph;
}

// Function to generate a random undirected graph using adjacency list
vector<vector<int>> generateRandomUndirectedGraph_List(int n, int e, string filename) {
    // Initialize adjacency list with empty vectors
    vector<vector<int>> graph(n);

    int edgeCount = 0;

    while (edgeCount < e) {
        int node1 = randomNode(n);
        int node2 = randomNode(n);
        
        // Ensure node1 and node2 are different and there is no edge between them
        if (node1 != node2) {
            // Check if node2 already exists in the adjacency list of node1
            if (find(graph[node1].begin(), graph[node1].end(), node2) == graph[node1].end()) {
                graph[node1].push_back(node2);
                graph[node2].push_back(node1); // Undirected graph, so add edge in both directions
                edgeCount++;
            }
        }
    }

    // Save adjacency list to CSV file
    ofstream outfile(filename);
    if (outfile.is_open()) {
        for (int i = 0; i < graph.size(); ++i) {
            outfile << i << ",";
            for (int j = 0; j < graph[i].size(); ++j) {
                outfile << graph[i][j] << ",";
            }
            outfile << endl;
        }
        outfile.close();
        cout << "Adjacency list saved to: " << filename << endl;
    } else {
        cout << "Error: Unable to open file for writing!" << endl;
    }

    return graph;
}

// Depth First Search Visit
void DFS_Visit(vector<Vertex>& G, int u, int& time, vector<vector<int>>& tree) {
    time=time+1;
    G[u].time = time;
    G[u].color = 'g'; // Mark u as visited (gray)

    // Debugging output
    cout << "Visiting node " << u << " with color " << G[u].color << " and adjacency list: ";
    for (int v : G[u].adj) {
        cout << v << " ";
    }
    cout << endl;

    // Visit all adjacent vertices of u
    for (int v : G[u].adj) {
        if (G[v].color == 'w') {
            G[v].pi = u; // Set parent of v as u
            // Add edge (u, v) to the DFS tree
            tree[u].push_back(v);
            DFS_Visit(G, v, time, tree);
        }
    }

    G[u].color = 'b'; // Mark u as finished (black)
}

// Depth First Search
vector<vector<int>> DFS(vector<Vertex>& G) {
    int time = 0;

    // Initialize all vertices
    for (int i = 0; i < G.size(); ++i) {
        G[i].color = 'w';
        G[i].pi = -1; // Null parent
        G[i].time = 0;
    }

    vector<vector<int>> tree(G.size());

    // Visit all vertices
    for (int i = 0; i < G.size(); ++i) {
        if (G[i].color == 'w') {
            DFS_Visit(G, i, time, tree);
        }
    }

    return tree;
}

// Breadth First Search
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
void saveTreeToCSV(vector<Vertex>& tree, string filename) {
    ofstream outfile(filename);
    if (outfile.is_open()) {
        outfile << "Source,Target" << endl;
        for (int i = 0; i < tree.size(); ++i) {
            if (tree[i].pi != -1) {
                outfile << tree[i].pi << "," << i << endl;
            }
        }
        outfile.close();
        cout << "Tree saved to: " << filename << endl;
    } else {
        cout << "Error: Unable to open file for writing!" << endl;
    }
}

int main() {
    int n, e;

    // Get user input for number of nodes and edges
    cout << "Enter the number of nodes (n): ";
    cin >> n;
    cout << "Enter the number of edges (e): ";
    cin >> e;

    // Check if e is within the limit
    if (e > (n * (n - 1)) / 2) {
        cout << "Invalid input: e should be less than or equal to (n choose 2)" << endl;
        return 1;
    }

    // Define file paths
    string matrix_filename = "/Users/macbookpro/Downloads/未命名檔案夾/adjacency_matrix.csv";
    string list_filename = "/Users/macbookpro/Downloads/未命名檔案夾/adjacency_list.csv";

    // Generate random undirected graph using both adjacency matrix and adjacency list
    vector<vector<int>> adj_matrix = generateRandomUndirectedGraph_Matrix(n, e, matrix_filename);
    vector<vector<int>> adj_list = generateRandomUndirectedGraph_List(n, e, list_filename);

    // Initialize vertices for DFS and BFS
    vector<Vertex> vertices_DFS(n);
    vector<Vertex> vertices_BFS(n);

    // Convert adjacency list to adjacency matrix
    vector<vector<int>> adj_matrix_converted(n, vector<int>(n, 0));
    for (int i = 0; i < n; ++i) {
        for (int j : adj_list[i]) {
            adj_matrix_converted[i][j] = 1;
            adj_matrix_converted[j][i] = 1; // Undirected graph, so add edge in both directions
        }
    }

    // Set adjacency lists for DFS and BFS vertices
    for (int i = 0; i < n; ++i) {
        vertices_DFS[i].adj = adj_matrix_converted[i];
        vertices_BFS[i].adj = adj_list[i];
    }

    // Perform DFS on the graph
    DFS(vertices_DFS);
    saveTreeToCSV(vertices_BFS, "/Users/macbookpro/Downloads/未命名檔案夾/dfs_tree.csv");


    // Perform BFS on the graph starting from vertex 0
    BFS(vertices_BFS, 0);
    saveTreeToCSV(vertices_BFS, "/Users/macbookpro/Downloads/未命名檔案夾/bfs_tree.csv");


    // Output the discovery time and parent of each vertex for DFS
    cout << "DFS Results:" << endl;
    for (int i = 0; i < n; ++i) {
        cout << "Vertex " << i << ": Discovery time = " << vertices_DFS[i].time << ", Parent = " << vertices_DFS[i].pi << endl;
    }

    // Output the distance and parent of each vertex for BFS
    cout << "BFS Results:" << endl;
    for (int i = 0; i < n; ++i) {
        cout << "Vertex " << i << ": Distance = " << vertices_BFS[i].d << ", Parent = " << vertices_BFS[i].pi << endl;
    }

    return 0;
}
