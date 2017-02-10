const double eps=1e-9;
int sgn(double x){return fabs(x)<eps?0:(x>0.0?1:-1);}
struct Hull_3
{
    int n,cnt; //初始化 n  点在内部 体积为正(面法向量向内)
    Point_3 ply[1005];
    int a[5000],b[5000],c[5000];
    bool ok[5000];
    bool v[5000];
    int q[5000];
    int vis[1005][1005];
    inline double S(const Point_3&a,const Point_3&b,const Point_3&c)
    {return (b-a)*(c-a)/Point_3(0,0,0);}
    inline double V(const Point_3&a,const Point_3&b,const Point_3&c,const Point_3&d)
    {return (b-a)*(c-a)%(d-a);}
    inline int ply_p(int f,const Point_3&p)
    {return sgn(V(ply[a[f]],ply[b[f]],ply[c[f]],p));}/*
    void deal(int p,int p1,int p2)
    {
        int f=vis[p1][p2];
        if(ok[f])
        {
            if(ply_p(f,ply[p])==1) dfs(p,f);
            else
            {
                a[cnt]=p2;b[cnt]=p1;c[cnt]=p;ok[cnt]=1;
                vis[p][p2]=vis[p1][p]=vis[p2][p1]=cnt++;
            }
        }
    }
    void dfs(int p,int f)
    {
        ok[f]=0;
        deal(p,b[f],a[f]);
        deal(p,c[f],b[f]);
        deal(p,a[f],c[f]);
    }*/
    inline bool deal(int p,int p1,int p2)
    {
        int f=vis[p1][p2];
        if(ok[f]&&v[f]==0)
        {
            if(ply_p(f,ply[p])==1)return 1;
            else
            {
                a[cnt]=p2;b[cnt]=p1;c[cnt]=p;ok[cnt]=1;
                vis[p][p2]=vis[p1][p]=vis[p2][p1]=cnt++;
            }
        }
        return 0;
    }
    void bfs(int p,int f)
    {
        int tail=0,front=1;
        memset(v,0,sizeof(v));
        q[0]=f;v[f]=1;
        while(tail!=front)
        {
            f=q[tail++];ok[f]=0;
            if(deal(p,b[f],a[f]))v[q[front++]=vis[b[f]][a[f]]]=1;
            if(deal(p,c[f],b[f]))v[q[front++]=vis[c[f]][b[f]]]=1;
            if(deal(p,a[f],c[f]))v[q[front++]=vis[a[f]][c[f]]]=1;
        }
    }
    bool same(int s,int e)
    {
        return ply_p(s,ply[a[e]])==0
             &&ply_p(s,ply[b[e]])==0
             &&ply_p(s,ply[c[e]])==0;
    }
    bool construct()
    {
        int i,j;
        if(n<4)return 0;
        bool f=1;
        for(i=1;i<n;i++)
            if(sgn(ply[0]/ply[i]))
            {
                swap(ply[1],ply[i]);
                f=0;break;
            }
        if(f)return 0;f=1;
        for(i=2;i<n;i++)
            if(sgn(S(ply[0],ply[1],ply[i])))
            {
                swap(ply[2],ply[i]);
                f=0;break;
            }
        if(f)return 0;f=1;
        for(i=3;i<n;i++)
            if(sgn(V(ply[0],ply[1],ply[2],ply[i])))
            {
                swap(ply[3],ply[i]);
                f=0;break;
            }
        if(f)return 0;cnt=0;
        for(i=0;i<4;i++)
        {
            a[cnt]=(i+1)%4;b[cnt]=(i+2)%4;c[cnt]=(i+3)%4;ok[cnt]=1;
            if(ply_p(cnt,ply[i])==1) swap(b[cnt],c[cnt]);
            vis[a[cnt]][b[cnt]]=vis[b[cnt]][c[cnt]]=vis[c[cnt]][a[cnt]]=cnt;
            cnt++;
        }
        for(i=4;i<n;i++)
        {
            for(j=0;j<cnt;j++)
                if(ok[j]&&ply_p(j,ply[i])==1)
                {
                    bfs(i,j);break;
                }
        }
        int k=cnt;
        cnt=0;
        for(i=0;i<k;i++)
            if(ok[i])
                a[cnt]=a[i],b[cnt]=b[i],c[cnt]=c[i],ok[cnt++]=1;
        return 1;
    }
    double area()
    {
        double ret=0;
        for(int i=0;i<cnt;i++)
            ret+=S(ply[a[i]],ply[b[i]],ply[c[i]]);
        return fabs(ret*0.5);
    }
    double volume()
    {
        double ret=0;
        for(int i=1;i<cnt;i++)
            ret+=V(ply[a[0]],ply[a[i]],ply[b[i]],ply[c[i]]);
        return fabs(ret/6);
    }
    int facepolygon()
    {
        int ret=0,i,j;
        bool f;
        for(i=0;i<cnt;i++)
        {
            for(j=0,f=1;j<i;j++)
                if(same(i,j)){f=0;break;}
            if(f)ret++;
        }
        return ret;
    }
    double dis(int f,const Point_3&p1)
    {
        return V(ply[a[f]],ply[b[f]],ply[c[f]],p1)/S(ply[a[f]],ply[b[f]],ply[c[f]]);
    }
    Point_3 Centre()
    {
        Point_3 ret=Point_3(0,0,0);
        double sum=0.0,z;
        for(int i=0;i<cnt;i++)
        {
            z=V(ply[a[0]],ply[a[i]],ply[b[i]],ply[c[i]]);
            ret=(ply[a[0]]+ply[a[i]]+ply[b[i]]+ply[c[i]])/4.0*z+ret;
            sum+=z;
        }
        return ret/sum;
    }
}h;
