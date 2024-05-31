#include <iostream>
#include <vector>
#include <algorithm>

struct Edge
{
    int u, v, w;
    bool operator<(const Edge &other) const
    {
        return w < other.w;
    }
};

int find(std::vector<int> &parent, int i)
{
    if (parent[i] != i)
    {
        parent[i] = find(parent, parent[i]);
    }
    return parent[i];
}

void unionSets(std::vector<int> &parent, std::vector<int> &rank, int x, int y)
{
    int rootX = find(parent, x);
    int rootY = find(parent, y);
    if (rootX != rootY)
    {
        if (rank[rootX] > rank[rootY])
        {
            parent[rootY] = rootX;
        }
        else if (rank[rootX] < rank[rootY])
        {
            parent[rootX] = rootY;
        }
        else
        {
            parent[rootY] = rootX;
            rank[rootX]++;
        }
    }
}

int kruskal(int n, std::vector<Edge> &edges)
{
    std::vector<int> parent(n + 1);
    std::vector<int> rank(n + 1, 0);
    for (int i = 1; i <= n; i++)
    {
        parent[i] = i;
    }

    std::sort(edges.begin(), edges.end());

    int mst_weight = 0;
    int mst_edges = 0;

    for (const auto &edge : edges)
    {
        int u = find(parent, edge.u);
        int v = find(parent, edge.v);

        if (u != v)
        {
            unionSets(parent, rank, u, v);
            mst_weight += edge.w;
            mst_edges++;
            if (mst_edges == n - 1)
                break;
        }
    }

    if (mst_edges != n - 1)
        return -1;
    return mst_weight;
}

int main()
{
    int n, m;
    std::cin >> n >> m;

    std::vector<Edge> edges(m);
    for (int i = 0; i < m; i++)
    {
        std::cin >> edges[i].u >> edges[i].v >> edges[i].w;
    }

    int result = kruskal(n, edges);
    std::cout << result << std::endl;

    return 0;
}