#ifndef WIDGET_HPP_INCLUDED
#define WIDGET_HPP_INCLUDED
#include <vector>

void GenerateMap(int a, int b);
void AddNumeric(int a,int b,int c,int d,int e,int f);
const int cellaszel=20;
const int szegely=(cellaszel/10);

class Szamos
{
public:
    int x,y,szel,mag,aktualis,minimum,maximum;
    bool sel,sel2;
    Szamos(int a,int b,int c,int d,int e,int f);
    void kirajzol();
    void check(genv::event ev);
};

class Negyzet
{
public:
    int x,y,szel,state;
    Negyzet(int a,int b);
    void kirajzol();
};

extern std::vector<std::vector<Negyzet*> > Palya;
extern std::vector<Szamos> Widgets; //Palyameret allito widgetek
#endif // WIDGET_HPP_INCLUDED
