#include <raylib.h>
#include <string>
#include <vector>
#include "radiobutton.cpp"
#pragma once

class RadioButtonControl {
public:
    std::vector <RadioButton*> buttons;
    //RadioButtonControl(int a) {
    //    for (int i = 0; i < a; ++i) {
    //        RadioButton(coord, size, color, text);
    //        buttons.push_back();
    //    }
    //}
    void Update() {
        int check;
        for (int i = 0; i < buttons.size(); ++i) {
            if (CheckCollisionPointRec(GetMousePosition(), {buttons[i]->coord.x, buttons[i]->coord.y, buttons[i]->size.x, buttons[i]->size.y})) {
                buttons[i]->active = true;
                int check = i;
                break;
            }
        }
        for (int i = 0; i < buttons.size(); ++i) {
            if (i!= check) {
                buttons[i]->active = false;
            }
        }
    }
};
