#include <iostream>
#include <vector>
#include <algorithm>
#include <queue>
#include <iomanip>
using namespace std;

struct process{
    int pid;
    int arrival_time;
    int burst_time;
    int remaining_time;
    int priority;
    int completion_time;
    int turnaround_time;
    int waiting_time;
    bool completed = false;
};
void priority_scheduling_non_preemptive(vector<process> &proc){
    int n = proc.size();
    int complete = 0;
    int current_time = 0;

    while(complete<n){
        int ind = -1;
        int highest_priority = INT_MAX;

        for(int i=0 ;i<n ;i++){
            if(!proc[i].completed && proc[i].arrival_time <= current_time){
                if(proc[i].priority < highest_priority ||
                    (proc[i].priority == highest_priority && 
                        (ind == -1 || proc[i].arrival_time < proc[ind].arrival_time))){
                        highest_priority = proc[i].priority;
                        ind = i;
                }
            }
        }
        if(ind != -1){
            current_time += proc[ind].burst_time;
            proc[ind].completion_time = current_time;
            proc[ind].turnaround_time = proc[ind].completion_time - proc[ind].arrival_time;
            proc[ind].waiting_time = proc[ind].turnaround_time - proc[ind].burst_time;
            proc[ind].completed = true;
            complete++;
        }
        else current_time++;
    }
}



void printPS(vector<process> &proc,int n){
    cout << " Priority Scheduling" << endl;
    cout <<"Pid\tArrival time\tBurst time\tpriority\tCompletion time\tTurnaround time\tWaiting time"<<endl;
    for(int i=0;i<n;i++){
        cout<<proc[i].pid<<"\t\t"<<proc[i].arrival_time<<"\t\t"<<proc[i].burst_time<<"\t\t"<<proc[i].priority<<"\t\t"<<
        proc[i].completion_time<<"\t\t"<<proc[i].turnaround_time<<"\t\t"<<proc[i].waiting_time<<endl;
    }
}

int main(){
    int n;
    cout << "Enter number of processes: ";
    cin >> n;
    
    vector<process> proc(n);
    cout << "Enter the process details (Arrival time, Burst time,Priority)" << endl;
    for(int i=0;i<n;i++){
        proc[i].pid = i + 1;
        cout << " Enter for process "<< i+1 << endl;
        cin >> proc[i].arrival_time >> proc[i].burst_time >> proc[i].priority;
        proc[i].remaining_time = proc[i].burst_time;  // initialize remaining time
        proc[i].completed = false;
    }
    priority_scheduling_non_preemptive(proc);
    printPS(proc,n);

}