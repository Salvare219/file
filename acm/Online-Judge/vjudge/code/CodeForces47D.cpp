#include<cstdio>
#include<cstring>
#include<cmath>
#include<algorithm>
#include<vector>
#include<queue>
using namespace std;

char s[20][50];
int x[20],ans;
int tes[50],now[50];
int main()
{
    int n,m;
    scanf("%d%d",&n,&m);
    for(int i=0;i<m;i++)
        scanf("%s%d",s[i],x+i);
    memset(tes,0,sizeof(tes));
    for(int i=0;i<x[0];i++)
        tes[n-i-1]=1;
    do
    {
        for(int i=0;i<n;i++)
            now[i]=(1-tes[i])^(s[0][i]-'0');
        bool f=0;
        for(int i=1;i<m;i++)
        {
            int sum=0;
            for(int j=0;j<n;j++)
                if(now[j]==s[i][j]-'0')sum++;
            if(sum!=x[i])f=1;
        }
        if(!f)ans++;
    }while(next_permutation(tes,tes+n));
    printf("%d\n",ans);
	return 0;
}