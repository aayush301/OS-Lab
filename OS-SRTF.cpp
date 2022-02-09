// SRTF (Shortest Remaining time First) CPU Scheduling Algorithm

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


void SRTF(int arrival[], int burst[], int n, int disp, float& avgTurnaroundTime, float& avgWaitingTime)
{
    
    int waitingTime[n]={0};
    int turnAroundTime[n]={0};
    int startServiceTime[n]={0};
    bool isCompleted[n]={false};
    int burstRemaining[n];

    int completed=0;
    int currentTime=0;
    int previd=-1;

    for(int i=0;i<n;i++)
        burstRemaining[i]=burst[i];

    vector<pair<int,int>>v;

    while(completed!=n)
    {
        int minburst=10000;
        int minid=-1;
        for(int i=0;i<n;i++)
        {
            if(arrival[i]<=currentTime && !isCompleted[i])
            {
                if(burstRemaining[i]<minburst)
                {
                    minburst=burstRemaining[i];
                    minid=i;
                }
                else if(burstRemaining[i]==minburst && arrival[i]<arrival[minid])
                {
                    minburst=burstRemaining[i];
                    minid=i;
                }
            }
        }

        if(minid!=-1)
        {
            if(minid!=previd)
            {
                currentTime+=disp;
                v.push_back({currentTime,minid});
            }
            burstRemaining[minid]-=1;
            currentTime++;
            
            if(burstRemaining[minid]==0)
            {
                turnAroundTime[minid]=currentTime-arrival[minid];
                waitingTime[minid]=turnAroundTime[minid]-burst[minid];
                isCompleted[minid]=true;
                completed++;
            }
            previd=minid;

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
    cout<<"Enter arrival time of each process:\n";
    for(int i=0;i<n;i++)
        cin>>arrival[i];
    cout<<"Enter CPU burst time of each process:\n";
    for(int i=0;i<n;i++)
        cin>>burst[i];

    cout<<setprecision(2)<<fixed<<endl;
    float avgw=0,avgt=0;
    SRTF(arrival,burst,n,0,avgt,avgw);
    
    cout<<"Average Turnaround Time: "<<avgt<<endl;
    cout<<"Average Waiting Time: "<<avgw<<endl;
    cout<<endl<<endl;

}