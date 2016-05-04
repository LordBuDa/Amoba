#include <graphics.hpp>
#include <iostream>
#include "widget.hpp"
#include "engine.hpp"
#include <vector>

using namespace std;
using namespace genv;


int main()
{
    event ev;
    AddNumeric(220,120,60,30,20,50);
    AddNumeric(310,120,60,30,20,50);
    while(gin >> ev)
    {
        if(ev.keycode==key_escape){return 0;}
        if(win==false)
        {
            if(play==false){Kezdo(ev);}
            if(play==true){Play(ev);}
        }
        if(win==true)
        {
            Meghalas(ev);
        }
    }
    return 0;
}
