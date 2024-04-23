#include <raylib.h>
#include <string>
#include <vector>
#include "Radiobutton.h"
#pragma once

class RadioButtonControl
{
public:
    RadioButton* buttons[12];
    void Update();
    void Draw();
    bool CheckUpdate();
    void NullUpdate();
    int SendNum();
};
