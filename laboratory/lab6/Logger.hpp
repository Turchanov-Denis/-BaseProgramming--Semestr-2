#pragma once

#include <fstream>
#include <sstream>
#include <ctime>

#define RED "\033[31m"
namespace utils {

    enum class Level {
        DEBUG,
        RELEASE
    };

    class Logger {
        static std::ofstream m_out;
        static Level m_level;

    public:
        static void SetLogFile(const std::string &path = "log.txt") {
            m_out.open(path);
        }

        static void SetLogLevel(Level level) {
            m_level = level;
        }

        static void Write(const std::string &msg) {
            switch (m_level) {
                case Level::DEBUG:
                    std::cout << RED << msg << std::endl;
                    if (m_out.is_open()) {
                        time_t now = std::time(0);
                        char *dt = ctime(&now);
                        m_out << dt << msg << std::endl;
                        m_out.flush();
                        break;

                    }
                case Level::RELEASE:
                    if (m_out.is_open()) {
                        time_t now = std::time(0);
                        char *dt = ctime(&now);
                        m_out << dt;
                        m_out << msg << std::endl;
                        m_out.flush();
                        break;
                    }
            }
        }


        template<typename T>
        Logger &operator<<(const T &t) {
            this->Write(static_cast<std::string>(t));
            return *this;
        }


    };

    std::ofstream Logger::m_out;
    Level Logger::m_level = Level::DEBUG;

}

