#include <stdlib.h> 
#include <sys/types.h> 
#include <unistd.h> 
int main() 
{ 
// Fork returns process id 
// in parent process 
pid_t child_pid = fork(); 
// Parent process 
if (child_pid > 0) 
sleep(50); 
// Child process 
else 
exit(0); 
return 0; 
} 

___________________________FCFS with arrival______________________

FCFS With Arrival time:
1.	Read Process Name, Arrival Time and Burst Time of ‘n’ process in three arrays
2.	Sort all of them based on Arrival time.
3.	Inside a Loop of 1 to n, for the first process (i=0), assign start[i]=arr[i]. For all other values of i, do the following,
a.	start of current process = finish of previous process
b.	waiting time of current process = start of current process – arrival of current process
c.	finish of current process = start of current process + burst of current process
d.	TAT of current process =finish of current process – arrival of current process
4.	Inside another loop,
a.	Print Process name, Arr time, burst time, Start time, Finish Time, TAT, WT of each process.
b.	Sum up TAT, sum up WT
5.	Print avg TAT and avg WT

#include<stdio.h>
#include<string.h>
int main()
{
    char pn[10][10],t[10];
    int arr[10],bur[10],star[10],finish[10],tat[10],wt[10],i,j,n,temp;
    int totwt=0,tottat=0;
    printf("Enter the number of processes:");
    scanf("%d",&n);
    for(i=0; i<n; i++)
    {
        printf("Enter the ProcessName, Arrival Time& Burst Time:");
        scanf("%s%d%d",&pn[i],&arr[i],&bur[i]);
    }
    for(i=0; i<n; i++)
    {
        for(j=0; j<n; j++)
        {
            if(arr[i]<arr[j])
            {
                temp=arr[i];
                arr[i]=arr[j];
                arr[j]=temp;
                temp=bur[i];
                bur[i]=bur[j];
                bur[j]=temp;
                strcpy(t,pn[i]);
                strcpy(pn[i],pn[j]);
                strcpy(pn[j],t);
            }

        }
    }
    for(i=0; i<n; i++)
    {
        if(i==0)
            star[i]=arr[i];
        else
            star[i]=finish[i-1];
        wt[i]=star[i]-arr[i];
        finish[i]=star[i]+bur[i];
        tat[i]=finish[i]-arr[i];
    }
    printf("\nPName Arrtime Burtime WaitTime Start TAT Finish");
    for(i=0; i<n; i++)
    {
        printf("\n%s\t\t%3d\t\t%3d\t\t%3d\t\t%3d\t\t%6d\t\t%6d",pn[i],arr[i],bur[i],wt[i],star[i],tat[i],finish[i]);
        totwt+=wt[i];
        tottat+=tat[i];
    }
    printf("\nAverage Waiting time:%f",(float)totwt/n);
    printf("\nAverage Turn Around Time:%f",(float)tottat/n);
    return 0;
}


_____________________________________SJF NON PREMP___________________________________________________________________________________

1- Sort all the processes in increasing order of burst time.
2- Initialize the waiting time of the first process as 0.
3- For each process in order (sorted by burst time), calculate waiting time and turnaround time
4- Calculate waiting time for i'th process as sum of all previous burst times.
5- Calculate turnaround time for i'th process as sum of its burst time and waiting time.
6- Calculate average waiting time as total waiting time divided by total number of processes.
7- Calculate average turnaround time as total turnaround time divided by total number of processes

#include<stdio.h>
 int main()
{
    int bt[20],p[20],wt[20],tat[20],i,j,n,total=0,pos,temp;
    float avg_wt,avg_tat;
    printf("Enter number of process:");
    scanf("%d",&n);
  
    printf("nEnter Burst Time:n");
    for(i=0;i<n;i++)
    {
        printf("p%d:",i+1);
        scanf("%d",&bt[i]);
        p[i]=i+1;         
    }
  
   //sorting of burst times
    for(i=0;i<n;i++)
    {
        pos=i;
        for(j=i+1;j<n;j++)
        {
            if(bt[j]<bt[pos])
                pos=j;
        }
  
        temp=bt[i];
        bt[i]=bt[pos];
        bt[pos]=temp;
  
        temp=p[i];
        p[i]=p[pos];
        p[pos]=temp;
    }
   
    wt[0]=0;            
  
   
    for(i=1;i<n;i++)
    {
        wt[i]=0;
        for(j=0;j<i;j++)
            wt[i]+=bt[j];
  
        total+=wt[i];
    }
  
    avg_wt=(float)total/n;      
    total=0;
  
    printf("nProcesst    Burst Time    tWaiting TimetTurnaround Time");
    for(i=0;i<n;i++)
    {
        tat[i]=bt[i]+wt[i];   
        total+=tat[i];
        printf("np%dtt  %dtt    %dttt%d",p[i],bt[i],wt[i],tat[i]);
    }
  
    avg_tat=(float)total/n;    
    printf("nnAverage Waiting Time=%f",avg_wt);
    printf("nAverage Turnaround Time=%fn",avg_tat);
}

