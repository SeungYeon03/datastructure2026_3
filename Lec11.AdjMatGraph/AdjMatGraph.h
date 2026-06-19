#pragma once
#include <stdio.h>
#include<queue>
#include "VertexSets.h"
#include "HeapNode.h"

#define INF 9999	//값이 9999 이상이면 간선 없음
using namespace std;

#define MAX_VTXS 256

class AdjMatGraph {
protected:
	int size;
	char vertices[MAX_VTXS];
	int adj[MAX_VTXS][MAX_VTXS];
public:
	AdjMatGraph() { reset(); }
	char getVertex(int i) { return vertices[i]; }
	int getEdge(int i, int j) { return adj[i][j]; }
	void setEdge(int i, int j, int val) { adj[i][j] = val; }
	bool isEmpty() { return size == 0; }
	bool isFull() { return size >= MAX_VTXS; }

	//그래프 초기화 -> 공백상태 그래프
	void reset() {
		size = 0;
		for (int i = 0; i < MAX_VTXS; i++)
			for (int j = 0; j < MAX_VTXS; j++)
				setEdge(i, j, 0);
	}
	void insertVertex(char name) {
		if (!isFull()) vertices[size++] = name;
		else printf("Error: 그래프 정점 개수 초과\n");
	}

	//간선 삽입: 무방향 그래프의 경우임
	void insertEdge(int u, int v) {
		setEdge(u, v, 1);
		setEdge(v, u, 1);	//방향 그래프에서는 삭제되고 <u,v>만 존재
	}

	void display(FILE* fp = stdout) {
		fprintf(fp, "%d\n", size);	//정점 개수 출력
		for (int i = 0; i < size; i++) {
			fprintf(fp, "%c", getVertex(i));	//정점 이름 출력
			for (int j = 0; j < size; j++)	//간선 정보 출력
				fprintf(fp, "%3d", getEdge(i, j));
			fprintf(fp, "\n");

		}
	}
};

#include "Node.h" //연결리스트 위한 노드 그래프 클래스 포함
class AdjListGraph {
protected:
	int size; //정점 개수
	char vertices[MAX_VTXS]; //정점 정보 (응용에 따라 확장 필요)
	Node* adj[MAX_VTXS]; //각 정점의 인접 리스트

public:
	AdjListGraph() :size(0) {}
	~AdjListGraph() { reset(); }
	bool isFull() { return size >= MAX_VTXS; }
	char getVertex(int i) { return vertices[i]; }

	void reset(void) {
		for (int i = 0; i < size; i++)
			if (adj[i] != NULL)delete adj[i];
	}
	void insertVertex (char val) { //정점 삽입 연산
		if (!isFull()) {
			vertices[size] = val;
			adj[size++] = NULL;
		}
		else printf("Error:그래프 정점 개수 초과\n");
	}
	void insertEdge(int u, int v) {	//간선 삽입 연산
		adj[u] = new Node(v, adj[u]); //인접 리스트에 추가
		adj[v] = new Node(u, adj[v]); //방향 그래프 ->주석 처리
	}
	void display() {
		printf("%d\n", size); //정점 개수 출력
		for (int i = 0; i < size; i++) {
			printf("%c", getVertex(i)); //정점 이름 출력
			for (Node* v = adj[i]; v != NULL; v = v->getLink())
				printf("%c", getVertex(v->getId()));
			printf("\n");
		}
		
	}
	Node* adjacent(int v) { return adj[v]; }
};


//DFS 구현 (인접 행렬)
//탐색 기능이 추가된 인접 행렬 기반 그래프 클래스
class SrchAMGraph : public AdjMatGraph {
	bool visited[MAX_VTXS]; //정점의 방문 정보
public:
	void resetVisited() {	//모든 정점을 방문하지 않았다고 설정
		for (int i = 0; i < size; i++)
			visited[i] = false;
	}
	bool isLinked(int u, int v) { return getEdge(u, v) != 0; }

	//깊이 우선 탐색 함수
	void DFS(int v) {
		visited[v] = true; // 현재 정점 방문
		printf("%c", getVertex(v)); //정점의 이름 출력
		for (int w = 0; w < size; w++)
			if (isLinked(v, w) && visited[w] == false)
				DFS(w); //연결+방문하지 않았으면 순환호출로 방문
	}
	//BFS 구현 (인접 리스트)
	void BFS(int v)
	{

		visited[v] = true;
		printf("%c" ,getVertex(v));

		queue<int> que;
		que.push(v); //시작 지점 큐에 저장
		while (!que.empty()) {
			int v = que.front();
			que.pop();

			for (int  w = 0; w < size; w++ )
				if (isLinked(v, w) && visited[w] == false) {
					visited[w] = true;
					printf("%c", getVertex(w));
					que.push(w);
				}
		}
		

	}

};

