// StringTests.cpp
//
// ICS 46 Spring 2021
// Project #0: Getting to Know the ICS 46 VM
//
// This is a set of unit tests, implementing using a library called
// Google Test, which demonstrate various aspects of the functionality
// of your String class.  When you're finished, all of these tests
// should pass.  (Note, too, that these tests are not exhaustive; we'll
// be testing your implementation more thoroughly, so you might want to
// write your own tests, as well.)

#include <gtest/gtest.h>
#include "OutOfBoundsException.hpp"
#include "String.hpp"


TEST(StringTests, emptyWhenDefaultConstructed)
{
    String s;
    EXPECT_TRUE(s.isEmpty());
}


TEST(StringTests, lengthIsZeroWhenDefaultConstructed)
{
    String s;
    EXPECT_EQ(0, s.length());
}


TEST(StringTests, toCharsIsEmptyCStringWhenDefaultConstructed)
{
    String s;
    EXPECT_STREQ("", s.toChars());
}


TEST(StringTests, canConstructFromCString)
{
    const char* chars = "Boo is snoring";

    String s{chars};

    EXPECT_EQ(14, s.length());
    EXPECT_STREQ(chars, s.toChars());
}


TEST(StringTests, canCopyConstructFromAnotherString)
{
    const char* chars = "Boo wants to know what's over there";

    String s{chars};
    String t{s};

    EXPECT_EQ(35, t.length());
    EXPECT_STREQ(chars, t.toChars());
}


TEST(StringTests, canCopyAssignFromAnotherString)
{
    const char* chars = "Boo is perfect";

    String s{chars};
    String t{"Hello"};

    t = s;

    EXPECT_EQ(14, t.length());
    EXPECT_STREQ(chars, t.toChars());
}


TEST(StringTests, canAppendChars)
{
    const char* chars = "Boo is";
    const char* moreChars = " the very best";

    String s{chars};
    String more{moreChars};
    s.append(more);

    EXPECT_EQ(20, s.length());
    EXPECT_STREQ("Boo is the very best", s.toChars());
}


TEST(StringTests, canObtainIndividualCharactersFromConstString)
{
    const char* chars = "Boo!";

    const String s{chars};

    EXPECT_EQ('B', s.at(0));
    EXPECT_EQ('o', s.at(1));
    EXPECT_EQ('o', s.at(2));
    EXPECT_EQ('!', s.at(3));
}


TEST(StringTests, canAssignIndividualCharactersInNonConstString)
{
    const char* chars = "Boo is happy";

    String s{chars};

    s.at(7) = 'g';
    s.at(8) = 'r';
    s.at(9) = 'e';
    s.at(10) = 'a';
    s.at(11) = 't';

    EXPECT_STREQ("Boo is great", s.toChars());
}


TEST(StringTests, obtainingCharactersFromConstStringOutOfBoundsFails)
{
    const char* chars = "Boo!";

    const String s{chars};

    EXPECT_THROW({ s.at(4); }, OutOfBoundsException);
}


TEST(StringTests, obtainingCharactersFromNonConstStringOutOfBoundsFails)
{
    const char* chars = "Boo!";

    String s{chars};

    EXPECT_THROW({ s.at(4); }, OutOfBoundsException);
}


TEST(StringTests, clearRemovesAllCharacters)
{
    String s{"Boo is asleep"};
    s.clear();

    EXPECT_EQ(0, s.length());
    EXPECT_STREQ("", s.toChars());
}


TEST(StringTests, compareToReturnsZeroWhenEquivalent)
{
    String s{"Where is Boo?"};
    String t{"Where is Boo?"};

    EXPECT_EQ(0, s.compareTo(t));
}


TEST(StringTests, compareToReturnsNegativeWhenLeftIsLessThanRight)
{
    String s{"earlier"};
    String t{"later"};

    EXPECT_LT(s.compareTo(t), 0);
}


TEST(StringTests, compareToReturnsPositiveWhenLeftIsGreaterThanRight)
{
    String s{"later"};
    String t{"earlier"};

    EXPECT_GT(s.compareTo(t), 0);
}


TEST(StringTests, concatenateBuildsNewStringContainingAllCharacters)
{
    String s{"It is"};
    String t{" great to see Boo"};
    String c = s.concatenate(t);

    EXPECT_EQ(22, c.length());
    EXPECT_STREQ("It is great to see Boo", c.toChars());
}


TEST(StringTests, containsCanFindSubstringsWhenPresent)
{
    String s{"Is Boo great today?"};
    String t{"Boo"};

    EXPECT_TRUE(s.contains(t));
}


TEST(StringTests, containsCanFailToFindSubstringsWhenNotPresent)
{
    String s{"Boo is definitely great today"};
    String t{"absolutely"};

    EXPECT_FALSE(s.contains(t));
}


TEST(StringTests, stringsAreEqualWhenContainingTheSameCharacterSequences)
{
    const char* chars = "Boo looks hungry";

    String s{chars};
    String t{chars};

    EXPECT_TRUE(s.equals(t));
}


TEST(StringTests, stringsAreNotEqualWhenCharactersAreDifferent)
{
    String s{"Hello"};
    String t{"Boo"};

    EXPECT_FALSE(s.equals(t));
}


TEST(StringTests, canFindSubstringsWhenPresent)
{
    String s{"Is Boo great today?"};
    String t{"Boo"};

    EXPECT_EQ(3, s.find(t));
}


TEST(StringTests, canFailToFindSubstringsWhenNotPresent)
{
    String s{"Boo is definitely great today"};
    String t{"absolutely"};

    EXPECT_EQ(-1, s.find(t));
}


TEST(StringTests, emptyWhenContainingNoCharacters)
{
    String s{""};

    EXPECT_TRUE(s.isEmpty());
}


TEST(StringTests, notEmptyWhenContainingCharacters)
{
    String s{"Boo"};

    EXPECT_FALSE(s.isEmpty());
}


TEST(StringTests, lengthIsNumberOfCharacters)
{
    String s{"This is Boo's day"};

    EXPECT_EQ(17, s.length());
}


TEST(StringTests, canObtainSubstring)
{
    String s{"Every day is Boo's day"};
    String t = s.substring(13, 16);

    EXPECT_EQ(3, t.length());
    EXPECT_STREQ("Boo", t.toChars());
}


TEST(StringTests, obtainingSubstringOutOfBoundsFails)
{
    String s{"Boo's eyes are closed"};
    
    EXPECT_THROW({ s.substring(15, 100); }, OutOfBoundsException);
}


TEST(StringTests, toCharsReturnsNullTerminatedCStyleString)
{
    const char* chars = "Boo is sleeping";

    String s{chars};

    EXPECT_STREQ(chars, s.toChars());
}

