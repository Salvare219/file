/*
求四边形的两个费马点，查资料得知，第三个点是没有必要的，枚举每两个点对的组合，反复求两个三角形费马点直到与基准点逼近到一点，对于每个点对的情况取小就是最后的答案。
*/
#include<stdio.h>
#include<string.h>
#include<math.h>
#include<iostream>
#include<algorithm>
using namespace std;

const double eps=1e-8;
const double pi=acos(-1.0);
struct point_t
{
    double x, y;
    point_t() { }
    point_t(double tx, double ty) : x(tx), y(ty) { }
    point_t operator-(const point_t &r) const
    {
        return point_t(x - r.x, y - r.y);
    }
    point_t operator+(const point_t &r) const
    {
        return point_t(x + r.x, y + r.y);
    }
    point_t operator*(const double r) const
    {
        return point_t(x * r, y * r);
    }
    point_t operator/(const double r) const
    {
        return point_t(x / r, y / r);
    }
    void read()
    {
        scanf("%lf%lf", &x, &y);
    }
} p[4], tp[4];

int dblcmp(double x)
{
    return (x < -eps ? -1 : x > eps);
}

double dist(point_t p1, point_t p2)
{
    return sqrt((p1.x - p2.x) * (p1.x - p2.x) + (p1.y - p2.y) * (p1.y - p2.y));
}

double cross(point_t p1, point_t p2)
{
    return p1.x * p2.y - p1.y * p2.x;
}

double dot(point_t p1, point_t p2)
{
    return p1.x * p2.x + p1.y * p2.y;
}

double angle(point_t p1, point_t p2, point_t p3)
{
    double d = dot(p2 - p1, p3 - p1) / dist(p1, p2) / dist(p1, p3);
    return acos(d);
}

point_t inter(point_t a, point_t b, point_t c, point_t d)
{
    point_t p1 = b - a, p2 = d - c;
    double a1 = p1.y, b1 = -p1.x, c1;
    double a2 = p2.y, b2 = -p2.x, c2;
    c1 = a1 * a.x + b1 * a.y;
    c2 = a2 * c.x + b2 * c.y;
    return point_t((c1 * b2 - c2 * b1) / (a1 * b2 - a2 * b1), (c1 * a2 - c2 * a1) / (b1 * a2 - b2 * a1));
}

point_t ver(point_t p1, point_t p2)
{
    point_t v = (p2 - p1) / 2 * sqrt(3.0);
    swap(v.x, v.y);
    v.x = -v.x;
    return v;
}

point_t fermat(point_t p1, point_t p2, point_t p3)
{
    if (angle(p1, p2, p3) > pi / 3 * 2) return p1;
    if (angle(p2, p1, p3) > pi / 3 * 2) return p2;
    if (angle(p3, p1, p2) > pi / 3 * 2) return p3;
    point_t v1 = ver(p1, p2);
    point_t m1 = (p1 + p2) / 2;
    if (dblcmp(cross(p3 - p1, p2 - p1)) * dblcmp(cross(v1 + m1 - p1, p2 - p1)) > 0) v1.x = -v1.x, v1.y = -v1.y;
    m1 = m1 + v1;
    point_t v2 = ver(p1, p3);
    point_t m2 = (p1 + p3) / 2;
    if (dblcmp(cross(p2 - p1, p3 - p1)) * dblcmp(cross(v2 + m2 - p1, p3 - p1)) > 0) v2.x = -v2.x, v2.y = -v2.y;
    m2 = m2 + v2;
    return inter(p3, m1, p2, m2);
}

int main()
{
    int T;
    scanf("%d", &T);
    while(T--)
    {
        for (int i=0; i<4;i++) p[i].read();
        double res = 1e10;
        for (int i=0; i<4; i++)
        {
            for (int j=i+1; j<4; j++)
            {
                int l=0, r=3;
                for (int k=0; k<4; k++)
                {
                    if (k==i||k==j)tp[l++]=p[k];
                    else tp[r--]=p[k];
                }
                point_t f1=tp[2];
                point_t f2=fermat(tp[0],tp[1],tp[2]);
                bool c=0;
                for (;;)
                {
                    point_t tf1, tf2;
                    if (c==0)
                    {
                        tf1=fermat(tp[2],tp[3],f2);
                        tf2=f2;
                    }
                    else
                    {
                        tf1=f1;
                        tf2=fermat(tp[0],tp[1],f1);
                    }
                    c^=1;
                    if(dblcmp(dist(tf1, f1)) == 0 && dblcmp(dist(tf2, f2)) == 0) break;
                    else f1 = tf1, f2 = tf2;
                }
                res = min(res, dist(f2, tp[0]) + dist(f2, tp[1]) + dist(f1, tp[2]) + dist(f1, tp[3]) + dist(f1, f2));
            }
        }
        printf("%.4lf\n",res);
    }
    return 0;
}
