#pragma once

#include <vector>
#include <string>

namespace ap {
    // Default conversion template
    template<typename T> struct convert_from_string_to {};

    // Integral conversions
    template<> struct convert_from_string_to<int> {
        static int convert(const std::string& s) { return std::stoi(s); }
    };
    template<> struct convert_from_string_to<long> {
        static long convert(const std::string& s) { return std::stol(s); }
    };
    template<> struct convert_from_string_to<unsigned long> {
        static unsigned int convert(const std::string& s) { return std::stoul(s); }
    };
    template<> struct convert_from_string_to<long long> {
        static long long convert(const std::string& s) { return std::stoll(s); }
    };
    template<> struct convert_from_string_to<unsigned long long> {
        static unsigned long long convert(const std::string& s) { return std::stoull(s); }
    };

    // Floating point conversions
    template<> struct convert_from_string_to<float> {
        static float convert(const std::string& s) { return std::stof(s); }
    };
    template<> struct convert_from_string_to<double> {
        static float convert(const std::string& s) { return std::stod(s); }
    };
    template<> struct convert_from_string_to<long double> {
        static float convert(const std::string& s) { return std::stold(s); }
    };

    // String conversion
    template<> struct convert_from_string_to<std::string> {
        static std::string convert(const std::string& s) { return s; }
    };

    // Boolean conversion
    template<> struct convert_from_string_to<bool> {
        static bool convert(const std::string& s) { return s == "1" || s == "true"; }
    };

    // Designates whether given argument is optional or required
    enum class mode {
        REQUIRED,
        OPTIONAL
    };

    class parser {
    private:
        struct argstruct {
            std::string shortarg;
            std::string longarg;
            std::string helpstr;
            mode        required;
            bool        parsed;

            argstruct(const std::string& sa,
                      const std::string& la,
                      const std::string& hs,
                      mode rq,
                      bool ps)
                : shortarg(sa)
                , longarg(la)
                , helpstr(hs)
                , required(rq)
                , parsed(ps) {}
        };

        int                                    m_argc;
        std::vector<std::string>               m_argv;
        std::vector<argstruct>                 m_args;
        std::vector<std::function<void(void)>> m_populate_args;

        void remove_equals(std::vector<std::string>& argv) {
            int new_argc = std::count_if(argv.begin(), argv.end(), [](const std::string& s) {
                return s.find("=") != std::string::npos;
            }) + argv.size();

            argv.reserve(new_argc);

            auto it = argv.begin();
            while (it != argv.end()) {
                auto idx = it->find("=");
                if (idx != std::string::npos) {
                    auto arg = it->substr(0, idx);
                    auto val = it->substr(idx+1);

                    it = argv.erase(it);
                    it = argv.insert(it, val);
                    it = argv.insert(it, arg);
                }
                if (it != argv.end()) {
                    ++it;
                }
            }
        }

        void expand_shortargs(std::vector<std::string>& argv) {
            // TODO
        }

    public:
        parser(int argc, char* argv[]) {
            m_argv = std::vector<std::string>(argv, argv+argc);

            // Reformat argv in case --arg=val notation is used
            remove_equals(m_argv);
            
            // Expand shortargs in case -ab notation is used
            expand_shortargs(m_argv);
        }

        template<typename T>
        bool add(const std::string& shortarg,
                 const std::string& longarg,
                 T* ptr,
                 const std::string& helpstr,
                 mode m = mode::REQUIRED) {

            argstruct as(shortarg, longarg, helpstr, m, false);

            return false;
        }

        bool parse() {
            return false;
        }

        int argc() const {
            return m_argc;
        }

        const std::vector<std::string>& argv() const {
            return m_argv;
        }
    };
}
