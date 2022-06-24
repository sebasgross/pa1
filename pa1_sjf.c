//
// Created by Sebastian Grossmann on 6/23/22.
//

#include"pa1.h"
#include <math.h>
#include<time.h>
#define frand() (rand()/(double)RAND_MAX)
#define nrand() (sqrt(-2*log(frand()))*cos(2*M_PI*frand()))

heap generate_arrival_times(int n, int k){
    heap h = create_heap(n);
    for(int i = 0; i < n;i++)
        min_insert(&h, frand()*k);
    return h;
}

//heap generate_sjf(int n, int k){
//    heap h = create_heap(n);
//    int d;
//    double v;
//    for(int i = 0; i < n;i++)
//        d = k/n;
//        v = d/4.0;
//        int burst_time = (int)round(nrand()*v + d);
//        min_insert(&h, burst_time);
//    return h;
//}

int main(int argc, char** argv) {
    srand(time(NULL));
    int n = 2;
    int k = 4;
    int d = k/n;
    while(*++argv){
        if(**argv == '-' && (*argv)[1] == 'n')
            n = atoi(*++argv);
        else if(**argv == '-' && (*argv)[1] == 'k')
            k = atoi(*++argv);
        else if(**argv == '-' && (*argv)[1] == 'd')
            d = atoi(*++argv);
        else
            continue;
    }
    double v = d/4.0;
    //CLA Handling
    printf("CLA Handling!\n");
    heap arrival_times = generate_arrival_times(n,k);
    printf("# of processes: %d first 20 arrive times:\n", arrival_times.size);
    heap copy = clone(arrival_times);
    for(int i = 0; i < 20;i++)
        printf("%d\t", min_delete(&copy));
    putchar('\n');
    //FIFO requires a queue but SJF a Heap
    lnklst_queue queue = create_queue2();
    printf("1\n");
    heap2 sjf_heap = create_heap2(n);
    printf("2\n");

    int t = 0;//time of my simultor
    double att = 0.0;//keeps track of TTs sum
    process * current = NULL;
    while(!current || t < k || !is_empty3(sjf_heap)){
        while(t == get_min(arrival_times)){//new process arrives
            process p;
            p.arrival_time = t;
            p.remaining_time = p.burst_time =
                    (int)round(nrand()*v + d);
            p.tt = 0;
            p.priority_level = rand()%10 + 1;
            min_insert2(&sjf_heap, &p);
            min_delete(&arrival_times);
            printf("t=%d: a new process admitted, bt = %d\n", t, p.burst_time);
        }
        if(current == NULL && !is_empty3(sjf_heap)){
            current = (process*)malloc(sizeof(process));
            *current = min_delete2(&sjf_heap);
        }
        if(current != NULL){
            current->remaining_time--;
            if(current->remaining_time == 0){
                current->tt = (t+1) - current->arrival_time;//termination-arrival
                printf("t=%d: a process with arrival time %d and bt %d got terminated with TT = %d\n", t+1, current->arrival_time, current->burst_time, current->tt);
                att += current->tt;
                free(current);
                current = NULL;
            }
        }
        t++;
    }
    printf("FIFO Algorithm for (n,k)=(%d,%d): ATT= %.3f, d= %d, d/ATT= %.3f\n", n, k, att/n, d, d*n/att);
    return 0;
}