// SJF (Shortest-Job First) CPU Scheduling Algorithm

#include<iostream>      // for console input and output
#include<iomanip>       // for setting the width
#include<cstdlib>       // for clearing the screen
#include<vector>        // for vector and pair
#include<algorithm>     // for sort() function
using namespace std;

bool comp(pair<int,int>p1,pair<int,int>p2)
{
    return p1.first<p2.first;
}


void SJF(int arrival[], int burst[], int n, int disp, float& avgTurnaroundTime, float& avgWaitingTime)
{
    int waitingTime[n]={0};
    int turnAroundTime[n]={0};
    int startServiceTime[n]={0};
    bool isCompleted[n]={false};

    int completed=0;
    int currentTime=0;

    while(completed!=n)
    {
        int minburst=10000;
        int minid=-1;
        for(int i=0;i<n;i++)
        {
            if(arrival[i]<=currentTime && !isCompleted[i])
            {
                if(burst[i]<minburst)
                {
                    minburst=burst[i];
                    minid=i;
                }
                else if(burst[i]==minburst && arrival[i]<arrival[minid])
                {
                    minburst=arrival[i];
                    minid=i;
                }
            }
        }
        if(minid!=-1)
        {
            startServiceTime[minid]=currentTime+disp;
            waitingTime[minid]=startServiceTime[minid]-arrival[minid];
            turnAroundTime[minid]=waitingTime[minid]+burst[minid];
            isCompleted[minid]=true;
            completed++;
            currentTime=startServiceTime[minid]+burst[minid];
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

    vector<pair<int,int>>v(n);
    for(int i=0;i<n;i++)
    {
        v[i]={startServiceTime[i],i};
    }
    sort(v.begin(),v.end(),comp);

    cout<<"\nTime and order of jobs are:\n";
    for(int i=0;i<n;i++)
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
    cout<<"Enter arrival time of each process:\n";
    for(int i=0;i<n;i++)
        cin>>arrival[i];
    cout<<"Enter CPU burst time of each process:\n";
    for(int i=0;i<n;i++)
        cin>>burst[i];

    cout<<setprecision(2)<<fixed<<endl;
    
    float avgw=0,avgt=0;
    SJF(arrival,burst,n,0,avgt,avgw);
    
    cout<<"Average Turnaround Time: "<<avgt<<endl;
    cout<<"Average Waiting Time: "<<avgw<<endl;
    cout<<endl<<endl;

}