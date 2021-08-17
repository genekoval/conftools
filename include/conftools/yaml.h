#pragma once

#include <fmt/format.h>
#include <netcore/netcore>
#include <yaml-cpp/yaml.h>
#include <timber/timber>

#define CONVERT(Type) \
    template <> \
    struct convert<Type> { \
        static auto decode(const Node&, Type&) -> bool; \
    };

#define DECODE(Type, ...) \
    auto convert<Type>::decode(const Node& node, Type& t) -> bool { \
        return conftools::decode_type(node, t, __VA_ARGS__); \
    }

namespace conftools {
    template <typename T, typename Type>
    struct property {
        std::string name;
        Type T::* member;

        property(std::string_view name, Type T::* member) :
            name(name),
            member(member)
        {}
    };

    template <typename T, typename Type>
    struct optional : property<T, Type> {
        optional(std::string_view name, Type T::* member) :
            property<T, Type>(name, member)
        {}
    };

    template <typename T, typename Type>
    struct required : property<T, Type> {
        required(std::string_view name, Type T::* member) :
            property<T, Type>(name, member)
        {}
    };

    template <typename T, typename Type>
    auto decode_type_member(
        const YAML::Node& node,
        T& t,
        const optional<T, Type>& prop
    ) -> bool {
        if (node[prop.name]) {
            (t.*prop.member) = node[prop.name].template as<Type>();
        }

        return true;
    }

    template <typename T, typename Type>
    auto decode_type_member(
        const YAML::Node& node,
        T& t,
        const required<T, Type>& prop
    ) -> bool {
        if (node[prop.name]) {
            (t.*prop.member) = node[prop.name].template as<Type>();
            return true;
        }

        const auto mark = node.Mark();

        throw std::runtime_error(fmt::format(
            "missing node '{}' at line {}, column {}",
            prop.name,
            mark.line + 1,
            mark.column + 1
        ));
    }

    template <typename T, typename ...Properties>
    auto decode_type(
        const YAML::Node& node,
        T& t,
        Properties... properties
    ) -> bool {
        return (decode_type_member(node, t, properties) && ...);
    }
}

namespace YAML {
    template <typename T>
    struct convert<std::optional<T>> {
        static auto decode(
            const Node& node,
            std::optional<T>& optional
        ) -> bool {
            optional = node.template as<T>();
            return true;
        }
    };

    CONVERT(ext::group);
    CONVERT(ext::user);
    CONVERT(std::filesystem::path);
    CONVERT(std::filesystem::perms);
    CONVERT(netcore::unix_socket);
    CONVERT(timber::level);
}
