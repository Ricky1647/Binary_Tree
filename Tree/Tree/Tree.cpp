// Tree.cpp : 定義主控台應用程式的進入點。
//

#include "stdafx.h"
#include <iostream>
using namespace std;
// Example
// Huffman Tree Node
struct HuffNode {       //Leaf Node
	int data;
	char symbol;
	HuffNode *leftChild;  //左孩子
	HuffNode *rightChild; //右孩子
};
// min-heap class
class MinHeap {
public:
	MinHeap() {  
		heapSize = 0;
	};
		bool IsEmpty();//回傳true當優先權佇列是空的
		void Push(int x); //加一個元素到優先權佇列中
		//void Pop();  //刪除最大優先權的元素
		//void ChangeSizeD(int *,const int oldSize, const int newSize);		// ChangeSizeD 在課本第130⾴
		void print();
private:
	int *heap; // element array   元素陣列
	int heapSize; // number of elements in heap 堆積裡的元素個數
	int capacity; // size of the array heap     陣列heap的大小(容量)
	};
//*********************主程式******************
int main() {
	int size;                  //輸入大小
	cout << "輸入大小";
	cin >> size;
	cout << endl;
	char *arr = new char[size];//符號
	int *freq = new int[size]; //權重
	// Read_user_input();
	// while(cin >> x) you will need it;
	MinHeap  min_heap;
	for (int i = 0; i < size; i++) {
		int ham = 0;
		cin >> ham;
		min_heap.Push(ham);
	}
		
		// Initalize the leaf node
		//for (int i = 0; i < size; i++) {    //建樹葉節點
		//	HuffNode leaf_node;
		//	leaf_node.data = freq[i];
		//	leaf_node.symbol = arr[i];
		//	leaf_node.leftChild = leaf_node.rightChild = nullptr;
		//	//min_heap.Push(leaf_node);
		//}
		 min_heap.print();
		// cout << complete_tree_max_level(min_heap) << endl;
		return 0;
	}	bool MinHeap::IsEmpty() {
		return(heapSize==0);
	}
	void MinHeap::Push(int x) {
		if (heapSize == capacity) {
			//ChangeSizeD(heap, capacity, 2 * capacity);
			capacity *= 2;
		}
		if (IsEmpty()) 
		{
			heap[1] = x;
			heapSize++;
			return;
		}
		cout << "ss"<<heapSize;
		++heapSize;
		int currentNode = heapSize;
		while (currentNode != 1 && heap[currentNode / 2] > x) {
		//氣泡上升法
			heap[currentNode] = heap[currentNode / 2];
			currentNode /= 2;
		}
		heap[currentNode] = x;
	}
	void MinHeap::print() {
		int duck = 1;
		for (int i = 1; i <= heapSize; i++) {
			cout << heap[i] << "__";
			if (i%duck == 0) {
				cout << endl;
				duck *= 2;
			}
		}
	}