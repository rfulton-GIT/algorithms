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

void swap(int* A, int i,int j){
	int tmp = A[j];
	A[j] = A[i];
	A[i] = tmp;
}


/*
sorts not in-place, in time O(nlgn)
*/
int bubble_count(int *A, int size){
	int count = 0;
	for (int i = 0; i < size - 1; ++i){
		for (int j = i + 1; j<size; ++j){
			count += A[j] < A[i];
		}
	}
	return count;
}

int merge_count(int *A, int size) {
	int *B = malloc(size*sizeof(int));
	int *C = malloc(size*sizeof(int));

	int *tmp_p;
	int p,q;
	int insert;
	int count = 0;
	int caboose;
	// deepcopy the array
	for (int i = 0; i < size; ++i){
		C[i] = A[i];
	}

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
					count += (start+interval) - p;
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
	free(B);
	free(C);
	return count;
}

int main() {
	int L = 10000;
	int A[10000];
	int cbbl, cmerge;
	for (int i = 0; i < L; ++i){
		A[i] = rand() % L;
	}
	cbbl = bubble_count(A,L);
	cmerge = merge_count(A,L);
	printf("cbbl == cmerge: %s\n", cbbl == cmerge ? "true" : "false");
	return 0;
}




