#ifndef RCAESAR_TYPE_4_H
#define RCAESAR_TYPE_4_H

#include <string>
#include <iostream>
#include "../utils/utils.h"
#include "../utils/ColorTextManager.h"
#include "../utils/CaesarStatus.h"
#include "../utils/InteractiveTerminal.h"

namespace RCaesar {
    namespace Caesars {
        CaesarStatus type4(std::vector<std::string> &custom_sheet) {
            std::string inpx;
            std::vector<std::string> customSheets = custom_sheet;
            ::std::string res;
            ShowInstructions::show_help_for_encode_type_4();

            ::std::cout << ::std::endl
                        << "Enter the group size (number of characters per group): ";
            int groupSize;
            if (!(::std::cin >> groupSize)) {
                ::std::cin.clear();
                IGNORE_REMAIN_CHARACTERS_UNTIL_MEET_LINE_FEED
                INVALID_STEPS
                return CaesarStatus(RCaesar::Status::FAILED, "", "Invalid Steps.");
            }

            ::std::cout << "Enter the text to encode (lowercase letters only): ";
            ::std::cin >> inpx;
            ::std::string inp = to_lower(inpx);

            ::std::vector<::std::string> splited = split_size(groupSize, inp);
            ::std::cout << CONSOLE_COLOR_CYAN << "[Info]: " << CONSOLE_COLOR_DEFAULT
                        << "Text split into " << splited.size() << " groups" << ::std::endl;

            for (int groupIdx = 0; groupIdx < splited.size(); groupIdx++) {
                ::std::string currentGroup = splited[groupIdx];
                ::std::cout << "\nProcessing group " << (groupIdx + 1) << " of " << splited.size() << " (" << currentGroup << ")" << ::std::endl;

                ::std::vector<::std::string> sheetOptions = {
                    "Use default alphabet",
                    "Use existing custom sheet",
                    "Add new custom sheet"};
                ::std::cout << "\nSelect encryption alphabet for this group:" << ::std::endl;
                int sheetChoice = InteractiveTerminal::showMenu(sheetOptions);

                ::std::string selectedSheet = default_alphabet;

                if (sheetChoice == 1) {
                    if (customSheets.empty()) {
                        ::std::cout << ColorTextManager::Colors::CTM_Yellow << "[Warning]: " << CONSOLE_COLOR_DEFAULT
                                    << "No custom sheets available. Using default alphabet." << ::std::endl;
                    } else {
                        ::std::cout << "\nAvailable custom sheets:" << ::std::endl;
                        ::std::vector<::std::string> sheetList;
                        for (int i = 0; i < customSheets.size(); i++) {
                            sheetList.push_back("Sheet " + ::std::to_string(i) + ": " + customSheets[i]);
                        }
                        int sheetUid = InteractiveTerminal::showMenu(sheetList);
                        selectedSheet = customSheets[sheetUid];
                    }
                } else if (sheetChoice == 2) {
                    ::std::cout << "Enter new custom sheet (26 unique letters): ";
                    ::std::string newSheet;
                    ::std::cin >> newSheet;

                    try {
                        bool isValid = check_encrypt_sheet_valid(newSheet);
                        customSheets.push_back(newSheet);
                        int newUid = static_cast<int>(customSheets.size() - 1);
                        ::std::cout << CONSOLE_COLOR_GREEN << "[Success]: " << CONSOLE_COLOR_DEFAULT
                                    << "New sheet added with ID: " << newUid << ::std::endl;
                        selectedSheet = newSheet;
                    } catch (std::exception &e) {
                        ::std::cout << CONSOLE_COLOR_RED << "[Error]: " << CONSOLE_COLOR_DEFAULT
                                    << e.what() << ::std::endl;
                        ::std::cout << "Using default alphabet instead." << ::std::endl;
                    }
                }

                ::std::cout << "Enter shift steps for this group: ";
                int steps;
                if (!(::std::cin >> steps)) {
                    ::std::cin.clear();
                    IGNORE_REMAIN_CHARACTERS_UNTIL_MEET_LINE_FEED
                    INVALID_STEPS
                    return CaesarStatus(RCaesar::Status::FAILED, "", "Invalid Steps.");
                }

                if (steps < 0) {
                    steps = 26 + steps;
                }

                ::std::cout << "\nProcessing group encryption..." << ::std::endl;
                for (size_t i = 0; i < currentGroup.length(); i++) {
                    res += move_alpha_fwd(currentGroup[i], steps, selectedSheet);
                }
            }

            return CaesarStatus(RCaesar::Status::SUCCESS, res);
        }
    }
}

#endif