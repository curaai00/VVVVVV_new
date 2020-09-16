#ifndef SPACESTATION2_H
#define SPACESTATION2_H

#include <json.hpp>
#include <string>

class spacestation2class
{
public:
    spacestation2class();
    ~spacestation2class() {}
    const short* loadlevel(int rx, int ry);
    std::string roomname;
    nlohmann::json station_table;
};

#endif /* SPACESTATION2_H */
