# Dynamic Programming

## Basic

- [Dynamic programming](https://en.wikipedia.org/wiki/Dynamic_programming) is both a mathematical optimization method and a computer programming method.
- In both contexts it refers to simplifying a complicated problem by breaking it down into simpler sub-problems in a recursive manner. While some decision problems cannot be taken apart this way, decisions that span several points in time do often break apart recursively. Likewise, in computer science, if a problem can be solved optimally by breaking it into sub-problems and then recursively finding the optimal solutions to the sub-problems, then it is said to have [optimal substructure](https://en.wikipedia.org/wiki/Optimal_substructure).
- If sub-problems can be nested recursively inside larger problems, so that dynamic programming methods are applicable, then there is a relation between the value of the larger problem and the values of the sub-problems.
- There are two key attributes that a problem must have in order for dynamic programming to be applicable:
  - [optimal substructure](https://en.wikipedia.org/wiki/Optimal_substructure)
  - [overlapping sub-problems](https://en.wikipedia.org/wiki/Overlapping_subproblems)
- If a problem can be solved by combining optimal solutions to non-overlapping sub-problems, the strategy is called **divide and conquer** instead. This is why merge sort and quick sort are not classified as dynamic programming problems.


## Overlapping Sub-problems

- In computer science, a problem is said to have overlapping subproblems if the problem can be broken down into **subproblems which are reused several times** or **a recursive algorithm for the problem solves the same subproblem** over and over rather than always generating new subproblems.
- Overlapping sub-problems means that the answer from each problem can be reused for two or more larger problems by storing the answer in memory.
  - It leads to save time to operate.
  - The memory space that the result will be saved is called **cache**.
- [Memoization](https://en.wikipedia.org/wiki/Memoization) is an optimization technique used primarily to speed up computer programs by storing the results of expensive function calls and returning the cached result when the same inputs occur again.
- For example, the problem of computing the Fibonacci sequence exhibits overlapping subproblems.
  - Before memoization:

    ``` c++
    int fibonacci(int n) {
        if (n <= 2) return 1;
        return fibonacci(n - 1) + fibonacci(n - 2);
    }
    
    /* Flow:
    f(5) = f(4) + f(3) = 5
            |      |
            |      f(3) = f(2) + f(1) = 2
            |               |      |
            |               |    f(1) = 1
            |               |
            |             f(2) = 1
            |
            f(4) = f(3) + f(2) = 3
                    |       |
                    |     f(2) = 1
                    |
                    f(3) = f(2) + f(1) = 2
                             |      |
                             |      f(1) = 1
                             |
                           f(2) = 1
    */
    ```

  - After memoization

    ``` c++
    int fibonacci(int n) {
        int r = 1;
        if (cache[n - 1] != 0) r = cache[n - 1];
        else {
            if (n > 2) r = fibonacci(n - 1) + fibonacci(n - 2);
            cache[n - 1] = r;
        }
        return r;
    }

    /* Flow:
    f(5) = f(4) + f(3) = 5
            |      |
            f(4) = f(3) + f(2) = 3
                    |       |
                    f(3) = f(2) + f(1) = 2
                            |      |
                            |      f(1) = 1
                            |
                            f(2) = 1
    */
    ```

- Notice that **memoization** can be applied in case of referential transparent function.
  - [Referential transparency](https://en.wikipedia.org/wiki/Referential_transparency) means that the result returned by the function must be determined only by the input of the function.
  - There should not be any external causes such as global variables or behaviors from other program.
- Memoization Template

    ``` c++
    int cache[MAX_N][MAX_N];
    int someObscureFunction(int a, int b) {
        if (...) return ...; // Base case
        int &ret = cache[a][b];
        if (ret != -1) return ret;
        // Calculate the answer.
        // ...
        return ret;
    }

    int main() {
        // Initialize cache.
        memset(cache, -1, sizeof(cache));
    }
    ```

- But, if the cache has the type as floating points like `double` or `float`, you need to initialize the cache by iterating not calling `memset()`.
- **How to measure the time complexity in Memoization**
  - `(the # of sub-problems) * (the # of iterating in each sub-problem)`
  - Notice that this is a rule of thumb, so it may take a shorter time if most of the answers can be found only in some of the sub-problems.

## Optimal Substructure

- In computer science, a problem is said to have optimal substructure **if an optimal solution can be constructed from optimal solutions of its subproblems.**
- This property is used to determine the usefulness of dynamic programming and greedy algorithms for a problem.
  - Typically, a greedy algorithm is used to solve a problem with optimal substructure if it can be proven by induction that this is optimal at each step. 
  - **Otherwise, provided the problem exhibits overlapping subproblems as well, dynamic programming is used.**
  - If there are no appropriate greedy algorithms and the problem fails to exhibit overlapping subproblems, often a lengthy but straightforward search of the solution space is the best alternative.
- **Example.** return the `maximum-sum` of all the paths from (0, 0) to the bottom line in the given triangle. It is able to move down or to diagonal direction only.
  - Test Case

    ``` text
    6
    1  2
    3  7  4
    9  4  1  7
    2  7  5  9  4
     => 28

    1 
    2 4
    8 16 8
    32 64 32 64
    128 256 128 256 128
     => 341
    ```

  - [Recurrence Relation](https://en.wikipedia.org/wiki/Recurrence_relation) for Exhaustive Search
  
    ``` cpp
    /*
    triangle[][] is the given 2-D array
    pathSum(y, x, sum) returns the maximum sum from (y, x) to the bottom line
    when the current total sum from (0, 0) to (y, x) is sum.

    Thus,
    
    pathSum(y, x, sum) = max(pathSum(y+1, x, sum + triangle[y][x]),
                             pathSum(y+1, X+1, sum + triangle[y][x]))
    */
    int n, triangle[100][100];
    
    int pathSum(int y, int x, int sum) {
        if (y == n - 1) return sum + triangle[y][x];
        sum += triangle[y][x];
        return max(pathSum(y+1, x, sum), pathSum(y+1, x+1, sum));
    }
    ```

  - Memoization

    ``` c++
    int n, triangle[100][100];
    int cache[100][100][MAX_NUMBER * 100 + 1];

    int pathSum(int y, int x, int sum) {
        if (y == n - 1) return sum + triangle[y][x];
        int &ret = cache[y][x][sum];
        if (ret != -1) return ret;
        sum += triangle[y][x];
        return ret = max(pathSum(y+1, x, sum), pathSum(y+1, x+1, sum));
    }
    ```

  - **Problems**
    - It is waste memory space so much because the size of `cache` is determined by numbers in the given array.
    - Also, it may work such as the exhaustive search if each path sum is different. It means that there might not be overlapping sub-problems.
  - Notice that any sub-problem that the recursive call will solve is determined by the parameters, `(y, x)` because the next path will be created by the coordinate. However, `sum` has the information about which path it passed by so it is the parameter in relation to the previous path.
  - In other words, it does not need `sum` when the definition of the recursive function is changed such as:

    ``` c++
    /*
    pathSum(y, x) returns the maximum part-sum from (y, x) to the bottom line.
    
    >> NOT the sum of total path. <<

    pathSum(y, x) = max(pathSum(y+1, x), pathSum(y+1, x+1)) + triangle[y][x]
    */

    int n, triangle[100][100];
    int cache[100][100];
    
    // O(n^2)
    int pathSum(int y, int x) {
        if (y == n - 1) return triangle[y][x];
        int &ret = cache[y][x];
        if (ret != -1) return ret;
        return ret = max(pathSum(y+1, x), pathSum(y+1, x+1)) + triangle[y][x];
    }
    ```

  - In summary, it is easy to see that `sum` is useless to solve sub-problems of moving from (y,x) to the bottom line.
  - **No matter what path this sub-problem has been reached so far, it means that the remaining sub-problems can be always optimally solved.**
  - Answer: [TRIANGLEPATH.cpp](./TRIANGLEPATH.cpp)
- **REMIND.** The optimal substructure is a condition that establishes a problem and a partitioning method. This condition is established if you can easily obtain the optimal solution of the entire problem by simply having the optimal solution of each sub-problem. Regardless of the choices we've made so far, we just need to solve each part of the problem optimally, so we know the optimal solution of the overall problem.
- **Example.** return the shortest path from city A to city Z.
  - In this case, it is easy to get the answer by adding the shortest path from city A to city X and the shortest path from city X to city Z. If there are several city X, it is able to use iteration.

    ``` text
    minCost(A, Z) = minCost(A, X) + minCost(X, Z)

    Or,

    cost = INF; // minCost(A, Z)
    for X in several cities from A to Z
      cost = min(cost, minCost(A, X) + minCost(X, Z))
    ```

  - But, how should we choose the path **when tolls on the highway is less than $30?**
    - Assume that there are two paths from X to Z.
    
      ``` text
                |  Travel Time  |  Tolls  |
        PATH 1  |    2 hours    |   $10   |
        PATH 2  |    1 hour     |   $20   |
      ```
    
    - As you could see, the shortest path from X to Z is `PATH 2`.
    - What if the tolls of the path from A to X is $15? i.e. we should select `PATH 1`. (there are not any other choices.)
    - In this case, **there is not a optimal substructure** because the optimal solution of a sub-problem does not lead to the optimal solution of the entire problem.


## How To Code

1. Design the exhaustive search algorithm that returns the optimal solution among all of the answers.
2. Modify the definition of a sub-problem to obtain the answer on the following choices, rather than the answer of the entire problem including previous solutions.
3. Reduce the parameters of a recursive function if they have some information related with previous choices.
   - In case of the optimal substructure, it needs to remove parameters including the previous data. 
   - Notice that our goal is to create many overlapping sub-problems as possible.
   - The smaller the number of the input, the more overlapping sub-problems, so we can use the memoization actively.
4. Take the proper conversion for memoization if the input has a type as an array or a string.
5. Exploit the memoization!


## How to calculate number of cases

1. Design the exhaustive search algorithm that returns all the solution. To count accurately every step, it should satisfy the property for each choice such as:
   - All cases should be included in this choice.
   - Any case does not be included in two or more choices.
2. Transform or reduce the input of a recursive function associated with previous data, as if solving an optimization problem.
3. Make sure that the recursive function calls always the cases which choose next sub-problems.
4. Exploit the memoization!

