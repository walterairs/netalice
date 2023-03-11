cmake_minimum_required(VERSION "3.16.3")

project(netalice VERSION "1.0.0" DESCRIPTION "a TUI based net analysis tool" LANGUAGES "C")

set(SRC_FILES
    source/main.c
    source/ui/ui.c
    source/tools/speedtest/speedtest.c
)

add_executable(netalice ${SRC_FILES})