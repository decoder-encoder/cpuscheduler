# CPU Scheduling Simulator

A C++ program that simulates how an Operating System schedules processes. It implements multiple scheduling algorithms to calculate core execution metrics like Completion Time, Turnaround Time, and Waiting Time.

## Algorithms Included
* **FCFS** (First Come First Served)
* **SJF** (Shortest Job First - Non-Preemptive)
* **Priority Scheduling** (Preemptive)
* **Priority Scheduling** (Non-Preemptive)
* **Round Robin** (Time Quantum based)

---

## How to Run the Project

1. Open your terminal in the project folder.
2. Compile the code (Works on Mac and Linux):
   ```bash
   g++ main.cpp -o scheduler