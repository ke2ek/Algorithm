# Time Complexity

## [Time Complexity](https://en.wikipedia.org/wiki/Time_complexity)

- Time complexity is commonly estimated by counting the number of elementary operations performed by the algorithm, supposing that each elementary operation takes a fixed amount of time to perform.
- Since an algorithm's running time may vary among different inputs of the same size, one commonly considers the worst-case time complexity, which is the maximum amount of time required for inputs of a given size.
- We usually measure time complexity as the number of dominating(=maximum) iterations of a function.
- Example: `O(N^2)`

    ``` c++
    int majority1(const vector<int>& A) {
        int N = A.size();
        int majority = -1, majorityCount = 0;
        for (int i = 0; i < N; i++) {
            int V = A[i], count = 0;
            for (int j = 0; j < N; j++) {
                if (A[j] == V) count++;
            }
            if (count > majorityCount) {
                majorityCount = count;
                majority = V;
            }
        }
        return majority;
    }
    ```

- Example: `O(N)`

    ``` c++
    int majority2(const vector<int>& A) {
        int N = A.size();
        vector<int> count(101, 0);
        for (int i = 0; i < N; i++) {
            count[A[i]]++;
        }
        int majority = 0;
        for (int i = 1; i <= 100; i++) {
            if (count[i] > count[majority])
                majority = i;
        }
        return majority;
    }
    ```


## [Linear Time](https://en.wikipedia.org/wiki/Time_complexity#Linear_time)

- O(N), where N is the input size.

    ``` c++
    // O(N^2)
    vector<double> movingAverage1(const vector<double>& A, int M) {
        vector<double> ret;
        int N = A.size();
        for (int i = M-1; i < N; i++) {
            double partialSum = 0;
            for (int j = 0; j < M; j++)
                partialSum += A[i-j]
            ret.push_back(partialSum / M);
        }
        return ret;
    }

    // O(N)
    vector<double> movingAverage2(const vector<double>& A, int M) {
        vector<double> ret;
        int N = A.size();
        double partialSum = 0;
        for (int i = 0; i < M-1; i++)
            partialSum += A[i];
        for (int i = M-1; i < N; i++) {
            partialSum += A[i];
            ret.push_back(partialSum / M);
            partialSum -= A[i-M+1];
        }
        return ret;
    }
    ```


## [Quasilinear Time](https://en.wikipedia.org/wiki/Time_complexity#Quasilinear_time)

- Time complexity less than linear time.
- Binary Search: O(log2(N))
    - C++ provides the two binary search functions, `lower_bound()` and `upper_bound()`.


## [Polynomial Time](https://en.wikipedia.org/wiki/Time_complexity#Polynomial_time) 

- Most of algorithms take polynomial time.


## [Exponential Time](https://en.wikipedia.org/wiki/Time_complexity#Exponential_time)

- Example: Factorization


## [Big O notation](https://en.wikipedia.org/wiki/Big_O_notation)

- In computer science, big O notation is used to classify algorithms according to how their run time or space requirements grow as the input size grows.
- When speaking: O(N^2) => order and square.


## Example: [Max Sum of Continuous Part](https://en.wikipedia.org/wiki/Maximum_subarray_problem)

- Time Complexity: `O(N^3)`

    ``` c++
    const int MIN = numeric_limits<int>::min();
    
    int inefficientMaxSum(const vector<int>& A) {
        int N = A.size();
        int ret = MIN;
        for (int i = 0; i < N; i++) {
            for (int j = i; j < N; j++) {
                int sum = 0;
                for (int k = i; k <= j; k++) sum += A[k];
                ret = max(ret, sum);
            }
        }
        return ret;
    }
    ```

- Time Complexity: `O(N^2)`

    ``` c++
    int betterMaxSum(const vector<int>& A) {
        int N = A.size();
        int ret = MIN;
        for (int i = 0; i < N; i++) {
            int sum = 0;
            for (int j = i; j < N; j++) {
                sum += A[j];
                ret = max(ret, sum);
            }
        }
        return ret;
    }
    ```

- Time Complexity: `O(N * lg(N))`

    ``` c++
    int fastMaxSum(const vector<int>& A, int lo, int hi) {
        if (lo == hi) return A[lo];
        int mid = (lo + hi) / 2;
        int left = MIN, right = MIN, sum = 0;
        for (int i = mid; i >= lo; i--) {
            sum += A[i];
            left = max(left, sum);
        }

        sum = 0;
        for (int j = mid + 1; j <= hi; j--) {
            sum += A[j];
            right = max(right, sum);
        }
        
        // If there is the max-sum in one of two sub-ranges,
        int single = max(fastMaxSum(A, lo, mid), fastMaxSum(A, mid + 1, hi));
        return max(left + right, single);
    }
    ```

- Time Complexity: `O(N)`

    ``` c++
    int fastestMaxSum(const vector<int>& A) {
        int N = A.size();
        int ret = MIN, psum = 0;
        for (int i = 0; i < N; i++) {
            psum = max(psum, 0) + A[i];
            ret = max(psum, ret);
        }
        return ret;
    }
    ```

