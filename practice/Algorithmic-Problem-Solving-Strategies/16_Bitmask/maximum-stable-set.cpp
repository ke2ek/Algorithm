/* Problem) Count the number of Maximum Stable Set
 *
 * A stable set means a set not exploding.
 * So, the maximum stable set is the exploding set
 * when one chemicals is added in the set.
 * i.e. in the maximum stable set, any kind of chemicals can not be added.
 *
 */

#include <iostream>
using namespace std;
#define MAXN 128

int n;
int explodes[MAXN]; // bitset, explodes[i] = a set of exploding with i-th chemicals

bool isStable(int set) {
	for (int i = 0; i < n; i++) {
		// if set has i-th chemicals and the exploding of i-th
		if ((set & (1 << i)) && (set & explodes[i]))
			return false;
	}
	return true;
}

int countStableSet() {
	int ret = 0;
	// check all set
	for (int set = 1; set < (1<<n); set++) {
		if (!isStable(set)) continue;
		// check if it is maximum stable set
		bool canExtend = false;
		for (int add = 0; add < n; add++) {
			// if set does not have other chemicals and the exploding of the chemicals 
			if ((set & (1 << add)) == 0 && (set & explodes[add]) == 0) { // same as `if (isStable(set | add))`
				canExtend = true;
				break;
			}
		}
		if (!canExtend) ret++;
	}
	return ret;
}

int main() {
	// Enter the n
	// Fill explodes array
	cout << "count = " << countStableSet() << endl;
	// This works well when n is a small number.
	return 0;
}
