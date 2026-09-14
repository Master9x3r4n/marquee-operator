#include <climits>
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <array>
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