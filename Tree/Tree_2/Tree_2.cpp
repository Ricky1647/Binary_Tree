// Tree_2.cpp : 定義主控台應用程式的進入點。
//Tree 蛀蟲了換一棵樹

#include "stdafx.h"
#include <iostream>
#include<vector>
#include<math.h>
using namespace std;
struct HuffNode {       //Leaf Node
	 int data;
	char symbol;
	HuffNode *leftChild;  //左孩子
	HuffNode *rightChild; //右孩子
};
//函式的多載 ，非常好用!!!!!!
bool operator>(const HuffNode& a, const HuffNode& b) {
	return a.data > b.data;
}
bool operator<(const HuffNode& a, const HuffNode& b) {
	return a.data < b.data;
}
ostream &operator<<(ostream &out, HuffNode &node) {
	out << node.data;
	return out;
}
class MinHeap {
	friend ostream &operator<<(ostream &out, HuffNode &node);
	//friend bool operator>(const HuffNode& a, const HuffNode& b);
	//friend bool operator<(const HuffNode& a, const HuffNode& b);
public:
	MinHeap(int x) {
		heapsize = 0;
		heap = new HuffNode[x+1];
		/*heap.resize(x+1);*/
		capacity = x;
	}
	void push(const HuffNode &);
	bool IsEmpty();
	void print();
	void pop();
private:
	HuffNode *heap;
	/*vector<HuffNode>heap;*/
	int heapsize;//現在heap裡面的節點樹
	int capacity;//heap的容量
};
int main()
{
	int size;
	cout << "Input size[int]: ";
	cin >> size;
	MinHeap min_heap(size);
	char* symbol = new char[size];
	int* frequency = new int[size];
	/*cout << "Input symbol[char]: ";
	for (int i = 0; i < size; i++)
		cin >> symbol[i];*/
	cout << "Input frequency[int]: ";
	for (int i = 0; i < size; i++)
		cin >> frequency[i];
	for (int i = 0; i < size; i++) {
		HuffNode dot;
		dot.data = frequency[i];
		dot.symbol = symbol[i];
		dot.leftChild = NULL;
		dot.rightChild = NULL;
		min_heap.push(dot);
	}
	min_heap.print();
    return 0;
}
void MinHeap::print() {
	int duck = 1;
	int cat = 1;
	for (int i = 1; i <= capacity; i++) {
		cout << heap[i] << "__";
		if (i%duck == 0) {
			cout << endl;
			cat *= 2;
			duck += cat;
		}
		
	}
}
void MinHeap::push(const HuffNode & duck) {
	if (IsEmpty()) {
		heap[1] = duck;
		heapsize = 1;
	}
	else {
		int currentnode = ++heapsize;
		while (currentnode != 1 && heap[currentnode / 2] > duck) {
			heap[currentnode] = heap[currentnode/2];
			currentnode /= 2;
		}
		heap[currentnode] = duck;
	}
	//heap[heapsize++] = duck;
	//int idx = heapsize;
	//while (idx > 1) {
	//	if (heap[idx-1  ] < heap[idx / 2 - 1]) {
	//		HuffNode temp = heap[idx - 1];
	//		heap[idx - 1] = heap[idx / 2 - 1];
	//		heap[idx / 2 - 1] = temp;
	//	}
	//	idx /= 2;
	//}
}
bool MinHeap::IsEmpty(){
	return heapsize == 0;
}
void MinHeap::pop() {
	
}
