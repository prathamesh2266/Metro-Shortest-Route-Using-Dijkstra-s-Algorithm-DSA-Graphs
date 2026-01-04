#include <iostream>
#include <vector>
#include <string>
#include <climits>
#include <algorithm>

using namespace std;

const int N = 30;   // total stations

/* -----------------------------
   Convert string to lowercase
----------------------------- */
string toLower(string s)
{
    transform(s.begin(), s.end(), s.begin(), ::tolower);
    return s;
}

/* -----------------------------
   Get station index
----------------------------- */
int getIndex(string name, vector<string>& stations)
{
    name = toLower(name);
    for (int i = 0; i < stations.size(); i++)
        if (toLower(stations[i]) == name)
            return i;
    return -1;
}

/* -----------------------------
   Dijkstra Algorithm
----------------------------- */
vector<int> dijkstra(int graph[N][N], int src)
{
    vector<int> dist(N, INT_MAX), parent(N, -1);
    vector<bool> visited(N, false);

    dist[src] = 0;

    for (int i = 0; i < N - 1; i++)
    {
        int u = -1, minDist = INT_MAX;

        for (int j = 0; j < N; j++)
            if (!visited[j] && dist[j] < minDist)
                minDist = dist[j], u = j;

        if (u == -1) break;

        visited[u] = true;

        for (int v = 0; v < N; v++)
        {
            if (graph[u][v] && !visited[v] &&
                dist[u] + 1 < dist[v])
            {
                dist[v] = dist[u] + 1;
                parent[v] = u;
            }
        }
    }
    return parent;
}

/* -----------------------------
   Build path from parent array
----------------------------- */
vector<int> buildPath(vector<int>& parent, int dest)
{
    vector<int> path;
    while (dest != -1)
    {
        path.push_back(dest);
        dest = parent[dest];
    }
    reverse(path.begin(), path.end());
    return path;
}

/* -----------------------------
   MAIN FUNCTION
----------------------------- */
int main()
{
    // Station list (line-wise order)
    vector<string> stations = {
        // Purple Line (0–13)
        "PCMC","Sant Tukaram Nagar","Bhosari","Kasarwadi","Phugewadi",
        "Dapodi","Bopodi","Khadki","Range Hill","Shivaji Nagar",
        "Civil Court","Budhwar Peth","Mandai","Swargate",

        // Aqua Line (14–29)
        "Vanaz","Anand Nagar","Ideal Colony","Nal Stop","Garware College",
        "Deccan Gymkhana","Chhatrapati Sambhaji Udyan","Civil Court",
        "Mangalwar Peth","PMC","Pune Railway Station","Ruby Hall Clinic",
        "Bund Garden","Yerawada","Kalyani Nagar","Ramwadi"
    };

    // Line mapping
    vector<string> line(N);
    for (int i = 0; i <= 13; i++) line[i] = "Purple";
    for (int i = 14; i < N; i++) line[i] = "Aqua";

    // Graph (Adjacency Matrix)
    int graph[N][N] = {0};

    // Purple line connections
    for (int i = 0; i < 13; i++)
        graph[i][i+1] = graph[i+1][i] = 1;

    // Aqua line connections
    for (int i = 14; i < 29; i++)
        graph[i][i+1] = graph[i+1][i] = 1;

    // Interchange: Civil Court (Purple ↔ Aqua)
    graph[10][21] = graph[21][10] = 1;

    string srcName, destName;
    
     cout << "----- Pune Metro Stations -----\n\n";

    cout << "Purple Line (PCMC to Swargate):\n";
    cout << "PCMC\n";
    cout << "Sant Tukaram Nagar\n";
    cout << "Bhosari (Nashik Phata)\n";
    cout << "Kasarwadi\n";
    cout << "Phugewadi\n";
    cout << "Dapodi\n";
    cout << "Bopodi\n";
    cout << "Khadki\n";
    cout << "Range Hill\n";
    cout << "Shivaji Nagar\n";
    cout << "Civil Court (Interchange)\n";
    cout << "Budhwar Peth\n";
    cout << "Mandai\n";
    cout << "Swargate\n\n";

    cout << "Aqua Line (Vanaz to Ramwadi):\n";
    cout << "Vanaz\n";
    cout << "Anand Nagar\n";
    cout << "Ideal Colony\n";
    cout << "Nal Stop\n";
    cout << "Garware College\n";
    cout << "Deccan Gymkhana\n";
    cout << "Chhatrapati Sambhaji Udyan\n";
    cout << "Civil Court (Interchange)\n";
    cout << "Mangalwar Peth\n";
    cout << "PMC\n";
    cout << "Pune Railway Station\n";
    cout << "Ruby Hall Clinic\n";
    cout << "Bund Garden\n";
    cout << "Yerawada\n";
    cout << "Kalyani Nagar\n";
    cout << "Ramwadi\n\n";

    cout << "Enter source station: ";
    getline(cin, srcName);

    cout << "Enter destination station: ";
    getline(cin, destName);

    int src = getIndex(srcName, stations);
    int dest = getIndex(destName, stations);

    if (src == -1 || dest == -1)
    {
        cout << "Invalid station name!" << endl;
        return 0;
    }

    vector<int> parent = dijkstra(graph, src);
    vector<int> path = buildPath(parent, dest);

    cout << "\nFinal Route:\n";

    // Same line
    if (line[src] == line[dest])
    {
        cout << stations[src] << " -> " << stations[dest] << endl;
    }
    else
    {
        // Find interchange point
        for (int i = 1; i < path.size(); i++)
        {
            if (line[path[i]] != line[path[i-1]])
            {
                cout << stations[src] << " -> "
                     << stations[path[i]] << " -> "
                     << stations[dest] << endl;
                break;
            }
        }
    }

    return 0;
}
