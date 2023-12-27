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
    constexpr auto expected = perms::owner_read | perms::owner_write |
                              perms::group_read | perms::others_read;

    const auto socket = load(R"(
path: /run/conf/tools.sock
mode: 644
)");

    ASSERT_TRUE(socket.mode.has_value());
    ASSERT_EQ(expected, socket.mode.value());
}
