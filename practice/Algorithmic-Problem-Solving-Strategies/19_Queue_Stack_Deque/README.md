# Data Structure using an Array or a Linked list

## Basic

- push() operation means to put data on the structure.
- pop() operation means to take data out.

## Stack

- **Last In First Out, LIFO**

	``` text
	push(A); push(B);
	---------------- 
	| A | B |
	----------------
			^
			top

	push(C);
	---------------- 
	| A | B | C |
	----------------
				^
				top

	pop();
	---------------- 
	| A | B |
	----------------
			^
			top
	```

- In C++, there is the library [`stack<T>`](http://www.cplusplus.com/reference/stack/stack/).

## Queue

- **First In First Out, FIFO**

	``` text
	push(A); push(B);
	---------------- 
	| A | B |
	----------------
	^		^
	front	back

	push(C);
	---------------- 
	| A | B | C |
	----------------
	^			^
	front		back

	pop();
	---------------- 
	| B | C |
	----------------
	^		^
	front	back
	```

- In C++, there is the library [`queue<T>`](http://www.cplusplus.com/reference/queue/queue/).

## Deque

- It has operations used in stack and queue.
- It is possible to push and pop in front/back of the data structure.

	``` text
	push_back(A); push_back(B);
	---------------- 
	| A | B |
	----------------
	^		^
	front	back

	push_front(C);
	---------------- 
	| C | A | B |
	----------------
	^			^
	front		back

	pop_back();
	---------------- 
	| C | A |
	----------------
	^		^
	front	back

	pop_front();
	---------------- 
	| A |
	----------------
	^	^
	frt bak
	```

