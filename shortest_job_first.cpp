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

void findSJF(process proc[], int n) {
    int remainingtime[n];
    for (int i = 0; i < n; i++) {
        remainingtime[i] = proc[i].burst_time;
    }

    int current_time = 0, complete = 0, shortest = -1;
    while (complete < n) {
        int min_burst = INT_MAX;
        bool found = false;

        for (int i = 0; i < n; i++) {
            if (proc[i].arrival_time <= current_time && remainingtime[i] < min_burst && remainingtime[i] > 0) {
                min_burst = remainingtime[i];
                shortest = i;
                found = true;
            }
        }

        if (!found) {
            current_time++;
            continue;
        }

        
        remainingtime[shortest]--;
        current_time++;

        if (remainingtime[shortest] == 0) {
            complete++;
            proc[shortest].completion_time = current_time;
            proc[shortest].turnaround_time = proc[shortest].completion_time - proc[shortest].arrival_time;
            proc[shortest].waiting_time = proc[shortest].turnaround_time - proc[shortest].burst_time;
        }
    }
}

void printSJF(process proc[], int n) {
    cout << "\nSJF (Preemptive) Scheduling:\n";
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

    
    sort(proc, proc + n, [](process a, process b) {
        return a.arrival_time < b.arrival_time;
    });

    findSJF(proc, n);
    printSJF(proc, n);
    printAverages(proc, n);

    return 0;
}