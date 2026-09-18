#include <climits>
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <array>
#include <thread>
#include <chrono>
constexpr int HEIGHT = 7;

class Marquee
{
private:
    std::vector<std::array<std::string, HEIGHT>> marqueeChars;
    std::array<std::string, HEIGHT> marqueeText;
    std::string inputText;
    int refreshSpeed;
    bool running;

public:
    // Constructor
    Marquee(std::string txt = "csopesy", int rspd = 1000)
    {
        inputText = txt;
        refreshSpeed = rspd;
        running = true;
    }

    void setText(std::string txt)
    {
        inputText = txt;
        generateMarqueeText();
    }

    std::string getText()
    {
        return inputText;
    }

    void setSpeed(int spd)
    {
        refreshSpeed = spd;
    }

    int getSpeed()
    {
        return refreshSpeed;
    }

    bool isRunning()
    {
        return running;
    }

    void setRunning(bool run)
    {
        running = run;
    }

    void printMarquee()
    {
        for (int j = 0; j < HEIGHT; j ++)
        {
            std::cout << marqueeText[j]; 
            std::cout << "\n";
        }
    }

    // Scroll ASCII art horizontally across `width` columns.
    void scrollMarquee(
             int width = 120,
             int delay_ms = 80)
    {
        if (width <= 0) return;

        // Longest line determines scroll distance
        std::size_t art_width = 0;
        for (const auto& line : marqueeText)
            art_width = std::max(art_width, line.size());

        if (art_width == 0) return;

        int pos = width;              // start just off the right edge
        int pass = 0;

        std::cout << "\x1b[?25l";     // hide cursor

        while (running) {
            std::cout << "\x1b[H";    // home cursor

            for (const auto& line : marqueeText) {
                std::string frame(width, ' ');
                for (std::size_t i = 0; i < line.size(); ++i) {
                    int x = pos + static_cast<int>(i);
                    if (x >= 0 && x < width) frame[x] = line[i];
                }
                std::cout << frame << "\n";
            }
            std::cout << std::flush;

            if (--pos + static_cast<int>(art_width) < 0) {
                pos = width;
                ++pass;
            }

            std::this_thread::sleep_for(std::chrono::milliseconds(delay_ms));
        }

        std::cout << "\x1b[?25h";     // restore cursor
    }
    
    // While I originally made this function by hand with AI assistance, I regenerated the code to accomodate for the fixed widths
    bool initializeFont()
    {
        std::ifstream inputFile("text/ascii_font.txt");
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
            // Guard against short/long lines: pad or truncate so all rows match
            // (optional but safer — remove if your file is guaranteed uniform)
            character[j] = currLine;
            j++;
    
            if (j == HEIGHT)
            {
                // Find bounding box of non-space columns across all rows
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
                    // All-space glyph (the space character). Give it a fixed width.
                    for (int r = 0; r < HEIGHT; ++r)
                        trimmed[r] = "      ";   // 5 cols wide, adjust to taste
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
        generateMarqueeText();
        return true;
    }

private:
    void generateMarqueeText() 
    {
        int spaceOffset = 32; // 32 is starting off set for space char
        marqueeText.fill("");
        for (int k = 0; k < HEIGHT; k ++)
        {
            for (size_t j = 0; j < inputText.length(); j++)
            {
                //Get current character
                int ascii = static_cast<int>(inputText[j]) - spaceOffset; 
                if (ascii < 0 || ascii >= (int)marqueeChars.size()) ascii = 0; 

                marqueeText[k] += marqueeChars[ascii][k];
            }
        }
    }
    
};