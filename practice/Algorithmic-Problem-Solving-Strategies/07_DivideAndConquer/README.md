# Divide And Conquer

## Basic

- In computer science, [divide and conquer](https://en.wikipedia.org/wiki/Divide-and-conquer_algorithm) is an algorithm design paradigm. A divide-and-conquer algorithm recursively breaks down a problem into two or more sub-problems of the same or related type, until these become simple enough to be solved directly. The solutions to the sub-problems are then combined to give a solution to the original problem.
- It is different from a recursion call because **it divides the original problem into the same size of sub-problems**, whereas the recursion  call divides each problem into one piece and the others.

    ``` text
    Recursion:
    |  a     b     c     d     e     f  |
    |  a  |  b     c     d     e     f  |
          |  b  |  c     d     e     f  |
                |  c  |  d     e     f  |
                      |  d  |  e     f  |
                            |  e  |  f  |

    Divide and Conquer:
    |  a     b     c     d     e     f  |
    |  a     b     c  |  d     e     f  |
    |  a  |  b     c  |  d  |  e     f  |
          |  b  |  c  |     |  e  |  f  |
    ```

- It is composed of three steps as like below.
  - **Divide.** splitting the problem into the small problems(sub-problems).
  - **Merge.** making the answer of a problem by collecting answers from each sub-problem.
  - **Base Case.** the smallest problems that can not be divided are straightforward so can be solved immediately.
- Considerations
  - Could you divide the given problem into two or more parts?
  - Could you combine each answers of sub-problems efficiently?
  - How does it work? Is it better than other solutions?


## How to calculate faster

- The sum of a sequence
    - Example: calculate the sum of [1,2, ..., N].
    
    ``` c++
    // Recursive Call: O(N)
    int recursiveSum(int n) {
        if (n == 1) return 1; // base case
        return n + recursiveSum(n - 1);
    }

    // Divide and Conquer: O(lg(N))
    int fastSum(int n) {
        if (n == 1) return 1; // base case
        if (n & 1) return fastSum(n - 1) + n; // if n is not even
        return 2 * fastSum(n / 2) + (n / 2) * (n / 2);
    }

    /* Proof of Concept
    fastSum(n) = 1 + 2 + ... + n
               = (1 + 2 + ... + (n/2)) + ((n/2 + 1) + ... + n)
               = fastSum(n/2) + ((n/2 + 1) + ... + n)
    
    We need to convert the second term above.
    because each problem should be defined as the sum of [1, x].

    ((n/2 + 1) + ... + n) = (n/2 + 1) + (n/2 + 2) + ... + (n/2 + n/2)
                          = (n/2) * (n/2) + fastSum(n/2)
    
    Thus,
    
    fastSum(n) = 2 * fastSum(n/2) + (n/2) * (n/2)
    */
    ```

- The power of a square matrix
  - Example: calculate A^m, where A is a square matrix of N by N.

    ``` c++
    // Returns a identity matrix of N by N.
    vector<vector<int>> identity(int N) {
        vector<vector<int>> E(N, vector<int> (N, 0));
        for (int i = 0; i < N; i++) E[i][i] = 1;
        return E;
    }

    // O(N^3)
    vector<vector<int>> multiply(vector<vector<int>>& A,
                                 vector<vector<int>>& B)
    {
        int A_ROWS = A.size(), B_COLS = B[0].size();
        int MIDDLE = A[0].size(); // = B.size()
        vector<vector<int>> C(A_ROWS, vector<int> (B_COLS, 0));
        for (int i = 0; i < A_ROWS; i++)
            for (int j = 0; j < B_COLS; j++)
                for (int k = 0; k < MIDDLE; k++)
                    C[i][j] += A[i][k] * B[k][j];
        return C;
    }

    // Recursive Call: O(N^3 * M)
    vector<vector<int>> recursivePow(vector<vector<int>>& A, int m)
    {
        if (m == 0) return identity(A.size());
        return multiply(A, recursivePow(A, m - 1));
    }

    // Divide and Conquer: O(N^3 * lg(M))
    vector<vector<int>> fastPow(vector<vector<int>>& A, int m)
    {
        if (m == 0) return identity(A.size());
        if (m & 1) return multiply(A, fastPow(A, m - 1));
        vector<vector<int>> half = fastPow(A, m - 1);
        return multiply(half, half); // A^m = A^(m/2) * A^(m/2)
    }
    ```

## Overlapping Subproblems

- Assume that `fastPow(A, m)` tries to divide `m` into the same size when `m` is odd. 
  - ex) `A^7 = A^3 * A^4` not `A^6 * A`
