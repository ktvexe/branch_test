#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <stdint.h>

#define likely(x)      __builtin_expect(!!(x), 1)
#define unlikely(x) __builtin_expect(!!(x), 0)
static inline __attribute__((always_inline))
void get_cycles(unsigned *high,unsigned *low)
{
    asm volatile ("CPUID\n\t"
                    "RDTSC\n\t"
                    "mov %%edx, %0\n\t"
                    "movl %%eax, %1\n\t": "=r" (*high), "=r" (*low)::"%rax","%rbx","%rcx","%rdx"
                 );
}

static inline __attribute__((always_inline))
void get_cycles_end(unsigned *high,unsigned *low){

    asm volatile("RDTSCP\n\t"
            "mov %%edx, %0\n\t"
            "mov %%eax, %1\n\t"
            "CPUID\n\t": "=r" (*high), "=r" (*low)::"%rax","%rbx","%rcx","%rdx"
            );
}

static inline __attribute__((always_inline))
uint64_t diff_in_cycles(unsigned high1,unsigned low1,unsigned high2,unsigned low2){
    uint64_t start,end;
    start = ( ((uint64_t)high1 << 32) | low1 );
    end = ( ((uint64_t)high2 << 32) | low2 );
    return end-start;
}


void merge(int src1[], int src2[], int dst[], int n)
{
    int i1 = 0, i2 = 0, id = 0;
    while (i1 < n && i2 < n) {
#if defined(NORMAL)
    dst[id++] = (src1[i1] < src2[i2]) ?
                    src1[i1++] : src2[i2++];

#elif defined(UNLIKELY)
    dst[id++] = (unlikely(src1[i1] < src2[i2])) ?
                    src1[i1++] : src2[i2++];
#elif defined(LIKELY)
    dst[id++] = (likely(src1[i1] < src2[i2])) ?
                    src1[i1++] : src2[i2++];
#elif defined(BITWISE)
    int t = src1[i1] - src2[i2];
        dst[id++] = (~t & src1[i1++]) + (t & src2[i2++]);
#endif
    
    }
    while (i1 < n)
        dst[id++] = src1[i1++];
    while (i2 < n)
        dst[id++] = src2[i2++];
}

int main(){
    int num = 3000;
    int arr1[num];
    int arr2[num];
    unsigned timec_high1,timec_low1,timec_high2,timec_low2;
    arr1[0]=0;
    arr2[0]=3;
    srand(time(NULL));
    for(int i =1;i< num;i++){
        arr1[i]=(rand()%10)+arr1[i-1];
        arr2[i]=(rand()%10)+arr2[i-1];
    }

    int dest[2*num];
    get_cycles(&timec_high1,&timec_low1);
    merge(arr1,arr2,dest,num);
    get_cycles_end(&timec_high2,&timec_low2);
    printf("DONE %ld\n",diff_in_cycles(timec_high1,timec_low1,timec_high2,timec_low2));
}
