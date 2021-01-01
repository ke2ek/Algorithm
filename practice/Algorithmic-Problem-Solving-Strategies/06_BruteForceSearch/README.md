# Brute-Force Search or Exhaustive Search

## [Brute-Force Search](https://en.wikipedia.org/wiki/Brute-force_search)

- In computer science, brute-force search or exhaustive search, also known as generate and test, is a very general problem-solving technique and algorithmic paradigm that consists of **systematically enumerating all possible candidates for the solution** and checking whether each candidate satisfies the problem's statement.
- For example, to calculate the shortest path, we are able to try out all the cases of the problem. That way, we can find the shortest path among all the distances we got. (If the number of cases does not exceed the upper bound)

## [Recursion](https://en.wikipedia.org/wiki/Recursion_(computer_science))

- In computer science, recursion is a method of solving a problem **where the solution depends on solutions to smaller instances of the same problem**.
- Such problems can generally be solved by **iteration**, but this needs to identify and index the smaller instances at programming time.
- Example: sum

    ``` c++
    // Requirement: n >= 1
    // Return the sum of the range [0, n].

    int iterativeSum(int n) {
        int ret = 0;
        for (int i = 1; i <= n; i++)
            ret += i;
        return ret;
    }

    int recursiveSum(int n) {
        if (n == 1) return 1; // base case
        // Take one piece from the given problem.
        return n + recursiveSum(n - 1);
    }
    ```
    
- A recursive function definition has one or more `base cases`, meaning input(s) for which the function produces a result trivially (without recurring), and one or more recursive cases, meaning input(s) for which the program recurs (calls itself).
- The recursive call replaces the iteration inside a function, which it is useful if the iteration has a nested structure.
- Example: pick 4 elements among N elemnts.

    ``` c++
    for (int i = 0; i < n; i++)
        for (int j = i+1; j < n; j++)
            for (int k = j+1) k < n; k++)
                for (int l = k+1; l < n; l++)
                    cout << i << " " << j << " " << k << " " << l << endl;

    // We need to think about picking 5 or more elements.
    // Will you just extend the nested iteration to 5 or more?
    ```

    ``` c++
    // n : the number of elements
    // picked : previously selected elements
    // toPick : elements to pick next
    void pick(int n, vector<int>& picked, int toPick) {
        // base case: if we can choose nothing, print the picked elements.
        if (toPick == 0) { printPicked(picked); return; }
        // Get the smallest number possible.
        int smallest = picked.empty() ? 0 : picked.back() + 1;
        // In this step, choose one element.
        for (int next = smallest; next < n; next++) {
            picked.push_back(next);
            pick(n, picked, toPick - 1);
            picked.pop_back();
        }
    }
    ```
