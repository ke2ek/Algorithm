# Linear Data Structure

## Dynamic Array

- Array
	- Elements are stored in successive locations in memory.
	- The time complexity of operation to return and change an element is O(1).
- In a dynamic array, it is able to resize an array.
	- Elements are copied to the newly allocated array.
	- A pointer of the original array refers to a new array.
	- The time complexity is O(N) in case N is the number of elements.
	
	``` c++
	int size;		// the size of an array
	ElementType* array;	// the pointer of an array
	```

- In a dynamic array, it is possible to append new element to the end of an array. 
	- Extra memory space is already allocated in preparation for more memory will be required.
	- So, append() can be done in constant time.
	- The `capacity` of an array means the size of total memory including extra space.
	- The `size` of an array means the number of elements.
	- Notice that the capacity of an array != the size of an array
	
	``` c++
	array[size++] = newValue; // part of `append(newValue)`
	```

	- If the extra space is full, re-allocation is done.
	
	```c++
	// part of `append(newValue)`
	// Re-allocation
	if (size == capacity) {
		// In this case, append() can not be done in constant time.
		// int newCapacity = capacity + M;
		int newCapacity = capacity * 2; // it is close to O(1) averagely
		int* newArray = new int[newCapacity];
		
		// Copy the original elements to new array.
		for (int i=0; i<size; i++) {
			newArray[i] = array[i];
		}

		if (array) delete [] array;
		array = newArray;
		capacity = newCapacity;
	}
	
	// Append new value
	array[size++] = newValue;
	```

- The Dynamic Array is **different** from a dynamically allocated array that is generated with `new` operator.


## Linked List

- Elements are stored in scattered locations in memory.
- Each element has pointers to refer to the previous and next elements.

	``` c++
	// Node of doubly linked list
	struct ListNode {
		int element;
		ListNode *prev, *next;
	}
	```

- Also, Linked List has pointers to refer to the first node and the last node.

	``` c++
	struct LinkedList {
		// some members ...
		ListNode *head;	// the pointer of the first node.
		ListNode *tail;	// the pointer of the last node.
	}
	```

- When an array is accessed arbitrarily, time is taken linearly.
- In a Linked List, appending and deleting a specific element can be done in constant time.
- And splicing and recovery can be done in constant time.

	``` c++
	// delete / recover
	void deleteNode(ListNode* node) {
		node->prev->next = node->next;
		node->next->prev = node->prev;
	}

	// Assume that the previous and the next of the node to recover would not been deleted.
	void recoverNode(ListNode* node) {
		node->prev->next = node;
		node->next->prev = node;
	}
	```

- But getting the size of a list and finding a specific node can be done in O(N) in case N is the number of nodes.
- There is a library implementing the linked list in C++. i.e. [STL Container `list<T>`](http://www.cplusplus.com/reference/list/list/).

