#ifndef INPUTSIMULATOR_H_INCLUDED
#define INPUTSIMULATOR_H_INCLUDED

#include <windows.h>
#include <string>

using namespace std;

void text_entry(wstring text);

void key_press(WORD vk);

void key_down(WORD vk);

void key_up(WORD vk);

#endif // INPUTSIMULATOR_H_INCLUDED
