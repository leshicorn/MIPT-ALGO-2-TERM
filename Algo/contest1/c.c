#define _CRT_SECURE_NO_WARNINGS
#include "stdio.h"
#include "string.h"
#include "stdlib.h"

#define min(a, b) (((a) < (b)) ? (a) : (b))


typedef long long ll;

const long long N = 1e5 + 1;
#define _MOD_CONST_ 1073741824;




ll* allocateArray(int size) {
	return (ll*)malloc(size * sizeof(ll));
}

void copyArray(ll* to, ll* from, int f, int t) {
	for (int i = 0; f + i < t; i++) {
		to[i] = from[f + i];
	}
}

void merge(ll* b, ll* c, ll* a, int sizeB, int sizeC) {
	int i = 0;
	int j = 0;
	int p = 0;
	while (i < sizeB && j < sizeC) {
		if (b[i] <= c[j]) {
			a[p++] = b[i];
			i++;
		}
		else {
			a[p++] = c[j];
			j++;
		}
	}
	while (i < sizeB) {
		a[p++] = b[i];
		i++;
	}
	while (j < sizeC) {
		a[p++] = c[j];
		j++;
	}
}



void mergeSort(ll* a, int size) {
	if (size == 1) {
		return;
	}
	int pivot = size / 2;
	ll* b = allocateArray(pivot);
	ll* c = allocateArray(size - pivot);
	copyArray(b, a, 0, pivot);
	copyArray(c, a, pivot, size);
	mergeSort(b, pivot);
	mergeSort(c, size - pivot);
	merge(b, c, a, pivot, size - pivot);
	free(b);
	free(c);
}


int check(ll mid, ll* points, int n, int k) {
	ll cnt = 0;
	ll start = points[0];
	ll temp = start + mid;
	ll i = 1;
	while (i < n) {
		while (i < n && temp >= points[i]) {
			i++;
		}
		cnt++;
		if (i >= n) {
			break;
		}
		temp = points[i] + mid;
	}
	return (k >= cnt) ? 1 : 0;
}



int main() {
	int n, k;
	if (scanf("%d%d", &n , &k) == 1) {

	}
	ll* points = allocateArray(n);
	for (int i = 0; i < n; ++i) {
		if (scanf("%lld", &points[i]) == 1) {

		}
	}
	ll l = 0;
	ll r = 2147483647;
	mergeSort(points, n);
	ll mid;
	while (r - l > 1) {
		mid = (l + r) >> 1;
		if (check(mid, points, n, k)) {
			r = mid;
		}
		else {
			l = mid;
		}
	}
	if (check(l, points, n, k) == 1) {
		printf("%lld", l);
		free(points);
		return 0;
	}
	if (check(mid, points, n, k) == 1) {
		printf("%lld", mid);
		free(points);
		return 0;
	}
	if (check(r, points, n, k) == 1) {
		printf("%lld", r);
		free(points);
		return 0;
	}
}