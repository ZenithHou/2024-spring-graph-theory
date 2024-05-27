#include <iostream>
#include <vector>
#include <algorithm>
#include <queue>

const int MAXN = 1001;
const int INF = 1e9;

struct Edge
{
    int to, weight;
};

std::vector<Edge> graph[MAXN];
std::vector<int> dist1(MAXN, INF);
std::vector<int> dist2(MAXN, INF);

void dijkstra(int start, std::vector<int> &dist)
{
    std::priority_queue<std::pair<int, int>,
                        std::vector<std::pair<int, int>>,
                        std::greater<std::pair<int, int>>>
        pq;

    dist[start] = 0;
    pq.push({0, start});

    while (!pq.empty())
    {
        int d = pq.top().first;
        int u = pq.top().second;
        pq.pop();

        if (d > dist[u])
            continue;

        for (auto edge : graph[u])
        {
            int v = edge.to;
            int w = edge.weight;
            if (dist[v] > dist[u] + w)
            {
                dist[v] = dist[u] + w;
                pq.push({dist[v], v});
            }
        }
    }
}

int main()
{
    int n, m;
    std::cin >> n >> m;

    for (int i = 0; i < m; i++)
    {
        int u, v, w;
        std::cin >> u >> v >> w;
        graph[u].push_back({v, w});
        graph[v].push_back({u, w});
    }

    dijkstra(1, dist1);
    dijkstra(n, dist2);

    if (dist1[n] == INF)
    {
        std::cout << -1 << std::endl;
        return 0;
    }

    int min_distance = dist1[n];

    for (int u = 1; u <= n; ++u)
    {
        for (auto edge : graph[u])
        {
            int v = edge.to;
            if (dist1[u] != INF && dist2[v] != INF)
            {
                min_distance = std::min(min_distance, dist1[u] + dist2[v]);
            }
            if (dist1[v] != INF && dist2[u] != INF)
            {
                min_distance = std::min(min_distance, dist1[v] + dist2[u]);
            }
        }
    }

    std::cout << min_distance << std::endl;
    return 0;
}
