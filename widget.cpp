#include <graphics.hpp>
#include "widget.hpp"
#include "engine.hpp"
#include <vector>
#include <sstream>
#include <cmath>

using namespace std;
using namespace genv;

vector<vector<Negyzet*> > Palya;
vector<Szamos> Widgets;

void GenerateMap(int a, int b)
{
    Palya.clear();
    gout.open((a*cellaszel+20),(b*cellaszel+20));
    for(int i=0;i<a;i++)
    {
        vector<Negyzet* > w;
        for(int j=0;j<b;j++)
        {
            Negyzet *n=new Negyzet(i*cellaszel+10,j*cellaszel+10);
            w.push_back(n);
        }
        Palya.push_back(w);
    }
}
void AddNumeric(int a,int b,int c,int d,int e,int f)
{
    Szamos w(a,b,c,d,e,f);
    Widgets.push_back(w);
}

Szamos::Szamos(int a,int b,int c,int d,int e,int f)
    {
        x=a;
        y=b;
        szel=c;
        mag=d;
        sel=false;
        sel2=false;
        aktualis=e;
        minimum=e;
        maximum=f;
    }
Negyzet::Negyzet(int a,int b)
    {
        x=a;
        y=b;
        szel=cellaszel;
        state=-1;
    }

void Szamos::kirajzol()
{
    if(sel){gout<<move_to(szel+x-mag/2,y)<<color(0,20,200)<<box(mag/2,mag/2);}
    if(sel2){gout<<move_to(szel+x-mag/2,y+mag/2)<<color(0,20,200)<<box(mag/2,mag/2);}

    gout<<color(255,50,0)<<move_to(x,y)<<box(szel,2)<<box(-2,mag)<<box(-szel,-2)<<box(2,-mag);
    gout<<move_to(szel+x-mag/2,y)<<box(2,mag)<<move_to(szel+x-mag/2,y+mag/2)<<box(mag/2,2);
    gout<<move_to(szel+x-mag/3,y+mag/2.5)<<text("+")<<move_to(szel+x-mag/3,y+mag/1.5)<<text("_");
    stringstream zsemle;
    string s;
    zsemle<<aktualis;
    zsemle>>s;
    gout<<move_to(x+10,y+mag/1.5)<<text(s);
}
void Szamos::check(event ev)
{
    if(ev.pos_x>(szel+x-mag/2) && ev.pos_x<(szel+x) && ev.pos_y>y && ev.pos_y<y+mag/2)
    {
        sel=true;
        if( ev.button==btn_left){aktualis++;}
    }
    else{sel=false;}
    if(ev.pos_x>(szel+x-mag/2) && ev.pos_x<(szel+x) && ev.pos_y>y+mag/2 && ev.pos_y<y+mag)
    {
        sel2=true;
        if(ev.button==btn_left){aktualis--;}
    }
    else{sel2=false;}

    if(aktualis<minimum){aktualis=minimum;}
    if(aktualis>maximum){aktualis=maximum;}
}
void Negyzet::kirajzol()
{
    gout<<move_to(x,y)<<color(150,150,150)<<box(szel,szel)<<move_to(x+(szegely/2),y+(szegely/2))<<color(0,0,0)<<box(szel-szegely,szel-szegely);
    if(state==0)
    {
        gout<<color(200,80,80)<<move_to(x+5,y+5)<<line_to((x+cellaszel-5),(y+cellaszel-5));
        gout<<move_to((x+cellaszel-5),(y))<<line_to(x+5,(y+cellaszel-5));
    }
    if(state==1)
    {
        gout<<move_to(x+cellaszel/4,y+cellaszel/4);
        for(float i=0;i<200;i++)
        {
            gout<<color(200,80,80)<<move(sin(i)*cellaszel/4,cos(i)*cellaszel/4)<<dot;
        }
    }
}

