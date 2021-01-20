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

- asdf