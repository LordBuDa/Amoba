#include <iostream>
#include <graphics.hpp>
#include "engine.hpp"
#include "widget.hpp"
#include <vector>

using namespace std;
using namespace genv;

int player=0;
int a=20;
int b=20;
bool win=false;
bool play=false;
bool dontetlen=false;
vector<Negyzet> sorbanX, sorbanO;

void Check(Negyzet &n, event ev)
{
    if(ev.pos_x<(n.x+cellaszel-(szegely/2)) && ev.pos_x>(n.x+(szegely/2)) && ev.pos_y>(n.y+(szegely/2)) &&ev.pos_y<(n.y+cellaszel-(szegely/2)) &&ev.button==btn_left )
    {
        if(n.state==-1)
        {
            if(player==0){n.state=0;player=1;}
            else{n.state=1;player=0;}
        }
    }
}

void CheckX(int i, int j, vector<vector<Negyzet> > Palya)
{
    if(Palya[i][j].state==0)
    {
        sorbanX.push_back(Palya[i][j]);
        if(sorbanX.size()==5){win=true;play=false;return;}
    }
    else{sorbanX.clear();}
}
void CheckO(int i, int j, vector<vector<Negyzet> > Palya)
{
    if(Palya[i][j].state==1)
    {
        sorbanO.push_back(Palya[i][j]);
        if(sorbanO.size()==5){win=true;play=false;return;}
    }
    else{sorbanO.clear();}
}
void FinalCheck(vector<vector<Negyzet> > Palya)
{
    int n=Palya.size();
    int m=Palya[0].size();
    //fuggoleges
    for(int i=0;i<n;i++)
    {
        for(int j=0;j<m;j++)
        {
            CheckX(i,j,Palya);
            CheckO(i,j,Palya);
        }
        sorbanX.clear();
        sorbanO.clear();
    }
    //vizszintes
    for(int j=0;j<m;j++)
    {
        for(int i=0;i<n;i++)
        {
            CheckX(i,j,Palya);
            CheckO(i,j,Palya);
        }
        sorbanX.clear();
        sorbanO.clear();
    }
    //keresztbe balra le (x=i+j allando)
    for(int x=0;x<(n+m-1);x++)
    {
        int i=(x<m ? 0 : x-m+1);
        while(i<n && x-i>=0)
        {
            CheckX(i,x-i,Palya);
            CheckO(i,x-i,Palya);
            i++;
        }
        sorbanX.clear();
        sorbanO.clear();
    }
    //keresztbe jobbra le (x=i-j allando)
    for(int x=n-1;x>-m;x--)
    {
        int i=(x>0 ? x : 0);
        while(i<n && i-x<m)
        {
            CheckX(i,i-x,Palya);
            CheckO(i,i-x,Palya);
            i++;
        }
        sorbanX.clear();
        sorbanO.clear();
    }
    //betelt-e
    int t=0;
    for(int i=0;i<Palya.size();i++)
        {
            for(int j=0;j<Palya[i].size();j++)
            {
                if(Palya[i][j].state==-1)
                {
                    t++;
                }
            }
        }
    if(t==0){play=false;win=true;dontetlen=true;}
    gout<<refresh;
}

void Play(event ev)
{
    vector<vector<Negyzet> > deref;
        for(int i=0;i<Palya.size();i++)
        {
            vector<Negyzet> v;
            for(int j=0;j<Palya[i].size();j++)
            {
                Check(*Palya[i][j],ev);
                Palya[i][j]->kirajzol();
                v.push_back(*Palya[i][j]);
            }
            deref.push_back(v);
        }
        FinalCheck(deref);
}

void Kezdo(event ev)
{
    gout.open(430,300);
    gout<<move_to(0,0)<<color(100,100,100)<<box(430,300);
    gout.load_font("airstrikebullet.ttf",85);
    gout<<move_to(50,20)<<color(250,50,0)<<text("AMOBA");
    gout.load_font("airstrikelaser.ttf",20);
    gout<<move_to(15,120)<<text("A palya merete:");
    gout<<move_to(285,125)<<text("X");
    gout.load_font("LiberationSans-Regular");
    for(int i=0;i<Widgets.size();i++)
    {
        Widgets[i].check(ev);
        Widgets[i].kirajzol();

    }
    gout.load_font("airstrikelaser.ttf",23);
    gout<<move_to(10,200)<<color(250,50,0)<<text("Jatek kezdesehez nyomj Entert!");
    gout.load_font("airstrikelaser.ttf",18);
    gout<<move_to(140,240)<<text("Kilepes: Esc");

    a=Widgets[0].aktualis;
    b=Widgets[1].aktualis;
    if(ev.keycode==key_enter)
    {
        play=true;
        GenerateMap(Widgets[0].aktualis,Widgets[1].aktualis);
    }
    gout<<refresh;
}

void Meghalas(event ev)
{
    gout<<move_to(0,0)<<color(0,0,0)<<box((a*cellaszel+20),(b*cellaszel+20));
    if(dontetlen)
    {
        gout.load_font("airstrikelaser.ttf",45);
        gout<<move_to(70,40)<<color(0,0,255)<<text("Dontetlen!");
        gout.load_font("airstrikelaser.ttf",35);
        gout<<move_to(50,140)<<text("A palya betelt!");
    }
    else
    {
        gout.load_font("airstrikelaser.ttf",50);
        gout<<move_to(40,40)<<color(0,0,255)<<text("A  nyertes: ");
        string s;
        if(player==1)
        {
            s="Az  1.  jatekos ( X )";
        }
        else{s="A  2.  jatekos ( kor )";}
        gout.load_font("airstrikelaser.ttf",35);
        gout<<move_to(20,140)<<text(s);
    }
    gout.load_font("airstrikelaser.ttf",27);
    gout<<color(255,0,0)<<move_to(10,290)<<text("Uj jatekhoz nyomj Entert!");
    gout<<move_to(10,330)<<text("Fomenuhoz nyomj Space-t!");
    gout<<move_to(130,380)<<text("Kilepes: Esc");

    if(ev.keycode==key_enter){win=false;play=true;GenerateMap(a,b);}
    if(ev.keycode==key_space){win=false;play=false;}

    gout<<refresh;
}
