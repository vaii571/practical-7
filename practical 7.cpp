//Graph : Minimum spanning Tree
 #include<iostream> using namespace std;
const int V = 5; // Number of vertices (Constant) const 
int MAX_EDGES = V * (V - 1) / 2; // Maximum possible edges in a graph
// Structure to represent an edge 
struct Edge
 { int src, dest, weight;
};
// Function to find the subset of an element `i` (uses path compression) 
int find(int parent[], int i) 
{
if (parent[i] != i){
parent[i] = find(parent, parent[i]);
 return parent[i];
}
// Function to do union of two subsets (uses union by rank) 
void Union(int parent[], int rank[], int x, int y)
 { int xroot = find(parent, x); 
 int yroot = find(parent, y);
if (rank[xroot] < rank[yroot]) 
{ parent[xroot] = yroot;
} 
else if (rank[xroot] > rank[yroot]) 
{ parent[yroot] = xroot;
} 
else
 { parent[yroot] = xroot; 
rank[xroot]++;
}
}

// Function to sort edges in increasing order of their weight
 void sortEdges(Edge edges[], int E) 
 { for (int i = 0; i < E - 1; i++) 
 { for (int j = 0; j < E - i - 1; j++) 
 { if (edges[j].weight > edges[j + 1].weight) 
 {
// Swap edges[j] and edges[j+1] 
Edge temp = edges[j]; 
edges[j] = edges[j + 1]; 
edges[j + 1] = temp;
}
}
}
}
// Function to construct and print MST using Kruskal's algorithm 
void kruskalMST(Edge edges[], int E) 
{ Edge result[V - 1]; // Store the resultant MST
 int parent[V], rank[V];
// Initialize subsets for union-find 
for (int v = 0; v < V; v++)
 { parent[v] = v; 
 rank[v] = 0;
}
// Sort edges by weight 
sortEdges(edges, E);
int e = 0; // Number of edges in MST 
for (int i = 0; e < V - 1 && i < E; i++) {
int x = find(parent, edges[i].src); 
int y = find(parent, edges[i].dest);
if (x != y)
 { result[e++] = edges[i]; // Include this edge in the MST
Union(parent, rank, x, y); // Union the two sets
}
}
// Print the result 
cout << "\nMinimum Spanning Tree (Kruskal):\nEdge \tWeight\n";
 for (int i = 0; i < e; i++) 
 { cout << result[i].src << " - " << result[i].dest << "\t" << result[i].weight << "\n";
}
}
// Function to implement Prim's Algorithm
int minKey(int key[], bool inMST[])
 { int min = 999999;
  int min_index;
   for (int v = 0; v < V; v++)
    { if (!inMST[v] && key[v] < min)
	 { min = key[v]; min_index = v;
}
}
return min_index;
}
void primMST(int graph[V][V])
 { int parent[V], key[V]; 
 bool inMST[V] = {false};
  for (int i = 0; i < V; i++) 
  { key[i] = 999999; 
  parent[i] = -1;
}
key[0] = 0; 
for (int count = 0; count < V - 1; count++)
 { int u = minKey(key, inMST);
  inMST[u] = true;
   for (int v = 0; v < V; v++) 
   { 
   if (graph[u][v] && !inMST[v] && graph[u][v] < key[v]) 
   { parent[v] = u;
    key[v] = graph[u][v];
}
}
}
cout << "Minimum Spanning Tree (Prim):\nEdge \tWeight\n";
 for (int i = 1; i < V; i++) 
 { cout << parent[i] << " - " << i << "\t" << graph[i][parent[i]] << "\n";
}
}
// Function to input adjacency matrix for Prim's Algorithm and edge list for Kruskal's Algorithm
 void inputGraph(int graph[V][V], Edge edges[], int &E) 
 { cout << "Enter the adjacency matrix (0 for no connection): \n"; 
 E = 0; // Initialize the number of edges
  for (int i = 0; i < V; i++) 
  { for (int j = 0; j < V; j++)
   { cin >> graph[i][j];
    if (graph[i][j] != 0 && i < j) 
	{ // Add edge to the edge list for Kruskal 
	edges[E++] = {i, j, graph[i][j]};
}
}
}
}
int main()
 { int graph[V][V];
Edge edges[MAX_EDGES];
 int E; // Number of edges
inputGraph(graph, edges, E);
cout << "\nRunning Prim's Algorithm...";
primMST(graph);
cout << "\nRunning Kruskal's Algorithm..."; kruskalMST(edges, E);
return 0;
}
