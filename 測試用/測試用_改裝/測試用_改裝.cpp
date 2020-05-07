// 測試用_改裝.cpp : 定義主控台應用程式的進入點。
//

#include "stdafx.h"
#include<iostream>
using namespace std;
//間霍夫曼樹節點
struct HuffNode {       //Leaf Node
	int data;
	char symbol;
	HuffNode *leftChild;  //左孩子
	HuffNode *rightChild; //右孩子
};
class MinHeap {
public:
	MinHeap() {  };
		bool IsEmpty();
		void Push(int x);
		void Pop();
		void ChangeSizeD(int *a, const int oldSize, const int newSize);
		// ChangeSizeD 在課本第130⾴
private:
	int *heap; // element array
	int heapSize; // number of elements in heap
	int capacity; // size of the array heap
	};
int main()
{
    return 0;
}

