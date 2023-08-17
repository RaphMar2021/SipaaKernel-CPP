#include "lib.h"

namespace Sk {

uint32_t Lib::RNGSeed = 0;

void Lib::InitRNG(uint32_t seed)
{
    RNGSeed = seed;
}

uint32_t Lib::Random()
{
    RNGSeed = (214013 * RNGSeed + 2531011);
    return (RNGSeed >> 16) & 0x7FFF;
}

int Lib::StringCompare(const char *str1, const char *str2)
{
    while (*str1 && (*str1 == *str2))
    {
        str1++;
        str2++;
    }

    return *(unsigned char *)str1 - *(unsigned char *)str2;
}

int Lib::ToUpper(int c)
{
    if (c >= 'a' && c <= 'z')
    {
        return c - ('a' - 'A');
    }
    else
    {
        return c;
    }
}

int Lib::ToLower(int c)
{
    if (c >= 'A' && c <= 'Z')
    {
        return c + ('a' - 'A');
    }
    else
    {
        return c;
    }
}

void Lib::IToString(int value, char *str, int base)
{
    static char num[] = "0123456789abcdefghijklmnopqrstuvwxyz";
    char *wstr = str;
    int sign;

    if (base < 2 || base > 35)
    {
        *wstr = '\0';
        return;
    }

    if ((sign = value) < 0)
        value = -value;

    do
        *wstr++ = num[value % base];
    while (value /= base);
    if (sign < 0)
        *wstr++ = '-';
    *wstr = '\0';

    ReverseString(str, wstr - 1);
}

void Lib::UToString(unsigned int value, char *str, int base)
{
    static char num[] = "0123456789abcdefghijklmnopqrstuvwxyz";
    char *wstr = str;

    if (base < 2 || base > 35)
    {
        *wstr = '\0';
        return;
    }

    do
        *wstr++ = num[value % base];
    while (value /= base);
    *wstr = '\0';

    ReverseString(str, wstr - 1);
}

void Lib::UlliToString(unsigned long long int value, char *str, int base)
{
    static char num[] = "0123456789abcdefghijklmnopqrstuvwxyz";
    char *wstr = str;

    if (base < 2 || base > 35)
    {
        *wstr = '\0';
        return;
    }

    do
        *wstr++ = num[value % base];
    while (value /= base);
    *wstr = '\0';

    ReverseString(str, wstr - 1);
}

void Lib::ReverseString(char *begin, char *end)
{
    char aux;
    while (end > begin)
        aux = *end, *end-- = *begin, *begin++ = aux;
}

char *Lib::CopyString(char *dest, const char *src)
{
    char *originalDest = dest;

    while (*src != '\0')
    {
        *dest = *src;
        dest++;
        src++;
    }

    *dest = '\0';
    return originalDest;
}

}