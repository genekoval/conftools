#include <conftools/yaml.h>

namespace {
    auto parse_mode(const std::string& string) -> std::filesystem::perms {
        return static_cast<std::filesystem::perms>(
            std::stoi(string, nullptr, 8)
        );
    }
}

namespace YAML {
    auto convert<netcore::unix_socket>::decode(
        const Node& node,
        netcore::unix_socket& socket
    ) -> bool {
        socket.group =
            conftools::optional<decltype(netcore::unix_socket::group)>(
                node,
                "group"
            );

        if (node["mode"]) {
            socket.mode = parse_mode(node["mode"].as<std::string>());
        }

        socket.path = node["path"].as<std::string>();

        socket.owner =
            conftools::optional<decltype(netcore::unix_socket::owner)>(
                node,
                "owner"
            );

        return true;
    }
}
