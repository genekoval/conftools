#include <conftools/yaml.h>

namespace {
    auto is_number(std::string_view string) -> bool {
        return !string.empty() &&
               std::find_if_not(
                   string.begin(),
                   string.end(),
                   [](unsigned char c) { return std::isdigit(c); }
               ) == string.end();
    }
}

namespace YAML {
    auto convert<ext::group>::decode(const Node& node, ext::group& group)
        -> bool {
        const auto g = node.as<std::string>();

        if (is_number(g)) {
            group = ext::group(static_cast<gid_t>(std::stoi(g)));
        }
        else group = ext::group(g);

        return true;
    }

    auto convert<ext::user>::decode(const Node& node, ext::user& user) -> bool {
        const auto u = node.as<std::string>();

        if (is_number(u)) {
            user = ext::user(static_cast<uid_t>(std::stoi(u)));
        }
        else user = ext::user(u);

        return true;
    }
}
