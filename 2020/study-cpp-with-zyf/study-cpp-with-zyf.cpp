#include <iostream>
#include <vector>
#include <stack>
#include <queue>
#include <string>
#include <cstring>

using namespace std;

struct Node {
	int val;

	Node* next;
};


int arr[10000];

int main() {
	stack<int> my_stack;
	queue<int> my_queue;

	for (int i = 0; i < 10; i += 1) {
		my_stack.push(i);
	}

	int n = 100;
	int simplest_arr[2] = {};
	int* malloc_arr = (int*)malloc(n * sizeof(int));
	int* new_arr = new int[n];

	struct StudentWithVeryLongName {
		int id;
		char name[20];
	};

	StudentWithVeryLongName s;

	s.id = 1;
	strcpy_s(s.name, "Student Name");

	cout << s.name << endl;

	float f = 10.12;
	double d = 10.12;
	int x = d;

	cout << ('a' + 12) << endl;

	// release the memeory
	free(malloc_arr);
	delete[] new_arr;

	string your_name = "Zhang Yifei";
	string my_name = "Yang Ruini";

	string another_name = my_name;

	vector<int> vec_arr(n, 128);

	for (int i = 0; i < n; i += 1) {
		vec_arr.push_back(i);
		my_stack.push(i);
	}

	return 0;
}