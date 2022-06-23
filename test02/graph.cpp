#include"GRAF.h"
#include"al.h"
#include<iostream>
using namespace std;
int main()
{
	int al;
	cout << "请输入你想调用的算法:" << endl;
	cout << "1. 拓扑排序算法      - Topological sort algorithm" << endl
		<< "2. 单源最短路算法     - Dijkstra algorithm" << endl
		<< "3. 最小生成树算法     - Prim algorithm" << endl
		<< "4. 最大流增广路径算法 - Maximium flow (Augmented path) algorithm" << endl
		<< "5. 割点计算算法       - Articulation finding algorithm" << endl
		<< "6. 强连通分支算法     - Strong Connected Component algorithm" << endl
		<< "7. 欧拉回路算法       - Euler circuit algorithm" << endl
		<< "退出请按Enter键" << endl;
	al = cin.get();
	switch (al)
	{
	case 49:
		topsort();
		break;
	case 50:
		Dijkstra();
		break;
	case 51:
		prim();
		break;
	case 52:
		maxflow();
		break;
	case 53:
		findArt();
		break;
	case 54:
		strong_connect();
		break;
	case 55:
		euler();
		break;
	case 10:
		exit(0);
}
}
