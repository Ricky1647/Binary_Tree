#include "stdafx.h"

#include<iostream>
#include<string>
using namespace std;

struct HuffNode {
	int frequency;
	char symbol;
	struct HuffNode* leftNode;
	struct HuffNode* rightNode;
};
bool operator< (const HuffNode& a, const HuffNode& b) {
	return a.frequency < b.frequency;
}
bool operator> (const HuffNode& a, const HuffNode& b) {
	return a.frequency > b.frequency;
}
ostream& operator<<(ostream& os, const HuffNode& a) {
	os << a.frequency;
	return os;
}
template<class T>
class MinHeap {
	friend ostream& operator<<(ostream& os, const HuffNode& a);
public:
	MinHeap() {
		heapSize = 0;
		capacity = 10;
		heap = new T[capacity];
	}
	bool IsEmpty() {
		return heapSize == 0;
	}
	int size() {
		return heapSize;
	}
	const T& Top() {
		if (!IsEmpty())
			return heap[0];
	}
	void Push(const T& newNode) {
	/*	if (heapSize == capacity)
			ChangeSize1D(heap, capacity, capacity * 2);*/
		heap[heapSize++] = newNode;
		int idx = heapSize;
		while (idx > 1) {
			if (heap[idx - 1] < heap[idx / 2 - 1]) {
				T temp = heap[idx - 1];
				heap[idx - 1] = heap[idx / 2 - 1];
				heap[idx / 2 - 1] = temp;
			}
			idx /= 2;
		}
	}
	void Pop() {
		if (!IsEmpty()) {
			heap[0] = heap[--heapSize];
			int idx = 1;
			while (idx * 2 <= heapSize) {
				int smallerChildIdx = idx * 2;
				if (idx * 2 + 1 <= heapSize)
					if (heap[idx * 2] < heap[idx * 2 - 1])
						smallerChildIdx++;
				if (heap[idx - 1] > heap[smallerChildIdx - 1]) {
					T temp = heap[idx - 1];
					heap[idx - 1] = heap[smallerChildIdx - 1];
					heap[smallerChildIdx - 1] = temp;
				}
				idx *= 2;
			}
		}
	}
	/*void ChangeSize1D(T* a, const int oldSize, const int newSize) {
		if (newSize > oldSize) {
			T* temp = new T[newSize];
			memcpy(temp, heap, sizeof(heap));
			delete heap;
			heap = temp;
			capacity = newSize;
		}
	}*/
	void printTree() {
		int idx = 0;
		while (idx < heapSize) {
			if (floor(log2(idx + 1)) == log2(idx + 1))
				cout << '\n';
			cout << heap[idx++] << "__";
		}
	}
	int maxLevel() {
		return int(log2(heapSize));
	}
private:
	T* heap;
	int heapSize;
	int capacity;
};
void PreTrace(const HuffNode& root, int& maxLevel, int& nodeCount, int level = 0) {
	nodeCount++;
	if (level > maxLevel)
		maxLevel = level;
	cout << root.frequency << ' ';
	if (root.leftNode != nullptr)
		PreTrace(*(root.leftNode), maxLevel, nodeCount, level + 1);
	if (root.rightNode != nullptr)
		PreTrace(*(root.rightNode), maxLevel, nodeCount, level + 1);
}
void InTrace(const HuffNode& root, int& maxLevel, int& nodeCount, int level = 0) {
	nodeCount++;
	if (level > maxLevel)
		maxLevel = level;
	if (root.leftNode != nullptr)
		InTrace(*(root.leftNode), maxLevel, nodeCount, level + 1);
	cout << root.frequency << ' ';
	if (root.rightNode != nullptr)
		InTrace(*(root.rightNode), maxLevel, nodeCount, level + 1);
}
void encode(const HuffNode& root, string s = "") {
	if (root.leftNode == nullptr && root.rightNode == nullptr)
		cout << root.symbol << " : " << s << '\n';
	else {
		if (root.leftNode != nullptr)
			encode(*(root.leftNode), s + '1');
		if (root.rightNode != nullptr)
			encode(*(root.rightNode), s + '0');
	}
}
void decode(HuffNode& root, const string& s) {
	struct HuffNode* ptr = &root;
	for (unsigned int i = 0; i < s.size(); i++) {
		if (s[i] == '1' && ptr != nullptr) {
			ptr = ptr->leftNode;
		}
		else if (s[i] == '0' && ptr != nullptr) {
			ptr = ptr->rightNode;
		}
		if (ptr != nullptr)
			if (ptr->leftNode == nullptr && ptr->rightNode == nullptr) {
				cout << ptr->symbol;
				ptr = &root;
			}
	}
}
int main() {
	int size;
	cout << "Input size[int]: ";
	cin >> size;

	char* symbol = new char[size];
	int* frequency = new int[size];
	cout << "Input symbol[char]: ";
	for (int i = 0; i < size; i++)
		cin >> symbol[i];
	cout << "Input frequency[int]: ";
	for (int i = 0; i < size; i++)
		cin >> frequency[i];
	cout << "==========================================";

	MinHeap<HuffNode> min_heap;
	for (int i = 0; i < size; i++) {
		HuffNode leaf_node;
		leaf_node.frequency = frequency[i];
		leaf_node.symbol = symbol[i];
		leaf_node.leftNode = leaf_node.rightNode = nullptr;
		min_heap.Push(leaf_node);
	}

	cout << "\nMinHeap Tree:";
	min_heap.printTree();
	cout << "\nMax Level: " << min_heap.maxLevel();
	cout << "\n\n==========================================";

	cout << "\nHuffman Tree:";
	while (min_heap.size() > 1) {
		struct HuffNode* ptr1 = new HuffNode(min_heap.Top());
		min_heap.Pop();
		struct HuffNode* ptr2 = new HuffNode(min_heap.Top());
		min_heap.Pop();
		struct HuffNode new_node = { ptr1->frequency + ptr2->frequency, ' ', ptr2, ptr1 };
		min_heap.Push(new_node);
	}
	struct HuffNode root = min_heap.Top();
	cout << "\nPreorder: ";
	int preMaxLevel, preNodeCount = 0, inMaxLevel, inNodeCount = 0;
	PreTrace(root, preMaxLevel, preNodeCount);
	cout << "\nInorder: ";
	InTrace(root, inMaxLevel, inNodeCount);
	cout << "\nMax Level: " << preMaxLevel;
	cout << "\nNumber of Node: " << preNodeCount;
	cout << "\n\n==========================================";

	cout << "\nHuffman Coding:\n";
	encode(root);
	cout << "\n==========================================";

	string code;
	//code = "111001100010110100110011010101011001001110111";
	cout << "\nInput sequence for decode: ";
	cin >> code;
	cout << "\n\nDecoded Huffman Data:\n";
	decode(root, code);
	cout << '\n';

	delete[] symbol;
	delete[] frequency;

	system("PAUSE");
	return 0;
}