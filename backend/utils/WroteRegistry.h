#ifndef WROTE_REGISTRY
#define WROTE_REGISTRY

#include <windows.h>
#include "ErrorHandler.h"

namespace RCaesar {
    class Registry {
    public:
        static void WriteRegistryFlag(bool show) {
            HKEY hKey;
            const char* keyPath = "SOFTWARE\\Rinmwen\\RCaesar";
            const char* valueName = "ShowIntroWarning";

            DWORD dwValue = show ? 1 : 0;
            LONG openResult = RegCreateKeyExA(
                HKEY_CURRENT_USER,
                keyPath,
                0,
                NULL,
                REG_OPTION_NON_VOLATILE,
                KEY_ALL_ACCESS,
                NULL,
                &hKey,
                NULL
                );

            if (openResult == ERROR_SUCCESS) {
                LONG setValueResult = RegSetValueExA(
                    hKey,
                    valueName,
                    0,
                    REG_DWORD,
                    (LPBYTE)&dwValue,
                    sizeof(DWORD)
                    );

                if (setValueResult != ERROR_SUCCESS) {
                    ErrorHandler::ErrorHandler::getInstance()->makeError("Failed to set registry value",
                                                                         "WroteRegistry.h");
                }
                RegCloseKey(hKey);
            } else {
                ErrorHandler::ErrorHandler::getInstance()->makeError(
                    &"Failed to create or open registry key, possible reason is: You have not enough permissions. Error Code" [ openResult ],
                    "WroteRegistry.h"
                    );
            }
        }

        static bool ReadRegistryFlag() {
            HKEY hKey;
            const char *KeyPath = "SOFTWARE\\Rinmwen\\RCaesar", *valueName = "ShowIntroWarning";
            DWORD dwType = REG_DWORD, dwSize = sizeof(DWORD), dwValue = 0;

            LONG openResult = RegOpenKeyExA(
                HKEY_CURRENT_USER,
                KeyPath,
                0,
                KEY_READ,
                &hKey
                );

            if (openResult == ERROR_SUCCESS) {
                LONG queryValueResult = RegQueryValueExA(
                    hKey,
                    valueName,
                    NULL,
                    &dwType,
                    (LPBYTE)&dwValue,
                    &dwSize
                    );

                if (queryValueResult == ERROR_SUCCESS && dwType == REG_DWORD) {
                    RegCloseKey(hKey);
                    return dwValue != 0;
                } else {
                    ErrorHandler::ErrorHandler::getInstance()->makeError("Failed to query registry value",
                                                                         "WroteRegistry.h");
                }
                RegCloseKey(hKey);
            } else {
                ErrorHandler::ErrorHandler::getInstance()->makeError(
                    &"Failed to query registry key. Error Code" [ openResult ],
                    "WroteRegistry.h"
                );
            }
            return false;
        }
    };
}

#endif