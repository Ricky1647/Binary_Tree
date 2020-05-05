// Tree.cpp : 定義主控台應用程式的進入點。
//

#include "stdafx.h"
#include <iostream>
using namespace std;
struct HuffNode {       //Leaf Node
	int data;
	char symbol;
	HuffNode *leftChild;  //左孩子
	HuffNode *rightChild; //右孩子
};
class MinHeap {
public:
	MinHeap() {  
		heapSize = 0;
		heap = new int[100000]; //忘記給空間拉幹!!!!!!!!!!!!!!!!!!!!!!
	};
		bool IsEmpty();//回傳true當優先權佇列是空的
		void Push(int x); //加一個元素到優先權佇列中
		void print();
private:
	int *heap; // element array   元素陣列
	int heapSize; // number of elements in heap 堆積裡的元素個數
	int capacity; // size of the array heap     陣列heap的大小(容量)
	};
//--------------------------------------------------
int main() {
	int size;                  //輸入大小
	cout << "輸入大小";
	cin >> size;
	cout << endl;
	//char *arr = new char[size];//符號
	//int *freq = new int[size]; //權重
	MinHeap  min_heap;
	for (int i = 0; i < size; i++) {
		int ham = 0;
		cin >> ham;
		min_heap.Push(ham);
	}
		
		 min_heap.print();
		 ;
		return 0;
	} 	bool MinHeap::IsEmpty() {
		return(heapSize==0);
	}
	void MinHeap::Push(int x) {
		if (heapSize == capacity) {
			capacity *= 2;
		}
		if (IsEmpty()) 
		{
			heap[1] = x;
			heapSize=1;
		}
		else {
			int currentNode = ++heapSize;
			while (currentNode != 1 && heap[currentNode / 2] > x) {
				heap[currentNode] = heap[currentNode / 2];
				currentNode /= 2;
			}
			heap[currentNode] = x;
		}
	}
	void MinHeap::print() {
		int duck = 1;
		int cat = 1;
		for (int i = 1; i <= heapSize; i++) {
			cout << heap[i] << "__";
			if (i%duck == 0) {
				cout << endl;
				cat *= 2;
				duck += cat;
			}
		}
	}