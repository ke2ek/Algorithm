# Justification Proof

## [Mathematical Induction](https://en.wikipedia.org/wiki/Mathematical_induction)

- Proof.
    - Divide what you want to prove into several steps.
    - Show the proof of concept on the first step. (=how it works)
    - Prove the next step. It means all the next steps could be valid continuously.


## [Loop Invariant](https://en.wikipedia.org/wiki/Loop_invariant)

- In computer science, a loop invariant is a property of a program loop that is true before (and after) each iteration. It is a logical assertion, sometimes checked within the code by an assertion call.
- The loop invariants will be true on entry into a loop and following each iteration, so that on exit from the loop both the loop invariants and the loop termination condition can be guaranteed.
- Example: Binary Search

    ``` c++
    // Requirement: a parameter is sorted by ascending order.
    // Assume that A[-1] = negative infinity, A[n] = positive infinity.
    // Return x (A[i-1] < x <= A[i])
    int binarySearch(const vector<int>& A, int x) {
        int n = A.size();
        int lo = -1, hi = n;
        // loop invariant 1: lo < hi
        // loop invariant 2: A[lo] < x <= A[hi]
        while (lo + 1 < hi) {
            int mid = (lo + hi) / 2;
            if (A[mid] < x) lo = mid;
            else hi = mid;
            // Also, loop invariant must be valid here.
        }
        return hi;
    }
    ```

- Example: Insertion Sort

    ``` c++
    void insertionSort(vector<int>& A) {
        for (int i = 0; i < A.size(); i++) {
            // loop invariant 1: A[0..i-1] has been sorted already.
            // Insert A[i] at one of A[0..i-1].
            int j = i;
            while (j > 0 && A[j-1] > A[i]) {
                // loop invariant 2: all the elements in A[j+1 .. i] are greater than A[j].
                // loop invariant 3: A[0..i] is always sorted, except A[j].
                swap(A[j-1], A[j]);
                --j;
            }
        }
        // According to loop invariant, A[] is sorted.
    }
    ```

- In C++, `#include <cassert>` provides the function, `assert(CONDITION)`.

    ``` c++
    int binarySearch(const vector<int>& A, int x) {
        int n = A.size();
        int lo = -1, hi = n;
        assert(lo < hi);
        while (lo + 1 < hi) {
            assert(A[lo] < x && x <= A[hi]);
            int mid = (lo + hi) / 2;
            if (A[mid] < x) lo = mid;
            else hi = mid;
        }
        return hi;
    }
    ```


## [Proof By Contradiction](https://en.wikipedia.org/wiki/Proof_by_contradiction)

- In logic and mathematics, proof by contradiction is a form of proof that establishes the truth or the validity of a proposition, by showing that assuming the proposition to be false leads to a contradiction.
- When proving that any choice is always best, `Proof By Contradiction` is used a lot.
    - We usually assume that there is better answer than we choose, and then show that it could not be.
- Generally, use the `proof by contradiction` every step to show the result of our algorithm is best, and then prove by the `mathematical induction` that it could be choose the best answer on the next step. 


## Example

- [Pigeonhole Principle](https://en.wikipedia.org/wiki/Pigeonhole_principle)
- [Constructive Proof](https://en.wikipedia.org/wiki/Constructive_proof)
    - [Stable Marriage Problem](https://en.wikipedia.org/wiki/Stable_marriage_problem)

