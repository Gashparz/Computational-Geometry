#include <graphics.h>
#include <conio.h>
#include <windows.h>
#include <iostream>
#include <fstream>
#include <algorithm>
#include <iomanip>
#include <fstream>
#define x first
#define y second
using namespace std;
const int NMAX=120004;
int n, i;
typedef pair<double, double> punct;
punct v[NMAX], st[NMAX];


inline double cp(const punct &a,const punct &b,const punct &c)
{
    return (b.x-a.x)*(c.y-a.y)-(b.y-a.y)*(c.x-a.x);
}


inline int cmp(const punct& a, const punct& b)
{
    return cp(v[1], a, b)<0;
}


void sortare()
{ //se alege cel mai din stanga punct.
    //se translateaza sistemul cu originea in punctul ales
    //Se sorteaza toate punctele in functie de  (unghiul polar).
    int i, p=1;
    for (i=2; i<=n; ++i)
        if (v[i]<v[p])
            p=i;
    swap(v[1],v[p]);
    sort(v+2,v+n+1,cmp);
}


int main()
{
   //int gd = DETECT, gm;

   //initgraph(&gd, &gm, "C:\\TC\\BGI");
   initwindow(500,500);
    ifstream f("date.in");
    int m ;
    f>>m;

    line(250, 10, 250, 490);
    line(10, 250, 490, 250);

    line(247, 15, 250, 10); // sageata sus
    line(250, 10, 253, 15);

    line(487, 247, 490, 250); // sageata dreapta
    line(487, 253, 490, 250);

    f>>n;
    for(i=1; i<=n; i++)
    {
        double x, y;
        f>>x>>y;
        setcolor(LIGHTMAGENTA);
        if(x >= 0 && y >= 0) // cadranul 1
        {
            v[i].x = 250 + x * (250 / m);
            v[i].y = 250 - y * (250 / m);
        }
        else
            if ( x < 0 && y >= 0) // cadranul 2
        {
            v[i].x = 250 + x * (250 / m);
            v[i].y = 250 - y * (250 / m);
        }
        else
            if ( x < 0 && y < 0) // cadranul 3
        {
            v[i].x = 250 + x * (250 / m);
            v[i].y = 250 - y * (250 / m);
        }
        else
            if( x >= 0 && y < 0) // cadranul 4
        {
            v[i].x = 250 + x * (250 / m);
            v[i].y = 250 - y * (250 / m);
        }
        line(v[i].x - 1, v[i].y, v[i].x + 1, v[i].y);
        line(v[i].x, v[i].y - 1, v[i].x, v[i].y + 1);
        Sleep(500);
    }
    f.close ();
    sortare();
    //se construieste o stiva care retine punctele de pe
    st[1]=v[1];
    st[2]=v[2];
    int vf=2;
    for(i=3; i<=n; i++)
    {

        while(vf>=2 && cp(st[vf-1],st[vf],v[i])>0)
            vf--;
        st[++vf]=v[i];
    }

    setcolor(LIGHTBLUE);
    double a,b;
    cout<<"Punctele ce formeaza poligonul:\n";
    cout<<(st[i].x - 250)/(250/m)<<" "<<(250 - st[i].y)/(250/m)<<"\n";
    Sleep(1000);
    for(i=1; i<vf; i++)
    {
        a = (st[i+1].x - 250)/(250/m);
        b= (250 - st[i+1].y)/(250/m);
        cout<<a<<" "<< b<<endl;
        Sleep(1000);

        line(st[i].x, st[i].y, st[i+1].x, st[i+1].y);


        Sleep(2000);
    }
    line(st[1].x, st[1].y, st[vf].x, st[vf].y);

   getch();
   closegraph();
   return 0;
}
