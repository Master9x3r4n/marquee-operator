#include <climits>
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <array>
#include <windows.h>
#define HEIGHT 7

void printMarquee(std::vector<std::array<std::string, 7>> characters, std::string text)
{
    std::string space = "      "; // contrary to the function below, this must be at start

    // Get ascii equivalents
    std::vector<int> ascii;
    for (size_t j = 0; j < text.length(); j ++)
    {   
        ascii.push_back(text[j]);
    }

    for (int j = 0; j < HEIGHT; j ++)
    {
        for (size_t k = 0; k < text.length(); k ++)
        {
            // 32 is starting off set for space char
            if (ascii[k] == 32)
                std::cout << space;
            else
                std::cout << characters[ascii[k] - 32][j]; 
        }
        std::cout << "\n";
    }
}

void clear_screen() {
    std::cout << "\033[H\033[J";
}

void clear_marquee() {
    std::cout << "\033[1;10r";
}

void displayMarquee(std::vector<std::array<std::string, 7>> characters, std::string text, int refreshSpeed, bool isMarqueeRunning) {
    std::vector<char> v(text.begin(), text.end());
    unsigned int n = text.length();
    std::string empty = "";

    if (isMarqueeRunning) {
        while (isMarqueeRunning) {
            std::string s;
            // marquee text going from right to left
            printMarquee(characters, "");
            std::cout << std::flush;
            Sleep(refreshSpeed);
            clear_marquee();
            for (unsigned int i = 0; i <= n * 2; i++) {
                // read marquee text up to the last character
                // and display it as (n - s.len) spaces + text queue
                if (i < n) {
                    s += text.substr(i, 1);
                    std::string render = empty;
                    render = render.insert(0, n - s.length() + 1, ' ') + s;
                    printMarquee(characters, render);
                }
                // after reading all the chars, each char must disappear one by one, starting from left char
                else {
                    std::string render = empty;
                    if (s.length() > 0)
                        s = s.substr(1, s.length() - 1) + render.insert(0, n - s.length() + 3, ' ');
                    printMarquee(characters, s);
                }
                std::cout << std::flush;
                Sleep(refreshSpeed);
                clear_marquee();
            }
        }
    }
    else {
        printMarquee(characters, text);
    }
}

// While I originally made this function by hand with AI assistance, I regenerated the code to accomodate for the fixed widths
std::vector<std::array<std::string, HEIGHT>> initializeFont()
{
    std::ifstream inputFile("text/ascii_font.txt");
    std::vector<std::array<std::string, HEIGHT>> characters;

    if (!inputFile.is_open()) {
        std::cerr << "Error: Could not open ascii_font.txt" << std::endl;
        return characters;
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

            characters.push_back(trimmed);
            j = 0;
        }
    }

    inputFile.close();
    return characters;
}