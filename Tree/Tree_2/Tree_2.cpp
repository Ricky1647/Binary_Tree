// Tree_2.cpp : 定義主控台應用程式的進入點。
//Tree 蛀蟲了換一棵樹

#include "stdafx.h"
#include <iostream>
#include<vector>
#include<math.h>
#include<string>
#include<string.h>
#include <algorithm>
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
	void Inorder(HuffNode *current, int& a, int& max, int level = 0);
	void pop();
	void encode(HuffNode*root, string word = "");
	void decode(HuffNode&root, string& arr);
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
	cout << "==========================================" << endl;
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
	while (min_heap.sizeback() > 1) {
		HuffNode *ptr1 = new HuffNode; //極度重要 重新再看
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
	//HuffNode *root = &(min_heap.top());
	HuffNode *root = &(min_heap.top());
	HuffNode root1 = min_heap.top();
	min_heap.Preorder(root);
	cout << endl;
	cout << "inorder : ";
	min_heap.Inorder(root, node, max);
	cout << endl << "Max Level : " << max - 1 << endl;
	cout << "Nunber of Node : " << node << endl;
	cout << "==========================================" << endl;
	cout << "Huffman coding" << endl;
	min_heap.encode(root);
	cout << "==========================================" << endl;
	string ham;

	cout << "Input sequence for decode: ";
	cin >> ham;
	min_heap.decode(root1, ham);
	cout << endl << "==========================================" << endl;
	cout << "Input a string : ";
	string inp;
	cin >> inp;
	char *book = new char[inp.size()];
	char *arr1 = new char[inp.size()];
	int  *arr2 = new int[inp.size()];
	for (int i = 0; i < inp.size(); i++) {
		book[i] = inp[i];
	}
	arr1[0] = book[0];
	arr2[0] = 1;
	int c = 1;
	int d = 0;
	for (int i = 1; i < inp.size(); i++) {
		for (int j = 0; j < c; j++) {
			if (book[i] == arr1[j]) {
				arr2[j] += 1;
				j = c;
			}
			else if (book[i] != arr1[j] && j == (c - 1))
			{
				arr1[c] = book[i];
				d += 1;
				arr2[d] = 0;
				c += 1;
			}
		}
	}
	for (int i = 0; i < c; i++)  //氣泡排序法來讓字母由小到大
		for (int j = 0; j < c - i - 1; j++)
			if (arr1[j] > arr1[j + 1])
			{
				char tmp = arr1[j];
				int tmp1 = arr2[j];
				arr1[j] = arr1[j + 1];
				arr2[j] = arr2[j + 1];
				arr1[j + 1] = tmp;
				arr2[j + 1] = tmp1;
			}
	cout << "Your input size[int]: " << c;
	cout << endl;
	cout << "Your input symbol[char]: ";
	for (int i = 0; i < c; i++)
		cout << arr1[i] << " ";
	cout << endl;
	cout << "Your input frequency[int]: ";
	for (int i = 0; i < c; i++)
		cout << arr2[i] << " ";
	cout << endl << "==========================================" << endl;
	MinHeap Tree(c);
	for (int i = 0; i < c; i++) {
		HuffNode dot;
		dot.data = arr2[i];
		dot.symbol = arr1[i];
		dot.leftChild = NULL;
		dot.rightChild = NULL;
		Tree.push(dot);
	}
	cout << "MinHeap Tree" << endl;
	Tree.print();
	cout << endl;
	cout << "==========================================" << endl;
	while (Tree.sizeback() > 1) {
		HuffNode *ptr1_tree = new HuffNode; //極度重要 重新再看
		Tree.copy(ptr1_tree);
		Tree.pop();
		HuffNode *ptr2_tree = new HuffNode;
		Tree.copy(ptr2_tree);
		Tree.pop();
		HuffNode newnode_tree = { ptr1_tree->data + ptr2_tree->data,' ',ptr2_tree,ptr1_tree };
		Tree.push(newnode_tree);
	}
	int node_tree = 0;
	int max_tree = 0;
	cout << "Huffman Tree" << endl;
	cout << "preorder : ";
	HuffNode *root_tree = &(Tree.top());
	HuffNode root1_tree = Tree.top();
	Tree.Preorder(root_tree);
	cout << endl;
	cout << "inorder : ";
	Tree.Inorder(root_tree, node_tree, max_tree);
	cout << endl << "Max Level : " << max_tree - 1 << endl;
	cout << "Nunber of Node : " << node_tree << endl;
	cout << "==========================================" << endl;
	cout << "Huffman coding" << endl;
	Tree.encode(root_tree);
	cout << "==========================================" << endl;
	string ham_tree;
	cout << "Input sequence for decode: ";
	cin >> ham_tree;
	Tree.decode(root1_tree, ham_tree);
	cout << endl << "==========================================" << endl;
	delete[] arr1;
	delete[] book;
	delete[] arr2;
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
		//int currentnode = ++heapsize;
		//while (currentnode != 1 && heap[currentnode / 2] > duck) {
		//	heap[currentnode] = heap[currentnode/2];
		//	currentnode /= 2;
		//}
		//heap[currentnode] = duck;
		heap[++heapsize] = duck;
		for (int idx = 1; idx <= heapsize; idx++) {
			while (heap[idx / 2] > heap[idx]) {
				HuffNode temp = heap[idx];
				heap[idx] = heap[idx / 2];
				heap[idx / 2] = temp;
				idx /= 2;
			}
		}

		/*int idx = heapsize;*/
		//while (idx > 1) {
		//	if (heap[idx  ] < heap[idx / 2]) {
		//		HuffNode temp = heap[idx ];
		//		heap[idx ] = heap[idx / 2];
		//		heap[idx / 2] = temp;
		//	}
		//	idx /= 2;
		//}
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
bool MinHeap::IsEmpty() {
	return heapsize == 0;
}
void MinHeap::pop() {
	heap[1] = heap[heapsize];
	heapsize--;
	//int idx = heapsize;
	//for (int idx = 2; idx <= heapsize; idx++) { //我自己的
	int idx = 1;
	while (idx * 2 <= heapsize) {
		int smallchild = idx * 2;
		if (idx * 2 + 1 <= heapsize)
			if (heap[idx * 2] > heap[idx * 2 + 1])
				smallchild++;
		if (heap[idx] > heap[smallchild])
		{
			HuffNode temp = heap[idx];
			heap[idx] = heap[smallchild];
			heap[smallchild] = temp;
		}
		idx =idx*2;
		/*	HuffNode temp = heap[idx];
			heap[idx] = heap[idx / 2];
			heap[idx / 2] = temp;
			idx /= 2;*/
	}
	//}
	//int idx = 1;
	//while (idx * 2 <= heapsize) {
	//	int smallerChildIdx = idx * 2;
	//	if (idx * 2 + 1 <= heapsize)
	//		if (heap[idx * 2] < heap[idx * 2 - 1])
	//			smallerChildIdx++;
	//	if (heap[idx - 1] > heap[smallerChildIdx - 1]) {
	//		HuffNode temp = heap[idx - 1];
	//		heap[idx - 1] = heap[smallerChildIdx - 1];
	//		heap[smallerChildIdx - 1] = temp;
	//	}
	//	idx *= 2;
	//}
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
void MinHeap::Inorder(HuffNode *current, int& a, int& max, int level) {

	if (current) {                          // if current != NULL
		Inorder(current->leftChild, a, max, level + 1);        // 走左子樹
		cout << current->data << " ";   //輸出權重 
		a++; //節點加加
		Inorder(current->rightChild, a, max, level + 1);       // 走右子樹
	}
	//為甚麼我這個level一定會多1，原因就是我的判斷式是current所以當我遞迴的時候就算已經沒有子樹了，但max還是會吃到+1的level
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
void MinHeap::encode(HuffNode *root, string word) {   //用遞迴跑編碼
	if (root->leftChild == nullptr&&root->rightChild == nullptr)
	{
		cout << root->symbol << " : " << word << endl;
	}
	if (root->leftChild != nullptr)//左枝編1
		encode(root->leftChild, word + '1');
	if (root->rightChild != nullptr)//右枝編0
		encode(root->rightChild, word + '0');
}
void MinHeap::decode(HuffNode&root, string& arr) {

	struct HuffNode* ptr = &root;
	for (int i = 0; i < arr.size(); i++) {
		if (ptr->leftChild != nullptr) {
			if (arr[i] == '1') {		//	走左指數
				ptr = ptr->leftChild;
			}
		}
		if (ptr->rightChild != nullptr) {
			if (arr[i] == '0') {        //  走右指數
				ptr = ptr->rightChild;
			}
		}
		if (ptr->leftChild == nullptr&&ptr->rightChild == nullptr)
		{
			cout << ptr->symbol;
			ptr = &root;
		}
	}

}
//	void decode(HuffNode*root,string& arr,char symbol=' ');
