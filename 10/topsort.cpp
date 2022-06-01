#include<vector>
#include<queue>
#include<iostream>

using namespace std;
const int N = 100010;
vector<vector<int>>edges;//邻接表存储图
int indges[N];//每个点的入度
vector<int>ans;//答案存储点的序列
int main()
{

    int n, m; //指点的个数和边的条数
    cin >> n >> m;
    edges.resize(n + 1);
    int x, y;
    queue<int>que;
    for (int i = 0; i < m; i++)
    {
        cin >> x >> y;
        edges[x].push_back(y);
        indges[y]++;
    }
    for (int i = 1; i <= n; i++)
    {
        if (indges[i] == 0)
        {
            que.push(i);
        }
    }
    while (que.size())
    {
        auto u = que.front();
        que.pop();
        ans.push_back(u);
        indges[u]--;  //去除一个点，其入度不能为0了
        for (auto& v : edges[u])
        {
            indges[v]--;
            if (indges[v] == 0)
            {
                que.push(v);
            }
        }
    }
    if (ans.size() == n)
    {
        for (auto& num : ans)cout << num << " ";
    }
    else cout << -1 << endl;

    return 0;
}