___________________________SJF PREMP__________________________________________________________
1- Create an array rem_bt[] to keep track of remaining burst time of processes.
2- Initialize time : t = 0
3- Keep traversing the all processes while all processes are not done. Do following for i'th process if it is not done yet.
    a- If rem_bt[i] > quantum
       (i)  t = t + quantum
       (ii) rem_bt[i] -= quantum
    c- Else // Last cycle for this process
       (i)  t = t + rem_bt[i]
       (ii) wt[i] = t - bt[i]
       (iii) rem_bt[i] = 0;
4- Calculate waiting time and turnaround time for each process.
5- Calculate average waiting time as total waiting time divided by total number of processes.
6- Calculate average turnaround time as total turnaround time divided by total number of processes.



#include <stdio.h>
  
int main() 
{
      int arrival_time[10], burst_time[10], temp[10];
      int i, smallest, count = 0, time, limit;
      double wait_time = 0, turnaround_time = 0, end;
      float average_waiting_time, average_turnaround_time;
      printf("nEnter the Total Number of Processes:t");
      scanf("%d", &limit); 
      printf("nEnter Details of %d Processesn", limit);
      for(i = 0; i < limit; i++)
      {
            printf("nEnter Arrival Time:t");
            scanf("%d", &arrival_time[i]);
            printf("Enter Burst Time:t");
            scanf("%d", &burst_time[i]); 
            temp[i] = burst_time[i];
      }
      burst_time[9] = 9999;  
      for(time = 0; count != limit; time++)
      {
            smallest = 9;
            for(i = 0; i < limit; i++)
            {
                  if(arrival_time[i] <= time && burst_time[i] < burst_time[smallest] && burst_time[i] > 0)
                  {
                        smallest = i;
                  }
            }
            burst_time[smallest]--;
            if(burst_time[smallest] == 0)
            {
                  count++;
                  end = time + 1;
                  wait_time = wait_time + end - arrival_time[smallest] - temp[smallest];
                  turnaround_time = turnaround_time + end - arrival_time[smallest];
            }
      }
      average_waiting_time = wait_time / limit; 
      average_turnaround_time = turnaround_time / limit;
      printf("nnAverage Waiting Time:t%lfn", average_waiting_time);
      printf("Average Turnaround Time:t%lfn", average_turnaround_time);
      return 0;
}


__________________________________Non-Preemptive – Priority________________________________________________________________________________________-
1- Create an array rem_bt[] to keep track of remaining burst time of processes.
2- Initialize time : t = 0
3- Keep traversing the all processes while all processes are not done. Do following for i'th process if it is not done yet.
    a- Find process with highest priority that has arrived for the first time in the queue
    b- Assign CPU to that process
    c- Calculate waiting time for that process
    d- Increment total waiting time by adding waiting time of that process
4- Calculate average waiting time as total waiting time divided by total number of processes.

#include<stdio.h>
 
int main()
{
    int bt[20],p[20],wt[20],tat[20],pr[20],i,j,n,total=0,pos,temp,avg_wt,avg_tat;
    printf("Enter Total Number of Process:");
    scanf("%d",&n);
 
    printf("\nEnter Burst Time and Priority\n");
    for(i=0;i<n;i++)
    {
        printf("\nP[%d]\n",i+1);
        printf("Burst Time:");
        scanf("%d",&bt[i]);
        printf("Priority:");
        scanf("%d",&pr[i]);
        p[i]=i+1;           //contains process number
    }
 
    //sorting burst time, priority and process number in ascending order using selection sort
    for(i=0;i<n;i++)
    {
        pos=i;
        for(j=i+1;j<n;j++)
        {
            if(pr[j]<pr[pos])
                pos=j;
        }
 
        temp=pr[i];
        pr[i]=pr[pos];
        pr[pos]=temp;
 
        temp=bt[i];
        bt[i]=bt[pos];
        bt[pos]=temp;
 
        temp=p[i];
        p[i]=p[pos];
        p[pos]=temp;
    }
 
    wt[0]=0; //waiting time for first process is zero
 
    //calculate waiting time
    for(i=1;i<n;i++)
    {
        wt[i]=0;
        for(j=0;j<i;j++)
            wt[i]+=bt[j];
 
        total+=wt[i];
    }
 
    avg_wt=total/n;      //average waiting time
    total=0;
 
    printf("\nProcess\t    Burst Time    \tWaiting Time\tTurnaround Time");
    for(i=0;i<n;i++)
    {
        tat[i]=bt[i]+wt[i];     //calculate turnaround time
        total+=tat[i];
        printf("\nP[%d]\t\t  %d\t\t    %d\t\t\t%d",p[i],bt[i],wt[i],tat[i]);
    }
 
    avg_tat=total/n;     //average turnaround time
    printf("\n\nAverage Waiting Time=%d",avg_wt);
    printf("\nAverage Turnaround Time=%d\n",avg_tat);
 
return 0;
}



___________________________Pre-emptive – Priority_______________________________________________________________________________________
1- Create an array rem_bt[] to keep track of remaining burst time of processes.
2- Initialize time : t = 0
3- Keep traversing the all processes while all processes are not done. Do following for i'th process if it is not done yet.
    a- Find process with highest priority that has arrived for the first time in the queue
    b- Assign CPU to that process
    c- Calculate waiting time for that process
    d- Increment total waiting time by adding waiting time of that process
    e- If a new process with higher priority than the current running process arrives, then stop the execution of current process and start executing newly arrived higher priority process.
