#ifndef COMMANDS_H
#define COMMANDS_H

#include <string>
#include <vector>

#include "marquee.h"

void viewHelp();
void setText(Marquee& marquee, std::vector<std::string> args);
void setSpeed(Marquee& marquee, std::vector<std::string> args);
void displayDefault(bool show = true);
void clearCommandArea();
void commandInterface(bool& isProgramRunning, Marquee& marquee);

#endif