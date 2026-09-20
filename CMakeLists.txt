cmake_minimum_required(VERSION 3.16)
project(OSMarquee VERSION 1.0 LANGUAGES CXX)


set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# Marquee uses std::thread, so link the platform's thread library.
find_package(Threads REQUIRED)

# Explicit source list (same files run.bat passed to g++). Add new .cpp files here.
add_executable(os_marquee
    main.cpp
    helpers/commands.cpp
    helpers/marquee.cpp
    helpers/text.cpp
)

target_link_libraries(os_marquee PRIVATE Threads::Threads)

# Your old -Wall, made compiler-aware.
if(MSVC)
    target_compile_options(os_marquee PRIVATE /W4)
else()
    target_compile_options(os_marquee PRIVATE -Wall)
endif()

# Your old -static (only needed for MinGW so the .exe doesn't depend on MinGW DLLs).
if(MINGW)
    target_link_options(os_marquee PRIVATE -static)
endif()

# Marquee::initializeFont() opens "helpers/text/ascii_font.txt" relative to the
# working directory, so copy it next to the executable after every build.
add_custom_command(TARGET os_marquee POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E make_directory $<TARGET_FILE_DIR:os_marquee>/helpers/text
    COMMAND ${CMAKE_COMMAND} -E copy_if_different
            ${CMAKE_CURRENT_SOURCE_DIR}/helpers/text/ascii_font.txt
            $<TARGET_FILE_DIR:os_marquee>/helpers/text/ascii_font.txt
)

# Replacement for run.bat:  cmake --build build --target run
add_custom_target(run
    COMMAND os_marquee
    WORKING_DIRECTORY $<TARGET_FILE_DIR:os_marquee>
    DEPENDS os_marquee
    USES_TERMINAL
)