4- Calculate average waiting time as total waiting time divided by total number of processes.

#include <bits/stdc++.h>

using namespace std;

#define totalprocess 5

// Making a struct to hold the given input

struct process
{
int at,bt,pr,pno;
};

process proc[50];

/*
Writing comparator function to sort according to priority if
arrival time is same
*/

bool comp(process a,process b)
{
if(a.at == b.at)
{
return a.pr<b.pr;
}
else
{
	return a.at<b.at;
}
}

// Using FCFS Algorithm to find Waiting time
void get_wt_time(int wt[])
{
// declaring service array that stores cumulative burst time
int service[50];

// Initialising initial elements of the arrays
service[0] = proc[0].at;
wt[0]=0;


for(int i=1;i<totalprocess;i++)
{
service[i]=proc[i-1].bt+service[i-1];

wt[i]=service[i]-proc[i].at;

// If waiting time is negative, change it into zero
	
	if(wt[i]<0)
	{
	wt[i]=0;
	}
}

}

void get_tat_time(int tat[],int wt[])
{
// Filling turnaroundtime array

for(int i=0;i<totalprocess;i++)
{
	tat[i]=proc[i].bt+wt[i];
}
	
}

void findgc()
{
//Declare waiting time and turnaround time array
int wt[50],tat[50];

double wavg=0,tavg=0;

// Function call to find waiting time array
get_wt_time(wt);
//Function call to find turnaround time
get_tat_time(tat,wt);
	
int stime[50],ctime[50];

stime[0] = proc[0].at;
ctime[0]=stime[0]+tat[0];

// calculating starting and ending time
for(int i=1;i<totalprocess;i++)
	{
		stime[i]=ctime[i-1];
		ctime[i]=stime[i]+tat[i]-wt[i];
	}
	
cout<<"Process_no\tStart_time\tComplete_time\tTurn_Around_Time\tWaiting_Time"<<endl;
	
	// display the process details
	
for(int i=0;i<totalprocess;i++)
	{
		wavg += wt[i];
		tavg += tat[i];
		
		cout<<proc[i].pno<<"\t\t"<<
			stime[i]<<"\t\t"<<ctime[i]<<"\t\t"<<
			tat[i]<<"\t\t\t"<<wt[i]<<endl;
	}
	
		// display the average waiting time
		//and average turn around time
	
	cout<<"Average waiting time is : ";
	cout<<wavg/(float)totalprocess<<endl;
	cout<<"average turnaround time : ";
	cout<<tavg/(float)totalprocess<<endl;

}

int main()
{
int arrivaltime[] = { 1, 2, 3, 4, 5 };
int bursttime[] = { 3, 5, 1, 7, 4 };
int priority[] = { 3, 4, 1, 7, 8 };
	
for(int i=0;i<totalprocess;i++)
{
	proc[i].at=arrivaltime[i];
	proc[i].bt=bursttime[i];
	proc[i].pr=priority[i];
	proc[i].pno=i+1;
	}
	
	//Using inbuilt sort function
	
	sort(proc,proc+totalprocess,comp);
	
	//Calling function findgc for finding Gantt Chart
	
	findgc();

	return 0;
}


_______________________________Round Robin_________________________________________________________________________________

1- Create an array rem_bt[] to keep track of remaining burst time of processes.
2- Initialize time : t = 0
3- Keep traversing the all processes while all processes are not done. Do following for i'th process if it is not done yet.
    a- If rem_bt[i] > quantum
       (i)  t = t + quantum
       (ii) rem_bt[i] -= quantum
    b- Else // Last cycle for this process
       (i)  t = t + rem_bt[i]
       (ii) wt[i] = t - bt[i]
       (iii) rem_bt[i] = 0;
4- Calculate average waiting time as total waiting time divided by total number of processes.


