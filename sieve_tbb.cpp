#include <iostream>
#include <stdlib.h>
#include <sys/time.h>
#include "tbb/parallel_for.h"
#include "tbb/task_scheduler_init.h"
using namespace std;

int nth_prime=10000000;
int num_of_threads=4;
int arr[10000000];
int size=179424674;
int main() {
        int q,k;
        struct timeval start,end;
        tbb::task_scheduler_init init(num_of_threads);

        gettimeofday(&start,NULL);
        int i,j,m=0;
        char *sieve = static_cast<char*>(calloc(size, 1));
        for(int i=2; i*i <= size; i++) {
                if (!sieve[i]) {
                        tbb::parallel_for(i+i, size, i, [=](int j) { sieve[j] = 1; });
                }
        }
        for (i=2; i<size; i++) {
                if (!sieve[i])  arr[m++]=i;
        }
        free(sieve);
        q = nth_prime;
        for(i=1;i<q;i++) {}
		
        gettimeofday(&end,NULL);

        double myTime = (end.tv_sec+(double)end.tv_usec/1000000) - (start.tv_sec+(double)start.tv_usec/1000000);
        cout << q << "th prime is: " << arr[q-1] << "\n";
        cout << "Total time: " << myTime << " seconds." << "\n";
        return 0;
}