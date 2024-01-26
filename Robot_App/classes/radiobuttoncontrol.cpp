#include <raylib.h>
#include <string>
#include <vector>
#include "radiobutton.cpp"
#pragma once

class RadioButtonControl
{
public:
    std::vector<RadioButton *> buttons;
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
    bool CheckUpdate() {
        for (int i = 0; i < buttons.size(); ++i)
        {
            if (buttons[i]->active) {
                return true;
            }
        }
        return false;
    }
    void NullUpdate() {
        for (int i = 0; i < buttons.size(); ++i)
        {
            if (buttons[i]->active) {
                buttons[i]->active = false;
            }
        }
    }
    int SendNum() {
        for (int i = 0; i < buttons.size(); ++i)
        {
            if (buttons[i]->active) {
                return i;
            }
        }
    }
};
