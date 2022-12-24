#include "MGraph.h"
#include <vector>

MGraph::MGraph(int n)
{
	if (n < 0) {
		n = 0;
	}
	this->n = n;
	this->matrix = new int* [n];
	for (int i = 0; i < n; i++) {
		matrix[i] = new int[n];
	}
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			matrix[i][j] = 0;
		}
	}

}

MGraph::~MGraph()
{
	for (int i = 0; i < n; i++) {
		delete matrix[i];
	}
	delete[]matrix;
}

bool MGraph::addEdge(int from_p, int to_p, int length, int directions)
{
	if (length < 1 or from_p > n or from_p < 1 or to_p > n or to_p < 1) {
		return false;
	}
	matrix[from_p - 1][to_p - 1] = length;
	if (directions == 2) {
		matrix[to_p - 1][from_p - 1] = length;
	}
	return true;
}

void MGraph::printChainsAB(int init_node, int fin_node, vector<int> path, int *nodes) {
	nodes[init_node] = 1;
	path.push_back(init_node + 1);
	if (init_node == fin_node)
	{
		//путь найден, печатаем и возвращаемся.        
		cout << "---> ";
		for (int i = 0; i < path.size(); i++) {
			cout << " " << path[i];
		}
		this->all_paths.push_back(path);
		cout << endl;
		return;
	}
	
	//рекурсивно продолжаем поиск для дочерних нод 
	for (int i = 0; i < n; i++) {
		int* curnodes = new int[n];
		for (int j = 0; j < n; j++) {
			curnodes[j] = nodes[j];
		}
		if (matrix[init_node][i] != 0 && init_node != i && nodes[i] == 0) {
			printChainsAB(i, fin_node, path, curnodes);
			
		}
	}
}


//выводит все цепочки в графе, используя метод поиска в глубину
void MGraph::printChains() {
	all_paths.clear();
	int* nodes = new int[n];
	for (int i = 0; i < n; i++) {
		nodes[i] = 0;
	}
	//i - точка старта
	vector<int> startS;
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			for (int k = 0; k < n; k++) {
				nodes[k] = 0;
			}
			if (i != j) {
				printChainsAB(i, j, startS, nodes);
			}
		}
	}
}

//выводит кратчайший путь в графе методом «Построения дерева решений»
void MGraph::printShortest(int p1, int p2) {
	vector<int> tmp, tmp1;
	int min = pow(2, 16) - 1;
	for (auto k = 0; k < this->all_paths.size(); ++k) {
		if (this->all_paths[k][0] == p1 && this->all_paths[k][this->all_paths[k].size() - 1] == p2) {
			tmp = this->all_paths[k];
			int k = 0;
			for (auto d = 0; d < tmp.size() - 1; ++d) {
				k += (this->matrix[tmp[d] - 1][tmp[d + 1] - 1]);
			}
			if (k <= min) {
				tmp1 = tmp;
				min = k;
			}
		}
	}
	if (min != pow(2, 16) - 1) {
		cout << "---> ";
		for (auto i : tmp1) {
			std::cout << i << " ";
		}
		std::cout << "(length = " << min << ")\n";
	}
	else {
		cout << "no path " << p1 << " -> " << p2 << "\n";
	}
	min = pow(2, 16) - 1;
}

//выводит матрицу смежности
void MGraph::printGraph() {
	if (n == 0) {
		cout << "empty\n";
		return;
	}
	else if (n > 10) {
		cout << "graph is too big\n";
		return;
	}
	cout << "to\\from\t|\t";
	for (int i = 0; i < n; i++) {
		cout << i + 1 << "\t";
	}
	cout << "\n_";
	for (int i = -1; i < n; i++) {
		cout << "________";
	}
	cout << "\n";
	for (int y = 0; y < n; y++) {
		cout << y + 1 << "\t|\t";
		for (int x = 0; x < n; x++) {
			if (matrix[x][y] != 0) {
				cout << matrix[x][y];
			}
			else
			{
				cout << " ";
			}
			cout << "\t";
		}
		cout << "\n";
	}
}

//тестирование функций
void MGraph::test() {
	int task;
	cout << "How many points? ";
	cin >> task;
	MGraph g(task);
	task = 1;
	int data1, data2, data3, data4;
	cout << "Choose task:";
	while (task < 6 and task > 0) {
		cout << "\n1) Print graph\n2) Add edge\n3) Print all chains\n4) Find shortest way\n5) Fill random\n> ";
		cin >> task;
		switch (task)
		{
		case 1:
			g.printGraph();
			cout << "---completed---\n";
			break;
		case 2:
			cout << "point1 point2 length: ";
			cin >> data1 >> data2 >> data3;
			cout << "directions (1/2): ";
			cin >> data4;
			if (g.addEdge(data1, data2, data3, data4)) {
				cout << "---added---\n";
			}
			else {
				cout << "---wrong input---\n";
			}
			break;
		case 3:
			g.printChains();
			cout << "---completed---\n";
			break;
		case 4:
			cout << "point1 point2: ";
			cin >> data1 >> data2;
			g.printShortest(data1, data2);
			cout << "---completed---\n";
			break;
		case 5:
			for (int i = 0; i < g.getN(); i++) {
				for (int j = 0; j < g.getN(); j++) {
					if (rand() % 2 != 0) {
						if (i != j) {
							g.addEdge(i + 1, j + 1, rand() % 100, rand() % 10);
						}
						
					}
				}
				
			}
			cout << "---filled---\n";
			break;
		default:
			break;
		}
	}
	cout << "---exit---\n";
}
