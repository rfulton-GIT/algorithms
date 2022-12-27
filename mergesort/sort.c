#include <stdio.h>
#include <stdlib.h>

int min(int a, int b){
	return (a < b) ? a : b;
}
void printArr(int *arr, int size){
	for (int i = 0; i < size; ++i){
		printf("%d ", arr[i]);
	}
	printf("\n");
}


/*
sorts not in-place, in time O(nlgn)
*/
void sort(int *A, int size) {
	int *B = malloc(size*sizeof(int));
	int *C = A;
	int *tmp_p;
	int p,q;
	int insert;

	for (int interval = 1; interval < size; interval = interval << 1) {
		tmp_p = C;
		C = B;
		B = tmp_p;

		for (int start = 0; start < size; start += 2*interval) {
			p = start;
			q = start + interval;
			insert = start;
			while (p < start+interval && q < min(start+2*interval, size)){
				if (*(B+q) < *(B+p)) {
					*(C+insert) = *(B+q);
					++q;		
				} else{
					*(C+insert) = *(B+p);
					++p;
				}
				++insert;
			}
			if (p == start + interval){
				while (q < min(start + 2*interval, size)) {
					*(C+insert) = *(B+q);
					++q;
					++insert;	
				}
			} else {
				while (p < min(start + interval, size)){
					*(C+insert) = *(B+p);
					++p;
					++insert;
				}
			}
			
		}
		
		
		if (interval == size) {
			break;
		}
	}
	if (A == C){
		free(B);	
	} else {
		for (int i = 0; i < size; ++i){
			A[i] = C[i];
		}
		free(C);
	}	
}


int main() {
	int bigPrime = 1000013;
	int shift = 47;
	int scalar = 101;
	int* A = malloc(bigPrime*sizeof(int));
	for (int i = 0; i < bigPrime; ++i){
		A[i] = (i+shift)*scalar % bigPrime;
	}
	printf("First 10 elements: ");
	printArr(A,10);
	sort(A,bigPrime);
	printf("First 10 elements: ");
	printArr(A,10);
	free(A);
	return 0;
}




