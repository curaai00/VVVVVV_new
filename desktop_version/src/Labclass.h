#ifndef LABCLASS_H
#define LABCLASS_H

#include <json.hpp>
#include <string>

class labclass
{
public:
    labclass();
    ~labclass();

    const short* loadlevel(int rx, int ry);

    std::string roomname;
    int rcol;
    nlohmann::json level_table;
};
#endif /* LABCLASS_H */
