cmake_minimum_required(VERSION 3.22)

project(TimetableMachine)


set(CMAKE_CXX_STANDARD 23)


add_executable( importProgram
                rawData.cpp
                time.cpp
                import.cpp
                )

add_executable( processProgram
                time.cpp
                lesson.cpp
                group.cpp
                subject.cpp
                timetable.cpp
                process.cpp
                )