#include <graphics.hpp>
#include "widget.hpp"
#include "engine.hpp"

int main()
{
    AddNumeric(220,120,60,30,20,50); //Palyameret allito widgetek
    AddNumeric(310,120,60,30,20,50);
    EventLoop();
    return 0;
}
