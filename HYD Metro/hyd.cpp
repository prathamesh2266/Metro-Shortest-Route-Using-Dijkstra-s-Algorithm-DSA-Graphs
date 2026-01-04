#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <climits>

using namespace std;

/* ---------- Utility ---------- */
string toLower(string s)
{
    transform(s.begin(), s.end(), s.begin(), ::tolower);
    return s;
}

int getIndex(string name, vector<string>& stations)
{
    name = toLower(name);
    for (int i = 0; i < stations.size(); i++)
        if (toLower(stations[i]) == name)
            return i;
    return -1;
}

/* ---------- Dijkstra ---------- */
vector<int> dijkstra(vector<vector<int>>& graph, int src)
{
    int N = graph.size();
    vector<int> dist(N, INT_MAX), parent(N, -1);
    vector<bool> visited(N, false);

    dist[src] = 0;

    for (int i = 0; i < N - 1; i++)
    {
        int u = -1, mn = INT_MAX;
        for (int j = 0; j < N; j++)
            if (!visited[j] && dist[j] < mn)
                mn = dist[j], u = j;

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

/* ---------- MAIN ---------- */
int main()
{
    /* -------- Stations -------- */

    vector<string> stations = {

        // 🔴 Red Line (27)
        "Miyapur","JNTU College","KPHB Colony","Kukatpally",
        "Dr. B. R. Ambedkar Balanagar","Moosapet","Bharat Nagar",
        "Erragadda","ESI Hospital","SR Nagar","Ameerpet",
        "Panjagutta","Irrummanzil","Khairatabad","Lakdikapool",
        "Assembly","Nampally","Gandhi Bhavan",
        "Osmania Medical College","MG Bus Station","Malakpet",
        "New Market","Moosrambagh","Dilshukhnagar",
        "Chaitanyapuri","Victoria Memorial","LB Nagar",

        // 🟢 Green Line (9)
        "JBS Parade Ground","Secunderabad West","Gandhi Hospital",
        "Musheerabad","RTC X Roads","Chikkadpally",
        "Narayanguda","Sultan Bazaar","MG Bus Station",

        // 🔵 Blue Line (23)
        "Nagole","Uppal","Stadium","NGRI","Habsiguda","Tarnaka",
        "Mettuguda","Secunderabad East","JBS Parade Ground",
        "Paradise","Rasoolpura","Prakash Nagar","Begumpet",
        "Ameerpet","Madhura Nagar","Yusufguda",
        "Jubilee Hills Road No. 5","Jubilee Hills Check Post",
        "Peddamma Gudi","Madhapur","Durgam Cheruvu",
        "HITEC City","Raidurg"
    };

    int N = stations.size();
    vector<vector<int>> graph(N, vector<int>(N, 0));

    /* -------- Red Line edges -------- */
    for (int i = 0; i < 26; i++)
        graph[i][i+1] = graph[i+1][i] = 1;

    /* -------- Green Line edges -------- */
    for (int i = 27; i < 35; i++)
        graph[i][i+1] = graph[i+1][i] = 1;

    /* -------- Blue Line edges -------- */
    for (int i = 36; i < N-1; i++)
        graph[i][i+1] = graph[i+1][i] = 1;

    /* -------- Interchange links (CORRECT) -------- */

    // Ameerpet: Red (10) <-> Blue (49)
    graph[10][49] = graph[49][10] = 1;

    // MG Bus Station: Red (19) <-> Green (35)
    graph[19][35] = graph[35][19] = 1;

    // JBS Parade Ground: Green (27) <-> Blue (44)
    graph[27][44] = graph[44][27] = 1;

    /* -------- Loop for multiple queries -------- */
    char choice;
    do
    {
        string srcName, destName;

        cout << "\nEnter source station: ";
        getline(cin, srcName);
        cout << "Enter destination station: ";
        getline(cin, destName);

        int src = getIndex(srcName, stations);
        int dest = getIndex(destName, stations);

        if (src == -1 || dest == -1)
        {
            cout << "Invalid station name!\n";
        }
        else
        {
            vector<int> parent = dijkstra(graph, src);
            vector<int> path = buildPath(parent, dest);

            cout << "\nFinal Route:\n";
            cout << stations[src];

            vector<string> interchanges = {
                "Ameerpet",
                "MG Bus Station",
                "JBS Parade Ground"
            };

            for (int idx : path)
            {
                for (string ic : interchanges)
                {
                    if (stations[idx] == ic &&
                        stations[idx] != stations[src] &&
                        stations[idx] != stations[dest])
                    {
                        cout << " -> " << stations[idx];
                    }
                }
            }

            cout << " -> " << stations[dest] << endl;
        }

        cout << "\nDo you want to find another route? (y/n): ";
        cin >> choice;
        cin.ignore();

    } while (choice == 'y' || choice == 'Y');

    return 0;
}
