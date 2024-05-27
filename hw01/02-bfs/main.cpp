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

bool cmp(std::vector<int> a, std::vector<int> b)
{
    if (a.size() != b.size())
    {
        return (a.size() < b.size());
    }
    else
    {
        return a < b;
    }
}

int main()
{
    int v, e;
    cin >> v >> e;
    adj.assign(v, vector<int>());
    visited.assign(v, false);

    for (int i = 0; i < e; i++)
    {
        int a, b;
        std::cin>>a>>b;
        adj[a].push_back(b);
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

    sort(paths.begin(), paths.end(), cmp);

    for (size_t i = 0; i < paths[0].size(); i++)
    {
        cout << paths[0][i];
        if (i < paths[0].size() - 1)
            cout << "->";
    }
    cout << "\n";

    return 0;
}
