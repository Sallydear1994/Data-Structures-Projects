// WordChecker_SanityCheckTests.cpp
//
// ICS 46 Spring 2021
// Project #4: Set the Controls for the Heart of the Sun
// 
// This is a set of "sanity checking" unit tests for your WordChecker
// implementation, provided primarily as a mechanism for ensuring that
// your implementation is compatible with the unit tests we'll be using
// to test it, and to give you a quick example of how each of the member
// functions works.  These tests don't verify all of the functionality
// you're implementing.
//
// As with the sanity-checking unit tests you saw in other projects, you
// should not modify these in any way -- don't add #include directives,
// and don't change the code within the tests.  These should all compile
// and pass before you submit your WordChecker implementation.

#include <string>
#include <vector>
#include <gtest/gtest.h>
#include "ListSet.hpp"
#include "WordChecker.hpp"

/*
TEST(WordChecker_SanityCheckTests, canCreateWithSetOfStrings)
{
    WordChecker w{ListSet<std::string>{}};
}


TEST(WordChecker_SanityCheckTests, wordsExistWhenInSet)
{
    ListSet<std::string> set;
    set.add("HELLO");
    set.add("THERE");
    set.add("BOO");

    WordChecker checker{set};

    EXPECT_TRUE(checker.wordExists("HELLO"));
    EXPECT_TRUE(checker.wordExists("THERE"));
    EXPECT_TRUE(checker.wordExists("BOO"));
}


TEST(WordChecker_SanityCheckTests, wordsDoNotExistWhenNotInSet)
{
    ListSet<std::string> set;
    set.add("HELLO");
    set.add("THERE");
    set.add("BOO");

    WordChecker checker{set};

    EXPECT_FALSE(checker.wordExists("NOTBOO"));
    EXPECT_FALSE(checker.wordExists("HELLOTHERE"));
}


TEST(WordChecker_SanityCheckTests, canGenerateSuggestions)
{
    ListSet<std::string> set;
    set.add("ABDC");
    set.add("ZZZZZ");

    WordChecker checker{set};

    std::vector<std::string> suggestions = checker.findSuggestions("ABCD");

    ASSERT_EQ(1, suggestions.size());
    ASSERT_EQ("ABDC", suggestions[0]);
}


// User Test Cases
TEST(WordChecker_SanityCheckTests, swapAdjacentCharacters)
{
    ListSet<std::string> set;
    set.add("BATMAN");

    WordChecker checker{set};

    std::vector<std::string> suggestions = checker.findSuggestions("BAMTAN");

    ASSERT_EQ(1, suggestions.size());
    ASSERT_EQ("BATMAN", suggestions[0]);
}


TEST(WordChecker_SanityCheckTests, checkDuplicatesSwapAdjacentCharacters)
{
    ListSet<std::string> set;
    set.add("BATMAN");
    set.add("BATMAN");

    WordChecker checker{set};

    std::vector<std::string> suggestions = checker.findSuggestions("BAMTAN");

    ASSERT_EQ(1, suggestions.size());
    ASSERT_EQ("BATMAN", suggestions[0]);
}


TEST(WordChecker_SanityCheckTests, UsercheckInsertedCharacters)
{
    ListSet<std::string> set;
    set.add("BATMAN");
    //set.add("BATMANS");

    WordChecker checker{set};
    //std::vector<std::string> suggestions = checker.findSuggestions("ATMAN");
    //std::vector<std::string> suggestions = checker.findSuggestions("BATAN");
    //std::vector<std::string> suggestions = checker.findSuggestions("BATMN");
    std::vector<std::string> suggestions = checker.findSuggestions("BATMA");
    ASSERT_EQ(1, suggestions.size());
    ASSERT_EQ("BATMAN", suggestions[0]);
}


TEST(WordChecker_SanityCheckTests, UsercheckDeletedCharacters)
{
    ListSet<std::string> set;
    set.add("BATMAN");
    WordChecker checker{set};
    //std::vector<std::string> suggestions = checker.findSuggestions("ZBATMAN");
    //std::vector<std::string> suggestions = checker.findSuggestions("BAYTMAN");
    std::vector<std::string> suggestions = checker.findSuggestions("BATMANP");
    ASSERT_EQ(1, suggestions.size());
    ASSERT_EQ("BATMAN", suggestions[0]);
}


TEST(WordChecker_SanityCheckTests, UsercheckReplacedCharacters)
{
    ListSet<std::string> set;
    set.add("BATMAN");
    WordChecker checker{set}; 
    std::vector<std::string> suggestions = checker.findSuggestions("AATMAN");
    //std::vector<std::string> suggestions = checker.findSuggestions("BAAMAN");
    //std::vector<std::string> suggestions = checker.findSuggestions("BATMAA");
    ASSERT_EQ(1, suggestions.size());
    ASSERT_EQ("BATMAN", suggestions[0]);
}


TEST(WordChecker_SanityCheckTests, UserCheckSpacedStrings)
{
    ListSet<std::string> set;
    set.add("MISS");
    set.add("SPELLING");
    set.add("MISSPELLING");
    WordChecker checker{set}; 
    std::vector<std::string> suggestions = checker.findSuggestions("MISSSPELLING");
    ASSERT_EQ(2, suggestions.size());
    ASSERT_EQ("MISSPELLING", suggestions[0]);
    ASSERT_EQ("MISS SPELLING", suggestions[1]);

}


TEST(WordChecker_SanityCheckTests, UserCheckDuplicate)
{
    ListSet<std::string> set;
    set.add("MISS");
    set.add("MISS");
    WordChecker checker{set}; 
    std::vector<std::string> suggestions = checker.findSuggestions("MISSP");
    ASSERT_EQ(1, suggestions.size());
    ASSERT_EQ("MISS", suggestions[0]);
}
*/