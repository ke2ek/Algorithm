# Part Sum

## Basic

- partSum(n): sum of an array range [0,n]
- Be able to get sum of the specific range [a,b] using partSum().
    - partSum(b) - partSum(a-1)
    - Notice that time complexity is O(1).

    ``` c++
    // O(n)
    vector<int> partialSum(const vector<int> &v) 
    {
        vector<int> ret(v.size());
        ret[0] = v[0];
        for (int i=1; i<v.size(); i++) {
            ret[i] = ret[i-1] + v[i];
        }
        return ret;
    }
    
    // O(1)
    int rangeSum(const vector<int> &psum, int a, int b)
    {
        if (a == 0) return psum[b];
        return psum[b] - psum[a-1];
    }
    
    // sqpsum: the squared of partial sum
    // Return the variance of range [a,b]
    double variance(const vector<int> &sqpsum,
                    const vector<int> &psum,
                    int a, int b)
    {
        double mean = rangeSum(psum, a, b) / double(b - a + 1); // Average
        double ret = rangeSum(sqpsum, a, b);
        ret -= 2 * mean * rangeSum(psum, a, b);
        ret += (b - a + 1) * mean * mean;
        return ret / (b - a + 1);
    }
    ```

## Implement with a 2-Dimensional Array

- How to calculate the partial sum from [y1,x1] to [y2,x2]
    - sum(y1,x1,y2,x2) = pSum(y2,x2) - pSum(y2,x1-1) - pSum(y1-1,x2) + pSum(y1-1,x1-1)

    ``` c++
    int gridSum(const vector<vector<int> > &psum,
                int y1, int x1, int y2, int x2)
    {
        int ret = psum[y2][x2];
        if (y1 > 0) ret -= psum[y1-1][x2];
        if (x1 > 0) ret -= psum[y2][x1-1];
        if (y1 > 0 && x1 > 0) ret += psum[y1-1][x1-1];
        return ret;
    }
    ```

