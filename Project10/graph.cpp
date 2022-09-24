#include "graph.h"
#include <iostream>
#include <vector>
#include <queue>
#include <iomanip>

using namespace std;

graph::graph()
{

}

void graph::input()
{ 

    cout << "введите количество вершин ";
    cin >> n;
    cout << "введите матрицу смежности" << endl;
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            cin >> a[i][j];
            if (a[i][j] != 0)
                g[i].push_back(j);
			n_matrix[i][j] = 0;
			componenta[i][j] = 0;
			
        }
    }
   
}
void graph::dfs(int v) {
    used[v] = true;
    comp.push_back(v);
    for (size_t i = 0; i < g[v].size(); ++i) {
        int to = g[v][i];
        if (!used[to])
            dfs(to);
    }
}
void graph::find_comps() {
	cur = 0;
	for (int i = 0; i < n; ++i)
        used[i] = false;
    for (int i = 0; i < n; ++i)
        if (!used[i]) {
            comp.clear();
            dfs(i);
			
			
            cout << "Компонента № " << cur + 1 << ": ";
			for (size_t j = 0; j < comp.size(); ++j)
			{
				cout << ' ' << comp[j] + 1;
				gv[cur].push_back(comp[j]);
				componenta[cur][j] = comp[j] + 1 ;
				
			}
			cout << endl;
			cur++;
		}
	
}

void graph::new_matrix(int in)
{
	for (int i = 0; i < n; i++)
		for (int j = 0; j < n; j++)
			n_matrix[i][j] = 0;

	for (size_t ii = 0; ii < (gv[in].size()); ++ii)
	{
		for (size_t ij = 0; ij < (gv[in].size()) - 1; ++ij)
		{
			for (int i = 0; i < n; i++)
			{
				for (int j = 0; j < n; j++)
				{
					if ((gv[in][ii] == i) && (gv[in][ij] == j) && ((ii) != (ij)))
					{
						n_matrix[i][j] = a[i][j];
						n_matrix[j][i] = a[j][i];
					}
				}
			}
		}
	}
	cout << endl;
	
}


void graph::spanningtree(int ii)
{
	int min = 9999, row = 0, col = 0, index = 0;
	for (int i = 0; i < n; i++)
	{
		mindist[i] = visited[i] = 0;
	}
	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < n; j++)
		{
			if (n_matrix[i][j] < min && n_matrix[i][j] != 0)
			{
				min = n_matrix[i][j];
				row = i;
				col = j;
			}
		}
	}
	visited[row] = 1;
	visited[col] = 1;
	mindist[index++] = min;
	cout << "Компонента № " << ii + 1 << endl;
	cout << "Ребра :" << " Вес ребра" << endl;
	cout << endl << row + 1 << " " << col + 1 << " : " << mindist[index - 1] << endl;

	sumdist += mindist[index - 1];

	 
	for (int i = 0; i < n; i++)
	{
		min = 9999;
		for (int j = 0; j < n; j++)
		{

			if (visited[j] == 1)
			{
				for (int k = 0; k < n; k++)
				{
					if (n_matrix[j][k] < min && n_matrix[j][k] != 0 && visited[k] == 0)
					{
						min = n_matrix[j][k];
						row = j;
						col = k;
					}
				}
			}
		}
		if (min != 9999)
		{
			mindist[index++] = min;
			visited[row] = visited[col] = 1;
			cout << row + 1 << " " << col + 1 << " : " << mindist[index - 1] << endl;
			
			sumdist += mindist[index - 1];
			
		}
	}
	int total = 0;
	cout << endl;

	for (int i = 0; i < n - 1; i++)
	{

		total = total + mindist[i];
	}
	cout << endl << "Общая длина пути   " << total << endl;;

}

void graph::imaginary_edge_matrix()
{
	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < n; j++)
		{
			imiginary_matrix[i][j] = 0;
			imiginary_matrix_flag[i][j] = 0;
		}
	}
	cout << "Введите длины мнимых ребер" << endl;
	cout << "номер вершины : номер вершины = длина ребра" << endl;
	for (int i = 0; i < n; i++)
	{
		for (int j = i + 1; j < n; j++)
		{
			if (a[i][j] == 0 && i != j && imiginary_matrix[j][i] == 0 )
			{
				cout << i + 1 << " : " << j + 1 << " = ";
				imiginary_matrix[i][j] = rand() % 100;
				cout << setw(5) << imiginary_matrix[i][j]  << endl;
				//cin >> imiginary_matrix[i][j];
				imiginary_matrix[j][i] = imiginary_matrix[i][j];
			}
			
		}
	}
}
void graph::unification_comp()
{
	for (int i = 0; i < cur; i++)
	{
		new_matrix(i); // создает отдельную матрицу для каждой компоненты
		spanningtree(i);
	}
}

