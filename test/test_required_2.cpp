#include <catch.hpp>

#include <argparser.hpp>

TEST_CASE("Test required args", "[required]") {
    constexpr int argc = 3;
    const char* argv[argc] = {
        "test.exe",
        "-f", "First",
    };

    ap::parser p(argc, const_cast<char**>(argv));
    p.add("-f", "--first", "My first name");
    p.add("-l", "--last",  "My last name");
    
    REQUIRE(!p.parse().success());
}