#ifndef WAIT_H
#define WAIT_H

#include <windows.h>

namespace RCaesar {
    using w_dword = DWORD;

    class Wait {
    public:
        static void wait_for(w_dword millisecs) {
            Sleep(millisecs);
        }

        static void wait_then_clear(w_dword millisecs) {
            Sleep(millisecs);
            system("cls");
        }
    };
}

#endif // WAIT_H