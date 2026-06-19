#pragma once
#define MAX_HEAP_NODE 100

//HeapNode.h 힙에 저장할 노드 클래스

class HeapNode {
    int key;    //간선 가중치
    int v1;     // 정점 1
    int v2;     //정점 2

public:
    HeapNode()
        : key(0), v1(0), v2(0) {
    }

    HeapNode(int k, int u, int v)
        : key(k), v1(u), v2(v) {
    }
    void setKey(int k, int u, int v) {
        key = k;
        v1 = u;
        v2 = v;
    }
    int getKey() { return key; }
    int getv1() { return v1; }
    int getv2() { return v2; }
};

class MinHeap {
    HeapNode node[MAX_HEAP_NODE];
    int size;

public:
    MinHeap() {
        size = 0;
    }

    bool isEmpty() {
        return size == 0;
    }

    bool isFull() {
        return size == MAX_HEAP_NODE - 1;
    }

    HeapNode getParent(int i) {
        return node[i / 2];
    }

    HeapNode getLeft(int i) {
        return node[i * 2];
    }

    HeapNode getRight(int i) {
        return node[i * 2 + 1];
    }

    // 삽입
    void insert(int key, int u, int v) {
        if (isFull()) return;

        int i = ++size;

        while (i != 1 &&
            key < getParent(i).getKey()) {
            node[i] = getParent(i);
            i /= 2;
        }

        node[i].setKey(key, u, v);
    }

    // 삭제 (최소값 제거)
    HeapNode remove() {
        HeapNode item = node[1];
        HeapNode temp = node[size--];

        int parent = 1;
        int child = 2;

        while (child <= size) {

            if (child < size &&
                node[child].getKey() >
                node[child + 1].getKey())
                child++;

            if (temp.getKey() <=
                node[child].getKey())
                break;

            node[parent] = node[child];

            parent = child;
            child *= 2;
        }

        node[parent] = temp;
        return item;
    }
};


