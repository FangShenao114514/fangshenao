#include<stdio.h>
#include<iostream>
using namespace std;
int w[10];
typedef struct vnode {     //顶点
	char data;
	struct anode* first;
}vnode, adjlist[100];
typedef struct anode {    //边节点 
	int adj;
	struct anode* next;
}anode;
typedef struct    //图结构体
{
	adjlist ver;
	int num1, num2;
}def;
int locate(def g, char x)//查找节点下标
{
	int i;
	for (i = 0; i < g.num1; i++)
	{
		if (x == g.ver[i].data)
			break;
	}
	return i;
}
void cre(def& g)  //建立图，以邻接表存储
{
	int a, b, i, j, x, y;
	char m, n;
	anode* p1 = NULL, * p2 = NULL;
	cout << "请输入图的结点个数与边的个数：" << endl;
	cin >> a >> b;
	g.num1 = a;
	g.num2 = b;
	cout << "请输入顶点信息：(以空格分开)" << endl;
	for (i = 0; i < a; i++)
	{
		cin >> g.ver[i].data;
		g.ver[i].first = NULL;
	}
	cout << endl;
	for (int i = 0; i < b; i++)
	{
		cout << "请输入边的序偶对：形如 a b" << endl;
		cin >> m >> n;
		x = locate(g, m);
		y = locate(g, n);
		p1 = new anode;
		p1->adj = y;
		p1->next = g.ver[x].first;
		g.ver[x].first = p1;
		p2 = new anode;
		p2->adj = x;
		p2->next = g.ver[y].first;
		g.ver[y].first = p2;
	}
}
int firstnode(def g, int r) //下标为r的点的邻接点的下标
{
	if (g.ver[r].first)
		return g.ver[r].first->adj;
	else
		return -1;
}
int nextnode(def g, int r, int h) {
	int flag = 0;
	anode* p = NULL;
	p = g.ver[r].first;
	while (p)
	{
		if (p->adj == h)
		{
			flag = 1;
			break;
		}
		p = p->next;
	}
	if (flag && p->next)
		return p->next->adj;
	else
		return -1;
}
void BFS(def g, int u) {    //广度优先遍历
	int qu[20], front, rear;
	int k;
	rear = front = 0;
	anode* p = NULL;
	cout << g.ver[u].data << " ";
	w[u] = 1;
	rear = (rear + 1) % 20;
	qu[rear] = u;
	while (rear != front)
	{
		front = (front + 1) % 20;
		k = qu[front];
		p = g.ver[k].first;
		while (p)
		{
			if (w[p->adj] == 0)
			{
				cout << g.ver[p->adj].data << " ";
				w[p->adj] = 1;
				rear = (rear + 1) % 20;
				qu[rear] = p->adj;
			}
			p = p->next;
		}
	}

}
void BFStree(def g, int u) {    //输出广度优先遍历的生成树的边集
	int qu[20], front, rear;
	int k;
	rear = front = 0;
	anode* p = NULL;
	w[u] = 0;
	rear = (rear + 1) % 20;
	qu[rear] = u;
	while (rear != front)
	{
		front = (front + 1) % 20;
		k = qu[front];
		p = g.ver[k].first;
		while (p)
		{
			if (w[p->adj] == 1)
			{
				cout << "(" << g.ver[k].data << "," << g.ver[p->adj].data << ")" << " ";
				w[p->adj] = 0;
				rear = (rear + 1) % 20;
				qu[rear] = p->adj;
			}
			p = p->next;
		}
	}

}
void DFS(def g, int u)  //深度优先遍历
{
	int h;
	w[u] = 1;
	cout << g.ver[u].data << " ";
	for (h = firstnode(g, u); h >= 0; h = nextnode(g, u, h))
		if (!w[h])
			DFS(g, h);
}
void DFStree(def g, int u)   //输出深度优先遍历的生成树的边集
{
	anode* p = NULL;
	w[u] = 0;
	p = g.ver[u].first;
	while (p)
	{
		if (w[p->adj] == 1)
		{
			cout << "(" << g.ver[u].data << "," << g.ver[p->adj].data << ")" << " ";
			DFStree(g, p->adj);
		}
		p = p->next;
	}
}
int main()
{
	int i, u;
	char r;
	for (i = 0; i < 10; i++)
		w[i] = 0;
	def g;
	cre(g);
	cout << "输入起始点：" << endl;
	cin >> r;
	u = locate(g, r);
	cout << "深度优先遍历序列：" << endl;
	DFS(g, u);
	cout << endl << "深度优先遍历生成树边集：" << endl;
	DFStree(g, u);
	cout << endl << "广度优先遍历序列：" << endl;
	BFS(g, u);
	cout << endl << "广度优先遍历生成树边集：" << endl;
	BFStree(g, u);
	return 0;
}