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
    int completion_time;
    int turnaround_time;
    int waiting_time;
};

void calculatetimes(process proc[],int n,int quannum){
    int remainingtime[n];
    for (int i=0;i<n;i++){
        remainingtime[i] = proc[i].burst_time;
    }
    int currenttime = 0;
    bool alldone = false;
    while(!alldone){
        alldone = true;
        for(int i=0;i<n;i++){
            if(remainingtime[i] > 0){
                alldone = false;
                if(remainingtime[i] > quannum){
                    currenttime = currenttime + quannum;
                    remainingtime[i] = remainingtime[i] - quannum;
                }
                else{
                    currenttime = currenttime + remainingtime[i];
                    proc[i].completion_time = currenttime;
                    remainingtime[i] = 0;
                }
            }
        }
    }
}

void findturnaround_time(process proc[] ,int n){
    for(int i=0;i<n;i++){
        proc[i].turnaround_time = proc[i].completion_time - proc[i].arrival_time;
    }
}

void findwaiting_time(process proc[],int n){
    for(int i=0;i<n;i++){
        proc[i].waiting_time = proc[i].turnaround_time - proc[i].burst_time;
    }
}

void printRR(process proc[],int n){
    cout << "RR Scheduling" << endl;
    cout <<"Pid\tArrival time\tBurst time\tCompletion time\tTurnaround time\tWaiting time"<<endl;
    for(int i=0;i<n;i++){
        cout<<proc[i].pid<<"\t\t"<<proc[i].arrival_time<<"\t\t"<<proc[i].burst_time<<"\t\t"<<
        proc[i].completion_time<<"\t\t"<<proc[i].turnaround_time<<"\t\t"<<proc[i].waiting_time<<endl;
    }
}


int main(){
    int n,quannum;
    cout << "Enter number of processes: ";
    cin >> n;
    cout << "Enter time quantum: ";
    cin >> quannum;
    process proc[n] ;
    cout << "Enter the process details (Pid, Arrival time, Burst time)" << endl;
    for(int i=0;i<n;i++){
        cout << " Enter for process "<< i+1 << endl;
        proc[i].pid = i+1;
        cin >> proc[i].arrival_time>>proc[i].burst_time;
    }

    calculatetimes(proc,n,quannum);
    findturnaround_time(proc,n);
    findwaiting_time(proc,n);
    printRR(proc,n);
    
}