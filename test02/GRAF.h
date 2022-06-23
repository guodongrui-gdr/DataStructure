#ifndef GRAF_H
#define GRAF_H
#include <iostream>
#include<queue>
#include<vector>
using namespace std;

struct ARC { //定义边
    int from;     // 边的起点
    int to;       // 边的终点
    int weight;   // 边的权值
    bool visited; // 是否被访问
};
struct VTX { // 定义顶点
    int nodeName; // 顶点信息
    int inDegree; // 入度
    int outDegree;// 出度
    bool visited; // 是否被访问
    int num;      // 编号
    int low;      // 割点计算算法中点能到达的最低顶点的编号
    int dis;      // 单源最短路算法中顶点与源点的距离
    VTX* parent;  // 父节点
};

class GRAF {
private:  
    int nodenum;
    int arcnum;
    int count = 1;
    ARC arc_list[401];// 边集
    VTX vtx_list[101];// 顶点集

    // 查找start, end之间是否有边,若有则返回边在边集中的索引
    int findarc(int start, int end)
    {
        for (int i = 1; i <= 2 * arcnum; i++)
        {
            if (arc_list[i].from == start && arc_list[i].to == end)
                return i;
        }
        return 0;
    }

    // 将图中各种属性重置
    void reset()
    {
        for (int i = 1; i <= nodenum; i++)
        {
            vtx_list[i].low = 0;
            vtx_list[i].num = 0;
            vtx_list[i].visited = false;
        }
        for (int i = 0; i < arcnum; i++)
        {
            arc_list[i].visited = false;
        }
    }
    // 排序
    //const int & median3(int left, int right)
    //{
    //    int center = (left + right) / 2;
    //    if (arc_list[center].weight < arc_list[left].weight)
    //        std::swap(arc_list[left], arc_list[center]);
    //    if (arc_list[right].weight < arc_list[left].weight)
    //        std::swap(arc_list[left], arc_list[left]);
    //    if (arc_list[right].weight < arc_list[center].weight)
    //        std::swap(arc_list[center], arc_list[right]);
    //    std::swap(arc_list[center], arc_list[right - 1]);
    //    return arc_list[right - 1].weight;
    //}

    //void quicksort(int left, int right)
    //{
    //    if (left >= right) return;
    //    int pivot = median3(left, right);
    //    int i = left - 1, j = right + 1;
    //    int x = arc_list[left + right >> 1].weight;
    //    while (i < j)
    //    {
    //        do i++; while (arc_list[i].weight < x);
    //        do j--; while (arc_list[j].weight > x);
    //        if (i < j) swap(arc_list[i], arc_list[j]);
    //    }
    //    quicksort(left, j);
    //    quicksort(j + 1, right);
    //}

    // 广度优先搜索
    int BFS(int start, int end, int pre[])
    {
#define maxn 0x7fffffff
        queue<int> myqueue;
        int flow[100];
        while (!myqueue.empty())  //队列清空
            myqueue.pop();
        for (int i = 1; i <= nodenum; ++i) {
            pre[i] = -1;
        }
        flow[start] = maxn;
        myqueue.push(start);
        while (!myqueue.empty()) {
            int index = myqueue.front();
            myqueue.pop();
            if (index == end)  //找到了增广路径
                break;
            for (int i = index + 1; i <= nodenum; ++i) {
                if (pre[i] == -1 && arc_list[findarc(index, i)].weight > 0)
                {
                    pre[i] = index;
                    flow[i] = min(arc_list[findarc(index, i)].weight, flow[index]);  //关键：迭代的找到增量
                    myqueue.push(i);
                }
            }
        }
        if (pre[end] == -1)  //残留图中不再存在增广路径
            return -1;
        else
            return flow[end];
    }

    // 深度优先搜索(先序遍历)
    void DFS_pre(int start, vector<int>& path)
    {
        vtx_list[start].visited = true;
        path.push_back(start);
        for (int i = 1; i <= nodenum; i++)
        {
            if (!vtx_list[i].visited && findarc(start, i))
            {
                DFS_pre(i, path);
            }
        }
    }

    // 深度优先搜索(后序遍历)
    void DFS_post(int start, vector<int>& path)
    {
        vtx_list[start].visited = true;
        for (int i = 1; i <= nodenum; i++)
        {
            if (!vtx_list[i].visited && findarc(start,i))
            {
                DFS_post(i, path);
            }
        }
        path.push_back(start);
    }

    void printPath(int v)
    {       
        if (vtx_list[v].parent != NULL)
        {
            printPath(vtx_list[v].parent->nodeName);
        }
        cout << v << " ";   
    }

    // 寻找割点
    void findArt(VTX& v,vector<int>& result)
    {
        v.visited = true;
        v.low = v.num = count++;
        
        for (int i = 1; i <= nodenum; i++)
        {   
            VTX* w = new VTX;
            if (findarc(v.nodeName, i))
            {
                w = &vtx_list[i];
            }
            if (w->nodeName > 0)
            {
                if (!w->visited)
                {
                    w->parent = &v;
                    findArt(*w, result);
                    if (v.nodeName!=1 && w->low >= v.num)
                        result.push_back(v.nodeName);
                    v.low = min(v.low, w->low);
                }
                else
                    if (v.parent!=NULL && v.parent->nodeName != w->nodeName)
                        v.low = min(v.low, w->num);
            }
        }
    }

