#include "ColorTextManager.h"

/// \namespace \c RCaesar - Main Namespace
namespace RCaesar {
    /// \namespace \c ColorTextManager - A namespace that work for change the color of console text. A part of Utils.
    namespace ColorTextManager {
        /**
         * @brief @c setColor() Set the color.
         *
         * This function implemented the @c ConsoleTextManager::setColor in the header. The main design logic is here:
         * \n\n
         * - Make the function is platform-irrelevant, that means this function should have different
         * logic in different platforms. But something secret: I only wants this be run in Windows, but for
         * better coding experience, wrote the macros isn't bad huh?
         * \n
         * - On Windows, call @c SetConsoleTextAttribute() in @c windows.h, to change the text attribute.
         * \n
         * - On Linux/macOS, use ANSI escape sequences to change the color. Although Windows supported ANSI
         * escape sequences in newer version of Windows Terminal, but @c SetConsoleTextAttribute() is more directly.
         * \n
         * @sa https://en.wikipedia.org/wiki/ANSI_escape_code
         * @note Only @c std::cout and @c std::cerr streams are supported.
         *
         * @param os The @c std::ostream stream instance.
         * @param colors The color you want to change.
         */
        void ConsoleTextManager::setColor(std::ostream &os, RCaesar::ColorTextManager::Colors colors) {
            if (&os == &std::cout || &os == &std::cerr) {
#ifdef _WIN32
                HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
                switch (colors) {
                case Colors::CTM_Red:
                    SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_INTENSITY);
                    break;
                case Colors::CTM_Green:
                    SetConsoleTextAttribute(hConsole, FOREGROUND_GREEN | FOREGROUND_INTENSITY);
                    break;
                case Colors::CTM_Yellow:
                    SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_INTENSITY);
                    break;
                case Colors::CTM_Blue:
                    SetConsoleTextAttribute(hConsole, FOREGROUND_BLUE | FOREGROUND_INTENSITY);
                    break;
                case Colors::CTM_Purple:
                    SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_BLUE | FOREGROUND_INTENSITY);
                    break;
                case Colors::CTM_Cyan:
                    SetConsoleTextAttribute(hConsole, FOREGROUND_GREEN | FOREGROUND_BLUE | FOREGROUND_INTENSITY);
                    break;
                case Colors::CTM_White:
                    SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE | FOREGROUND_INTENSITY);
                    break;
                case Colors::CTM_Default:
                    SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
                    break;
                }
#else
                switch (colors) {
                case Colors::CTM_Red:
                    os << "\033[31m";
                    break;
                case Colors::CTM_Green:
                    os << "\033[32m";
                    break;
                case Colors::CTM_Yellow:
                    os << "\033[33m";
                    break;
                case Colors::CTM_Blue:
                    os << "\033[34m";
                    break;
                case Colors::CTM_Purple:
                    os << "\033[35m";
                    break;
                case Colors::CTM_Cyan:
                    os << "\033[36m";
                    break;
                case Colors::CTM_White:
                    os << "\033[37m";
                    break;
                case Colors::CTM_Default:
                    os << "\033[0m";
                    break;
                }
#endif
            }
        }

        /**
         * @brief @c resetColor() As the name, reset the color.
         *
         * It just calls @c setColor() to change the color to default. Nothing special.
         *
         * @param os The @c std::ostream stream instance. Default is @c std::cout
         */
        void ConsoleTextManager::resetColor(std::ostream &os) {
            setColor(os, Colors::CTM_Default);
        }
    } // namespace ColorTextManager
} // namespace RCaesar