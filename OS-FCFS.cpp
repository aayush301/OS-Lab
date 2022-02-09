// FCFS (First Come First Served) CPU Scheduling Algorithm

#include<iostream>
#include<queue>
#include<cstdlib>
#include<climits>
using namespace std;

void displayqueue(queue<pair<int,int>>q)
{
    while(!q.empty())
    {
        cout<<q.front().first+1<<" "<<q.front().second<<"\n";
        q.pop();
    }
    cout<<endl;
}

void FCFS(int n,int arrival[],int burst[])
{
    int currtime=arrival[0];
    pair<int,int>nextArrival={0,arrival[0]};
    pair<int,int>nextDeparture={INT_MAX,INT_MAX};
    queue<pair<int,int>>q;
    int i=-1;
    int waitingTime[n]={0};
    int turnAroundTime[n]={0};
    bool isArrival=true;
    bool isCPUbusy=false;
    
    while(i<n-1)
    {
        if(isArrival)
        {
            int process=nextArrival.first;
            if(process<n-1)
                nextArrival={process+1,arrival[process+1]};
            else
                nextArrival={INT_MAX,INT_MAX};
            if(! isCPUbusy)
            {
                isCPUbusy=true;
                nextDeparture={process,currtime+burst[process]};
            }
            else
            {
                q.push({process,arrival[process]});
            }
        }
        else
        {
            i++;
            turnAroundTime[i]=currtime-arrival[i];
            cout<<"After departure of process "<<i+1<<":\n";
            if(!q.empty())
                cout<<"Process getting CPU: "<<i+2<<endl;
            cout<<"List of processes in ready queue with their arrival time:\n";
            displayqueue(q);
            if(!q.empty())
            {
                int pstart=q.front().first;
                int parrival=q.front().second;
                q.pop();
                waitingTime[pstart]=currtime-parrival;
                nextDeparture={pstart,currtime+burst[i+1]};
            }
            cout<<endl;
        }
        
        if(nextArrival.second<nextDeparture.second)
        {
            currtime=nextArrival.second;
            isArrival=true;
        }
        else
        {
            currtime=nextDeparture.second;
            
            isArrival=false;
        }
    }

    float avgWaitingTime=0;
    float avgTurnAroundTime=0;
    cout<<"Waiting time of Processes:\n";
    for(int i=0;i<n;i++)
    {
       cout<<"Process "<<i+1<<": "<<waitingTime[i]<<endl;
       avgWaitingTime+=waitingTime[i];
    }
    cout<<"\nTurn around time of Processes:\n";
    for(int i=0;i<n;i++)
    {
       cout<<"Process "<<i+1<<": "<<turnAroundTime[i]<<endl;
       avgTurnAroundTime+=turnAroundTime[i];
    }
    cout<<"\nAverage Waiting Time: "<<avgWaitingTime/n<<endl;
    cout<<"Average Turn around time: "<<avgTurnAroundTime/n<<endl;

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
    cout<<endl<<endl;
    FCFS(n,arrival,burst);
    cout<<endl<<endl;
    

}