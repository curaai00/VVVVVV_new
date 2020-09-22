#pragma once

#include "XmlParsable.h"

class Stat : public XmlParsable
{
public:
    Stat();

    void reset(void);

    void save(const std::string& savearea);

    bool isSaved(void) const { return _isSaved; }
    void setSaved(bool isSaved) { _isSaved = isSaved; }

    void resetClock(void);
    int totalSeconds(void) const;
    void increaseSecond(void);
    std::string getTimeStr(void) const;

    inline std::string getSavetime(void) const { return _savetime; }
    inline void setSavetime(void) { _savetime = getTimeStr(); };
    inline void setSavetime(const std::string& s) { _savetime = s; };

    bool loadFromXml(std::string pKey, const char* pText) override;
    void saveToXml(tinyxml2::XMLDocument& doc,
                   tinyxml2::XMLElement* msgs) override;

    int seconds, minutes, hours;

private:
    std::string _savetime = "00:00";
    std::string _savearea = "nowhere";
    bool _isSaved = false;
};