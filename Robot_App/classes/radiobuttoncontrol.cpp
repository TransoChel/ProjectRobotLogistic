#include "radioButtonControl.h"

void RadioButtonControl::Update()
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

void RadioButtonControl::Draw()
{
    for (int i = 0; i < buttons.size(); ++i)
    {
        buttons[i]->Draw();
    }
}

bool RadioButtonControl::CheckUpdate()
{
    for (int i = 0; i < buttons.size(); ++i)
    {
        if (buttons[i]->active) {
            return true;
        }
    }
    return false;
}

void RadioButtonControl::NullUpdate() 
{
    for (int i = 0; i < buttons.size(); ++i)
    {
        if (buttons[i]->active) {
            buttons[i]->active = false;
        }
    }
}

int RadioButtonControl::SendNum() 
{
    for (int i = 0; i < buttons.size(); ++i)
    {
        if (buttons[i]->active) {
            return i;
        }
    }
}