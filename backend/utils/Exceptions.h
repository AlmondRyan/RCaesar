#ifndef EXCEPTIONS_H
#define EXCEPTIONS_H

#include <exception>
#include <string>

/// \namespace \c RCaesar - Main Namespace
namespace RCaesar {
    /// \namespace \c Exceptions - A sub module of @c RCaesar namespace, handles the common exceptions.
    /// \n\n
    /// OH MY GOD HERE ARE THE EXCEPTIONS! THE BAD-AS-HELL GUYS ARE COMING!! THIS IS CONDITION ONE ALERT!!!
    namespace Exceptions {
        /// \class \c UnsupportedCharacter
        /// \n\n
        /// Oh my god dude, how many unsupported characters did you entered? -- The Application said helplessly.
        class UnsupportedCharacter : public std::exception {
        public:
            explicit UnsupportedCharacter(const char* msg) : message(msg) {}
            const char* what() const noexcept override {
                return message.c_str();
            }
        private:
            std::string message;
        };

        /// \class \c NotValidLength
        /// \n\n
        /// Hey dude, length is not enough! Um, I means, the English alphabet has 26 letters!
        class NotValidLength : public std::exception {
        public:
            explicit NotValidLength(const char* msg) : message(msg) {}
            const char* what() const noexcept override {
                return message.c_str();
            }
        private:
            std::string message;
        };

        /// \class \c SheetIsNotUnique
        /// \n\n
        /// The encode shi... sheet is not unique! I promise, I didn't say the s-word just now!
        /// Just make it unique, unique is all you need!
        class SheetIsNotUnique : public std::exception {
        public:
            explicit SheetIsNotUnique(const char* msg) : message(msg) {}
            const char* what() const noexcept override {
                return message.c_str();
            }
        private:
            std::string message;
        };

        /// \class \c OutOfVariableLength
        /// \n\n
        /// Sorry dude, this is not my bad, it is the computer's bad! It just limit it! Your value is too big!
        class OutOfVariableLength : public std::exception {
        public:
            explicit OutOfVariableLength(const char* msg) : message(msg) {}
            const char* what() const noexcept override {
                return message.c_str();
            }
        private:
            std::string message;
        };
    }
}

#endif