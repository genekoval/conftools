#pragma once

#include <netcore/netcore>
#include <yaml-cpp/yaml.h>

namespace conftools {
    template <typename Optional>
    auto optional(
        const YAML::Node& node,
        const std::string& key
    ) -> Optional {
        if (auto value = node[key]) {
            return value.as<typename Optional::value_type>();
        }

        return {};
    }
}

namespace YAML {
    template <>
    struct convert<ext::group> {
        static auto decode(
            const Node& node,
            ext::group& group
        ) -> bool;
    };

    template <>
    struct convert<ext::user> {
        static auto decode(
            const Node& node,
            ext::user& group
        ) -> bool;
    };

    template <>
    struct convert<netcore::unix_socket> {
        static auto decode(
            const Node& node,
            netcore::unix_socket& socket
        ) -> bool;
    };
}
