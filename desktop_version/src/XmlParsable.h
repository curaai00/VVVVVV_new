#pragma once

#include "UtilityClass.h"
#include <string>
#include <tinyxml2.h>

class XmlParsable
{
public:
    virtual bool loadFromXml(std::string pKey, const char* pText) = 0;
    virtual void saveToXml(tinyxml2::XMLDocument& doc,
                           tinyxml2::XMLElement* msgs) = 0;
};

inline void _linkXmlMsg(tinyxml2::XMLDocument& doc,
                        tinyxml2::XMLElement* msgs,
                        std::string key,
                        const char* var)
{
    tinyxml2::XMLElement* msg = doc.NewElement(key.c_str());
    msg->LinkEndChild(doc.NewText(var));
    msgs->LinkEndChild(msg);
}

inline void linkXmlMsg(tinyxml2::XMLDocument& doc,
                       tinyxml2::XMLElement* msgs,
                       std::string key,
                       int var)
{
    _linkXmlMsg(doc, msgs, key, help.String(var).c_str());
}
inline void linkXmlMsg(tinyxml2::XMLDocument& doc,
                       tinyxml2::XMLElement* msgs,
                       std::string key,
                       std::string var)
{
    _linkXmlMsg(doc, msgs, key, var.c_str());
}
inline void linkXmlMsg(tinyxml2::XMLDocument& doc,
                       tinyxml2::XMLElement* msgs,
                       std::string key,
                       const bool* var,
                       int length)
{
    std::string _str;
    for (size_t i = 0; i < length; i++)
        _str += help.String(var[i]) + ",";

    _linkXmlMsg(doc, msgs, key, _str.c_str());
}