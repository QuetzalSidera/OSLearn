cmake_minimum_required(VERSION 4.2)
project(OSLearn C)

set(CMAKE_C_STANDARD 11)

add_executable(OSLearn main.c
        Chapter1/CpuTest/cpu.c
        Chapter1/MemTest/mem.c
        Chapter1/ThreadTest/thread.c)
