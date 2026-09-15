#include <iostream>
#include <string>
#include <vector>
#include <sstream>
#include <array>
#include <thread>

#include "header/marquee.h"
#include "header/text.h"
#include "header/commands.h"

#define HEIGHT 7

int main() 
{
    std::vector<std::array<std::string, 7>> characters = initializeFont();

    bool isProgramRunning = true;
    std::string marqueeText = "CSOPESY";
    bool isMarqueeRunning = false;
    int refreshSpeed = 1000;

    clear_screen();
    displayMarquee(characters, marqueeText, refreshSpeed, isMarqueeRunning);
    while (isProgramRunning)
    {
        command_interface(isMarqueeRunning, marqueeText, refreshSpeed, isProgramRunning);
        clear_screen();
    }
}