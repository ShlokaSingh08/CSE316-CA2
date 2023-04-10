#include<stdio.h>
#include<stdlib.h>

struct process {
    int pid; // process ID
    int burst_time; // burst time (estimated run time)
    int waiting_time; // waiting time
    int priority; // priority based on estimated run time and waiting time
};

int main() {
    int n, i, j;
    float avg_waiting_time = 0;
    printf("Enter the number of processes: ");
    scanf("%d", &n);
    
    // allocate memory for processes
    struct process *proc = (struct process*)malloc(n * sizeof(struct process));
    
    // read process details from user
    for(i=0; i<n; i++) {
        printf("Enter the burst time for process %d: ", i+1);
        scanf("%d", &proc[i].burst_time);
        proc[i].pid = i+1;
        proc[i].waiting_time = 0;
    }
    
    printf("\nGantt chart:\n");
    int total_time = 0;
    while(1) {
        // calculate priorities
        for(i=0; i<n; i++) {
            if(proc[i].burst_time > 0) {
                proc[i].priority = 1 + proc[i].waiting_time / proc[i].burst_time;
            } else {
                proc[i].priority = -1; // process completed
            }
        }
        
        // find process with highest priority
        int highest_priority = -1, highest_priority_proc;
        for(i=0; i<n; i++) {
            if(proc[i].priority > highest_priority) {
                highest_priority = proc[i].priority;
                highest_priority_proc = i;
            }
        }
        
        // update waiting time and check if all processes are completed
        int completed = 1;
        for(i=0; i<n; i++) {
            if(i != highest_priority_proc) {
                if(proc[i].burst_time > 0) {
                    proc[i].waiting_time++;
                    completed = 0;
                }
            }
        }
        
        // if all processes completed, exit loop
        if(completed) {
            break;
        }
        
        // execute process with highest priority for 1 unit of time
        printf("%d | P%d ", total_time, proc[highest_priority_proc].pid);
        proc[highest_priority_proc].burst_time--;
        total_time++;
    }
    printf("%d\n", total_time);
    
    // calculate waiting time for each process and average waiting time
    for(i=0; i<n; i++) {
        proc[i].waiting_time = total_time - proc[i].burst_time;
        avg_waiting_time += proc[i].waiting_time;
        printf("Waiting time for process P%d = %d\n", proc[i].pid, proc[i].waiting_time);
    }
    avg_waiting_time /= n;
    printf("Average waiting time = %.2f\n", avg_waiting_time);
    
    // free memory allocated for processes
    free(proc);
    
    return 0;
}
