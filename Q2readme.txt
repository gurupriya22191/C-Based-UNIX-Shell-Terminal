This program demonstrates the use of Linux’s scheduling policies for different processes. Three processes have been created, where each of the three processes count from 1 to 2^32. The three processes are reated with fork() and thereafter the child processes uses execl() family system calls to run another C file which will do the counting mentioned above.

Process 1 : Uses SCHED OTHER scheduling discipline with standard priority (nice:0).
Process 2 : Uses SCHED RR scheduling discipline with default priority.
Process 3 : Uses SCHED FIFO scheduling discipline with default priority.


Each of these processes times the process of counting from 1 to 2^32. To time the execution, the parent process gets the clock timestamp (using clock_gettime()) before the fork and after each process terminates (the event of which could be identified when the blocking system call waitpid() returns).

These three schedulers have been benchmarked by changing the scheduling classes of the three processes. Histograms are generated showing which scheduler completes the task when, depending upon the scheduling policy, with one axis showing the time to complete, and the other showing the scheduling priorities. (Python has been used to plot the histogram.)

Inorder to correctly benchmark scheduling policy, all the three processes are in READY state and then it is the policy that decides which process to give the CPU first.

As we analyze the output we can note that the Process 3 which Uses SCHED FIFO scheduling discipline takes the least amount of time. 
The Process 2 which uses SCHED RR scheduling discipline has an intermediate time of execution. 
And the Process 1 which uses SCHED OTHER scheduling discipline takes the largest amount of time for execution.