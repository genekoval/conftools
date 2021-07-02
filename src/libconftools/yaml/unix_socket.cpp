#include <conftools/yaml.h>

static auto is_number(std::string_view string) -> bool {
    return
        !string.empty() &&
        std::find_if_not(
            string.begin(),
            string.end(),
            [](unsigned char c) {
                return std::isdigit(c);
            }
        ) == string.end();
}

static auto parse_mode(const std::string& string) -> std::filesystem::perms {
    return static_cast<std::filesystem::perms>(std::stoi(string, nullptr, 8));
}

namespace YAML {
    auto convert<netcore::unix_socket>::decode(
        const Node& node,
        netcore::unix_socket& socket
    ) -> bool {
        socket.path = node["path"].as<std::string>();

        if (node["mode"]) {
            socket.mode = parse_mode(node["mode"].as<std::string>());
        }

        if (node["owner"]) {
            const auto owner = node["owner"].as<std::string>();

            if (is_number(owner)) {
                socket.owner = static_cast<uid_t>(std::stoi(owner));
            }
            else socket.owner = owner;
        }

        if (node["group"]) {
            const auto group = node["group"].as<std::string>();

            if (is_number(group)) {
                socket.group = static_cast<gid_t>(std::stoi(group));
            }
            else socket.group = group;
        }

        return true;
    }
}
