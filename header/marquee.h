#include <climits>
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <array>
constexpr int HEIGHT = 7;

class Marquee
{
private:
    std::vector<std::array<std::string, HEIGHT>> marqueeChars;
    std::vector<std::array<std::string, HEIGHT>> marqueeText;
    std::string inputText;
    int refreshSpeed;

public:
    Marquee(std::string txt = "csopesy", int rspd = 1000)
    {
        inputText = txt;
        refreshSpeed = rspd;
    }

    void setText(std::string txt)
    {
        inputText = txt;
    }

    std::string getText()
    {
        return inputText;
    }

    void setSpeed(int spd)
    {
        refreshSpeed = spd;
    }

    int getSpeed(int spd)
    {
        return refreshSpeed;
    }

    void printMarquee()
    {
        generateMarqueeText();
        for (int j = 0; j < HEIGHT; j ++)
        {
            for (size_t k = 0; k < inputText.length(); k ++)
            {
                // 32 is starting off set for space char
                std::cout << marqueeText[k][j]; 
            }
            std::cout << "\n";
        }
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
        return true;
    }

private:
    void generateMarqueeText() 
    {
        marqueeText.clear();
        for (size_t j = 0; j < inputText.length(); j++)
        {
            // 32 is starting off set for space char
            int ascii = static_cast<int>(inputText[j]) - 32; 
            if (ascii < 0 || ascii >= (int)marqueeChars.size()) continue; 
            marqueeText.push_back(marqueeChars[ascii]);
        }
    }

};