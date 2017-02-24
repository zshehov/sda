#ifndef _DIJKSTRA
#define _DIJKSTRA

//performs dijkstra's algorithm for an adjacency matrix graph with a fixed size
//this implementation can print the shortest path from source to the other vertices
//only works for connected graphs
//prim's algorithm for MST is two steps away from here

#include<iostream>
#include<climits>

#define SIZE 9
//find the next lowest up to now that hasn't been marked as ready
int findLowest(int* result, bool* done) {
	int min = INT_MAX;
	int minIndex = -1;
	for (size_t lowest = 0; lowest < SIZE; ++lowest) {
		if (result[lowest] <= min && !done[lowest]) {
			min = result[lowest];
			minIndex = lowest;
		}
	}
	if (minIndex != -1)
		done[minIndex] = true;

	return minIndex;
}

void dijkstra(int (&graph)[SIZE][SIZE], int source) {
	int result[SIZE];
	int path[SIZE];
	bool done[SIZE];


	for (size_t i = 0; i < SIZE; ++i) {
		result[i] = INT_MAX;
		done[i] = false;
	}

	result[source] = 0;
	path[source] = source;

	int s = findLowest(result, done);

	while (s != -1) {
		for (size_t i = 0; i < SIZE; ++i) {
			int potential = result[s] + graph[s][i];
			if (graph[s][i] && (result[i] > potential) && !done[i]) {
				result[i] = potential;
				path[i] = s;
			}
		}
		s = findLowest(result, done);
	}
	

	for (size_t i = 0; i < SIZE; ++i) {
		printf("Distance from %d to %d is %d\n", source, i, result[i]);
	}

	//prints shortest paths from source
	for (size_t i = 0; i < SIZE; ++i) {
		int j = i;
		printf("%d", i);
		while (j != source) {
			printf("<- %d", path[j]);
			j = path[j];
		}

		printf("\n");
	}
}

#endif //!_DIJKSTRA
