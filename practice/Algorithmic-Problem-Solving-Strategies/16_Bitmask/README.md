# Bitmask

## Basic

- a AND b: a & b
- a OR b: a | b
- a XOR b: a ^ b
- NOT a: ~a
- b-bit Left Shift: a << b  == a * (2^b)
- b-bit Right Shift: a >> b == a / (2^b)

## Tips

- Priority: < !=/==

    ``` c++
    int c = (6 & 4 == 4);    // (6 & 1) == 0
    int d = ((6 & 4) == 4);// (4 == 4) == 1
    ```

- Overflow

    ``` c++
    // Error at (1 << b) in case b >= 32
    // Integer is 32-bit, so overflow occurs
    bool isBitSet(unsigned long long a, int b) {
        return (a & (1 << b)) > 0;
    }
    
    // Good. Not used `signed` type.
    bool isBitSet(unsigned long long a, unsigned long long b) {
        return (a & (1 << b)) > 0;
    }
    ```

## Implement Set with Bitmask

- Each bit means whether there is an element or not.
    - 2^i == the value of i-th bit: 1 means i-th element exists but 0 means it does not exists.

- 0 means `Empty Set`.

    ``` c++
    bool isEmpty(int bitset) {
        return (bitset == 0);
    }
    ```

- Check if it is full

    ``` c++
    // (1 << N) - 1 is that all N bits is up.
    bool isFull(int bitset, int size) {
        return (bitset == (1 << size) - 1);
    }
    ```

- Add i-th element: `bitset |= (1 << i);`
- Remove i-th element: `bitset &= ~(1 << i);`
    - DO NOT USE: bitset -= (1 << i);
    - Minus operation works in case bitset always has i-th element.
    - Error occurs when bitset does not have i-th element.
- Check presence: `if (bitset & (1 << i)) { ... }`
    - bitset & (1 << i) == 0 or (1 << i)
    - bitset & (1 << i) != 1, if bitset has i-th element.
- Toggle i-th element: `bitset ^= (1 << i);`
- Operation of two set

    ``` c++
    int added = (a | b);            // union
    int intersection = (a & b);        // intersection
    int removed = (a & ~b);        // difference of sets
    int toggled = (a ^ b);            // union - intesection
    ```

- Get the number of 1 (up-bit)
    - gcc/g++: [`__builtin_popcount(bitset)`]()
    - Visual C++: [`__popcnt(bitset)`]()
    - Java: [`Integer.bitCount(bitset)`]()

- Get the minimum element, the right-most 1 bit
    - Counts how many 0 bit the end of the binary format of bitset has.
    - gcc/g++: [`__builtin_ctz(bitset)`]()
    - Visual C++: [`__BitScanForward(&index, bitset)`]()
    - Java: [`Integer.numberOfTrailingZeros(bitset)`]()
    - Using Two's complement

        ``` c++
        int firstBit = (bitset & -bitset);
        // -bitset == (~bitset) + 1
        ```

- Remove the minimum element: `bitset &= (bitset - 1);`
    - ex: 1101100 = 108 --> 108 - 1 = 1101000 --> 108 & 107 = 1101000 = 104
- Traverse all subset

    ``` c++
    for (int subset = bitset; bitset; bitset = ((subset-1) & bitset)) {
        // ...
    }
    // Notice that empty set is not visited.
    ```
- Define an array of range, [0, 15], as only one `unsigned long long` type

    ``` c++
    typedef unsigned long long uint64;
    // Return the value of the index in mask.
    int get(uint64 mask, int index) {
        return (mask >> (index << 2)) & 15;
    }
    // Return the conversion from the index to the value.
    uint64 set(uint64 mask, int index, uint64 value) {
        return mask & ~(15LL << (index <<2)) | (value << (index << 2));
    }
    ```

