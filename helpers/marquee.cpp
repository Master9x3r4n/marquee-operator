#include "headers/marquee.h"

#include <algorithm>
#include <chrono>
#include <climits>
#include <fstream>
#include <iostream>
#include <utility>

Marquee::Marquee(std::string txt, int rspd)
    : inputText(std::move(txt)), refreshSpeed(rspd), running(false), quit(false) {}

Marquee::~Marquee()
{
    shutdown();
}

void Marquee::setText(std::string txt)
{
    // only unlock inputText when `set_text` command is recognized
    std::lock_guard<std::mutex> lock(textMutex);
    inputText = txt;
    generateMarqueeText();
}

std::string Marquee::getText()
{
    std::lock_guard<std::mutex> lock(textMutex);
    return inputText;
}

void Marquee::setSpeed(int spd)
{
    refreshSpeed = std::max(1, spd);
}

int Marquee::getSpeed()
{
    return refreshSpeed;
}

bool Marquee::isRunning()
{
    return running;
}

void Marquee::setRunning(bool run)
{
    running = run;
}

void Marquee::startAnimation(int screenW)
{
    if (worker.joinable())
        return;

    quit = false;
    worker = std::thread(&Marquee::animationLoop, this, screenW);
}

void Marquee::shutdown()
{
    quit = true;
    if (worker.joinable())
        worker.join();
}

bool Marquee::initializeFont()
{
    std::ifstream inputFile("helpers/text/ascii_font.txt");
    marqueeChars.clear();

    if (!inputFile.is_open()) {
        std::cerr << "Error: Could not open ascii_font.txt" << std::endl;
        return false;
    }

    int j = 0;
    std::array<std::string, HEIGHT> character;
    std::string currLine;

    while (std::getline(inputFile, currLine))
    {
        character[j] = currLine;
        j++;

        if (j == HEIGHT)
        {
            int left  = INT_MAX;
            int right = -1;
            for (const std::string& row : character)
            {
                for (int c = 0; c < (int)row.size(); ++c)
                {
                    if (row[c] != ' ')
                    {
                        left  = std::min(left, c);
                        right = std::max(right, c);
                    }
                }
            }

            std::array<std::string, HEIGHT> trimmed;

            if (right < left)
            {
                for (int r = 0; r < HEIGHT; ++r)
                    trimmed[r] = "      ";
            }
            else
            {
                int width = right - left + 1;
                for (int r = 0; r < HEIGHT; ++r)
                    trimmed[r] = character[r].substr(left, width);
            }

            marqueeChars.push_back(trimmed);
            j = 0;
        }
    }

    inputFile.close();
    {
        std::lock_guard<std::mutex> lock(textMutex);
        generateMarqueeText();
    }
    return true;
}

void Marquee::animationLoop(int screenW)
{
    int pos = 0;
    while (!quit)
    {
        // save cursor position
        std::string frame = "\x1b" "7";

        {
            // locks marqueeText first from other threads other than this
            std::lock_guard<std::mutex> lock(textMutex);

            // find the max width of the ascii art for the marquee text
            std::size_t artWidth = 0;
            for (const auto& line : marqueeText)
                artWidth = std::max(artWidth, line.size());

            // for each row of the ascii art, print the necessary chars such that it aligns with the column pos
            for (int j = 0; j < HEIGHT; ++j)
            {
                std::string row(screenW, ' ');
                const std::string& line = marqueeText[j];

                for (std::size_t i = 0; i < line.size(); ++i)
                {
                    int x = pos + static_cast<int>(i);
                    if (x >= 0 && x < screenW) row[x] = line[i];
                }

                // move to next row
                frame += "\x1b[" + std::to_string(j + 1) + ";1H" + row;
            }

            if (running)
            {
                // move the column pos back to the very right
                if (--pos + static_cast<int>(artWidth) < 0)
                    pos = screenW;
            }
            else
            {
                // stay in left if the animation is not running
                pos = 0;
            }
        }

        // restore cursor position
        frame += "\x1b" "8";

        std::cout << frame << std::flush;

        int delay = running ? refreshSpeed.load() : 50;
        std::this_thread::sleep_for(std::chrono::milliseconds(delay));
    }
}

void Marquee::generateMarqueeText()
{
    int spaceOffset = 32;
    marqueeText.fill("");
    for (int k = 0; k < HEIGHT; k++)
    {
        for (size_t j = 0; j < inputText.length(); j++)
        {
            int ascii = static_cast<int>(inputText[j]) - spaceOffset;
            if (ascii < 0 || ascii >= (int)marqueeChars.size()) ascii = 0;

            marqueeText[k] += marqueeChars[ascii][k];
        }
    }
}