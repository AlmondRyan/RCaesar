#ifndef RCAESAR_TYPE_7_H
#define RCAESAR_TYPE_7_H

#include <string>
#include <iostream>
#include "../utils/utils.h"
#include "../utils/ColorTextManager.h"
#include "../utils/CaesarStatus.h"

namespace RCaesar {
    namespace Caesars {
        CaesarStatus type7() {
            std::string inpx;
            ShowInstructions::show_help_for_encode_type_1();
            ::std::string res;

            ::std::cout << ::std::endl
                        << "Enter the encrypted text (lowercase letters only): ";
            ::std::cin >> inpx;
            ::std::string inp = to_lower(inpx);

            ::std::cout << "Enter the initial shift step that was used (will increase for each character): ";
            int steps = 0;
            if (!(::std::cin >> steps)) {
                ::std::cin.clear();
                IGNORE_REMAIN_CHARACTERS_UNTIL_MEET_LINE_FEED
                INVALID_STEPS
                return CaesarStatus(RCaesar::Status::FAILED, "", "Invalid Steps.");
            }

            ::std::cout << "\nProcessing progressive decryption..." << ::std::endl;
            for (int i = 0; i < inp.size(); i++) {
                if (steps < 0) {
                    steps = 26 + steps;
                }
                int fstep = steps + i;
                res += move_alpha_bwd(inp.at(i), fstep);
            }
            return CaesarStatus(RCaesar::Status::SUCCESS, res);
        }

        CaesarStatus type7(std::string text, int initial_steps) {
            ::std::string res;
            ::std::string inp = to_lower(text);
            int steps = initial_steps;
            
            if (steps < 0) {
                steps = 26 + steps;
            }
            
            for (int i = 0; i < inp.size(); i++) {
                int fstep = steps + i;
                res += move_alpha_bwd(inp.at(i), fstep);
            }
            return CaesarStatus(RCaesar::Status::SUCCESS, res);
        }
    }
}

#endif