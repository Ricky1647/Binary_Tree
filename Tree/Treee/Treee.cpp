// Treee.cpp : 定義主控台應用程式的進入點。
//

#include "stdafx.h"
#include<iostream>
#include <string>
using namespace std;

int main()
{
	cout << "Input a string : ";
	string inp;
	cin >> inp;
	char *book=new char [inp.size()];
	char *arr1= new char[inp.size()];
	int  *arr2= new int[inp.size()];
	//char book[100]; 
	//char arr1[100];
	//int arr2[100];
	for (int i = 0; i < inp.size(); i++) {
		book[i] = inp[i];
	}
	//for (int i = 0; i < inp.size(); i++) {
	//	cout << book[i] << "";
	//}
	
	arr1[0] = book[0];
	arr2[0] = 1;
	int c = 1;
	int d = 0;
	for (int i = 1;i<inp.size() ;i++) {
		for (int j = 0;j<c; j++) {
			if (book[i] == arr1[j]) {
				arr2[j] += 1;
			 
				j = c;
			}
			else if(book[i]!=arr1[j]&&j==(c-1))
			{
				
			 
				arr1[c] = book[i];
				d += 1;
				arr2[d] = 0;
				c += 1;
			}
		}
	}
	
	//for (int i = 0; i < c; i++) {
	//	if (arr1[i] > arr1[i + 1]) {
	//		char temp = arr1[i];
	//		arr1[i] = arr1[i + 1];
	//		arr1[i + 1] = temp;
	//	}
	//}
	for (int i = 0; i<c; i++)
		for (int j = 0; j<c - i - 1; j++)
			if (arr1[j]>arr1[j + 1])
			{
				char tmp = arr1[j];
				int tmp1 = arr2[j];
				arr1[j] = arr1[j + 1];
				arr2[j] = arr2[j + 1];
				arr1[j + 1] = tmp;
				arr2[j + 1] = tmp1;
			}


	cout << "Your input size[int] " << c;
	cout<<endl;
	cout << "Your input symbol[char]";
	for (int i = 0; i < c; i++)
		cout << arr1[i] << " ";
	cout<<endl;
	cout << "Your input frequency[int]";
	for (int i = 0; i < c; i++)
		cout  << arr2[i] << " ";
	cout << endl;
	delete[] arr1;
	delete[] book;
	delete[] arr2;
	return 0;
}

//AADDTSSSRUUCEE_

/*MinHeap min_heap(size);
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
	int node_tree = 0;
	int max_tree = 0;
	cout << "Huffman Tree" << endl;
	cout << "preorder : ";
	HuffNode *root_tree = &(Tree.top());
	HuffNode root1_tree = Tree.top();
	Tree.Preorder(root_tree);
	cout << endl;
	cout << "inorder : ";
	Tree.Inorder(root_tree,node_tree,max_tree);
	cout <<endl<< "Max Level : " << max_tree-1<<endl;
	cout << "Nunber of Node : " << node_tree << endl;
	*/