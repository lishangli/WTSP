#include<iostream>
#include<cmath>
#include<bitset>
using namespace std;
#define N 9999
int x[10005],y[5005],r[1005];
int c[1005][1005];
int totalNum = 0;
struct timespec ts1,ts2;
    float time_s,time_ns,time_ms;
int data(const char* file,const char * output)
{
    freopen(file,"r",stdin);
    freopen(output,"w",stdout);
    //cout<<"error!";
    //freopen("case.out","w",stdout);
    int i=1;
    //cout<<"error!";
    //cin>>x[i]>>y[i]>>r[i];
    //cout<<x[i]<<y[i]<<r[i];
    while(cin>>x[i]>>y[i]>>r[i++]) ;//cout<<i-1<<x[i-1]<<y[i-1]<<r[i-1]<<endl;
    //cout<<"error!";
    i-=2;
    totalNum = i;
    //cout<<totalNum<<endl;

    int ct = 0;
    for(;i>=1;i--)
    {
        for(int j=totalNum;j>=1;j--)
        {
            if(i==j) continue;
            ++ct;
            //cout<<x[i];
            c[i][j] = c[j][i]=  sqrt(pow((x[i]-x[j]),2)+pow(y[i]-y[j],2));
            if(c[i][j]==0) c[i][j] = c[j][i] = c[i][j]+1;
            //cout<<i<<' '<<j<<' '<<c[i][j]<<" "<<ct<<endl;
            
        }
    }
    //cout<<'3'<<endl;
    return totalNum;
}
//TSP问题求解函数
void TSP(int n,int graph[1005][1005],int location,int C){
    clock_gettime(CLOCK_MONOTONIC,&ts1);
    //构建二维数组[i,2^n]，j模拟集合个数
    int **D = new int*[n+1];  //建行0～n，为方便理解和表示，第0行未使用
    int **Rec = new int*[n+1];  //建立Rec
    int **R = new int*[n+1];

    for(int i=1;i<=n;i++){
    //建列表示集合
        R[i] = new int [(int)pow(2,n)];
        D[i] = new int [(int)pow(2,n)]; 
        Rec[i] = new int [(int)pow(2,n)];
    }

    //初始化D、Rec
    for(int i=1;i<=n;i++){
        D[i][0]=graph[i][location]; //D[i,{}]
        R[i][0] = r[1];
        Rec[i][0]= -1;
        for(int j=1;j<=(int)pow(2,n)-1;j++){
            D[i][j]=N;
            R[i][j]=0;
            Rec[i][j] = -1;
        }
    }

    //动态规划
    for(int j=1;j<=(int)pow(2,n)-1;j++){    //对每一列求解
        for(int i=1;i<=n;i++){  //每一行找最短路径
            int min = N;
            if(((int)pow(2,i-1) & j) == 0){   //顶点集不能包含i
                int length = N;
                int reward = 0;
                for(int k=1;k<=n;k++){
				    if((int)pow(2,k-1) & j ){ //若顶点在集合中
                        length = graph[i][k] + D[k][j-(int)pow(2,k-1)];
                        reward = r[k] + R[k][j-(int)pow(2,k-1)];
                        if(R[i][j]<reward&&length<C){
                            R[i][j] = reward;
                        }
                        if(D[i][j]>length&&length<C){
                            min = reward;
                            D[i][j] = length;
                            //R[i][j] = reward;
                            Rec[i][j] = k;//局部最优决策
                        }
                    }
                }
            }
        }
    }
    //cout<<(int)pow(2,n)-1-(int)pow(2,location-1)<<endl;

    //最短路径长度
    int maxreward = 0,maxi = 0;
    for(int i=1;i<=pow(2,n)-1;i++)
    {
        if(R[location][i]>maxreward)
        {
            maxreward = R[location][i];
            maxi = i;
        }
    }
    clock_gettime(CLOCK_MONOTONIC,&ts2);
    time_s = ts2.tv_sec - ts1.tv_sec;
    time_ns = ts2.tv_nsec - ts1.tv_nsec;
    cout<<"Dynamic Programming Algorithm"<<endl;
    cout<<"Max Reward:      "<<maxreward<<endl;
    cout<<"Path Cost：      "<<D[location][maxi]<<endl;
    //cout<<"最大reward："<<R[location][(int)pow(2,n)-1-(int)pow(2,location-1)]<<endl;//最短路径长度

    cout<<"Path："<<location;

    int row = location;
    int column = maxi;

    while(column > 0){
        cout<< "->"<<Rec[row][column];
        row = Rec[row][column];
        column -= (int)pow(2,row-1);
    }
	cout<<"->"<<location<<endl;
    printf("run time is %fms\n",time_s*1000+time_ns/1000000);
    cout<<"--------------------------------------"<<endl;
}
int vis[9999];
int ct = 0 ;
int path[N];
int maxct = 0;
int d[N][N];
int mincost = 9999;
//int ans[10000];
int maxr = -1;
int maxc = 9999;
int minc = 9999;
void DFS(int n,int graph[1005][1005],int location,int ct,int C,int reward,int cost){
//     
    if(n==ct)
    {
        //if(location==8&&path[1]==5&&path[2]==3){
        //for(int i=1;i<ct;++i)
        //{
          //  cout<<path[i]<<"<-";
        //}
        if(cost+graph[location][1]<C&&cost+graph[location][1]<minc)
        {
            minc = cost + graph[1][location];
        }
        if(reward+r[1]>maxr&&cost+graph[location][1]<C)
        {
            maxr = reward + r[1];
            maxc = cost+graph[location][1];
        }
        //creout<<reward+graph[1][location]<<endl;}}
        
        return ;
    }

    int minm = 9999999;

    for(int i=2;i<=totalNum;++i)
    {
        if(vis[i]==0)
        {
            vis[i] = 1;
            path[ct] = i;
            DFS(n,graph,i,ct+1,C,reward+r[i],cost+graph[location][i]);
            vis[i] = 0;
            path[ct] = 0;
            //minm = min(temp,minm);
        }
    }
    //return minm;
}
int book[13];
const int INF = 11111111;
int sum = 0, n, m, cnt = 0, ans = INF;
//int ans = INF;

