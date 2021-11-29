cmake_minimum_required(VERSION 3.20)
project(philosophers C)

set(CMAKE_C_STANDARD 99)

add_executable(philo src/main.c
        src/utils/ft_atio.c
        src/utils/time.c
        src/utils/exit.c
        src/init.c)
