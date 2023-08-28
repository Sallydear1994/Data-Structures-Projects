// WordChecker.cpp
//
// ICS 46 Spring 2021
// Project #4: Set the Controls for the Heart of the Sun
//
// Replace and/or augment the implementations below as needed to meet
// the requirements.

#include "WordChecker.hpp"



WordChecker::WordChecker(const Set<std::string>& words)
    : words{words}
{
}


bool WordChecker::wordExists(const std::string& word) const
{
    return words.contains(word);
}

// Todo
std::vector<std::string> WordChecker::findSuggestions(const std::string& word) const
{
    // Nonsensical code because the compiler requires the member variables
    // 'words' to be used somewhere, or else it becomes a warning (which
    // turns into an error).
    words.isImplemented();
    std::vector<std::string> suggestedWords;
    std::string wordCopy = word;
    const std::string alphabet = "ABCDEFGHIJKLMNOPQRSTUVWXYZ ";

    // Swap adjacent characters algorithm
    for (int i = 0; i < word.length() - 1; i++)
    {
        std::swap(wordCopy[i], wordCopy[i + 1]);
        if (wordExists(wordCopy))
        {
            if (!duplicate(suggestedWords, wordCopy))
            {
                suggestedWords.push_back(wordCopy);
            }
        }
        std::swap(wordCopy[i], wordCopy[i + 1]);
    }

    // Insert characters into string algorithm
    for (int i = 0; i < word.length() + 1; i++)
    {
        for (int j = 0; j < alphabet.length(); j++)
        {
            std::string insertString = wordCopy;
            insertString.insert(i, alphabet.substr(j, 1));
            if (wordExists(insertString))
            {
                if (!duplicate(suggestedWords, insertString))
                {
                    suggestedWords.push_back(insertString);
                }
            }
        }
    }
    
    // Delete each char from string algorithm
    for (int i = 0; i < word.length(); i++)
    {
        std::string deletedCharString = wordCopy;
        deletedCharString.replace(i, 1, "");
        if (wordExists(deletedCharString))
        {
            if (!duplicate(suggestedWords, deletedCharString))
            {
                suggestedWords.push_back(deletedCharString);
            }
        }
    }

    // Replace each char in string algorithm
    for (int i = 0; i < word.length(); i++)
    {
        for (int j = 0; j < alphabet.length(); j++)
        {
            std::string replacedCharString = wordCopy;
            replacedCharString.replace(i, 1, alphabet.substr(j, 1));
            if (wordExists(replacedCharString))
            {
                if (!duplicate(suggestedWords, replacedCharString))
                {
                    suggestedWords.push_back(replacedCharString);
                }
            }
        }
    }

    // Insert whitespace in string algorithm
    for (int i = 0; i < word.length(); i++)
    {
        std::string words = wordCopy;
        words.insert(i, " ");
        std::stringstream wordPair(words);
        std::string test;
        int matchingPair = 0;
        for (int i = 0; i < 2; i++)
        {
            std::getline(wordPair, test, ' ');
            if (wordExists(test))
            {
                matchingPair += 1;
            }
            if (matchingPair == 2 && !duplicate(suggestedWords, test))
            {
                suggestedWords.push_back(words);
            }
        }
    }
    return suggestedWords;
    //return std::vector<std::string>{};
}


bool WordChecker::duplicate(std::vector<std::string> suggestedWords, const std::string& word) const
{
    for (int i = 0; i < suggestedWords.size(); i++)
    {
        if (suggestedWords[i] == word)
        {
            return true;
        }
    }
    return false;
}
