#ifndef ERROR_HANDLER
#define ERROR_HANDLER

#include <utility>
#include <vector>
#include <string>
#include <iostream>

#include "ColorTextManager.h"

namespace RCaesar {
    namespace ErrorHandler {
        enum ErrorType {
            ET_Error,
            ET_Warning
        };

        struct ErrorObj {
            ErrorType errorType;
            std::string desc;
            std::string definedInSource;

            ErrorObj(ErrorType et, std::string _desc, std::string _dis)
            : errorType(et), desc(std::move(_desc)), definedInSource(std::move(_dis)) {}
        };

        class ErrorHandler {
        private:
            ErrorHandler() = default;
            ErrorHandler(const ErrorHandler&) = delete;
            ErrorHandler& operator=(const ErrorHandler&) = delete;

            static ErrorHandler *instance;
            std::vector<ErrorObj> errorObj;
        public:
            static ErrorHandler *getInstance() {
                if (instance == nullptr) {
                    instance = new ErrorHandler();
                }
                return instance;
            }

            void makeWarning(const std::string &desc, const std::string &fromSource) {
                errorObj.push_back(ErrorObj(ET_Warning, desc, fromSource));
            }

            void makeError(const std::string &desc, const std::string &fromSource) {
                errorObj.push_back(ErrorObj(ET_Error, desc, fromSource));
            }

            void showErrors() {
                for (auto &i : errorObj) {
                    if (i.errorType == ET_Warning) {
                        std::cout << CONSOLE_COLOR_YELLOW << "[Warning]" <<
                            CONSOLE_COLOR_DEFAULT << ": " << i.desc << " in source: " <<
                            CONSOLE_COLOR_BLUE << i.definedInSource << std::endl;
                    } else if (i.errorType == ET_Error) {
                        std::cout << CONSOLE_COLOR_RED << "[Error]" <<
                            CONSOLE_COLOR_DEFAULT << ": " << i.desc << " in source: " <<
                            CONSOLE_COLOR_BLUE << i.definedInSource << std::endl;
                    }
                }
            }
        };

        ErrorHandler *ErrorHandler::instance = nullptr;
    }
}

#endif