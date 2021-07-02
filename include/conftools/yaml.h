#pragma once

#include <netcore/netcore>
#include <yaml-cpp/yaml.h>

namespace YAML {
    template <>
    struct convert<netcore::unix_socket> {
        static auto decode(
            const Node& node,
            netcore::unix_socket& socket
        ) -> bool;
    };
}
