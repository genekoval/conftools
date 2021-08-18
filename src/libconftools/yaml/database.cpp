#include <conftools/database.h>
#include <conftools/yaml.h>

#include <sstream>

namespace conftools {
    auto database_connection::str() const -> std::string {
        auto os = std::ostringstream();

        auto it = parameters.begin();
        const auto end = parameters.end();

        while (it != end) {
            os << it->first << "=" << it->second;
            if (++it != end) os << " ";
        }

        return os.str();
    }
}

namespace YAML {
    auto convert<conftools::database_connection>::decode(
        const Node& node,
        conftools::database_connection& connection
    ) -> bool {
        connection.parameters =
            node.as<decltype(conftools::database_connection::parameters)>();
        return true;
    }
}
