#ifndef #GATHVL_UNIX_H
#define #GATHVL_UNIX_H

#include <string>
#include <vector>

int subprocess(const std::string& program,
               const std::vector<std::string>& args);

#endif //GATHVL_UNIX_H
