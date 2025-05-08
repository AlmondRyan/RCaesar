#ifndef INTERACTIVE_TERMINAL_H
#define INTERACTIVE_TERMINAL_H

#include <windows.h>
#include <iostream>
#include <string>
#include <vector>
#include <sstream>
#include <conio.h>
#include "ColorTextManager.h"

namespace RCaesar {
    namespace InteractiveTerminal {
        enum KeyboardKeys {
            K_UpArrow = 72,
            K_DownArrow = 80,
            K_Enter = 13
        };

        void clearCurrentLine() {
            CONSOLE_SCREEN_BUFFER_INFO consoleScreenBufferInfo;
            HANDLE hStdOut = GetStdHandle(STD_OUTPUT_HANDLE);
            GetConsoleScreenBufferInfo(hStdOut, &consoleScreenBufferInfo);

            COORD coordinate = {
                0,
                consoleScreenBufferInfo.dwCursorPosition.Y
            };

            DWORD written;
            FillConsoleOutputCharacter(hStdOut, ' ', consoleScreenBufferInfo.dwSize.X,
                                       coordinate, &written);
            FillConsoleOutputAttribute(hStdOut, consoleScreenBufferInfo.wAttributes,
                                       consoleScreenBufferInfo.dwSize.X,
                                       coordinate, &written);

            SetConsoleCursorPosition(hStdOut, coordinate);
        }

        void setCursorPosition(int x, int y) {
            HANDLE hStdOut = GetStdHandle(STD_OUTPUT_HANDLE);
            COORD coord = {
                (SHORT)x,
                (SHORT)y
            };

            SetConsoleCursorPosition(hStdOut, coord);
        }

        COORD getCursorPosition() {
            CONSOLE_SCREEN_BUFFER_INFO consoleScreenBufferInfo;
            HANDLE hStdOut = GetStdHandle(STD_OUTPUT_HANDLE);
            GetConsoleScreenBufferInfo(hStdOut, &consoleScreenBufferInfo);

            return consoleScreenBufferInfo.dwCursorPosition;
        }
        
        int showMenu(const ::std::vector<::std::string>& options) {
            int selectedIndex = 0;
            int key;
            bool running = true;
            bool needRedraw = true;
            COORD initialPos = getCursorPosition();
            
            ::std::vector<::std::string> menuLines(options.size());

            while (running) {
                if (needRedraw) {
                    for (int i = 0; i < options.size(); i++) {
                        ::std::stringstream ss;
                        if (i == selectedIndex) {
                            ss << CONSOLE_COLOR_CYAN << "> " << options[i] << " <" << CONSOLE_COLOR_DEFAULT;
                        }
                        else {
                            ss << "  " << options[i] << "  ";
                        }
                        menuLines[i] = ss.str();
                    }

                    setCursorPosition(initialPos.X, initialPos.Y);
                    for (int i = 0; i < menuLines.size(); i++) {
                        clearCurrentLine();
                        ::std::cout << menuLines[i] << ::std::endl;
                    }

                    needRedraw = false;
                }

                key = _getch();
                if (key == 224) {
                    key = _getch();
                    switch (key) {
                    case KeyboardKeys::K_UpArrow:
                        selectedIndex = (selectedIndex > 0) ? selectedIndex - 1 : options.size() - 1;
                        needRedraw = true;
                        break;
                    case KeyboardKeys::K_DownArrow:
                        selectedIndex = (selectedIndex < options.size() - 1) ? selectedIndex + 1 : 0;
                        needRedraw = true;
                        break;
                    default:
                        break;
                    }
                }
                else if (key == KeyboardKeys::K_Enter) {
                    running = false;
                }
            }

            setCursorPosition(initialPos.X, initialPos.Y);
            for (int i = 0; i < options.size(); i++) {
                clearCurrentLine();
                ::std::cout << ::std::endl;
            }
            setCursorPosition(initialPos.X, initialPos.Y);

            return selectedIndex;
        }
    }
}

#endif