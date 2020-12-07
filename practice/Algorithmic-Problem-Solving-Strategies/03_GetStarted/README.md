# Get Started

## Write the code concisely and consistently.

- This is helpful to debugging easier.
- But, The code should be easy to read.


## Actively use **for-based-on-range** like `foreach`.


## Re-use the code.

- If you should write the same part in the code (maybe above 3 times), make it a function and reuse it.
- Try to write functions separately like `main()` and `solve()`.
- Ideally, one function should do one work.


## Understand the Standard Library.

- DO NOT WRITE basic algorithms like sorting, search, etc.
- Use the libraries which are provided, and understand how it works.
    - In C++, [STL(Standard Template Library)](https://www.cplusplus.com/reference/stl/)
    - In Python, [Collections](https://docs.python.org/3/library/collections.html)
- Especially, remember how time is spent on each algorithm.


## Keep the Format.

- Whenever you write a code differently, it causes mistakes.
    - Please save time to debug!
- Make your own template in advance.
- [template.cpp](../../../contest/template.cpp)


## Write the name of functions and variables clearly.

- Naming Convention
- [Google C++ Style Guide](https://google.github.io/styleguide/cppguide.html#Naming)
    - [KOR](https://jongwook.kim/google-styleguide/trunk/cppguide.xml#이름_규칙)


## Save all data after normalization.

- Normalize your data as soon as you enter or calculate it.
    - Especially, date time and string encoding/decoding format
- Ideally, the constructor in the Class do that thing.


## Separate the code and data.

- Bad

    ``` c++
    string getMonthName(int month) {
        if (month == 1) return "January";
        if (month == 2) return "February";
        ...
        return "December";
    }
    ```

- Good

    ``` c++
    const string monthName[] = {"January", "February", "March", "April", "May",
                                "June", "July", "August", "September", "October",
                                "November", "December"};

    // or direction to west, east, north, south.
    int dir[] = {0, -1, 0, 1, 0};

    void move(int y, int x) {
        for (int i = 0; i < 4; i++) {
            int ny = y + dir[i];
            int nx = x + dir[i+1];
            ...
        }
    }
    ```

## Common Mistakes

- Arithmetic Overflow
    - Remember the range of each data type.
    - If the result or the median is greater than 32-bit integer, use 64-bit long type.
    - [C++ data type](https://www.geeksforgeeks.org/c-data-types/)
- Out-of-bound
    - In C++, be careful to use index variables in an array.
- Off-by-one
    - The average of [i, j] in an array, A, is calculated by dividing the sum into `j - i + 1`, not `j - i`.
    - For example, in the range [1, 1], we divide the sum into 1, not 0.
- A typing error on constant variables.
    - For modular operation, when a divider, M, is 100000007, you might type 10000007 except for 0.
    - In C++, Python, etc, you can use it easily like `1e8` or `1e8 + 7`.
- Stack Overflow
    - Notice if your recursive function has base case.
    - Also, check if the function you wrote calls into the base case.
- Exception Handling
    - For example: the function which determine if it is a prime number.

    ``` c++
    // Bad
    bool isPrime(int n) {
        if (n % 2 == 0) return false; // even number is not prime number.
        for (int i = 2; i < n; i++)
            if (n % i == 0) return false;
        return true;
    }

    // Good
    bool isPrime(int n) {
        if (n == 1) return false; // 1 is not prime number
        if (n == 2) return true; // 2 is prime number
        if (n % 2 == 0) return false; // even number is not prime number.
        for (int i = 2; i < n; i++)
            if (n % i == 0) return false;
        return true;
    }
    ```

- Operation Priority
    - The priority of `&` is lower than the priority of `==`.
        - `if (b & 1 == 0)` == `if (b & (1 ==0))`
        - Need to modify `if ( (b & 1) == 0)`.
- Using more slowly input/output function.
    - `scanf/printf` is faster than `cin/cout`. 
- Variable Initialization
    - In Dynamic Programming, initialize the global variables certainly every new test case.
- Practice to debug with your eye.
    - Check if it works on small input.
    - Use assertion that causes error if the given condition is false.
    - Print the middle result while executing.
    - Debug with a dev tool if there is a runtime error.
- [Type Conversion](https://en.wikipedia.org/wiki/Type_conversion)
    - In C++, the type of operands is converted as like below.
        - If one operand is integer and another is double, **integer --> double**.
        - If both operands are integer or double, all converted to bigger type.
        - If both operands are smaller than integer, all converted to integer.
        - If one operand is unsigned integer and another is signed integer, both becomes unsinged integers.

        ``` c++
        unsigned char a = 17;
        short b = -18;
        int c = 2;
        unsigned int d = 0;

        cout << (a + b) * c + d << endl;
        // 4'294'967'294, not -2 because of d that is unsigned.
        ```

    - Be careful `size_t` in C++.
        - `.size()` returns unsigned integer, `size_t`.
        - In the following example, there can be out-of-bound, type conversion(from negative to big integer).

        ``` c++
        bool is Sorted(const vector<int>& seq) {
            for (int i = 0; i < seq.size() - 1; i++)
                if (seq[i] > seq[i+1])
                    return false;
            return true;
        }
        ```

