#include <catch.hpp>

#include <argparser.hpp>

TEST_CASE("Test arg assignments", "[assignments]") {
    constexpr int argc = 2;
    const char* argv[argc] = {
        "test.exe",
        "-b",
    };

    ap::parser p(argc, const_cast<char**>(argv));
    p.add("-b", "--boolean", "My boolean value", true);
    auto args = p.parse();

    REQUIRE(args.success());

    REQUIRE(args["-b"] == args["--boolean"]);
    REQUIRE(args["-b"] == "1");
}
