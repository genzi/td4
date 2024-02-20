# Build a library with my application sources
set(TD4_LIB_SOURCE
    td4/td4.cpp
)

add_library(${TD4_LIB_NAME} ${TD4_LIB_SOURCE})

# Add main(..) to the application library to have something we can run
add_executable(${APP_NAME} main.cpp simulator/simulator.cpp)
target_link_libraries(${APP_NAME} ${TD4_LIB_NAME})
target_link_libraries(${APP_NAME} ncurses)
