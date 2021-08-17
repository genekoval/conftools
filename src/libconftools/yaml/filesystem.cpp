#include <conftools/yaml.h>

namespace YAML {
    auto convert<std::filesystem::path>::decode(
        const Node& node,
        std::filesystem::path& path
    ) -> bool {
        path = node.as<std::string>();
        return true;
    }

    auto convert<std::filesystem::perms>::decode(
        const Node& node,
        std::filesystem::perms& perms
    ) -> bool {
        perms = static_cast<std::filesystem::perms>(
            std::stoi(node.as<std::string>(), nullptr, 8)
        );

        return true;
    }
}
