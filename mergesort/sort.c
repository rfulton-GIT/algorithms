#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int min(int a, int b){
	return (a < b) ? a : b;
}
void swap(int* A, int i,int j){
	int tmp = A[j];
	A[j] = A[i];
	A[i] = tmp;
}

void printArr(int *arr, int size){
	for (int i = 0; i < size; ++i){
		printf("%d ", arr[i]);
	}
	printf("\n");
}

int* bubble_sort(int *A, int size) {
	int* inOrder = malloc(size*sizeof(int));
	//Deepcopy
	for (int i = 0; i < size; ++i){
		inOrder[i] = A[i];
	}
	for (int i = 0; i < size; ++i){
		for (int j = size-1; j > i; --j){
			if (inOrder[j] < inOrder[j-1]){
				swap(inOrder,j,j-1);
			}
		}
	}
	return inOrder;
}

/*
sorts not in-place, in time O(nlgn)
*/
int* merge_sort(int *A, int size) {
	int *B = malloc(size*sizeof(int));
	int *C = malloc(size*sizeof(int));
	int *tmp_p;
	int p,q;
	int insert;
	//deepcopy array A
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
	return C;
}


int main() {
	int L = 100000;
	int A[100000];
	long int t1, t2, t3;
	for (int i = 0; i < L; ++i){
		A[i] = rand() % L;
	}
	time (&t1);
	int *merge = merge_sort(A, L);
	time (&t2);
	int *bbl = bubble_sort(A,L);
	time(&t3);
	printf("merge sort took %ld s, bubble sort took %ld s.\n", t2 - t1, t3-t2);
	int equality = 1;
	for (int i = 0; i < L; ++i){
		if (merge[i] != bbl[i]) {
			equality = 0;
			break;
		}
	}
	printf("mergesort == bubblesort : %s\n", equality ? "true" : "false");
	return 0;
}




