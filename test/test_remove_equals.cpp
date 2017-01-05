#include <catch.hpp>

#include <argparser.hpp>

TEST_CASE("Test remove equals 1", "[remove equals]") {
    constexpr int argc = 4;
    const char* argv[argc] = {
        "test.exe",
        "-f", "First",
        "-l=Last",
    };

    ap::parser p(argc, const_cast<char**>(argv));
    
    REQUIRE(p.argc() == argc + 1);
}

TEST_CASE("Test remove equals 2", "[remove equals]") {
    constexpr int argc = 5;
    const char* argv[argc] = {
        "test.exe",
        "-f", "First",
        "--middle=Middle",
        "-l=Last",
    };

    ap::parser p(argc, const_cast<char**>(argv));
    
    REQUIRE(p.argc() == argc + 2);
}