void graph::finding_the_right_edges()
{
	
	cout << endl;
	for (int i = 0; i < cur; i++)
	{
		for (int l = 0; l < n; l++)
		{
			for (int j = 1; j < cur; j++)
			{
				for (int k = 0; k < n; k++)
				{
					if (componenta[i][l] != 0 && componenta[j][k] != 0 && imiginary_matrix[componenta[i][l] - 1][componenta[j][k] - 1] != 0 && i != j )
					{
						imiginary_matrix_flag[componenta[i][l] - 1][componenta[j][k] - 1] = 1;
						imiginary_matrix_flag[componenta[j][k] - 1][componenta[i][l] - 1] = 1;
					}
				}
			}
		}
	}
}

void graph::min_search()
{
	int cc1 = 0, cc2= 0;
	int min = 9999, row = 0, col = 0, index = 0;
	int comp_flag[10];
	for (int i = 0; i < n; i++)
	{
		mindist_search[i] = visited_search[i] = comp_flag[i] = 0;
	}
	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < n; j++)
		{
			if (imiginary_matrix[i][j] < min && imiginary_matrix_flag[i][j] != 0)
			{
				min = imiginary_matrix[i][j];
				row = i;
				col = j;
				
			}
		}
	}
	visited_search[row] = 1;
	visited_search[col] = 1;
	comp_flag[comp_check2(row)] = 1;
	comp_flag[comp_check2(col)] = 1;
	mindist_search[index++] = min;
	cout << "Для компонент" << endl;
	cout << "Ребра :" << " Длина" << endl;
	cout << endl << row + 1 << " " << col + 1 << " : " << mindist_search[index - 1] << endl;

	for (int i = 0; i < n; i++)
	{
		min = 9999, cc1 = 0, cc2= 0;
		for (int j = 0; j < n; j++)
		{

			if (visited_search[j] == 1)
			{
				cc1= comp_check2(j);

				for (int k = 0; k < n; k++)
				{
					if (imiginary_matrix[j][k] < min && imiginary_matrix_flag[j][k] != 0 && visited_search[k] == 0 && check_comp1(j, k) == 1 && comp_flag[comp_check2(k)] == 0 && imiginary_matrix[j][k] != 0)
					{
						min = imiginary_matrix[j][k];
						row = j;
						col = k;
					}
				}
				for (int k = 0; k < n; k++)
				{
					for (int l = 0; l < n; l++)
					{
						if (imiginary_matrix[componenta[cc1][k] - 1][l] < min && imiginary_matrix_flag[componenta[cc1][k] - 1][l] != 0 && visited_search[l] == 0 && check_comp1(componenta[cc1][k] - 1, l) == 1 && comp_flag[comp_check2(l)] == 0 && imiginary_matrix[componenta[cc1][k] - 1][l] != 0)
						{
							min = imiginary_matrix[componenta[cc1][k] - 1][l];
							row = componenta[cc1][k] - 1;
							col = l;
						}
					}
				}
			}
		}
		if (min != 9999)
		{
			comp_flag[comp_check2(col)] = 1;
			mindist_search[index++] = min;
			visited_search[row] = visited_search[col] = 1;
			cout << row + 1 << " " << col + 1 << " : " << mindist_search[index - 1] << endl;
		}
	}
	int total = 0;
	cout << endl;

	for (int i = 0; i < n - 1; i++)
	{

		total = total + mindist_search[i];
	}
	sumdist += total;
	cout << endl << "Длина пути, соединяющего компоненты связности    "<< total << endl;
	cout << "Длина всего дерева: " << sumdist << endl << endl;

}

int graph::check_comp1(int a, int b)
{
	int aa = 0; int bb = 0;
	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < n; j++)
		{
			if (componenta[i][j] -1  == a)
				aa = i;
			if (componenta[i][j] - 1 == b)
				bb = i;
		}
	}
	if (aa == bb)
		return 0;
	else return 1;
}

int graph::comp_check2(int a)
{
	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < n; j++)
			if (componenta[i][j] - 1 == a)
				return i;
	}
}