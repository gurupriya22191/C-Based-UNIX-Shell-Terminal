#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <sched.h>
#include <time.h>
#include <math.h>

//    Commands to run in Ubuntu
//    gcc -o Q2count_exec Q2count.c -lm
//    gcc Q2.c -o a
//    ./a

int main(){
    FILE *file = fopen("data.txt", "w");
    int pid1, pid2, pid3, status;
    struct timespec start, end;
    
    clock_gettime(CLOCK_REALTIME, &start);
    pid1 = fork();
    if (pid1 == 0) {
        sched_yield();
        sched_setscheduler(0, SCHED_OTHER, NULL);
        char *args[] = {"./Q2count_exec", NULL};
        execvp(args[0], args);
        exit(0);
    } 
    else if (pid1 > 0) {
        waitpid(pid1, &status, 0);
        clock_gettime(CLOCK_REALTIME, &end);
        double time = (end.tv_sec - start.tv_sec) + (end.tv_nsec - start.tv_nsec) / 1e9;
        printf("Time taken by P1: %.6f s\n",time);
        fprintf(file, "%.6f\n", time);
    }
    else{
        perror("Fork Failed");
    }

    clock_gettime(CLOCK_REALTIME, &start);
    pid2 = fork();
    if (pid2 == 0) {
        sched_yield();
        struct sched_param data;
        data.sched_priority = 0;
        sched_setscheduler(0, SCHED_RR, &data);
        char *args[] = {"./Q2count_exec", NULL};
        execvp(args[0], args);
        exit(0);
    } 
    else if (pid2 > 0) {
        waitpid(pid2, &status, 0);
        clock_gettime(CLOCK_REALTIME, &end);
        double time = (end.tv_sec - start.tv_sec) + (end.tv_nsec - start.tv_nsec) / 1e9;
        printf("Time taken by P2: %.6f s\n",time);
        fprintf(file, "%.6f\n", time);
    }
    else{
        perror("Fork Failed");
    }

    clock_gettime(CLOCK_REALTIME, &start);
    pid3 = fork();
    if (pid3 == 0) {
        sched_yield();
        struct sched_param data;
        data.sched_priority = 0;
        sched_setscheduler(0, SCHED_FIFO, &data);
        char *args[] = {"./Q2count_exec", NULL};
        execvp(args[0], args);
        exit(0);
    } 
    else if (pid3 > 0) {
        waitpid(pid3, &status, 0);
        clock_gettime(CLOCK_REALTIME, &end);
        double time = (end.tv_sec - start.tv_sec) + (end.tv_nsec - start.tv_nsec) / 1e9;
        printf("Time taken by P3: %.6f s\n", time);
        fprintf(file, "%.6f\n", time);
    }
    else{
        perror("Fork Failed");
    }
    fclose(file);
    return 0;
}

