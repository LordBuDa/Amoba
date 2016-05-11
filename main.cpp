#include <graphics.hpp>
#include <iostream>
#include "widget.hpp"
#include "engine.hpp"
#include <vector>

using namespace std;
using namespace genv;


int main()
{
    AddNumeric(220,120,60,30,20,50); //Palya merete widgetek
    AddNumeric(310,120,60,30,20,50);
    EventLoop();
    return 0;
}
