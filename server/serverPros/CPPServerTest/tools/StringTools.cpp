#include "StringTools.h"
static char minibuffs[80] = "";
std::string StringTools::number2Str(unsigned int num)
{
    if (num == 0)
        return "0";
    sprintf(minibuffs, "%lu", num);
    return std::string(minibuffs,strlen(minibuffs));
}

std::string StringTools::number2Str(int num)
{
    if (num == 0)
        return "0";
    sprintf(minibuffs, "%d", num);
    return std::string(minibuffs, strlen(minibuffs));
}

std::string StringTools::number2Str(double num)
{
    if (num == 0)
        return "0";
    sprintf(minibuffs, "%g", num);
    return std::string(minibuffs, strlen(minibuffs));
}
