#include<cstdio>
#include<cstring>
#include<cmath>
#include<algorithm>
#include<vector>
#include<queue>
using namespace std;

struct Point
{
    double x,y;
    Point(double a=0.0,double b=0.0){x=a;y=b;}
    Point operator+(const Point&a)const{return Point(x+a.x,y+a.y);}
    Point operator-(const Point&a)const{return Point(x-a.x,y-a.y);}
    Point operator*(const double&a)const{return Point(x*a,y*a);}
    double operator*(const Point&a)const{return x*a.y-y*a.x;}
    Point operator/(const double&a)const{return Point(x/a,y/a);}
    double operator/(const Point&a)const{return sqrt((a.x-x)*(a.x-x)+(a.y-y)*(a.y-y));}
}hull[20050];
struct Line
{
    Point s,t;
    double arg;
    Line(){}
    Line(Point a,Point b){s=a;t=b;arg=atan2(b.y-a.y,b.x-a.x);}
    Point operator&(const Line&a)const{return (t-s)*((s-a.s)*(a.s-a.t))/((s-t)*(a.s-a.t))+s;}
    bool operator<(const Line&a)const
    {
        if(fabs(arg-a.arg)>1e-6)return arg<a.arg;
        else return (a.s-s)*(t-s)>1e-9;
    }
}q[20050],l[20050];
const double pi=acos(-1.0);
int halfplaneintersection(Line v[],int n,Point ans[])
{
    int front=0,tail=0;
    sort(v,v+n);q[0]=v[0];
    for(int i=1;i<n;i++)
        if(fabs(v[i-1].arg-v[i].arg)>1e-6)
        {
            while(front<tail&&(ans[tail-1]-v[i].s)*(v[i].t-v[i].s)>1e-9)tail--;
            while(front<tail&&(ans[front]-v[i].s)*(v[i].t-v[i].s)>1e-9)front++;
            //if(fabs(q[tail].arg+pi-v[i].arg)<1e-6)return 0;
            ans[tail]=v[i]&q[tail];q[++tail]=v[i];
        }
    while(front<tail&&(ans[tail-1]-q[front].s)*(q[front].t-q[front].s)>1e-9)tail--;
    ans[tail]=q[tail]&q[front];
    for(int i=front;i<=tail;i++)ans[i-front]=ans[i];
    return tail-front+1;
}
int main()
{
    int n;
    double x,y,x1,y1;
    while(~scanf("%d",&n))
    {
        l[0]=Line(Point(0.0,0.0),Point(10000.0,0.0));
        l[1]=Line(Point(10000.0,0.0),Point(10000.0,10000.0));
        l[2]=Line(Point(10000.0,10000.0),Point(0.0,10000.0));
        l[3]=Line(Point(0.0,10000.0),Point(0.0,0.0));
        for(int i=0;i<n;i++)
            scanf("%lf%lf%lf%lf",&x,&y,&x1,&y1),l[i+4]=Line(Point(x,y),Point(x1,y1));
        int k=halfplaneintersection(l,n+4,hull);
        double area=0.0;
        for(int i=1;i<k;i++)
            area+=(hull[i]-hull[0])*(hull[i-1]-hull[0]);
        printf("%.1f\n",fabs(area)/2.0);
    }
    return 0;
}