1.	#include<stdio.h>  
2.	#include<conio.h>  
3.	  
4.	void main()  
5.	{  
6.	    // initlialize the variable name  
7.	    int i, NOP, sum=0,count=0, y, quant, wt=0, tat=0, at[10], bt[10], temp[10];  
8.	    float avg_wt, avg_tat;  
9.	    printf(" Total number of process in the system: ");  
10.	    scanf("%d", &NOP);  
11.	    y = NOP; // Assign the number of process to variable y  
12.	  
13.	// Use for loop to enter the details of the process like Arrival time and the Burst Time  
14.	for(i=0; i<NOP; i++)  
15.	{  
16.	printf("\n Enter the Arrival and Burst time of the Process[%d]\n", i+1);  
17.	printf(" Arrival time is: \t");  // Accept arrival time  
18.	scanf("%d", &at[i]);  
19.	printf(" \nBurst time is: \t"); // Accept the Burst time  
20.	scanf("%d", &bt[i]);  
21.	temp[i] = bt[i]; // store the burst time in temp array  
22.	}  
23.	// Accept the Time qunat  
24.	printf("Enter the Time Quantum for the process: \t");  
25.	scanf("%d", &quant);  
26.	// Display the process No, burst time, Turn Around Time and the waiting time  
27.	printf("\n Process No \t\t Burst Time \t\t TAT \t\t Waiting Time ");  
28.	for(sum=0, i = 0; y!=0; )  
29.	{  
30.	if(temp[i] <= quant && temp[i] > 0) // define the conditions   
31.	{  
32.	    sum = sum + temp[i];  
33.	    temp[i] = 0;  
34.	    count=1;  
35.	    }     
36.	    else if(temp[i] > 0)  
37.	    {  
38.	        temp[i] = temp[i] - quant;  
39.	        sum = sum + quant;    
40.	    }  
41.	    if(temp[i]==0 && count==1)  
42.	    {  
43.	        y--; //decrement the process no.  
44.	        printf("\nProcess No[%d] \t\t %d\t\t\t\t %d\t\t\t %d", i+1, bt[i], sum-at[i], sum-at[i]-bt[i]);  
45.	        wt = wt+sum-at[i]-bt[i];  
46.	        tat = tat+sum-at[i];  
47.	        count =0;     
48.	    }  
49.	    if(i==NOP-1)  
50.	    {  
51.	        i=0;  
52.	    }  
53.	    else if(at[i+1]<=sum)  
54.	    {  
55.	        i++;  
56.	    }  
57.	    else  
58.	    {  
59.	        i=0;  
60.	    }  
61.	}  
62.	// represents the average waiting time and Turn Around time  
63.	avg_wt = wt * 1.0/NOP;  
64.	avg_tat = tat * 1.0/NOP;  
65.	printf("\n Average Turn Around Time: \t%f", avg_wt);  
66.	printf("\n Average Waiting Time: \t%f", avg_tat);  
67.	getch();  
68.	}  


_______________________________semaphore_____________________________________________________________________________________________________________
#include<semaphoers.h>
sem_t s;
void* child(void *arg){
printf("I am Child");
sem_post(&s);
return NULL;

}

int main(){
sem_init(&s,0,0);
printf("\nParent Begin");
Pthread_t tt;
pthread_create(&c,NULL,child,NULL);
sem_wait(&s);
printf("\n Parent End");
return 0;
}


___________semaphore2________________________
Ex 7	#include <iostream> #include <queue> #include <thread> #include <mutex>
#include <condition_variable>


struct Semaphore { int value;
std::queue<std::thread::id> q; std::mutex mtx; std::condition_variable cv;

Semaphore(int init) { value = init;
}
};

void P(Semaphore &s) { std::unique_lock<std::mutex>
lock(s.mtx);
s.value--;
if (s.value < 0) {


s.q.push(std::this_thread::get_id());	 
 
	s.cv.wait(lock);
}
}

void V(Semaphore &s) { std::unique_lock<std::mutex>
lock(s.mtx); s.value++;
if (s.value <= 0) {
std::thread::id id = s.q.front(); s.q.pop();
s.cv.notify_one();
}
}


void threadFunction(int id, Semaphore &s) {
std::cout << "Thread " << id << " is trying to acquire the semaphore\n";
P(s);
std::cout << "Thread " << id << " acquired the semaphore\n";

std::this_thread::sleep_for(std::chrono
::seconds(2));
std::cout << "Thread " << id << " releasing the semaphore\n";
V(s);
}