    // 欧拉回路
    void euler(int start, vector<int>& path)
    {
        path.push_back(start);
        {
            for (int i = 1; i <= nodenum; i++)
            {
                if (findarc(start, i) && !arc_list[findarc(start, i)].visited)
                {
                    arc_list[findarc(start, i)].visited = true;
                    arc_list[findarc(i, start)].visited = true;
                    euler(i, path);
                }
            }
        }
    }


public:
    GRAF(vector<vector<int> >& vt,int nodeNum, int arcNum) {
        nodenum = nodeNum;
        arcnum = arcNum;
        for (int i = 1; i <= nodeNum; i++) {
            vtx_list[i].nodeName = i;
            vtx_list[i].inDegree = 0;
            vtx_list[i].outDegree = 0;
            vtx_list[i].visited = 0;
            vtx_list[i].num = 0;
            vtx_list[i].low = 0;
            vtx_list[i].parent = NULL;
        }

        for (int i = 0; i< vt.size(); i++)
        {
            ARC edge;
            edge.from = vt[i][0] ;
            edge.to = vt[i][1];
            edge.weight = vt[i][2];
            edge.visited = false;
            ++vtx_list[vt[i][0]].outDegree;// 出度加1
            ++vtx_list[vt[i][1]].inDegree; // 入度加1
            //插入链接表的第一个位置
            arc_list[i+1] = edge;
        }
    }
    ~GRAF() {}
    int vnum(){
        return nodenum;
    }
    int anum() {
        return arcnum;
    }
    bool empty() {
        return (nodenum==0);
    }
    // 打印有向图
    void printDGraph() 
    {
        for (int i = 0; i < nodenum; i++) 
        {

            cout << "结点v" << vtx_list[i].nodeName << "的入度为";
            cout << vtx_list[i].inDegree <<",出度为"<< vtx_list[i].outDegree<<",以它为起始顶点的边为:";
            for(int j=0;j< nodenum;j++)
            { 
                if (arc_list[j].from == vtx_list[i].nodeName)
                {
                    cout << "(" << arc_list[j].from << "," << arc_list[j].to << "),权:" << arc_list[j].weight << "   ";
                }
            }
            cout << endl;
        }
    }

    // 打印无向图
    void printUGraph()
    {
        for (int i = 0; i < nodenum; i++)
        {
            cout << "结点v" << vtx_list[i].nodeName << "的度数为";
            cout << (vtx_list[i].inDegree + vtx_list[i].outDegree)/2 << ",以它为起始顶点的边为: ";
            for (int j = 0; j < nodenum; j++)
            {
                if (arc_list[j].from == vtx_list[i].nodeName)
                {
                    cout << "(" << arc_list[j].from << "," << arc_list[j].to << "),权:" << arc_list[j].weight << "   ";
                }
            }
            cout << endl;
        }
    }

    //  拓扑排序算法       - Topological sort algorithm
    void topsort()
    {
        VTX v_list[100];
        for (int i = 1; i <= nodenum; i++)
        {
            v_list[i] = vtx_list[i];
        }
        queue<VTX> q;
        int count = 0;
        while (!q.empty())
        {
            q.pop();
        }
        for (int i = 1; i <= nodenum; i++)
        {
            if (v_list[i].inDegree == 0)
                q.push(v_list[i]);
        }
        while (!q.empty())
        {
            VTX v = q.front();
            cout << v.nodeName<<" ";
            q.pop();
            vtx_list[v.nodeName].num = ++count;
            for (int j = 1; j <= nodenum; j++)
            {
                if (findarc(v.nodeName, j))
                {
                    if (--v_list[j].inDegree == 0)
                        q.push(v_list[j]);
                }
            }
        }
    }

    // 单源最短路算法     - Dijkstra algorithm
    void Dijkstra(int start)
    {
        int mindis = 10000;
        for (int i = 1; i <= nodenum; i++)
        {
            vtx_list[i].dis = mindis;
        }
        vtx_list[start].dis = 0;
        for (int i = 1; i <= nodenum; i++)
        {
            if (!vtx_list[i].visited && vtx_list[i].dis < mindis)
            {
                
                vtx_list[i].visited = true;
                for(int j=1;j<=nodenum;j++)
                { 
                    if (findarc(i, j) && !vtx_list[j].visited)
                    {   
                        
                        int cvw = arc_list[findarc(i, j)].weight;
                        if (vtx_list[i].dis + cvw < vtx_list[j].dis)
                        {
                            vtx_list[j].dis = vtx_list[i].dis + cvw;
                            vtx_list[j].parent = &vtx_list[i];
                        }
                    }
                }
            }
        }
        for (int i = 1; i <= nodenum; i++)
        {
            cout << i << " " << vtx_list[i].dis << " ";
            if(i!=start)
                printPath(i);
            cout << endl;
        }
    }

