cmake_minimum_required(VERSION 3.28)
set(CMAKE_TOOLCHAIN_FILE "C:/vcpkg/vcpkg/vcpkg/scripts/buildsystems/vcpkg.cmake" CACHE STRING "")
project(RCaesar)

set(CMAKE_CXX_STANDARD 11)

#find_package(Boost REQUIRED COMPONENTS system thread)

add_executable(RCaesar main.cpp
        utils/ColorTextManager.cpp
        utils/ColorTextManager.h
        utils/Exceptions.h
        utils/defs.h
        utils/Feature.cpp
        utils/Feature.h
        utils/utils.h
        utils/Base64Decoder.h
        utils/InteractiveTerminal.h
        utils/wait.h
        utils/defs.cpp
        utils/WroteRegistry.h
        utils/ErrorHandler.h
        caesars/type0.h
        utils/CaesarStatus.h
        caesars/type1.h
        caesars/type2.h
        caesars/type3.h
        caesars/type4.h
        caesars/type5.h
        caesars/type6.h
        caesars/type7.h
        utils/RequestParser.h
)

target_include_directories(RCaesar PRIVATE
        "C:\\vcpkg\\vcpkg\\vcpkg\\installed\\x64-windows\\include"
        ${CMAKE_CURRENT_SOURCE_DIR}
        nlohmann
)