#include "AdjMatGraph.h" //그래프 클래스 포함
#include <stdio.h>


void main()
{
	int num;
	printf("입력하세요. \n");
	scanf_s("%d", &num);
	if (num == 1) {		//인접행렬
		AdjMatGraph g;	//새로운 그래프 객체 생성

		for (int i = 0; i < 4; i++)
			g.insertVertex('A' + i); //정점 삽입, 'A' 'B', ...
		g.insertEdge(0, 1);
		g.insertEdge(0, 3);
		g.insertEdge(1, 2);
		g.insertEdge(1, 3);
		g.insertEdge(2, 3);
		printf("인접 행렬로 표현한 그래프 \n");
		g.display();
	}
	
	else if (num == 2) {	//인접리스트
		AdjListGraph g;	//새로운 그래프 객체 생성

		for (int i = 0; i < 4; i++)
			g.insertVertex('A' + i); //정점 삽입, 'A' 'B', ...
		g.insertEdge(0, 1); //간선 삽입
		g.insertEdge(0, 3);
		g.insertEdge(1, 2);
		g.insertEdge(1, 3);
		g.insertEdge(2, 3);
		printf("인접 리스트로 표현한 그래프 \n");
		g.display();
	}
	else if (num == 3) {	//깊이 우선 탐색 테스트 프로그램
		SrchAMGraph g; //DFS 탐색 기능 있는 그래프 객체 생성
		//g.load("graph.txt");  //파일 "graph.txt"로부터 g 설정
		//printf("그래프(graph.txt\n");
		//g.display();
		for (int i = 0; i < 4; i++)
			g.insertVertex('A' + i);

		g.insertEdge(0, 1);
		g.insertEdge(0, 3);
		g.insertEdge(1, 2);
		g.insertEdge(1, 3);
		g.insertEdge(2, 3);

		printf("DFS ==> "); 
		g.resetVisited();	//모든 정점을 방문하지 않았다고 하고
		g.DFS(0);	//0번째 정점(A)에서 깊이 우선 탐색 시작
		printf("\n");

		printf("BFS ==> ");
		g.resetVisited();
		g.BFS(0);
		printf("\n");

	}

	else if (num == 4) {		//kruskal 알고리즘
		
		WGraphMST g;
		g.load("graph.txt");
		printf("MST By Kruskal's Algorithm\n");
		g.display();
		g.Kruskal();	
	}

	else if (num == 5) {	//Prim 알고리즘
		WGraphMST g;
		g.load("graph.txt");
		printf("MST By Prim's Algorithm\n");
		g.display();
		g.Prim(0);
	}

	else if (num == 6) {

		WGraphDijkstra g;
		g.load("graph.txt");
		printf("Shortest Path By Dijkstra Algorithm\n");
		g.ShortestPath(0);
	}

	
}