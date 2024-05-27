#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

vector<vector<int>> adj;
vector<bool> visited;
vector<int> path;
vector<vector<int>> paths;

void dfs(int v, int end)
{
    visited[v] = true;
    path.push_back(v);

    if (v == end)
    {
        paths.push_back(path);
    }
    else
    {

        for (int next : adj[v])
        {
            if (!visited[next])
            {
                dfs(next, end);
            }
        }
    }

    visited[v] = false;
    path.pop_back();
}

int main()
{
    int v, e;
    cin >> v >> e;
    adj.assign(v, vector<int>());
    visited.assign(v, false);

    vector<int> p(v + 1);
    for (int i = 0; i <= v; i++)
    {
        cin >> p[i];
    }

    vector<int> q(e);
    for (int i = 0; i < e; i++)
    {
        cin >> q[i];
    }

    for (int i = 0; i < v; i++)
    {
        for (int j = p[i]; j < p[i + 1]; j++)
        {
            adj[i].push_back(q[j]);
        }
    }

    for (auto &edges : adj)
    {
        sort(edges.begin(), edges.end());
        auto last = unique(edges.begin(), edges.end());
        edges.erase(last, edges.end());
    }

    dfs(0, v - 1);
    if (paths.empty())
    {
        cout << "0\n";
        return 0;
    }

    for (auto &p : paths)
    {
        for (size_t i = 0; i < p.size(); i++)
        {
            cout << p[i];
            if (i < p.size() - 1)
                cout << "->";
        }
        cout << "\n";
    }
    return 0;
}
