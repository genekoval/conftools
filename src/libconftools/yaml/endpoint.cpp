#include <conftools/yaml.h>

using conftools::endpoint;
using std::chrono::seconds;

namespace YAML {
    auto convert<endpoint>::decode(
        const Node& node,
        endpoint& endpoint
    ) -> bool {
        endpoint.endpoint = node.as<netcore::endpoint>();

        endpoint.timeout = node["timeout"] ?
            seconds(node["timeout"].as<long>()) :
            seconds::zero();

        return true;
    }
}
