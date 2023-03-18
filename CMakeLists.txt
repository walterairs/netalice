cmake_minimum_required(VERSION "3.16.3")

project(netalice VERSION "1.0.0" DESCRIPTION "a TUI based net analysis tool" LANGUAGES "C")

set(SRC_FILES
    source/main.c
    source/ui/ui.c
    source/tools/speedtest/speedtest.c
    source/tools/downloadtest/downloadtest.c
)

find_package(Curses REQUIRED)
find_package(CURL REQUIRED)
include_directories(${CURSES_INCLUDE_DIR} ${CURL_INCLUDE_DIRS})

add_executable(netalice ${SRC_FILES})

target_link_libraries(netalice ${CURSES_LIBRARIES} ${CURL_LIBRARIES})

target_compile_options(netalice PRIVATE -Wall -Wextra -lcurl)
