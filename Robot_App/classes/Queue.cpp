#include "Queue.h"
#include <string>

Request* Queue::getNext() //Создание HTTP-запроса
{
    return priority[1];
}

void Queue::addRequest(Request request) //Функция создания очереди по HTTP-запросу
{
    requests.push_back(request);
}

Queue::Queue(std::vector<Request> requests) 
{
    for (short i = 0; i < requests.size(); i++)
    {
        addRequest(requests[i]); //Создать HTTP-запрос
    }
}

void Queue::draw(Vector2 coord, Color color)
{
    for(short i = 0; i < requests.size(); i++)
    {
        double drawPosition = i + drawDelta; //Создание переменной drawPosition для определения координат написания инфо о заказе в очереди
        DrawRectangleV({coord.x, coord.y + 75 * drawPosition}, {200, 50}, color); //Прямоугольничик
        const char text[5] = {char(requests[i].from + 65), '-', '>', char(requests[i].to + 65), 0}; //Задаем формулу написания текстика инфо о заказе в очереди
        rl_DrawText(&text[0], coord.x + 65, 10 + coord.y + 75 * drawPosition, 30, WHITE); //Текстик инфо о заказе в очереди
    }

    if (drawDelta >= 0) {
        drawDelta -= 0.1; //"Переносим строку"
    }
}

void Queue::sendRequest(Robot* robot, ceSerial* com)
{
    drawDelta++;
    robot->send(requests[0].getPath(), com);
    requests.erase(requests.begin());
}