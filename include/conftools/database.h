#pragma once

#include <map>
#include <string>

namespace conftools {
    struct database_connection {
        std::map<std::string, std::string> parameters;

        auto str() const -> std::string;
    };
}
