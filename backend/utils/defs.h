#include <string>

#define IGNORE_REMAIN_CHARACTERS_UNTIL_MEET_LINE_FEED ::std::cin.ignore(::std::numeric_limits<::std::streamsize>::max(), '\n');

#define FEAT_CHECK_UNSUPPORTED_CHARACTER 1
#define FEAT_CHECK_LENGTH_NOT_26 2
#define FEAT_SECRET 3

#define INVALID_STEPS ::std::cout << CONSOLE_COLOR_RED << "[Error]: " << CONSOLE_COLOR_DEFAULT << "Invalid input for steps. Please enter a NUMBER." << ::std::endl;

#define HOOK_MESSAGE_PROCESSED 1

extern const std::string default_alphabet;