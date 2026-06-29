cmake_minimum_required(VERSION 4.2)
project(assignment_4)

set(CMAKE_CXX_STANDARD 20)

add_executable(assignment_4 main.cpp
        Line.h
        TextEditor.cpp
        TextEditor.h
        Cipher.cpp
        Cipher.h
)