//연결 성분 최대로 연결된 부분 그래프들 구함
class ConnectedComponentGraph : public SrchAMGraph {
	bool visited[MAX_VTXS];
	int label[MAX_VTXS]; //정점의 색상 필드 추가
public:
	void labelDFS(int v, int color) {
		visited[v] = true; //현재 정점 방문
		label[v] = color; //현재 정점 색상
		for (int w = 0; w < size; w++)
			if (isLinked(v, w) && visited[w] == false)
				labelDFS(w, color);
	}
	void findConnectedComponent() {
		int count = 0;
		for (int i = 0; i < size; i++)
			if (visited[i] == false)
				labelDFS(i, ++count);
		printf("그래프 연결성분 개수 == %d\n", count);
		for (int i = 0; i < size; i++)
			printf("%c=%d", getVertex(i), label[i]);
		printf("\n");
	}
};

//가중치 그래프 표현하는 클래스
class WGraph : public AdjMatGraph {
public:
	void insertEdge(int u, int v, int weight) {
	if (weight > INF) weight = INF;
	setEdge(u, v, weight);
}
	bool hasEdge(int i, int j) { return(getEdge(i, j) < INF); }

	void load(const char* filename) {
		FILE* fp;
		fopen_s(&fp, filename, "r");
		if (fp != NULL) {
			int n, val;
			fscanf_s(fp, "%d", &n);
			for (int i = 0; i < n; i++) {
				char str[80];
				int val;
				fscanf_s(fp, "%s", str,sizeof(str));
				insertVertex(str[0]);
				for (int j = 0; j < n; j++) {
					fscanf_s(fp, "%d", &val);
					insertEdge(i, j, val);
				}
			}
		}
		fclose(fp);
	}
};

class WGraphMST : public WGraph {
public:
	int getMinVertex(bool* selected, int* dist) {
		int minv = 0;
		int mindist = INF;
		for (int v = 0; v < size; v++)
			if (!selected[v] && dist[v] < mindist) {
				mindist = dist[v];
				minv = v;

			}
		return minv;
	}
	void Kruskal() {		//Kruskal의 최소 비용 신장 트리 프로그램
		MinHeap heap;
		for (int i = 0; i < size - 1; i++)
			for (int j = 0; j < size; j++)
				if (hasEdge(i, j))
					heap.insert(getEdge(i, j), i, j);		//모든 간선 삽입
		VertexSets set(size);	//size개 집합 만듦
		int edgeAccepted = 0;
		while (edgeAccepted < size - 1) {
			HeapNode e = heap.remove();
			int uset = set.findSet(e.getv1());
			int vset = set.findSet(e.getv2());
			if (uset != vset) {
				printf("간선 추가: %c-%c (비용: %d)\n",
					getVertex(e.getv1()), getVertex(e.getv2()), e.getKey());
				set.unionSets(uset, vset); //두개 집합 합함
				edgeAccepted++;
			}
		}
	}

	//Prim MST 구현
	void Prim(int s) {
		bool selected[MAX_VTXS];		//정점이 이미 포함되었는지 확인
		int dist[MAX_VTXS];		//거리
		for (int i = 0; i < size; i++) {		//배열 초기화
			dist[i] = INF;
			selected[i] = false;
		}
		dist[s] = 0;
		for (int i = 0; i < size; i++) {
			int u = getMinVertex(selected, dist);
			selected[u] = true;
			if (dist[u] == INF) return;
			printf("%c", getVertex(u));
			for (int v = 0; v < size; v++)
				if (getEdge(u, v) != INF)
					if (!selected[v] && getEdge(u, v) < dist[v])
						dist[v] = getEdge(u, v);
		}
		printf("\n");
	}
};


//dijkstra 최단 경로 구현
class WGraphDijkstra : public WGraph {
	int dist[MAX_VTXS];			//시작 노드로부터의 최단 경로 거리
	bool found[MAX_VTXS];	//방문한 정점 표시
public:
	int chooseVertex() {
		int min = INF;
		int minpos = -1;
		for(int i=0; i<size; i++)
			if (dist[i] < min && !found[i]) {

				min = dist[i];
				minpos = i;
			}
		return minpos;
	}
	void printDistance() {
		for (int i = 0; i < size; i++)
			printf("%5d", dist[i]);
		printf("\n");
	}

	//최단 경로 알고리즘 : start 정점에서 시작
	void ShortestPath(int start) {
		for (int i = 0; i < size; i++) {
			dist[i] = getEdge(start, i);
			found[i] = false;
		}
		found[start] = true;
		dist[start] = 0;
		for (int i = 0; i < size; i++) {
			printf("Step%2d:", i + 1);
			printDistance();
			int u = chooseVertex();
			found[u] = true;
			for (int w = 0; w < size; w++)
				if (found[w] == false)
					if (dist[u] + getEdge(u, w) < dist[w])
						dist[w] = dist[u] + getEdge(u, w);
		}
	}
};