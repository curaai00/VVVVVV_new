#ifndef WARPCLASS_H
#define WARPCLASS_H

#include <json.hpp>
#include <string>

class warpclass
{
public:
    warpclass();
    ~warpclass(){};
    const short* loadlevel(int rx, int ry);
    std::string roomname;
    int rcol;
    bool warpx, warpy;
    nlohmann::json warp_table;
};

#endif /* WARPCLASS_H */
