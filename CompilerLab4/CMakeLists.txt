cmake_minimum_required(VERSION 3.16)
project(lab04)
set(CMAKE_CXX_STANDARD 14)
add_executable(Compilerlab4 
    main.cpp
    Compiler.cpp
    Dspace.cpp
    FA.cpp
    # Grammar.cpp
    lab3FA.cpp
    public.cpp
    Syntax.cpp
    SynAnalyzer.cpp
    Word.cpp
)