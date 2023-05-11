#pragma once

#include <netcore/netcore>

namespace conftools {
    struct endpoint {
        netcore::endpoint endpoint;
        std::chrono::seconds timeout;
    };
}
