#include <iostream>
#include <cmath>
#include <string.h>

const int MAX_N = 64;
unsigned char sieve[(MAX_N + 7) / 8];

inline bool isPrime(int k) {
	return sieve[k >> 3] & (1 << (k & 7)); // sieve[k/8] & (k % 8)
}

inline void setComposite(int k) {
	sieve[k >> 3] &= ~(1 << (k & 7));
}

void eratosthenes(int n) {
	memset(sieve, 255, sizeof(sieve));
	setComposite(0);
	setComposite(1);
	int sqrtn = int(sqrt(n));
	for (int i = 2; i <= sqrtn; i++) {
		if (isPrime(i))
			for (int j = i*i; j <= n; j += i)
				setComposite(j);
	}
}

int main() {
	eratosthenes(MAX_N);
	for (int i=1 ;i<MAX_N; i++) {
		printf("%d is prime? %d\n", i, isPrime(i));
	}
	return 0;
}
