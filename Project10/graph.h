#pragma once
#include<vector>
using namespace std;


class graph
{
private:
	int a[10][10], b[10][10], n = 0, cur = 0;
	int sumdist= 0;
	vector<int>  g[10];
	vector<int> gv[10]; // ������������ ��� �������� ����� �������
	int n_matrix[10][10]; // // ������� ��������� ��� ��������� (��� �����)
	bool used[10];
	vector<int> comp;
	int visited[100], mindist[100], dist[100], sum; //(��� ��������� �����)
	int visited_search[100], mindist_search[100];
	int imiginary_matrix[10][10]; // ������ �����
	int imiginary_matrix_flag[10][10];
	int componenta[10][10]; // ������� � ���������, ��������� � �����(���� ���������� � 1 )


public:
	void input();
	graph();
	void dfs(int v);
	void find_comps();
	void new_matrix(int in);
	void spanningtree(int ii);
	void imaginary_edge_matrix();
	void unification_comp();
	void finding_the_right_edges();
	void min_search();
	int check_comp1(int a, int b);
	int comp_check2(int a);

};