    // 最小生成树算法     - Prim algorithm
    void prim()
    {
        int mindis = 10000, weight = 0;
        VTX* next = &vtx_list[1];
        for (int i = 0; i <= nodenum; i++)
        {
            vtx_list[i].dis = mindis;
        }
        vtx_list[1].dis = 0;
        while (next!=NULL)
        {
            if (!next->visited && next->dis < mindis)
            {
                next->visited = true;
                int minidx = 0;
                for (int j = 1; j <= nodenum; j++)
                {
                    int arc = findarc(next->nodeName, j);
                    if (arc && !vtx_list[j].visited)
                    {
                        int cvw = arc_list[arc].weight;
                        if (cvw < vtx_list[j].dis)
                        {
                            vtx_list[j].dis = cvw;
                            vtx_list[j].parent = next;
                        }
                    }
                    if (vtx_list[j].dis < vtx_list[minidx].dis && !vtx_list[j].visited)
                        minidx = j;
                }
                next = &vtx_list[minidx];
            }
            else
                next = NULL;
        }
        for (int i = 1; i <= nodenum; i++)
        {
            if (vtx_list[i].parent != NULL)
            {
                weight += arc_list[findarc(vtx_list[i].parent->nodeName, i)].weight;
            }
        }
        cout << weight << endl;
        for (int i = 1; i <= nodenum; i++)
        {
            if (vtx_list[i].parent != NULL)
            {
                cout << vtx_list[i].parent->nodeName << " " << vtx_list[i].nodeName << endl;
            }
        }
    }
    // 最大流增广路径算法 - Maximium flow (Augmented path) algorithm
    void maxflow()
    {
        int increasement = 0;
        int sumflow = 0;
        int pre[100];
        while ((increasement = BFS(1, nodenum, pre)) != -1) {
            int k = nodenum;  //利用前驱寻找路径
            while (k != 1) {
                int last = pre[k];
                arc_list[findarc(last, k)].weight -= increasement;  //改变正向边的容量
                arc_list[findarc(k, last)].weight += increasement;  //改变反向边的容量
                k = last;
            }
            sumflow += increasement;
        }
        cout << sumflow << endl;
        for (int i = 1; i <= 2 * arcnum; i++)
        {
            for(int j=i+1;j <= 2 * arcnum;j++)
                if (arc_list[findarc(j, i)].weight >= 0)
                {
                    cout << i << " " << j << " " << arc_list[findarc(j, i)].weight << endl;
                }
        }
    }

    // 割点计算算法       - Articulation finding algorithm
    void findArt()
    {   
        int sz, k=1;
        for (int i = 1; i <= nodenum; i++)
        {
            vector<int> branch;
            DFS_post(i, branch);
            reset();
            if (i == 1)
            {
                sz = branch.size();
                vector<int> result;
                findArt(vtx_list[i], result);
                cout << k << ": " << result.size() << " ";
                for (int i = result.size() - 1; i >= 0; i--)
                {
                    cout << result[i] << " ";
                }
            }
            else if (branch.size() != sz)
            {
                k++;
                vector<int> result;
                findArt(vtx_list[i], result);
                cout << endl<< k << ": " << result.size() << " ";
                for (int i = result.size() - 1; i >= 0; i--)
                {
                    cout << result[i] << " ";
                }
            }
            reset();
        }
    }

    // 强连通分支算法     - Strong Connected Component algorithm
    void strong_connect()
    {
        vector<int> path, result;
        for (int i = 1; i <= nodenum; i++)
        {
            if (!vtx_list[i].visited)
            {
                DFS_post(i,path);
            }
        }
        for (int i = 0; i < arcnum; i++)
        {
            swap(arc_list[i].from, arc_list[i].to);
        }
        for (int i = 1; i <= nodenum; i++)
        {
            vtx_list[i].visited = false;
        }
        for (int i = path.size(); i >= 1; i--)
        {   
            vector<int> reversepath;
            if (!vtx_list[path[i - 1]].visited)
            {
                DFS_post(path[i-1],reversepath);
                for (int j = 0; j < reversepath.size(); j++)
                {
                    cout << reversepath[j] << " ";
                }
                cout << endl;
            }
        }
        
    }
    
    // 欧拉回路算法       - Euler circuit algorithm
    void euler()
    {
        int start = 1;
        vector<int> path;
        euler(start, path);

        for (int i = path.size() - 1; i >= 1; i--)
        {
            if (path[i] == start)
            {
                for (int j = 0; j < path.size(); j++)
                {
                    if (path[j] == path.back())
                    {
                        for (int k = 1; k < path.size() - i; k++)
                        {
                            swap(path[i + k], path[j + k]);
                        }
                        break;
                    }
                }
                if (path.back() != start)
                {
                    path.push_back(start);
                    vector<int>::iterator it = path.begin() + i;
                    path.erase(it);
                    break;
                }
            }
        }
        if (path.back() != path.front())
            cout << "不存在欧拉回路";
        else
        {
            for (int i = 0; i < path.size(); i++)
            {
                cout << path[i] << " ";
            }
            cout << endl;
        }
    }
};
#endif // !GRAF_H