void dfs(int a,int n)
{
    if(cnt>=n-1)
    {
        ans = min(sum + c[a][1],ans);
        return ;
    }
    book[a] = 1;
    for(int i=1;i<=n;++i)
    {
        if(!book[i])
        {
            sum+=c[a][i];
            cnt++;
            dfs(i,n);
            cnt--;
            sum -= c[a][i];
        }
    }
    book[a] = 0;
}

void greedy(int C)
{
    int v[N];
    int now = 1;
    int mins = N;
    int mini = -1;
    int flag = 1;
    int reward = 0;
    int cost = 0;
    cout<<"Nearest Greedy Result: "<<endl;
    cout<<"Path: 1<-";
    clock_gettime(CLOCK_MONOTONIC,&ts1);
    while(flag){
        flag = 0;
        mins = N;
    for(int i=2;i<=totalNum;++i)
    {
        if(v[i]==0)
        {
            flag = 1;
            if(c[i][now]<mins)
            {
                mins = c[i][now];
                mini = i;
            }
        }
    }
        if(flag==0) break;
        if(cost+c[mini][now]+c[mini][1]>C) {
            v[mini] = 1;
            //cout<<"|"<<mini;
            continue;
        }
        cost += c[mini][now];
        reward += r[mini];
        v[mini] = 1;
        cout<<mini<<"<-";
        now = mini;
    }
    clock_gettime(CLOCK_MONOTONIC,&ts2);
    time_s = ts2.tv_sec - ts1.tv_sec;
    time_ns = ts2.tv_nsec - ts1.tv_nsec;
    cout<<"1"<<endl;
    cout<<"Max Reward:      "<<reward+r[1]<<endl;
    cout<<"Path Cost:       "<<cost+c[now][1]<<endl;
    printf("run time is %fms\n",time_s*1000+time_ns/1000000);
    cout<<"--------------------------------------"<<endl;
}

void gready_reward(int C)
{
    int v[N];
    int flag = 1;
    int maxre = -1;
    int maxi = -1;
    int reward = 0;
    int cost = 0;
    int now = 1;
    for(int i=0;i<N;++i) v[i]=0;
    cout<<"Reward Greedy Result: "<<endl;
    cout<<"Path: 1<-";
    clock_gettime(CLOCK_MONOTONIC,&ts1);
    while(flag){
        flag = 0;
        maxre = -1;
    for(int i=2;i<=totalNum;++i)
    {
        //cout<<v[i];
        if(v[i]==0)
        {
            flag = 1;
            //cout<<"*";
            if(maxre<r[i])
            {
                maxre = r[i];
                maxi = i;
            }
        }
    }
    if(flag ==0 ) break;
    //cout<<maxi;
    if(cost+c[now][maxi]+c[maxi][1]>C) {
        v[maxi]=1;
        //cout<<"|"<<maxi;
        continue;
    }
    cost+=c[now][maxi];
    reward+=r[maxi];
    v[maxi]=1;
    cout<<maxi<<"<-";
    now = maxi;
    }
    clock_gettime(CLOCK_MONOTONIC,&ts2);
    time_s = ts2.tv_sec - ts1.tv_sec;
    time_ns = ts2.tv_nsec - ts1.tv_nsec;
    cout<<"1"<<endl;
    cout<<"Max Reward:      "<<reward+r[1]<<endl;
    cout<<"Path Cost:       "<<cost+c[now][1]<<endl;
    printf("run time is %fms\n",time_s*1000+time_ns/1000000);
    cout<<"--------------------------------------"<<endl;
}

