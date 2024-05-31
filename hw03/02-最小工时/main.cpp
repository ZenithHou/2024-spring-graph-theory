#include <iostream>
#include <vector>
#include <queue>
#include <climits>

using namespace std;

struct Node
{
    int duration;
    vector<int> nextNodes;
};

struct TimeSlot
{
    int EST = 0;
    int LST = INT_MAX;
};

int main()
{
    int n;
    cin >> n;
    vector<Node> nodes(n);
    vector<int> inDegree(n, 0);
    vector<TimeSlot> timeSlots(n);

    for (int i = 0; i < n; ++i)
    {
        int id, duration, cnt;
        cin >> id >> duration >> cnt;
        nodes[id].duration = duration;
        for (int j = 0; j < cnt; ++j)
        {
            int pre;
            cin >> pre;
            nodes[pre].nextNodes.push_back(id);
            inDegree[id]++;
        }
    }

    queue<int> q;
    for (int i = 0; i < n; ++i)
    {
        if (inDegree[i] == 0)
        {
            q.push(i);
            timeSlots[i].EST = 0;
        }
    }
    while (!q.empty())
    {
        int u = q.front();
        q.pop();
        for (int v : nodes[u].nextNodes)
        {
            timeSlots[v].EST = max(timeSlots[v].EST, timeSlots[u].EST + nodes[u].duration);
            if (--inDegree[v] == 0)
            {
                q.push(v);
            }
        }
    }

    // Calculate the total minimum time to complete all tasks
    int totalMinTime = 0;
    for (int i = 0; i < n; ++i)
    {
        totalMinTime = max(totalMinTime, timeSlots[i].EST + nodes[i].duration);
    }
    cout << totalMinTime << endl;

    // Initialize the LST for nodes with no outgoing edges (endpoint nodes)
    for (int i = 0; i < n; ++i)
    {
        if (nodes[i].nextNodes.empty())
        {
            timeSlots[i].LST = totalMinTime - nodes[i].duration;
        }
    }

    // Calculate the in-degrees of the reverse graph
    vector<int> reverseInDegree(n, 0);
    for (int i = 0; i < n; ++i)
    {
        for (int v : nodes[i].nextNodes)
        {
            reverseInDegree[i]++;
        }
    }

    // Reverse topological sort to calculate LST
    queue<int> qReverse;
    for (int i = 0; i < n; ++i)
    {
        if (reverseInDegree[i] == 0)
        {
            qReverse.push(i);
        }
    }
    while (!qReverse.empty())
    {
        int u = qReverse.front();
        qReverse.pop();
        for (int pre = 0; pre < n; ++pre)
        {
            for (int v : nodes[pre].nextNodes)
            {
                if (v == u)
                {
                    timeSlots[pre].LST = min(timeSlots[pre].LST, timeSlots[u].LST - nodes[pre].duration);
                    if (--reverseInDegree[pre] == 0)
                    {
                        qReverse.push(pre);
                    }
                }
            }
        }
    }

    // Output the maximum allowable delay for each node
    for (int i = 0; i < n; ++i)
    {
        cout << timeSlots[i].LST - timeSlots[i].EST << endl;
    }

    return 0;
}
