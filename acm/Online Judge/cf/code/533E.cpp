#include<bits/stdc++.h>
using namespace std;


char s[100050],f[100050];
int main()
{
    int n,f1=-1,f2=-1;
    scanf("%d%s%s",&n,s,f);
    for(int i=0;i<n;i++)
        if(s[i]==f[i]);
        else
        {
            f1=i;
            break;
        }
    for(int i=n-1;i>-1;i--)
        if(s[i]==f[i]);
        else
        {
            f2=i;
            break;
        }
    int ans=0,cnt=1;
    for(int i=f1;i<f2;i++)
        if(s[i]!=f[i+1])cnt=0;
    ans+=cnt;cnt=1;
    for(int i=f1;i<f2;i++)
        if(f[i]!=s[i+1])cnt=0;
    ans+=cnt;
    printf("%d\n",ans);
    return 0;
}
