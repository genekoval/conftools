#include <conftools/yaml.h>

#include <gtest/gtest.h>

using perms = std::filesystem::perms;

class YamlUnixSocketTest : public testing::Test {
protected:
    auto load(const char* yaml) -> netcore::unix_socket {
        return YAML::Load(yaml).as<netcore::unix_socket>();
    }
};

TEST_F(YamlUnixSocketTest, ParsePath) {
    const auto socket = load("path: /run/conf/tools.sock");

    ASSERT_EQ("/run/conf/tools.sock", socket.path);
    ASSERT_FALSE(socket.mode.has_value());
    ASSERT_FALSE(socket.owner.has_value());
    ASSERT_FALSE(socket.group.has_value());
}

TEST_F(YamlUnixSocketTest, ParseMode) {
    constexpr auto expected =
        perms::owner_read |
        perms::owner_write |
        perms::group_read |
        perms::others_read;

    const auto socket = load(R"(
path: /run/conf/tools.sock
mode: 644
)");

    ASSERT_TRUE(socket.mode.has_value());
    ASSERT_EQ(expected, socket.mode.value());
}

TEST_F(YamlUnixSocketTest, ParseOwnerNumeric) {
    constexpr auto expected = static_cast<uid_t>(1000);

    const auto socket = load(R"(
path: /run/conf/tools.sock
owner: 1000
)");

    ASSERT_TRUE(socket.owner.has_value());

    const auto& owner = socket.owner.value();

    if (auto* value = std::get_if<uid_t>(&owner)) {
        ASSERT_EQ(expected, *value);
    }
    else FAIL() << "owner is not numeric type";
}

TEST_F(YamlUnixSocketTest, ParseOwnerName) {
    const auto expected = "conf";

    const auto socket = load(R"(
path: /run/conf/tools.sock
owner: conf
)");

    ASSERT_TRUE(socket.owner.has_value());

    const auto& owner = socket.owner.value();

    if (auto* value = std::get_if<std::string>(&owner)) {
        ASSERT_EQ(expected, *value);
    }
    else FAIL() << "owner is not string type";
}

TEST_F(YamlUnixSocketTest, ParseGroupNumeric) {
    constexpr auto expected = static_cast<gid_t>(0);

    const auto socket = load(R"(
path: /run/conf/tools.sock
group: 0
)");

    ASSERT_TRUE(socket.group.has_value());

    const auto& group = socket.group.value();

    if (auto* value = std::get_if<gid_t>(&group)) {
        ASSERT_EQ(expected, *value);
    }
    else FAIL() << "group is not numeric type";
}

TEST_F(YamlUnixSocketTest, ParseGroupName) {
    const auto expected = "conf";

    const auto socket = load(R"(
path: /run/conf/tools.sock
group: conf
)");

    ASSERT_TRUE(socket.group.has_value());

    const auto& group = socket.group.value();

    if (auto* value = std::get_if<std::string>(&group)) {
        ASSERT_EQ(expected, *value);
    }
    else FAIL() << "group is not string type";
}
