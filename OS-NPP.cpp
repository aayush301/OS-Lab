// NPP (Non-preemptive Priority) CPU scheduling Algorithm

#include<iostream>      // for console input and output
#include<iomanip>       // for setting the width
#include<cstdlib>       // for clearing the screen
#include<vector>        // for vector and pair
using namespace std;

void NPP(int arrival[], int burst[], int priority[], int n, int disp, float& avgTurnaroundTime, float& avgWaitingTime)
{
    
    int waitingTime[n]={0};
    int turnAroundTime[n]={0};
    bool isCompleted[n]={false};

    int completed=0;
    int currentTime=0;

    vector<pair<int,int>>v;

    while(completed!=n)
    {
        int maxpriority=100000;
        int maxpid=-1;
        for(int i=0;i<n;i++)
        {
            if(arrival[i]<=currentTime && !isCompleted[i])
            {
                if(priority[i]<maxpriority)
                {
                    maxpriority=priority[i];
                    maxpid=i;
                }
                else if(priority[i]==maxpid && arrival[i]<arrival[maxpid])
                {
                    maxpriority=priority[i];
                    maxpid=i;
                }
            }
        }
        if(maxpid!=-1)
        {
            v.push_back({currentTime+disp,maxpid});
            currentTime+=disp+burst[maxpid];
            turnAroundTime[maxpid]=currentTime-arrival[maxpid];
            waitingTime[maxpid]=turnAroundTime[maxpid]-burst[maxpid];
            isCompleted[maxpid]=true;
            completed++;
        }
        else
            currentTime++;
    }

    for(int i=0;i<n;i++)
    {
        avgWaitingTime+=waitingTime[i];
        avgTurnaroundTime+=turnAroundTime[i];
    }
    avgWaitingTime=avgWaitingTime/n;
    avgTurnaroundTime=avgTurnaroundTime/n;


    cout<<"\nTime and order of jobs with their priority are:\n";
    for(int i=0;i<v.size();i++)
    {
        cout<<"T"<<v[i].first<<": "<<"p"<<v[i].second+1<<"("<<priority[v[i].second]<<")"<<endl;
    }
    cout<<endl;
    cout<<left<<setw(8)<<"Process"<<setw(16)<<"Turnaround Time"<<"Waiting Time"<<endl;
    for(int i=0;i<n;i++)
    {
        cout<<left<<"p"<<setw(7)<<i+1<<setw(16)<<turnAroundTime[i]<<waitingTime[i]<<endl;
    }
    cout<<endl;

}

int main()
{
    
    system("cls");
    int n;
    cout<<"Enter no. of processes: ";
    cin>>n;
    int arrival[n],burst[n],priority[n];
    cout<<"Enter arrival time of each process:\n";
    for(int i=0;i<n;i++)
        cin>>arrival[i];
    cout<<"Enter CPU burst time of each process:\n";
    for(int i=0;i<n;i++)
        cin>>burst[i];
    cout<<"Enter priority of each process:\n";
    for(int i=0;i<n;i++)
        cin>>priority[i];

    cout<<setprecision(2)<<fixed<<endl;
    
    float avgw=0,avgt=0;
    NPP(arrival,burst,priority,n,0,avgt,avgw);
    
    cout<<"Average Turnaround Time: "<<avgt<<endl;
    cout<<"Average Waiting Time: "<<avgw<<endl;
    cout<<endl<<endl;

}