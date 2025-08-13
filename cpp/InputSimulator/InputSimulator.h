#ifndef INPUTSIMULATOR_H_INCLUDED
#define INPUTSIMULATOR_H_INCLUDED

#include <windows.h>
#include <string>

using namespace std;

void text_entry(wstring text) {
    INPUT* inputs = new INPUT[text.size()]{};
    for (int i = 0; i < text.size(); i++) {
        inputs[i].type = INPUT_KEYBOARD;
        inputs[i].ki.wVk = 0;
        inputs[i].ki.wScan = text[i];
        inputs[i].ki.time = 0;
        inputs[i].ki.dwFlags = KEYEVENTF_UNICODE;
        inputs[i].ki.dwExtraInfo = 0;
    }

    SendInput(text.size(), inputs, sizeof(INPUT));
    delete[] inputs;
}

void key_press(WORD vk)
{
    INPUT inputs[2] = {};
    inputs[0].type = INPUT_KEYBOARD;
    inputs[0].ki.wVk = vk;
    inputs[0].ki.wScan = 0;
    inputs[0].ki.time = 0;
    inputs[0].ki.dwFlags = 0;
    inputs[0].ki.dwExtraInfo = 0;
    inputs[1].type = INPUT_KEYBOARD;
    inputs[1].ki.wVk = vk;
    inputs[1].ki.wScan = 0;
    inputs[1].ki.time = 0;
    inputs[1].ki.dwFlags = KEYEVENTF_KEYUP;
    inputs[1].ki.dwExtraInfo = 0;

    SendInput(ARRAYSIZE(inputs), inputs, sizeof(INPUT));
}

#endif // INPUTSIMULATOR_H_INCLUDED
