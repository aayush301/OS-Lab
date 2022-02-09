// RR (Round-robin) CPU Scheduling Algorithm

#include<iostream>      // for console output
#include<fstream>       // for file input
#include<iomanip>       // for setting the width
#include<cstdlib>       // for clearing the screen
#include<vector>        // for vector and pair
#include<queue>         // for queue
using namespace std;


void RR(int arrival[], int burst[], int n, int quantum, int disp, float& avgTurnaroundTime, float& avgWaitingTime)
{
        
    int waitingTime[n]={0};
    int turnAroundTime[n]={0};
    int startServiceTime[n]={0};
    int burstRemaining[n];
    for(int i=0;i<n;i++)
        burstRemaining[i]=burst[i];

    int completed=0;
    int currentTime=0;

    queue<int>q;
    q.push(0);
    int id;
    int mark[100]={0};
    int previd=-1;
    vector<pair<int,int>>v;

    while(completed!=n)
    {
        id=q.front();    
        q.pop();
        if(id!=previd)
        {
            currentTime=max(currentTime,arrival[id])+disp;
            v.push_back({currentTime,id});
        }
        previd=id;
        
        if(burstRemaining[id]>quantum)
        {
            burstRemaining[id]-=quantum;
            currentTime+=quantum;
        }
        else
        {
            currentTime+=burstRemaining[id];
            turnAroundTime[id]=currentTime-arrival[id];
            waitingTime[id]=turnAroundTime[id]-burst[id];
            burstRemaining[id]=0;
            completed++;
        }

        for(int i=1;i<n;i++)
        {
            if(arrival[i]<=currentTime && burstRemaining[i]>0 && mark[i]==0)
            {
                q.push(i);
                mark[i]=1;
            }
        }

        if(burstRemaining[id]>0)
            q.push(id);
        
        if(q.empty())
        {
            for(int i=1;i<n;i++)
            {
                if(burstRemaining[i]>0)
                {
                    q.push(i);
                    mark[i]=1;
                    break;
                }
            }
        }
    }

    for(int i=0;i<n;i++)
    {
        avgWaitingTime+=waitingTime[i];
        avgTurnaroundTime+=turnAroundTime[i];
    }
    avgWaitingTime=avgWaitingTime/n;
    avgTurnaroundTime=avgTurnaroundTime/n;

    cout<<"\nTime and order of jobs are:\n";
    for(int i=0;i<v.size();i++)
    {
        cout<<"T"<<v[i].first<<": "<<"p"<<v[i].second+1<<endl;
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
    int arrival[n],burst[n];
    int quantum;
    
    cout<<"Enter arrival time of each process:\n";
    for(int i=0;i<n;i++)
        cin>>arrival[i];
    
    cout<<"Enter CPU burst time of each process:\n";
    for(int i=0;i<n;i++)
        cin>>burst[i];
    
    cout<<"Enter the time quantum:\n";
    cin>>quantum;

    cout<<setprecision(2)<<fixed<<endl;
    
    float avgw=0,avgt=0;
    RR(arrival,burst,n,quantum,0,avgt,avgw);
    
    cout<<"Average Turnaround Time: "<<avgt<<endl;
    cout<<"Average Waiting Time: "<<avgw<<endl;
    cout<<endl<<endl;

}