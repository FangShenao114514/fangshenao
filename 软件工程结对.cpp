#include<iostream>
#include<fstream>
#include<stdio.h>
#include<string>
#include<malloc.h>
#include<stdlib.h>
#define MAX_SIZE 100
using namespace std;
typedef struct BBTreeNode {
	char data[20];
	BBTreeNode* lchild;
	BBTreeNode* rchild;
}BBTreeNode, * BBTree;//二叉排序树
typedef struct StuWorlds {
	char name[20];
	int num;
	BBTree head;
}StuComposition;//学生单词库
typedef struct Class {
	StuComposition* stu;
	int num;
	double** str;
}Class;//单词库集合与不重复度的二维数组
//二叉排序树相关函数
int TreeHeight(BBTree& T);//求深度
void TreeNum(BBTree& T, int& num);
void TreeInsert(BBTree& T, char* world);//插入
bool Search(BBTree& T, char* world);//查找
void newTreeNode(BBTree& T, char* world);
void CompareBBTree(BBTree& T1, BBTree& T2, double& num);//一个树相对另一个树不重复的元素的个数存放到num中
void RR(BBTree& T);
void RL(BBTree& T);
void LL(BBTree& T);
void LR(BBTree& T);
void ShowBBTree(BBTree& T);
//单词库相关函数
bool CreateStuWorlds(StuComposition& stu, char* adress0, char* name);//读取文件创建单词库
void CompareStu(StuComposition& stu1, StuComposition& stu2, double& num);
void ShowStu(StuComposition& stu);
//集合相关函数
bool CreateClass(Class& obj, int n, char** name, char* adress);
void ShowClass(Class& obj);
void ChaChong(Class& obj);//计算不重复度
//其它
char* GetAdress(char* name, char* adress0);//拼地址
int max(int a, int b);
//主函数
int main() {
	system("70");
	char adress[MAX_SIZE];
	char** name;
	int num;
	printf("使用说明:\n");
	printf("1.使用前请将所有作文文件存放于同一目录下\n");
	printf("2.文件格式为txt\n");
	printf("3。若两篇文章单词组中不相同的单词个数不超过5%，则认为两篇文章抄袭\n\n");
	printf("-----------------------------------------------------------------------\n");
	printf("输入存放地址:\n");
	scanf("%s", adress);
	printf("输入学生个数:\n");
	scanf("%d", &num);
	name = (char**)malloc(sizeof(char*) * num);
	printf("依次输入学生姓名（必须为文件名）:\n");
	for (int i = 0; i < num; i++) {
		name[i] = (char*)malloc(sizeof(char) * num);
		scanf("%s", name[i]);
	}
	Class obj;
	if(!CreateClass(obj, num, name, adress))return 0;
	ChaChong(obj);
	ShowClass(obj);
	printf("\n");
	return 0;
}
//函数实现
int TreeHeight(BBTree& T) {
	if (!T)
		return 0;
	else
		return 1 + max(TreeHeight(T->lchild), TreeHeight(T->rchild));
}
void TreeNum(BBTree& T, int& num) {
	if (!T)return;
	num++;
	TreeNum(T->lchild, num);
	TreeNum(T->rchild, num);
}
void newTreeNode(BBTree& T, char*world) {
	T = (BBTreeNode*)malloc(sizeof(BBTreeNode));
	strcpy(T->data, world);
	T->lchild = NULL;
	T->rchild = NULL;
}
void TreeInsert(BBTree& T, char* world) {
	if (!T) { newTreeNode(T, world); }
	else if (strcmp(world, T->data) < 0) { TreeInsert(T->lchild, world); }
	else if (strcmp(world, T->data) > 0) { TreeInsert(T->rchild, world); }
	else if (strcmp(world, T->data) == 0) { return; }
	int balance = TreeHeight(T->rchild) - TreeHeight(T->lchild);
	if (balance > 1) {
		if (strcmp(world, T->rchild->data) > 0) { RR(T); }
		else if (strcmp(world, T->rchild->data) < 0) { RL(T); }
	}
	if (balance < -1) {
		if (strcmp(world, T->lchild->data) < 0) { LL(T); }
		else if (strcmp(world, T->lchild->data) > 0) { LR(T); }
	}
}
void CompareBBTree(BBTree& T1, BBTree& T2, double& num) {
	if (!T1) { return; }
	if (!Search(T2, T1->data)) {
		num++;
	}
	CompareBBTree(T1->lchild, T2, num);
	CompareBBTree(T1->rchild, T2, num);
}
void RR(BBTree& T) {
	BBTreeNode* p1, * p2;
	p1 = T->rchild;
	p2 = T->rchild->lchild;
	p1->lchild = T;
	T->rchild = p2;
	T = p1;
}
void LL(BBTree& T) {
	BBTreeNode* p1, * p2;
	p1 = T->lchild;
	p2 = T->lchild->rchild;
	p1->rchild = T;
	T->lchild = p2;
	T = p1;
}
void LR(BBTree& T) {
	BBTreeNode* p1, * p2, * p3;
	p1 = T->lchild->rchild;
	p2 = p1->lchild;
	p3 = p1->rchild;
	p1->lchild = T->lchild;
	p1->rchild = T;
	T->lchild->rchild = p2;
	T->lchild = p3;
	T = p1;
}
void RL(BBTree& T) {
	BBTreeNode* p1, * p2, * p3;
	p1 = T->rchild->lchild;
	p2 = p1->rchild;
	p3 = p1->lchild;
	p1->rchild = T->rchild;
	p1->lchild = T;
	T->rchild->lchild = p2;
	T->rchild = p3;
	T = p1;
}
void ShowBBTree(BBTree& T) {
	if (!T)return;
	printf("%s ", T->data);
	ShowBBTree(T->lchild);
	ShowBBTree(T->rchild);
}
bool Search(BBTree& T, char* world) {
	if (!T) { return false; }
	else if (strcmp(world, T->data) < 0) { return Search(T->lchild, world); }
	else if (strcmp(world, T->data) > 0) { return Search(T->rchild, world); }
	else if (strcmp(world ,T->data)==0) {  return true; }
}
bool CreateStuWorlds(StuComposition &stu,char* adress0,char*name) {
	strcpy(stu.name, name);
	char* adress = GetAdress(name, adress0);
	ifstream ifs;
	ifs.open(adress, ios::in);
	if (!ifs.is_open()) { printf("文件 %s 打开失败", name); return false; }
	else {
		char world[20];
		while (ifs >> world)
			TreeInsert(stu.head, world);
		stu.num = 0;
		TreeNum(stu.head,stu.num);
		ifs.close();
	}
	return true;
}
void CompareStu(StuComposition& stu1, StuComposition& stu2, double& num) {
	CompareBBTree(stu1.head, stu2.head, num);
}
void ShowStu(StuComposition& stu) {
	printf("%s %d\n", stu.name, stu.num);
	ShowBBTree(stu.head);
	printf("\n");
}
void ChaChong(Class& obj) {
	for (int i = 0; i < obj.num; i++) {
		for (int j = 0; j < obj.num; j++) {
			if (i == j)continue;
			CompareStu(obj.stu[i],obj.stu[j],obj.str[i][j]);
		}
	}
	for (int i = 0; i < obj.num; i++) {
		for (int j = i; j < obj.num; j++) {
			obj.str[i][j] = (obj.str[i][j] + obj.str[j][i]) / (obj.stu[i].num + obj.stu[j].num);
			obj.str[j][i] = obj.str[i][j];
		}
	}
}
bool CreateClass(Class& obj, int n, char** name , char*adress) {
	obj.stu = (StuComposition*)malloc(sizeof(StuComposition)*n);
	obj.num = n;
	for (int i = 0; i < n; i++) {
		obj.stu[i].head = NULL;
		if(!CreateStuWorlds(obj.stu[i], adress, name[i]))return false;
		//ShowStu(obj.stu[i]);
	}
	obj.str = (double**)malloc(sizeof(double*) * obj.num);
	for (int i = 0; i < obj.num; i++) {
		obj.str[i] = (double*)malloc(sizeof(double) * obj.num);
		for (int j = 0; j < obj.num; j++) {
			obj.str[i][j] = 0;
		}
	}
	return true;
}
void ShowClass(Class& obj) {
	printf("抄袭学生如下(为空则没有）：\n");
	for (int i = 0; i < obj.num; i++) {
		for (int j = 0; j < obj.num; j++) {
			if (i == j)continue;
			if (obj.str[i][j] < 0.05) { printf("%s\n", obj.stu[i].name); continue; }
		}
	}
	printf("-----------------------------------------------------------------------\n");
	printf("详细判别如下：\n");
	for (int i = 0; i < obj.num; i++) {
		printf("学生%s\n", obj.stu[i]);
		for (int j = 0; j < obj.num; j++) {
			if (i == j)continue;
			printf("  与学生 %s 不重复度为: %.2lf%% ", obj.stu[j], obj.str[i][j] * 100);
			if (obj.str[i][j] < 0.05) { printf("*抄袭"); }
			printf("\n");
		}
	}
}
int max(int a, int b)
{
	return (a > b) ? a : b;
}
char* GetAdress(char* name, char* adress0) {
	int len = strlen(adress0);
	char* adress = (char*)malloc(sizeof(char) * MAX_SIZE);
	strcpy(adress, adress0);
	strcat(adress, "\\");
	strcat(adress, name);
	strcat(adress, ".txt");
	return adress;
}
