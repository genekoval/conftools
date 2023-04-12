#include <conftools/yaml.h>

namespace c = conftools;

using netcore::endpoint;
using netcore::inet_socket;
using netcore::unix_socket;

namespace YAML {
    auto convert<endpoint>::decode(
        const Node& node,
        endpoint& endpoint
    ) -> bool {
        if (node.IsScalar()) {
            endpoint = netcore::parse_endpoint(node.as<std::string>());
            return true;
        }

        if (node.IsMap()) {
            if (node["path"]) endpoint = node.as<unix_socket>();
            else endpoint = node.as<inet_socket>();

            return true;
        }

        return false;
    }

    DECODE(
        inet_socket,
        c::optional("host", &inet_socket::host),
        c::required("port", &inet_socket::port)
    );

    DECODE(
        unix_socket,
        c::optional("group", &unix_socket::group),
        c::optional("mode", &unix_socket::mode),
        c::optional("owner", &unix_socket::owner),
        c::required("path", &unix_socket::path)
    );
}
