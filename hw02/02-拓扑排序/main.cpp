#include <iostream>
#include <vector>
#include <queue>

int main()
{
    int n, m;
    std::cin >> n >> m;

    std::vector<std::vector<int>> graph(n + 1);
    std::vector<int> indegree(n + 1, 0);

    for (int i = 0; i < m; i++)
    {
        int u, v;
        std::cin >> u >> v;
        graph[u].push_back(v);
        indegree[v]++;
    }

    std::queue<int> q;
    for (int i = 1; i <= n; i++)
    {
        if (indegree[i] == 0)
        {
            q.push(i);
        }
    }

    std::vector<int> order;
    while (!q.empty())
    {
        int node = q.front();
        q.pop();
        order.push_back(node);

        for (auto adj : graph[node])
        {
            indegree[adj]--;
            if (indegree[adj] == 0)
            {
                q.push(adj);
            }
        }
    }

    if (order.size() != n)
    {
        std::cout << -1 << std::endl;
    }

    else
    {
        for (auto node : order)
        {
            std::cout << node << ' ';
        }
        std::cout << std::endl;
    }

    return 0;
}
