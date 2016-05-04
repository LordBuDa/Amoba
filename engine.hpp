#ifndef ENGINE_H_INCLUDED
#define ENGINE_H_INCLUDED
#include <vector>
#include "widget.hpp"

extern int player,a,b;
extern bool win,play,dontetlen;
extern std::vector<Negyzet> sorbanX, sorbanO;
void Check(Negyzet &n, genv::event ev);
void Check2(int i, int j, std::vector<std::vector<Negyzet> > Palya);
void FinalCheck(std::vector<std::vector<Negyzet> > Palya);
void Play(genv::event ev);
void Kezdo(genv::event ev);
void Meghalas(genv::event ev);

#endif // ENGINE_H_INCLUDED