int main() {	
 
	Semaphore s(1);
std::thread t1(threadFunction, 1, std::ref(s));
std::thread t2(threadFunction, 2, std::ref(s));
std::thread t3(threadFunction, 3, std::ref(s));
t1.join();
t2.join();
t3.join(); return 0;
}	
__________________thread create_____________________________________________--
#include <iostream>
#include <cstdlib>
#include <pthread.h>
using namespace std;
#define NUM_THREADS 5
void *PrintHello(void *threadid) {
   long tid;
   tid = (long)threadid;
   printf("Hello World! Thread ID, %d
", tid);
   pthread_exit(NULL);
}
int main () {
   pthread_t threads[NUM_THREADS];
   int rc;
   int i;
   for( i = 0; i < NUM_THREADS; i++ ) {
      cout << "main() : creating thread, " << i << endl;
      rc = pthread_create(&threads[i], NULL, PrintHello, (void *)i);
      if (rc) {
         printf("Error:unable to create thread, %d
", rc);
         exit(-1);
      }
   }
   pthread_exit(NULL);
}
_______________thread func________________________________________
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>

void* func(void* arg)
{
	// detach the current thread
	// from the calling thread
	pthread_detach(pthread_self());

	printf("Inside the thread\n");

	// exit the current thread
	pthread_exit(NULL);
}

void fun()
{
	pthread_t ptid;

	// Creating a new thread
	pthread_create(&ptid, NULL, &func, NULL);
	printf("This line may be printed"
		" before thread terminates\n");

	// The following line terminates
	// the thread manually
	// pthread_cancel(ptid);

	// Compare the two threads created
	if(pthread_equal(ptid, pthread_self())
		printf("Threads are equal\n");
	else
		printf("Threads are not equal\n");

	// Waiting for the created thread to terminate
	pthread_join(ptid, NULL);

	printf("This line will be printed"
		" after thread ends\n");

	pthread_exit(NULL);
}
// Driver code
int main()
{
	fun();
	return 0;
}



___________________________reader writer________________________________
semaphore mutex = 1;
semaphore wrt = 1;
int read_count = 0;

writer() {
    wait(wrt);
    // Writing is performed
    signal(wrt);
}

reader() {
    wait(mutex);
    read_count++;
    if (read_count == 1) {
        wait(wrt);
    }
    signal(mutex);

    // Reading is performed

    wait(mutex);
    read_count--;
    if (read_count == 0) {
        signal(wrt);
    }
    signal(mutex);
}



#include <pthread.h> 

#include <semaphore.h> 

#include <stdio.h> 

sem_t wrt; 

pthread_mutex_t mutex; 

int cnt = 1; 

int numreader = 0; 

void *writer(void *wno) 

{    

    sem_wait(&wrt); 

    cnt = cnt*2; 

    printf("Writer %d modified cnt to %d\n",(*((int *)wno)),cnt); 

    sem_post(&wrt); 

  

} 

void *reader(void *rno) 

{    

    // Reader acquire the lock before modifying numreader 

    pthread_mutex_lock(&mutex); 

    numreader++; 

    if(numreader == 1) { 

        sem_wait(&wrt); // If this id the first reader, then it will block the writer 

    } 

    pthread_mutex_unlock(&mutex); 

    // Reading Section 

    printf("Reader %d: read cnt as %d\n",*((int *)rno),cnt); 

  

    // Reader acquire the lock before modifying numreader 

    pthread_mutex_lock(&mutex); 

    numreader--; 

    if(numreader == 0) { 

        sem_post(&wrt); // If this is the last reader, it will wake up the writer. 

    } 

    pthread_mutex_unlock(&mutex); 

} 

  

int main() 

{    

  

    pthread_t read[10],write[5]; 

    pthread_mutex_init(&mutex, NULL); 

    sem_init(&wrt,0,1); 

  

    int a[10] = {1,2,3,4,5,6,7,8,9,10}; //Just used for numbering the producer and consumer 

  

    for(int i = 0; i < 10; i++) { 

        pthread_create(&read[i], NULL, (void *)reader, (void *)&a[i]); 

    } 

    for(int i = 0; i < 5; i++) { 

        pthread_create(&write[i], NULL, (void *)writer, (void *)&a[i]); 

    } 

  

    for(int i = 0; i < 10; i++) { 

        pthread_join(read[i], NULL); 

    } 

    for(int i = 0; i < 5; i++) { 

        pthread_join(write[i], NULL); 

    } 

  

    pthread_mutex_destroy(&mutex); 

    sem_destroy(&wrt); 

  

    return 0; 

     

} 

 

 ______________________dining philosopher__________________________________________________________________________________---
semaphore chopstick[5] = {1, 1, 1, 1, 1};

philosopher(int i) {
    while (true) {
        think();
        wait(chopstick[i]);
        wait(chopstick[(i + 1) % 5]);
        eat();
        signal(chopstick[i]);
        signal(chopstick[(i + 1) % 5]);
    }
}



 

#include <pthread.h> 
#include <semaphore.h> 

#include <stdio.h> 

#include <time.h> 

#define N 5 

#define THINKING 2 

#define HUNGRY 1 

#define EATING 0 

#define LEFT (phnum + 4) % N 

#define RIGHT (phnum + 1) % N 

  

int state[N]; 

int phil[N] = { 0, 1, 2, 3, 4 }; 

  

sem_t mutex; 

sem_t S[N]; 

  

void test(int phnum) 

{ 

if (state[phnum] == HUNGRY 

&& state[LEFT] != EATING 

&& state[RIGHT] != EATING) { 

// state that eating 

state[phnum] = EATING; 

  

sleep(2); 

  

printf("Philosopher %d takes fork %d and %d\n", 

phnum + 1, LEFT + 1, phnum + 1); 

  

printf("Philosopher %d is Eating\n", phnum + 1); 

  

// sem_post(&S[phnum]) has no effect 

// during takefork 

// used to wake up hungry philosophers 

// during putfork 

sem_post(&S[phnum]); 

} 

} 

  

// take up chopsticks 

void take_fork(int phnum) 

{ 

  

sem_wait(&mutex); 

  

// state that hungry 

state[phnum] = HUNGRY; 

  

printf("Philosopher %d is Hungry\n", phnum + 1); 

  

// eat if neighbours are not eating 

test(phnum); 

  

sem_post(&mutex); 

  

// if unable to eat wait to be signalled 

sem_wait(&S[phnum]); 

  

sleep(1); 

} 

  

// put down chopsticks 

void put_fork(int phnum) 

{ 

  

sem_wait(&mutex); 

// state that thinking 

state[phnum] = THINKING; 
printf("Philosopher %d putting fork %d and %d down\n", 
phnum + 1, LEFT + 1, phnum + 1); 
printf("Philosopher %d is thinking\n", phnum + 1);  

test(LEFT); 
test(RIGHT); 
sem_post(&mutex); 
}  

void* philosopher(void* num) 

{ 

while (1) { 


int* i = num; 

sleep(1); 
take_fork(*i); 

sleep(0); 

put_fork(*i); 

} 

} 

  

int main() 
{int i; 
pthread_t thread_id[N]; 
// initialize the semaphores 
sem_init(&mutex, 0, 1); 

  
for (i = 0; i < N; i++) 
sem_init(&S[i], 0, 0); 
for (i = 0; i < N; i++) { 
// create philosopher processes 
pthread_create(&thread_id[i], NULL, 
philosopher, &phil[i]); 
printf("Philosopher %d is thinking\n", i + 1); 
} 

for (i = 0; i < N; i++) 

pthread_join(thread_id[i], NULL); 
} 
_________________________banker_________________________________________________
Let Work and Finish be vectors of length ‘m’ and ‘n’ respectively. Initialize: Work = Available. Finish [i] = false; for i=1, 2, 3, 4….n.
Find an i such that both. a) Finish [i] = false. b) Need i <= Work. If no such i exists goto step 4
Work = Work + Allocation[i] Finish[i] = true goto step 2
If Finish [i] == true for all i then the system is in a safe state.
 
#include <stdio.h> 

int main() 

{ 

int n, m, i, j, k; 
n = 5; 
m = 3;  

int alloc[5][3] = { { 0, 1, 0 }, // P0 // Allocation Matrix 
{ 2, 0, 0 }, // P1 
{ 3, 0, 2 }, // P2 
{ 2, 1, 1 }, // P3 
{ 0, 0, 2 } }; // P4 

int max[5][3] = { { 7, 5, 3 }, // P0 // MAX Matrix 
{ 3, 2, 2 }, // P1 
{ 9, 0, 2 }, // P2 
{ 2, 2, 2 }, // P3 
{ 4, 3, 3 } }; // P4 

int avail[3] = { 3, 3, 2 }; // Available Resources 
int f[n], ans[n], ind = 0; 
for (k = 0; k < n; k++) { 

f[k] = 0; 
} 
int need[n][m]; 
for (i = 0; i < n; i++) { 
for (j = 0; j < m; j++) 
need[i][j] = max[i][j] - alloc[i][j]; 

} 

int y = 0; 
for (k = 0; k < 5; k++) { 
for (i = 0; i < n; i++) { 

if (f[i] == 0) { 

int flag = 0; 
for (j = 0; j < m; j++) { 

if (need[i][j] > avail[j]){ 
flag = 1; 
break; 
} 

} 

  

if (flag == 0) { 
ans[ind++] = i; 

for (y = 0; y < m; y++) 
avail[y] += alloc[i][y]; 
f[i] = 1; 

} 

} 
} 
} 
  
int flag = 1; 
for(int i=0;i<n;i++) 
{ 
if(f[i]==0) 
{ 
flag=0; 
printf("The following system is not safe"); 
break; 
} 
} 
 
if(flag==1) 
{ 
printf("Following is the SAFE Sequence\n"); 
for (i = 0; i < n - 1; i++) 
printf(" P%d ->", ans[i]); 
printf(" P%d", ans[n - 1]); 
} 
return (0); 

} 

________________________________first fit_________________________________________


First Fit	#include<stdio.h> void main()
{
int bsize[10], psize[10], bno, pno, flags[10], allocation[10], i, j; for(i = 0; i < 10; i++)
{


flags[i] = 0;
allocation[i] = -1;
}


printf("Enter no. of blocks: "); scanf("%d", &bno);
printf("\nEnter size of each block: "); for(i = 0; i < bno; i++)
{


scanf("%d", &bsize[i]);
}


printf("\nEnter no. of processes: "); scanf("%d", &pno);


printf("\nEnter size of each process: "); for(i = 0; i < pno; i++)
{


scanf("%d", &psize[i]);
}


for(i = 0; i < pno; i++)	//allocation as per first fit
{


for(j = 0; j < bno; j++)	

	{


if(flags[j] == 0 && bsize[j] >= psize[i])
{


allocation[j] = i; flags[j] = 1; break;
}
}
}


//display allocation details
printf("\nBlock no.\tsize\t\tprocess no.\t\tsize"); for(i
= 0; i < bno; i++)
{
printf("\n\t%d\t\t%d\t\t\t", i+1, bsize[i]); if(flags[i] == 1)
{


printf("%d\t\t\t\t%d",allocation[i]+1,psize[allocation[i]
]);
}


else
{
printf("Not allocated");


}
}
}

______________________________best fit_______________________________________________________

#include<stdio.h> 
void main(){ 
    	int fragment[20],b[20],p[20],i,j,nb,np,temp,lowest=9999; static int barray[20],parray[20];
printf("\n\t\t\tMemory Management Scheme - Best Fit"); printf("\nEnter the number of blocks:"); scanf("%d",&nb);
printf("Enter the number of processes:");


scanf("%d",&np);
printf("\nEnter the size of the blocks:-\n"); for(i=1;i<=nb;i++)
{


printf("Block no.%d:",i);
scanf("%d",&b[i]);
}


printf("\nEnter the size of the processes :-\n"); for(i=1;i<=np;i++)
{


printf("Process no.%d:",i);
scanf("%d",&p[i]);
}


for(i=1;i<=np;i++)
{


for(j=1;j<=nb;j++)
{


if(barray[j]!=1)
{	

	

temp=b[j]-p[i]; if(temp>=0) if(lowest>temp)
{


parray[i]=j;


lowest=temp;
}
}
}


fragment[i]=lowest;


barray[parray[i]]=1; lowest=10000;
}


printf("\nProcess_no\tProcess_size\tBlock_no\tBlock_s ize\tFragment"); for(i=1;i<=np && parray[i]!=0;i++)
{


printf("\n%d\t\t%d\t\t%d\t\t%d\t\t%d",i,p[i],parray[i], b[parray[i]],fragment[i]);
}
}	

________________________worst fit___________________________________________________________________________________________--


Wor st Fit	#include<stdio.h> int main()
{


int n,n1,i;


printf("enter the number of processes:"); scanf("%d",&n);
int process[n];
printf("\n enter the size of processes:\n"); for(i=0;i<n;i++)
{


scanf("%d",&process[i]);
}


printf("enter the no of memory blocks:"); scanf("%d",&n1);
int blocks[n1];
printf("\n enter the size of blocks:\n"); int total=0; for(i=0;i<n1;i++)
{


scanf("%d",&blocks[i]); total=total+blocks[i];
}


int process1[n1]; int job[n1]; int frag[n1]; int check[n1]; for(i=0;i<n1;i++)
{


check[i]=0;
}	

	

int j,used=0; i=0; while(i<n)

{
int max=-1,j1=-1,k=-1,max1; for(j=0;j<n1;j++)
{


max1=blocks[j]; if(max1>=max&&check[j]==0&&max1>=process[i])
{


max=max1;j1=j;
}


else
{


if(check[j]==0)
{


process1[j]=0; job[j]=0; frag[j]=blocks[j];
}
}
}


if(k!=j1)


{
process1[j1]=process[i]; job[j1]=i+1; frag[j1]=blocks[j1]-process[i]; used=used+process[i]; check[j1]=1;	

	int l;}i++;
}


printf("blocksize\tprocess size\tprocessno\tragmentaCon\n");


for(i=0;i<n1;i++)
{


printf("%d\t\t%d\t\t%d\t\t%d\n",blocks[i],process1[i], job[i],frag[i]);
}


printf("totalmemoryallocation:%d\n",total); printf("memoryused:%d\n",used);
}	



________________________page replacement_____________________________________________________________________________________________________________
First In First Out (FIFO):
When a page needs to be replaced, the oldest page in memory is selected for removal.
Pseudocode:
if (page not in memory) {
    remove oldest page from memory
    add new page to memory
}
Least Recently Used (LRU):
When a page needs to be replaced, the least recently used page in memory is selected for removal.
Pseudocode:
if (page not in memory) {
    remove least recently used page from memory
    add new page to memory
}
Optimal Page Replacement:
When a page needs to be replaced, the one that will not be used for the longest period of time is selected for removal.
Pseudocode:
if (page not in memory) {
    remove page that will not be used for longest period of time from memory
    add new page to memory
}

#include<stdio.h> 

int n,nf; 

int in[100]; 

int p[50]; 

int hit=0; 

int i,j,k; 

int pgfaultcnt=0; 

  

void getData() 

{ 

    printf("\nEnter length of page reference sequence:"); 

    scanf("%d",&n); 

    printf("\nEnter the page reference sequence:"); 

    for(i=0; i<n; i++) 

        scanf("%d",&in[i]); 

    printf("\nEnter no of frames:"); 

    scanf("%d",&nf); 

} 

  

void initialize() 

{ 

    pgfaultcnt=0; 

    for(i=0; i<nf; i++) 

        p[i]=9999; 

} 

  

int isHit(int data) 

{ 

    hit=0; 

    for(j=0; j<nf; j++) 

    { 

        if(p[j]==data) 

        { 

            hit=1; 

            break; 

        } 

  

    } 

  

    return hit; 

} 

  

int getHitIndex(int data) 

{ 

    int hitind; 

    for(k=0; k<nf; k++) 

    { 

        if(p[k]==data) 

        { 

            hitind=k; 

            break; 

        } 

    } 

    return hitind; 

} 

  

void dispPages() 

{ 

    for (k=0; k<nf; k++) 

    { 

        if(p[k]!=9999) 

            printf(" %d",p[k]); 

    } 

  

} 

  

void dispPgFaultCnt() 

{ 

    printf("\nTotal no of page faults:%d",pgfaultcnt); 

} 

  

void fifo() 

{ 

    initialize(); 

    for(i=0; i<n; i++) 

    { 

        printf("\nFor %d :",in[i]); 

  

        if(isHit(in[i])==0) 

        { 

  

            for(k=0; k<nf-1; k++) 

                p[k]=p[k+1]; 

  

            p[k]=in[i]; 

            pgfaultcnt++; 

            dispPages(); 

        } 

        else 

            printf("No page fault"); 

    } 

    dispPgFaultCnt(); 

} 

  

  

void optimal() 

{ 

    initialize(); 

    int near[50]; 

    for(i=0; i<n; i++) 

    { 

  

        printf("\nFor %d :",in[i]); 

  

        if(isHit(in[i])==0) 

        { 

  

            for(j=0; j<nf; j++) 

            { 

                int pg=p[j]; 

                int found=0; 

                for(k=i; k<n; k++) 

                { 

                    if(pg==in[k]) 

                    { 

                        near[j]=k; 

                        found=1; 

                        break; 

                    } 

                    else 

                        found=0; 

                } 

                if(!found) 

                    near[j]=9999; 

            } 

            int max=-9999; 

            int repindex; 

            for(j=0; j<nf; j++) 

            { 

                if(near[j]>max) 

                { 

                    max=near[j]; 

                    repindex=j; 

                } 

            } 

            p[repindex]=in[i]; 

            pgfaultcnt++; 

  

            dispPages(); 

        } 

        else 

            printf("No page fault"); 

    } 

    dispPgFaultCnt(); 

} 

  

void lru() 

{ 

    initialize(); 

  

    int least[50]; 

    for(i=0; i<n; i++) 

    { 

  

        printf("\nFor %d :",in[i]); 

  

        if(isHit(in[i])==0) 

        { 

  

            for(j=0; j<nf; j++) 

            { 

                int pg=p[j]; 

                int found=0; 

                for(k=i-1; k>=0; k--) 

                { 

                    if(pg==in[k]) 

                    { 

                        least[j]=k; 

                        found=1; 

                        break; 

                    } 

                    else 

                        found=0; 

                } 

                if(!found) 

                    least[j]=-9999; 

            } 

            int min=9999; 

            int repindex; 

            for(j=0; j<nf; j++) 

            { 

                if(least[j]<min) 

                { 

                    min=least[j]; 

                    repindex=j; 

                } 

            } 

            p[repindex]=in[i]; 

            pgfaultcnt++; 

  

            dispPages(); 

        } 

        else 

            printf("No page fault!"); 

    } 

    dispPgFaultCnt(); 

} 

  

  

  

void secondchance() 

{ 

    int usedbit[50]; 

    int victimptr=0; 

    initialize(); 

    for(i=0; i<nf; i++) 

        usedbit[i]=0; 

    for(i=0; i<n; i++) 

    { 

        printf("\nFor %d:",in[i]); 

        if(isHit(in[i])) 

        { 

            printf("No page fault!"); 

            int hitindex=getHitIndex(in[i]); 

            if(usedbit[hitindex]==0) 

                usedbit[hitindex]=1; 

        } 

        else 

        { 

            pgfaultcnt++; 

            if(usedbit[victimptr]==1) 

            { 

                do 

                { 

                    usedbit[victimptr]=0; 

                    victimptr++; 

                    if(victimptr==nf) 

                        victimptr=0; 

                } 

                while(usedbit[victimptr]!=0); 

            } 

            if(usedbit[victimptr]==0) 

            { 

                p[victimptr]=in[i]; 

                usedbit[victimptr]=1; 

                victimptr++; 

            } 

            dispPages(); 

  

        } 

        if(victimptr==nf) 

            victimptr=0; 

    } 

    dispPgFaultCnt(); 

} 

  

int main() 

{ 

    int choice; 

    while(1) 

    { 

        printf("\nPage Replacement Algorithms\n1.Enter data\n2.FIFO\n3.Optimal\n4.LRU\n5.Second Chance\n6.Exit\nEnter your choice:"); 

        scanf("%d",&choice); 

        switch(choice) 

        { 

        case 1: 

            getData(); 

            break; 

        case 2: 

            fifo(); 

            break; 

        case 3: 

            optimal(); 

            break; 

        case 4: 

            lru(); 

            break; 

        case 5: 

            secondchance(); 

            break; 

        default: 

            return 0; 

________________________file lock___________________________________________________________________________-

#include <sys/types.h> /*********** Write Lock Setter *******/ 

#include <unistd.h> 

#include <stdio.h> 

#include <stdlib.h> 

#include <fcntl.h> 

#include <errno.h> 

int main() 

{ 

    int fd; 

    struct flock lock, savelock; 

    fd = open("new.txt",O_RDWR); 

    lock.l_type=F_WRLCK; lock.l_start = 0; 

    lock.l_whence =SEEK_SET; 

    lock.l_len= 0; 

    savelock = lock; 

    fcntl(fd, F_SETLK, &savelock); 

    printf("Press ENTER to access 'new.txt' file\n"); 

    getchar(); 

    if (lock.l_type == F_WRLCK || lock.l_type == F_RDLCK) 

    { 

        printf("File is locked\n"); 

        printf("Press ENTER to unlock thefile");  

        getchar(); 

        lock.l_type = F_UNLCK; 

        fcntl(fd, F_SETLK, &savelock); 

        FILE* ptr; char ch; 

        ptr = fopen("new.txt", "r"); 

        if (NULL == ptr)  

        { 

            printf("file can't be opened \n"); 

        } 

        printf("Contents of new.txt: \n"); 

        do { 

            ch = fgetc(ptr); 

            printf("%c", ch); 

        }  

        while (ch != EOF); 

        printf("\n"); 

        fclose(ptr);  

        exit(1); 

    } 

    return 0; 

} 