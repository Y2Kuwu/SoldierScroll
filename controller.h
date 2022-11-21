#ifndef CONTROLLER_H
#define CONTROLLER_H
#include <SFML/Window.hpp>
class Controller
{
public:
Controller();

void init();
void capControls();

private:
bool gameIsStarted;

};

#endif