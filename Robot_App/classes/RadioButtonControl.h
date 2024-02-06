#include <raylib.h>
#include <string>
#include <vector>
#include "Radiobutton.h"
#pragma once

class RadioButtonControl
{
public:
    std::vector<RadioButton *> buttons;
    void Update();
    void Draw();
    bool CheckUpdate();
    void NullUpdate();
    int SendNum();
};
