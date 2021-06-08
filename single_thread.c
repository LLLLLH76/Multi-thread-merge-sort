#include <stdio.h>
#include <stdlib.h>
#include <malloc.h>
#include <sys/time.h>

#define N 10000
int array[N];

void merge(int left, int m, int right){
    int length = right - left + 1;
	int* temp = (int*)malloc(sizeof(int) * length);
	int i, j, k;
	i = left;
	j = m + 1;
	k = 0;
	while (i <= m && j <= right){
		if (array[i] < array[j])
			temp[k++] = array[i++];
		else
			temp[k++] = array[j++];
	}
	while (i <= m)
		temp[k++] = array[i++];
	while (j <= right)
		temp[k++] = array[j++];
	k = 0;
	for(i = left; i <= right; i++)
		array[i] = temp[k++];
	free(temp);
}

void sort(int start, int end){
	if(start < end){
		int mid = (end + start) / 2;
		int start1 = start;
		int end1 = mid;
		int start2 = mid+1;
		int end2 = end;
		sort(start1, end1);
		sort(start2, end2);
		merge(start, mid, end);
	}
}

int main() {
	for(int i = 0; i < N; i++)
		array[i] = N - i;
	struct timeval tv_begin, tv_end;
    gettimeofday(&tv_begin, NULL);
	sort(0, sizeof(array)/sizeof(int) - 1);
	gettimeofday(&tv_end, NULL);
	printf("single_thread: %ld usec\n", (tv_end.tv_sec*1000000+tv_end.tv_usec - tv_begin.tv_sec*1000000+tv_begin.tv_usec)/1000 );
	//for (int i = 0; i < sizeof(array)/sizeof(int); i++) {
	//	printf("%d ", array[i]);
	//}
	return 0;
}