void greedy_ratio(int C)
{
    int v[N];
    int flag = 1;
    int maxre = -1;
    int maxi = -1;
    int reward = 0;
    int cost = 0;
    int now = 1;
    for(int i=0;i<N;++i) v[i]=0;
    cout<<"Ratio Greedy Result: "<<endl;
    cout<<"Path: 1<-";
    clock_gettime(CLOCK_MONOTONIC,&ts1);
    while(flag){
        flag = 0;
        maxre = -1;
    for(int i=2;i<=totalNum;++i)
    {
        //cout<<v[i];
        if(v[i]==0)
        {
            flag = 1;
            //cout<<"*";
            if(maxre<(int)(r[i]/c[now][i]))
            {
                maxre = (int)(r[i]/c[now][i]);
                maxi = i;
            }
        }
    }
    if(flag ==0 ) break;
    //cout<<maxi;
    if(cost+c[now][maxi]+c[maxi][1]>C) {
        v[maxi]=1;
        //cout<<"|"<<maxi;
        continue;
    }
    cost+=c[now][maxi];
    reward+=r[maxi];
    v[maxi]=1;
    cout<<maxi<<"<-";
    now = maxi;
    }
    clock_gettime(CLOCK_MONOTONIC,&ts2);
    time_s = ts2.tv_sec - ts1.tv_sec;
    time_ns = ts2.tv_nsec - ts1.tv_nsec;
    cout<<'1'<<endl;
    cout<<"Max Reward:      "<<reward+r[1]<<endl;
    cout<<"Path Cost:       "<<cost+c[now][1]<<endl;
    printf("run time is %fms\n",time_s*1000+time_ns/1000000);
    cout<<"--------------------------------------"<<endl;
}

int main(int argc,char *argv[]){
    // cout<<"旅行家需要游历多少个城市？："<<endl;
    // int n;
    // cin>>n;
    // //建立二维数组模拟邻接矩阵
    // int **graph=new int* [n+1];
    // for(int i=1;i<=n;i++)
    //     graph[i] = new int[n+1];
    // for(int i=1;i<=n;i++){
    //     for(int j=1;j<=n;j++){
    //         cout<<"输入邻接矩阵graph["<<i<<"]["<<j<<"]的权："<<endl;
    //         cin>>graph[i][j];
    //     }
    // }
    // cout<<"旅行家现在在第几个城市？"<<endl;
    // int location;
    // cin>>location;
    // TSP(n,graph,location);   //TSP求解
    //test
    //cout<<"error!";
    //cout<<argv[1]<<argv[2]<<endl;
    totalNum = data(argv[1],argv[2]);
    //cout<<totalNum<<endl;
    int C=atoi(argv[3]);
    vis[1]=1;
    int mins = 9999;
    cout<<"--------------------------------------"<<endl;
    for(int i=totalNum;i>=1;i--)
    {   
        maxr = -1;
        minc = 999999;
        mincost = 9999;
        clock_gettime(CLOCK_MONOTONIC,&ts1);
        DFS(i,c,1,1,C,0,0);
        clock_gettime(CLOCK_MONOTONIC,&ts2);
        time_s = ts2.tv_sec - ts1.tv_sec;
        time_ns = ts2.tv_nsec - ts1.tv_nsec;
        //dfs(1,i);
        if(maxc<C)
        {
            cout<<"Naive Algorithm"<<endl;
            cout<<"Number of V:     "<<i<<endl;
            cout<<"Max Reward:      "<<maxr<<endl;
            cout<<"Path Cost:       "<<maxc<<endl;
            cout<<"Min cost:        "<<minc<<endl;
            printf("run time is %fms\n",time_s*1000+time_ns/1000000);
            cout<<"--------------------------------------"<<endl;
            break;
        }
        //cout<<maxs<<endl;
    }
    path[0] = 1;
    for(int i=1;i<=maxct;i++)
    {
        cout<<path[i]<<"<-";
    }
    cout<<"min cost:"<<d[1][1]<<endl;
    TSP(totalNum,c,1,C);
    greedy(C);
    gready_reward(C);
    greedy_ratio(C);
    return 0;
} 
