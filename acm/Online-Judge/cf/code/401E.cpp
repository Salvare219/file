#include<cstdio>
#include<cstring>
#include<cmath>
#include<algorithm>
#include<vector>
#include<queue>
using namespace std;

long long n,m,p;
int prim[50005],k;
int mi[100005];
bool vis[100005];
void pre()
{
    for(int i=2;i<100001;i++)
    {
        if(vis[i]==0) mi[i]=i,prim[k++]=i;
        for(int j=0;j<k && prim[j]*i<100001;j++)
        {
            vis[prim[j]*i]=1;
            mi[prim[j]*i]=prim[j];
            if(i%prim[j]==0) break;
        }
    }
}
int fk;
int fac[30];
long long dfs(long long b,long long c,long long s)
{
    if(b<2) return 0;
    long long ans=0,con;
    while(s<fk)
    {
        con=b/fac[s];
        ans=(ans+(m+1)*con%p-(fac[s]*c+con*fac[s]*c)*con/2%p-dfs(b/fac[s],c*fac[s],s+1))%p;
        s++;
    }
    return ans;
}
long long cal(long long s,long long l,long long r)
{
    fk=0;
    long long ss=s;
    while(ss!=1)
    {
        int c=mi[ss];
        fac[fk++]=c;
        while(ss%c==0)ss/=c;
    }
    long long a1=((m+1)*r-(1+r)*r/2-dfs(r,1,0))%p;
    long long a2=((m+1)*(l-1)-(l-1)*l/2-dfs(l-1,1,0))%p;
    long long ans=((a1-a2)%p+p)%p;
    return (n-s+1)*ans%p;
}
int main()
{
    long long l,r,sum=0;pre();
    scanf("%I64d%I64d%I64d%I64d%I64d",&n,&m,&l,&r,&p);
    for(long long i=1;i<=n;i++)
    {
        long long x,s;
        if(l>=i)x=sqrt(l*l-i*i);
        else x=1;
        if(r>=i)s=sqrt(r*r-i*i);
        else break;
        while(x*x+i*i<l*l)x++;
        while(s*s+i*i<=r*r)s++;s--;
        x=max(1ll,x);
        if(x>m)continue;
        s=min(s,1ll*m);
        if(x>s)continue;
        sum=(sum+cal(i,x,s)%p)%p;
    }
    sum=sum*2%p;
    if(l<=1&&r>=1)sum=(sum+1ll*n*(m+1)+1ll*(n+1)*m)%p;
    printf("%I64d\n",sum%p);
    return 0;
}