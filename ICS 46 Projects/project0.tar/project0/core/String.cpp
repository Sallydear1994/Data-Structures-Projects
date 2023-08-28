// String.cpp
//
// ICS 46 Spring 2021
// Project #0: Getting to Know the ICS 46 VM
//
// Implement all of your String member functions in this file.
//
// Note that the entire standard library -- both the C Standard
// Library and the C++ Standard Library -- is off-limits for this
// task, as the goal is to exercise your low-level implementation
// skills (pointers, memory management, and so on).

#include "String.hpp"
#include "OutOfBoundsException.hpp"

String::String()
{
    len = 0;
    str = nullptr;
}
String::String(const char* chars)
{
    len = 0;
    while (chars[len] != '\0')
        len++;
    str = new char[len + 1];
    for (unsigned int i = 0; i < len; i++)
        str[i] = chars[i];
    str[len] = '\0';
}
String::String(const String& s)
{
    len = 0;
    while (s.str[len] != '\0')
        len++;
    str = new char[len + 1];
    for (unsigned int i = 0; i < len; i++)
        str[i] = s.str[i];
    str[len] = '\0';
}
String::~String() noexcept
{
    delete str;
}
String& String::operator=(const String& s)
{
    len = 0;
    while (s.str[len] != '\0')
        len++;
    str = new char[len + 1];
    for (unsigned int i = 0; i < len; i++)
        str[i] = s.str[i];
    str[len] = '\0';
    return *this;
}

void String::append(const String& s)
{
    unsigned int newlen = len + s.len;
    char* tempstr = str;
    str = new char[newlen + 1];
    for (unsigned int i = 0; i < newlen; i++)
    {
        if (i < len)
            str[i] = tempstr[i];
        else
            str[i] = s.str[i - len];
    }
    len = newlen;
    str[newlen] = '\0';
    delete[] tempstr;
}
char String::at(unsigned int index) const
{
    if (index < len)
        return str[index];
    throw OutOfBoundsException();
}
char& String::at(unsigned int index)
{
    if (index < len)
        return str[index];
    throw OutOfBoundsException();
}
void String::clear()
{
    len = 0;
    str = nullptr;
}
int String::compareTo(const String& s) const noexcept
{
    for (int i = 0; i < (len < s.length() ? len : s.length()); i++)
    {
        if (str[i] != s.at(i))
            return str[i] - s.at(i);
    }
    return len - s.length();
    /*
    if (len == s.len)
    {
        for (int i = 0; i < len; i++)
        {
            if (str[i] < s.str[i])
                return -1;
            if (str[i] > s.str[i])
                return 1;
        }
        return 0;
    }
    if (len < s.len)
    {
        for (int i = 0; i < len; i++)
        {
            if (str[i] < s.str[i])
                return -1;
            if (str[i] > s.str[i])
                return 1;
        }
    }
    if (len > s.len)
    {
        for (int i = 0; i < s.len; i++)
        {
            if (str[i] < s.str[i])
                return -1;
            if (str[i] > s.str[i])
                return 1;
        }
    }
    return 0;*/
}
String String::concatenate(const String& s) const
{
    String newstr;
    newstr.append(*this);
    newstr.append(s);
    return newstr;
}
bool String::contains(const String& substring) const noexcept
{
    for (unsigned int i = 0; i < len; i++)
    {
        if (this->str[i] == substring.str[0])
        {
            if (this->len - i >= substring.len)
            {
                unsigned int checkindex = 0;
                unsigned int matchingchars = 0;
                while (substring.str[checkindex] != '\0')
                {
                    if (this->str[i + checkindex] == substring.str[checkindex])
                        matchingchars++;
                    else
                        break;
                    checkindex++;
                }
                if (matchingchars == substring.len)
                    return true;
            }
            else
                return false;
        }
    }
    return false;
}
bool String::equals(const String& s) const noexcept
{
    if (len == s.len)
    {
        for (int i = 0; i < len; i++)
        {
            if (str[i] != s.str[i])
                return false;
        }
        return true;
    }
    return false;
}
int String::find(const String& substring) const noexcept
{
    for (unsigned int i = 0; i < len; i++)
    {
        if (this->str[i] == substring.str[0])
        {
            if (this->len - i >= substring.len) // No reason to check rest of string if substring is bigger than remaining string
            {
                unsigned int checkindex = 0;
                unsigned int matchingchars = 0;
                while (substring.str[checkindex] != '\0')
                {
                    if (this->str[i + checkindex] == substring.str[checkindex])
                        matchingchars++;
                    else
                        break;
                    checkindex++;
                }
                if (matchingchars == substring.len)
                    return i;
            }
            else
                return -1;
        }
    }
    return -1;
}
bool String::isEmpty() const noexcept
{
    return len == 0;
}
unsigned int String::length() const noexcept
{
    return len;
}
String String::substring(unsigned int startIndex, unsigned int endIndex) const
{
    if ((endIndex > this->len) || (startIndex > endIndex))
        throw OutOfBoundsException();
    if (startIndex == endIndex)
        return "";
    int substrlen = endIndex - startIndex;
    char* substr = new char[substrlen + 1];
    for (unsigned int i = 0; i < substrlen; i++)
        substr[i] = str[startIndex + i];
    substr[substrlen] = '\0';
    String newstr(substr);
    delete[] substr;
    return newstr;

}
const char* String::toChars() const noexcept
{
    if (len == 0)
        return "";
    return str;
}
