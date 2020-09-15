#ifndef FINALCLASS_H
#define FINALCLASS_H

#include <json.hpp>
#include <string>

class finalclass
{
public:
    finalclass();
    ~finalclass(){};
    const short* loadlevel(int rx, int ry);

    std::string roomname;
    bool warpx, warpy;
    nlohmann::json level_table;
};

#endif /* FINALCLASS_H */
