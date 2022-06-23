#ifndef AL_H
#define AL_H
#include"GRAF.h"
#include<vector>

void topsort()
{
    int n, m;
    cout << "请输入顶点数和边数: ";
    cin >> n >> m;
    vector<vector<int> > v, vr;
    vector<int> b;
    for (int i = 0; i < m; i++)
    {
        int  begin, end, weight = 0;
        cin >> begin >> end;
        b.push_back(begin);
        b.push_back(end);
        b.push_back(weight);
        v.push_back(b);
        b.clear();
    }
    GRAF g(v, n, m);
    g.topsort();
}

void Dijkstra()
{
    int n, m, start;
    cout << "请输入顶点数和边数: ";
    cin >> n >> m;
    vector<vector<int> > v, vr;
    vector<int> b;
    for (int i = 0; i < m; i++)
    {
        int  begin, end, weight = 0;
        cin >> begin >> end >> weight;
        b.push_back(begin);
        b.push_back(end);
        b.push_back(weight);
        v.push_back(b);
        b.clear();
    }
    cout << "请输入源节点: ";
    cin >> start;
    GRAF g(v, n, m);
    g.Dijkstra(start);
}

void prim()
{
    int n, m;
    cout << "请输入顶点数和边数: ";
    cin >> n >> m;
    vector<vector<int> > v, vr;
    vector<int> b;
    for (int i = 0; i < m; i++)
    {
        int  begin, end, weight;
        cin >> begin >> end >> weight;
        b.push_back(begin);
        b.push_back(end);
        b.push_back(weight);
        v.push_back(b);
        b.clear();
        b.push_back(end);
        b.push_back(begin);
        b.push_back(weight);
        v.push_back(b);
        b.clear();
    }
    GRAF g(v, n, m);
    g.prim();
}

void maxflow()
{
    int n, m;
    cout << "请输入顶点数和边数: ";
    cin >> n >> m;
    vector<vector<int> > v;
    vector<int> b;
    for (int i = 0; i < m; i++)
    {
        int  begin, end, weight;
        cin >> begin >> end >> weight;
        b.push_back(begin);
        b.push_back(end);
        b.push_back(weight);
        v.push_back(b);
        b.clear();
        b.push_back(end);
        b.push_back(begin);
        b.push_back(0);
        v.push_back(b);
        b.clear();
    }
    GRAF g(v, n, m);
    g.maxflow();
}

void findArt()
{
    int n, m;
    cout << "请输入顶点数和边数: ";
    cin >> n >> m;
    vector<vector<int> > v;
    vector<int> b;
    for (int i = 0; i < m; i++)
    {
        int  begin, end, weight;
        cin >> begin >> end;
        b.push_back(begin);
        b.push_back(end);
        b.push_back(weight);
        v.push_back(b);
        b.clear();
        b.push_back(end);
        b.push_back(begin);
        b.push_back(0);
        v.push_back(b);
        b.clear();
    }
    GRAF g(v, n, m);
    g.findArt();
}

void strong_connect()
{
    int n, m;
    cout << "请输入顶点数和边数: ";
    cin >> n >> m;
    vector<vector<int> > v,vr;
    vector<int> b;
    for (int i = 0; i < m; i++)
    {
        int  begin, end, weight=0;
        cin >> begin >> end;
        b.push_back(begin);
        b.push_back(end);
        b.push_back(weight);
        v.push_back(b);
        b.clear();
    }
    GRAF g(v, n, m);
    g.strong_connect();
}

void euler()
{
    int n, m;
    cout << "请输入顶点数和边数: ";
    cin >> n >> m;
    vector<vector<int> > v;
    vector<int> b, path;
    for (int i = 0; i < m; i++)
    {
        int  begin, end, weight=0;
        cin >> begin >> end;
        b.push_back(begin);
        b.push_back(end);
        b.push_back(weight);
        v.push_back(b);
        b.clear();
        b.push_back(end);
        b.push_back(begin);
        b.push_back(0);
        v.push_back(b);
        b.clear();
    }
    GRAF g(v, n, m);
    g.euler();
}
#endif // !AL_H



