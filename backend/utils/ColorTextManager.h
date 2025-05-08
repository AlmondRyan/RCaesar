#ifndef COLOR_TEXT_MANAGER_H
#define COLOR_TEXT_MANAGER_H

#define NOMINMAX
#include <windows.h>
#include <iostream>

/// \namespace \c RCaesar - Main Namespace
namespace RCaesar {
    /// \namespace \c ColorTextManager - A namespace that work for change the color of console text. A part of Utils.
    namespace ColorTextManager {
        /// \enum \c ConsoleTextManager::Color - A enumeration that defines some colors that for 16-bit color system.
        enum class Colors {
            CTM_Default,
            CTM_Red,
            CTM_Green,
            CTM_Yellow,
            CTM_Blue,
            CTM_Purple,
            CTM_Cyan,
            CTM_White
        };

        /// \class \c ConsoleTextManager
        /// \brief A Manager only for Console Text Color. Yeah, that's it. Really simple.
        class ConsoleTextManager {
        public:
            /// \brief Default Constructor.
            ConsoleTextManager() = default;

            /// \brief Default Destructor.
            ~ConsoleTextManager() = default;

            /**
             * @brief @c setColor - Set console text color.
             *
             * Yes, you can use this to change the color. But, @b I @b DON'T @b RECOMMEND.
             * I override the @c \<\< operator, you shouldn't use this. Operator is more convenient, isn't it?
             * Just like this:
             *
             * @code
             * std::cout << ColorTextManager::Colors::CTM_Red << "This is red text" << std::endl
             *  << ColorTextManager::Colors::CTM_Default << "Oh yeah this is default color text hooray." << std::endl;
             * @endcode
             *
             * @param os The @c std::ostream stream instance.
             * @param colors The color you want to change.
             */
            static void setColor(std::ostream &os, Colors colors);

            /**
             * @brief @c resetColor - As the name is, reset the color. But, I don't know where should I place. Just let it there.
             *
             * @param os The @c std::ostream stream instance.
             */
            static void resetColor(std::ostream &os = std::cout);
        };

        /**
         * @brief @c operator\<\< - Overrides the stream output operator.
         *
         * YEAH THE MAIN IDOL IS HERE!
         * This is why I told you shouldn't use @c setColor() to change the color.
         * This is more convenient! Please use this!
         *
         * @param os The @c std::ostream stream instance.
         * @param colors The color you want to change.
         * @return os The @c std::ostream stream instance.
         */
        inline std::ostream &operator<<(std::ostream &os, Colors colors) {
            ConsoleTextManager::setColor(os, colors);
            return os;
        }
    }
}

// More convenient way to change the color, using the macro!
#define CONSOLE_COLOR_RED ColorTextManager::Colors::CTM_Red
#define CONSOLE_COLOR_DEFAULT ColorTextManager::Colors::CTM_Default
#define CONSOLE_COLOR_GREEN ColorTextManager::Colors::CTM_Green
#define CONSOLE_COLOR_YELLOW ColorTextManager::Colors::CTM_Yellow
#define CONSOLE_COLOR_BLUE ColorTextManager::Colors::CTM_Blue
#define CONSOLE_COLOR_PURPLE ColorTextManager::Colors::CTM_Purple
#define CONSOLE_COLOR_CYAN ColorTextManager::Colors::CTM_Cyan
#define CONSOLE_COLOR_WHITE ColorTextManager::Colors::CTM_White

#endif