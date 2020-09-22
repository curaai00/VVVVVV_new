#include "Stat.h"

Stat::Stat() {}

void Stat::save(const std::string& savearea)
{
    _isSaved = true;
    _savetime = getTimeStr();
    _savearea = savearea;
}

void Stat::reset(void)
{
    _savetime = "00:00";
    _savearea = "nowhere";
    setSaved(false);

    resetClock();
}
void Stat::resetClock(void)
{
    seconds = 0;
    minutes = 0;
    hours = 0;
}

int Stat::totalSeconds(void) const
{
    return seconds + (minutes * 60) + (hours * 60 * 60);
}

void Stat::increaseSecond(void)
{
    if (++seconds >= 60) {
        seconds -= 60;
        if (++minutes >= 60) {
            minutes -= 60;
            hours++;
        }
    }
}

std::string Stat::getTimeStr(void) const
{
    std::string res = "";
    if (hours > 0) {
        res += help.String(hours) + ":";
    }
    res += help.twodigits(minutes) + ":" + help.twodigits(seconds);
    return res;
}

bool Stat::loadFromXml(std::string pKey, const char* pText)
{
    if (pKey == "hours")
        hours = help.Int(pText);
    else if (pKey == "minutes")
        minutes = help.Int(pText);
    else if (pKey == "seconds")
        seconds = help.Int(pText);
    else
        return false;
    return true;
}
void Stat::saveToXml(tinyxml2::XMLDocument& doc, tinyxml2::XMLElement* msgs)
{
    linkXmlMsg(doc, msgs, "hours", hours);
    linkXmlMsg(doc, msgs, "minute", minutes);
    linkXmlMsg(doc, msgs, "seconds", seconds);
}