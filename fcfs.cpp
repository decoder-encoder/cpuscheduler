#include <iostream>
#include <vector>
#include <algorithm>
#include <queue>
#include <iomanip>
using namespace std;

struct process {
    int pid;
    int arrival_time;
    int burst_time;
    int completion_time;
    int turnaround_time;
    int waiting_time;
};

void sortByArrival(process proc[], int n) {
    sort(proc, proc + n, [](process a, process b) {
        return a.arrival_time < b.arrival_time;
    });
}

void findCompletionTime(process proc[], int n) {
    proc[0].completion_time = proc[0].arrival_time + proc[0].burst_time;
    for (int i = 1; i < n; i++) {
        if (proc[i].arrival_time > proc[i - 1].completion_time) {
            proc[i].completion_time = proc[i].arrival_time + proc[i].burst_time; 
        } else {
            proc[i].completion_time = proc[i - 1].completion_time + proc[i].burst_time;
        }
    }
}

void findTurnaroundTime(process proc[], int n) {
    for (int i = 0; i < n; i++) {
        proc[i].turnaround_time = proc[i].completion_time - proc[i].arrival_time;
    }
}

void findWaitingTime(process proc[], int n) {
    for (int i = 0; i < n; i++) {
        proc[i].waiting_time = proc[i].turnaround_time - proc[i].burst_time;
    }
}

void calculateFCFS(process proc[], int n) {
    sortByArrival(proc, n);
    findCompletionTime(proc, n);
    findTurnaroundTime(proc, n);
    findWaitingTime(proc, n);
}

void printFCFS(process proc[], int n) {
    cout << "\nFCFS Scheduling:\n";
    cout << "PID\tAT\tBT\tCT\tTAT\tWT\n";
    for (int i = 0; i < n; i++) {
        cout << proc[i].pid << "\t"
             << proc[i].arrival_time << "\t"
             << proc[i].burst_time << "\t"
             << proc[i].completion_time << "\t"
             << proc[i].turnaround_time << "\t"
             << proc[i].waiting_time << "\n";
    }
}

void printAverages(process proc[], int n) {
    float total_tat = 0, total_wt = 0;
    for (int i = 0; i < n; i++) {
        total_tat += proc[i].turnaround_time;
        total_wt += proc[i].waiting_time;
    }
    cout << fixed << setprecision(2);
    cout << "\nAverage Turnaround Time: " << total_tat / n << "\n";
    cout << "Average Waiting Time: " << total_wt / n << "\n";
}

int main() {
    int n;
    cout << "Enter number of processes: ";
    cin >> n;

    process proc[n];
    cout << "Enter process details (Arrival Time, Burst Time):\n";
    for (int i = 0; i < n; i++) {
        proc[i].pid = i + 1;
        cout << "Process " << proc[i].pid << ": ";
        cin >> proc[i].arrival_time >> proc[i].burst_time;
    }

    calculateFCFS(proc, n);
    printFCFS(proc, n);
    printAverages(proc, n);

    return 0;
}