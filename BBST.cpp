#include <iostream>
#include <set>
#include <string>
#include <fstream>
#include <chrono>
#include <iomanip>

using BBST = std::set<std::string>;

bool isMisspelled(const std::string &word, const BBST &dictionary)
{
    return dictionary.find(word) == dictionary.end();
}

int main()
{
    BBST dictionary;

    // Read words from a file and add them to the dictionary
    std::ifstream dictionaryFile("dictionary.txt");
    std::string word;

    while (dictionaryFile >> word)
    {
        dictionary.insert(word);
    }

    dictionaryFile.close();

    std::ifstream inputFile("english.txt");
    std::string inputText;

    if (inputFile)
    {
        std::string line;
        while (std::getline(inputFile, line))
        {
            inputText += line + " ";
        }

        inputFile.close();

        std::string currentWord;

        auto start = std::chrono::high_resolution_clock::now(); // Start the timer

        // Iterate over each character in the input text
        for (const char &c : inputText)
        {
            if (std::isalpha(c))
            {
                // Append alphabetic characters to the currentWord
                currentWord += std::tolower(c);
            }
            else if (!currentWord.empty())
            {
                // Check if the currentWord is misspelled
                if (isMisspelled(currentWord, dictionary))
                {
                    std::cout << "Misspelled word: " << currentWord << std::endl;
                }

                // Reset the currentWord for the next iteration
                currentWord.clear();
            }
        }

        // Check if there is a word at the end of the input text
        if (!currentWord.empty())
        {
            if (isMisspelled(currentWord, dictionary))
            {
                std::cout << "Misspelled word: " << currentWord << std::endl;
            }
        }

        auto end = std::chrono::high_resolution_clock::now(); // Stop the timer
        auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(end - start);
        double durationInSeconds = duration.count() / 1000.0;
        std::cout << "Time taken: " << std::fixed << std::setprecision(4) << durationInSeconds << " seconds" << std::endl;
    }
    else
    {
        std::cerr << "Failed to open the input file." << std::endl;
        return 1;
    }

    return 0;
}
