#include<bits/stdc++.h>
using namespace std;


vector<int>gra[200050];
long long dp[200050][2];
int a[200050];
void dfs(int s)
{
    int y;
    long long sum=0,d=1ll<<60,cnt=0,f=0;
    for(int i=0;i<gra[s].size();i++)
    {
        dfs(y=gra[s][i]);f++;
        if(dp[y][0]<dp[y][1])cnt++;
        sum+=max(dp[y][0],dp[y][1]);
        d=min(d,abs(dp[y][0]-dp[y][1]));
    }
    if(f==0)d=0;
    if(cnt&1)
        dp[s][1]=max(sum,sum-d+a[s]),dp[s][0]=sum-d;
    else
        dp[s][1]=sum+a[s],dp[s][0]=sum;
}
int main()
{
    int n,x;scanf("%d",&n);
    for(int i=1;i<=n;i++)
    {
        scanf("%d%d",&x,a+i);
        if(x!=-1)gra[x].push_back(i);
    }
    dfs(1);
    printf("%I64d\n",max(dp[1][0],dp[1][1]));
    return 0;
}
