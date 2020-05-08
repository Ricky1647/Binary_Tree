// Tree_2.cpp : 定義主控台應用程式的進入點。
//Tree 蛀蟲了換一棵樹

#include "stdafx.h"
#include <iostream>
#include<vector>
#include<math.h>
#include<string>
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
		heap = new HuffNode[100];
		/*heap.resize(x+1);*/
		capacity = x;
	}
	void push(const HuffNode &);
	bool IsEmpty();
	void print();
	void Inorder(HuffNode *current,int& a, int& max ,int level=0);
 	void pop();
	void encode(HuffNode*root, string word = "");
	void Preorder(HuffNode *current);
	HuffNode top();
	int sizeback();
	void copy(HuffNode *a);
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
	cout << "Input symbol[char]: ";
	for (int i = 0; i < size; i++)
		cin >> symbol[i];
	cout << "Input frequency[int]: ";
	for (int i = 0; i < size; i++)
		cin >> frequency[i];
	cout << "=========================================="<<endl;
	for (int i = 0; i < size; i++) {
		HuffNode dot;
		dot.data = frequency[i];
		dot.symbol = symbol[i];
		dot.leftChild = NULL;
		dot.rightChild = NULL;
		min_heap.push(dot);
	}
	cout << "MinHeap Tree" << endl;
	min_heap.print();
	cout << endl;
	cout << "==========================================" << endl;
	//min_heap.Inorder();
	/*min_heap.pop();
	min_heap.print();
	cout << endl;
	min_heap.pop();
	min_heap.print();*/
	while (min_heap.sizeback() > 1) {
		HuffNode *ptr1=new HuffNode ; //極度重要 重新再看
		min_heap.copy(ptr1);
		min_heap.pop();
		HuffNode *ptr2 = new HuffNode;
		min_heap.copy(ptr2);
		min_heap.pop();
		HuffNode newnode = { ptr1->data + ptr2->data,' ',ptr2,ptr1 };
		min_heap.push(newnode);
	}
	int node = 0;
	int max = 0;
	cout << "Huffman Tree" << endl;
	cout << "preorder : ";
	HuffNode *root = &(min_heap.top());
	min_heap.Preorder(root);
	cout << endl;
	cout << "inorder : ";
	min_heap.Inorder(root,node,max);
	cout <<endl<< "Max Level : " << max-1<<endl;
	cout << "Nunber of Node : " << node << endl;
	cout << "==========================================" << endl;
	cout << "Huffman coding" << endl;
	min_heap.encode(root);
	cout << "==========================================" << endl;
	//9 8 7 6 5 4 3 2 1
     return 0;
}
void MinHeap::print() {
	int duck = 1;
	int cat = 1;
	int level = 0;
	for (int i = 1; i <= heapsize; i++) {
		cout << heap[i] << "__";
		if (i%duck == 0) {
			cout << endl;
			cat *= 2;
			duck += cat;
			level++;
		}		
	}
	cout << endl << "Max Level:" << level << endl;
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
	heap[1] = heap[heapsize];
	heapsize--;
	//int idx = heapsize;
	for (int idx = 2; idx <= heapsize; idx++) {
		while (idx != 1 && heap[idx / 2] > heap[idx]) {
			HuffNode temp = heap[idx];
			heap[idx] = heap[idx / 2];
			heap[idx / 2] = temp;
			idx /= 2;
		}
	}
}
int MinHeap::sizeback() {
	return heapsize;
}
void MinHeap::copy(HuffNode *a) {
	a->data = heap[1].data;
	a->symbol = heap[1].symbol;
	a->leftChild = heap[1].leftChild;
	a->rightChild = heap[1].rightChild;
}
void MinHeap::Inorder(HuffNode *current, int& a, int& max,int level  ) {

	if (current) {                          // if current != NULL
		Inorder(current->leftChild,a,max,level+1);        // L
		cout << current->data << " ";   // 
		a++;
		Inorder(current->rightChild,a,max,level+1);       // R
	}
	if (level > max)
		max = level;
} 
HuffNode MinHeap::top() {
	return heap[1];
}
void MinHeap::Preorder(HuffNode *current) {
	if (current) {                          // if current != NULL
		cout << current->data << " ";   // V
		Preorder(current->leftChild);       // L
		Preorder(current->rightChild);      // R
	}
}
void MinHeap::encode(HuffNode *root , string word) {
	if (root->leftChild == nullptr&&root->rightChild == nullptr) 
	{
		cout << root->symbol << " : "<< word<<endl;
	}
	if (root->leftChild != nullptr)
		encode(root->leftChild , word + '1');
	if (root->rightChild != nullptr)
		encode(root->rightChild , word + '0');
}