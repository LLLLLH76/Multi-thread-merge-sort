#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>
#include <sys/time.h>

typedef struct Parameter{
	int start, end;
}Parameter;

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

void sort(Parameter* p)
{
    int start = p->start;
    int end = p->end;
	if (start < end) {
		pthread_t thread1, thread2;
		Parameter p1, p2;
		int mid = (end + start) / 2;
		p1.start = start;
		p1.end = mid;
		p2.start = mid+1;
		p2.end = end;
		pthread_create(&thread1, NULL, (void*)sort, (void*)&p1);
		pthread_create(&thread2, NULL, (void*)sort, (void*)&p2);
		pthread_join(thread1, NULL);
		pthread_join(thread2, NULL);
		merge(start, mid, end);
	}
}

int main(){
	for(int i = 0; i < N; i++)
		array[i] = N - i;
	pthread_t init_thread;
	Parameter p;
	p.start = 0;
	p.end = sizeof(array)/sizeof(int) - 1;
	struct timeval tv_begin, tv_end;
    gettimeofday(&tv_begin, NULL);
	pthread_create(&init_thread, NULL, (void*)sort, (void*)&p);
	pthread_join(init_thread, NULL);
	gettimeofday(&tv_end, NULL);
	printf("multi_thread: %ld usec\n", (tv_end.tv_sec*1000000+tv_end.tv_usec - tv_begin.tv_sec*1000000+tv_begin.tv_usec)/1000 );
	//for (int i = 0; i < sizeof(array)/sizeof(int); i++) {
	//	printf("%d ", array[i]);
	//}
	return 0;
}