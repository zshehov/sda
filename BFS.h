//implementation of bfs with a fixed size graph
#ifndef _BFS
#define _BFS

#include<queue>
#define SIZE 4

void BFS(int (&matrix)[SIZE][SIZE], int start) {

	bool checked[SIZE];

	for (size_t i = 0; i < SIZE; ++i) 
		checked[i] = false;

	std::queue<int> q;

	//initiate with the start element
	checked[start] = true;
	q.push(start);

	//go through the graph
	while (!q.empty()) {
		int current = q.front();

		for (size_t i = 0; i < SIZE; ++i) {
			if (!checked[i] && matrix[current][i] != 0) {
				q.push(i);
				checked[i] = true;
			}
		}

		q.pop();
	}
}
#endif // !_BFS
