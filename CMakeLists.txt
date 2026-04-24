cmake_minimum_required(VERSION 4.2)
project(OSLearn C)

set(CMAKE_C_STANDARD 11)

add_executable(OSLearn main.c
        Chapter1/CpuTest/cpu.c
        Chapter1/MemTest/mem.c
        Chapter1/ThreadTest/thread.c
        Chapter1/FileSystemTest/io.c
        Chapter2/Fork/fork.c
        Chapter2/Exec/exec.c
        Chapter3/PageTest/stack.c
        Chapter4/Thread/thread.c
        Mutex/BoundedBuffer/mutex.c
        Mutex/BoundedBuffer/monitor.c
        Mutex/SemWrite/mutex.c
        Mutex/MutexWrite/sem.c
        IPC/Fifo/main.c
)
