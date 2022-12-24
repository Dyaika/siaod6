#ifndef __MGRAPH_H
#define __MGRAPH_H
#include <iostream>
#include <string>
#include <random>
#include <vector>
#include <set>
using namespace std;
class MGraph
{
private:
	int n;
	int **matrix;
	vector<vector<int>> all_paths;
	void printChainsAB(int init_node, int fin_node, vector<int> path, int *nodes);
public:
	struct MyStack
	{
	private:
		struct Node {
			Node* prev = nullptr;
			int data = 0;
		};
		Node* top = nullptr;
		bool isEmpty() {
			return top == nullptr;
		}
		void push(int d) {
			Node* temp = new Node();
			temp->data = d;
			temp->prev = top;
			top = temp;
		}
		int pop() {
			int res = -1;
			if (top) {
				res = top->data;
				Node* temp = top;
				top = top->prev;
				delete temp;
			}
			return res;
		}
	};
	MGraph(int n = 0);
	~MGraph();

	//возвращает количество точек
	int getN() {
		return n;
	}
	//добавляет ребро
	bool addEdge(int from_p, int to_p, int length, int directions = 1);

	//выводит все цепочки в графе, используя метод поиска в глубину
	void printChains();

	//выводит кратчайший путь в графе методом «Построения дерева решений»
	void printShortest(int p1, int p2);

	//выводит матрицу смежности
	void printGraph();

	//тестирование функций
	static void test();

};
#endif // !__MGRAPH_H



