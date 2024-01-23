#include <raylib.h>
#include <string>
#include <vector>
#include "radiobutton.cpp"
#pragma once

class RadioButtonControl
{
public:
    std::vector<RadioButton *> buttons;
    // RadioButtonControl(int a) {
    //     for (int i = 0; i < a; ++i) {
    //         RadioButton(coord, size, color, text);
    //         buttons.push_back();
    //     }
    // }
    void Update()
    {
        int check = -1;
        for (int i = 0; i < buttons.size(); ++i)
        {
            if (buttons[i]->CheckButtonPressed())
            {
                buttons[i]->active = true;
                check = i;
                break;
            }
        }

        if (check >= 0)
        {
            for (int i = 0; i < buttons.size(); ++i)
            {
                if (i != check)
                {
                    buttons[i]->active = false;
                }
            }
        }
    }
    void Draw()
    {
        for (int i = 0; i < buttons.size(); ++i)
        {
            buttons[i]->Draw();
        }
    }
};
