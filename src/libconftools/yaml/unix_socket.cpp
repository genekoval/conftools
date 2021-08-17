#include <conftools/yaml.h>

namespace c = conftools;

namespace YAML {
    DECODE(
        netcore::unix_socket,
        c::optional("group", &netcore::unix_socket::group),
        c::optional("mode", &netcore::unix_socket::mode),
        c::optional("owner", &netcore::unix_socket::owner),
        c::required("path", &netcore::unix_socket::path)
    );
}