- In this case, it is easy to see that a lot of recursive calls are duplicated as like below.

    ``` text
    in case of odd, divide into half.

    pow(A, 31) -> pow(A, 16) -> pow(A, 8) -> pow(A, 4) -> pow(A, 2) -> pow(A, 1)
               -> pow(A, 15) -> pow(A, 8) -> pow(A, 4) -> pow(A, 2) -> pow(A, 1)
                             -> pow(A, 7) -> pow(A, 4) -> pow(A, 2) -> pow(A, 1)
                                          -> pow(A, 3) -> pow(A, 2) -> pow(A, 1)
                                                       -> pow(A, 1)

    in case of odd, make the number even by subtracting 1.
    pow(A, 31) -> pow(A, 30) -> pow(A, 15) -> pow(A, 14) -> pow(A, 7) -> pow(A, 6)
    -> pow(A, 3) -> pow(A, 2) -> pow(A, 1)
    ```

- **The time complexity vary according to how a problem is divided, even though it is the same problem.**


## Sorting with Divide and Conquer

- Time Complexity: `O(n * log(n))`
- [Merge Sort](https://en.wikipedia.org/wiki/Merge_sort)
  - Divide the unsorted list into n sublists, each containing one element (a list of one element is considered sorted).

    ![merge](https://upload.wikimedia.org/wikipedia/commons/thumb/e/e6/Merge_sort_algorithm_diagram.svg/600px-Merge_sort_algorithm_diagram.svg.png)

  - Repeatedly merge sublists to produce new sorted sublists until there is only one sublist remaining. This will be the sorted list.

    ![mereg2](https://upload.wikimedia.org/wikipedia/commons/c/cc/Merge-sort-example-300px.gif)

  - In each step, the number of sub-problems increases as twice and the size of each sub-problem decrease as twice. Therefore, it merges n elements every step (where n is the length of the given array) so merging spends constant time by O(n) every step.
  - The number of total steps is O(log(n)) because problems are divided into half in one step.

- [Quick Sort](https://en.wikipedia.org/wiki/Quicksort)
  - It works by selecting a `pivot` element from the array and partitioning the other elements into two sub-arrays, according to whether they are less than or greater than the pivot.
    - It does not need any additional merging process.
  - The sub-arrays are then sorted recursively. This can be done in-place, requiring small additional amounts of memory to perform the sorting.
  - Example: when a pivot is the last element in an array.

    ![quick](https://upload.wikimedia.org/wikipedia/commons/thumb/a/af/Quicksort-diagram.svg/400px-Quicksort-diagram.svg.png)

    ![quick2](https://upload.wikimedia.org/wikipedia/commons/6/6a/Sorting_quicksort_anim.gif)

  - Partitioning spends time by O(n) because it needs time in proportion with the length of an array every step.
  - However, it is not clear whether the two sub-problems are the same size when the pivot is the minimum or maximum element. In this case, the time complexity is O(n^2).


## [Karatsuba Algorithm](https://en.wikipedia.org/wiki/Karatsuba_algorithm)

- It is used to multiply two very large numbers, which are needed to be stored in the array.
- General process to multiply two numbers.

    ``` text
          1 2 3 4
        x 5 6 7 8
    -------------
          9 8 7 2
        8 6 3 8
      7 4 0 8
    6 1 7 0
    -------------
    7 0 0 6 6 5 2

    Or,
             1  2  3  4
          x  5  6  7  8
    -------------------
             8 16 24 32
          7 14 21 28
       6 12 18 24
    5 10 15 20
    -------------------
    5 16 34 60 61 52 32
    ```

- Simple algorithm: `O(n^2)`, where n is the length of the given number.

    ``` c++
    // Carry (https://en.wikipedia.org/wiki/Carry_(arithmetic))
    void normalize(vector<int>& num) {
        num.push_back(0);
        for (int i = 0; i < num.size(); i++) {
            if (num[i] < 0) {
                int borrow = (abs(num[i]) + 9) / 10;
                num[i+1] -= borrow;
                num[i] += borrow * 10;
            } else {
                num[i+1] += num[i] / 10;
                num[i] %= 10;
            }
        }
        while (num.size() > 1 && num.back() == 0)
            num.pop_back();
    }

    // Returns the result of multiplying two large numbers.
    // For instance, [3, 2, 1] means 123.
    vector<int> multiply(const vector<int>& a, const vector<int>& b) {
        vector<int> c(a.size() + b.size() + 1, 0);
        for (int i = 0; i < a.size(); i++)
            for (int j = 0; j < b.size(); j++)
                c[i+j] += a[i] * b[j];
        normalize(c);
        return c;
    }
    ```

- Advanced algorithm
  - Divide a number into half, and then we can get 4 pieces from two numbers.
  - Mutliply total 4 times. (except the power of 10 because it is calculated using a shift operator.)
  
    ``` text
    Assume that A and B are 256 digits.
    Each number could be represented as divided into half such as:

        A = A1 * 10^128 + A0
        B = B1 * 10^128 + B0
    
        A * B = (A1 * 10^128 + A0) * (B1 * 10^128 + B0)
              = A1 * B1 + (A1 * B0 + A0 * B1) * 10^128 + A0 * B0
    ```

  - But, its time complexity is O(n^2).
  - In Karatsuba algorithm, it is possible to calculate using multiplying three times.

    ``` text
    A * B = A1 * B1 * 10 ^256 + (A1 * B0 + A0 * B1) * 10^128 + A0 * B0

    In this case, we asssume that

        z0 = A0 * B0
        z1 = (A1 * B0 + A0 * B1)
        z2 = A1 * B1

    It is easy to get z0 and z2 with only one multipying.
    But, z1 uses it two times.
    
    In case of z1, it could be changed as like below.

        (A0 + A1) * (B0 + B1) = A0 * B0 + A1 * B0 + A0 * B1 + A1 * B1

        -> A1 * B0 + A0 * B1 = (A0 + A1) * (B0 + B1) - A0 * B0 - A1 * B1
                          z1 = (A0 + A1) * (B0 + B1) - z0 - z1
    ```

  - Karatsuba Algorithm

    ``` c++
    // a += b * (10^k);
    void addTo(vector<int>& a, const vector<int>& b, int k);
    
    // a -= b; (a >= b)
    void subFrom(vector<int>& a, const vector<int>& b);
    
    // Return the multiplication of two big integers.
    vector<int> karatsuba(const vector<int>& a, const vector<int>& b)
    {
        int an = a.size(), bn = b.size();
        // Assume that the length of a is not shorter than the length of b.
        if (an < bn) return karatsuba(b, a);
        // base case: a or b is empty.
        if (an == 0 || bn == 0) return vector<int> ();
        // base case: the length of a is short.
        if (an <= 50) return multiply(a, b); // O(n^2)
        int half = an / 2;
        vector<int> a0(a.begin(), a.begin() + half);
        vector<int> a1(a.begin() + half, a.end());
        vector<int> b0(b.begin(), b.begin() + min<int>(b.size(), half));
        vector<int> b1(b.begin() + min<int>(b.size(), half), b.end());

        // z2 = a1 * b1
        vector<int> z2 = karatsuba(a1, b1);
        // z0 = a0 * b0
        vector<int> z0 = karatsuba(a0, b0);
        addTo(a0, a1, 0); // a0 = a0 + a1
        addTo(b0, b1, 0); // b0 = b0 + b1
        // z1 = (a0 * b0) - z0 - z2
        vector<int> z1 = karatsuba(a0, b0);
        subFrom(z1, z0);
        subFrom(z1, z2);
        // ret = z0 + z1 * 10^half + z2 * 10^(half*2)
        vector<int> ret;
        addTo(ret, z0, 0);
        addTo(ret, z1, half);
        addTo(ret, z2, half + half);
        return ret;
    }
    ```

  - Time Complexity: `O(3^k)` = `O(3^(lg(n))` = `O(n^(lg(3))`
    - where _n_ is the length of an array, and _k_ is the depth of the recursive call when _n_ is 2^k. (k=lg(n))
    - in each step, the number of multiplications increases triple.
    - addTo() and subFrom() are proportional the length, _n_.
    - Notice that it is slower than O(n^2) algorithm if the size of input is small.
