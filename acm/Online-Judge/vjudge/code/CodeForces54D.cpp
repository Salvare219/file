#include<cstdio>
#include<cstring>
#include<cmath>
#include<cstdlib>
#include<algorithm>
#include<string>
#include<vector>
#include<map>
using namespace std;



char name[200],xu[200],sub[300];
int n,k;
bool vis[200][30];
int time[200];
bool cmp(char a,char b)
{
	return vis[a-'a']<vis[b-'a'];
}
int main()
{
//	freopen("1.txt","r",stdin);
	scanf("%d%d",&n,&k);
	scanf("%s%s",name,xu);
	for(int i=0;i<n;i++)
	{
		time[i]=k;
	}
	for(int i=0;xu[i];i++)
	{
		if(xu[i]=='1')
		{
			for(int j=0;name[j];j++)
			{
				if(sub[i+j]==0) sub[i+j]=name[j];
				else 
				{
					if(sub[i+j]==name[j]) continue;
					else 
					{
						printf("No solution\n");
						return 0;
					}
				}
			}
		}
	}
	for(int i=0;xu[i];i++)
	{
		if(xu[i]=='0')
		{
			bool f=0;
			for(int j=0;name[j];j++)
			{
				if(sub[i+j]==0) 
				{
					if(vis[i+j][name[j]-'a']) 
					{
							f=1;
							break;
					}
					else 
					{
						if(time[i+j]!=1)
						{
							time[i+j]--;
							vis[i+j][name[j]-'a']=1;
							f=1;
							break;
						}
					}
				}
				else 
				{
					if(sub[i+j]!=name[j]) 
					{
						f=1;
						break;
					}
				}
			}
			if(f==0) 
			{
				printf("No solution\n");
				return 0;
			}
		}
	}
	for(int i=0;i<n;i++)
	{
		if(sub[i]==0)
		{
			for(int j=0;j<k;j++)
			{
				if(vis[i][j]==0)
				{
					sub[i]='a'+j;
				}
			}
		}	
	}
	sub[n]=0;
	printf("%s\n",sub);
	return 0;
}