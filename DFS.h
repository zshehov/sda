//implementation of non-recursive dfs using stack on a graph with fixed size represented as adjacency matrix
#ifndef _DFS
#define _DFS

#include<stack>
#define SIZE 4

void DFS(int (&graph)[SIZE][SIZE], int start) {

	bool checked[SIZE];

	for (size_t i = 0; i < SIZE; ++i)
		checked[i] = false;

	std::stack<int> s;

	//initiate the stack with the start elment
	s.push(start);
	checked[start] = true;


	while (!s.empty()) {
		int current = s.top();
		checked[current] = true;
		s.pop();

		//push the ajacent nodes that are not yet checked
		for (size_t i = 0; i < SIZE; ++i) {
			if (!checked[i] && graph[current][i] != 0) 
				s.push(i);
			
		}
	}
}

#endif // !_DFS
