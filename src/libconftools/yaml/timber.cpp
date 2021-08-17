#include <conftools/yaml.h>

namespace YAML {
    auto convert<timber::level>::decode(
        const Node& node,
        timber::level& level
    ) -> bool {
        auto value = node.as<std::string>();
        auto l = timber::parse_level(value);

        if (!l) throw std::runtime_error("unknown log level: " + value);

        level = *l;
        return true;
    }
}
