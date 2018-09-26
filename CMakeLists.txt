cmake_minimum_required(VERSION 2.8)

project(microservice)

set(HEADERS
    microsvc_controller.hpp
    include/basic_controller.hpp
    include/controller.hpp
    include/network_utils.hpp
    include/runtime_utils.hpp
    include/std_micro_service.hpp
    include/usr_interrupt_handler.hpp
)

add_executable(${PROJECT_NAME} main.cpp microsvc_controller.cpp ${HEADERS})

find_package(Boost REQUIRED COMPONENTS system thread log program_options chrono)
find_package(Threads REQUIRED)

message(BOOST_LIBS " ${Boost_LIBRARIES}")
message(OPENSSL_LIBS " ${OPENSSL_LIBRARIES}")

# target_include_directories(${PROJECT_NAME} PRIVATE include)

target_link_libraries(${PROJECT_NAME}
    tcmalloc
    cpprest
    pthread
    boost_system
    boost_thread
    boost_log
    boost_program_options
    boost_chrono
    ssl
    crypto
)

target_compile_options(${PROJECT_NAME}
  PRIVATE
    -flto
    -march=native
    -std=c++17
#    -O
    -O3
#    -g3
    -m64
    -fno-omit-frame-pointer
    -Werror
    -Wno-unused-parameter
    -Wfatal-errors
    -pedantic-errors
    -Wall
    -Wno-missing-braces
    -Wcast-align
    -Wcast-qual
    -Wctor-dtor-privacy
    -Wextra
    -Wformat=2
    -Wmissing-declarations
    -Wno-long-long
    -Wnon-virtual-dtor
    -Woverlength-strings
    -Woverloaded-virtual
    -Wredundant-decls
    -Wreorder
    -Wswitch-default
    -Wunused-variable
    -Wwrite-strings
    -Wno-variadic-macros
    -Wno-unused-local-typedef
    -Wno-language-extension-token
    -fstrict-aliasing
    -Wconversion
    -Wfloat-equal
    -Wold-style-cast
    -Wunreachable-code
    -Wshadow
    -Wpointer-arith
    -Wcast-align
    -Wformat-nonliteral
    -Winit-self
    -floop-parallelize-all
    -ftree-parallelize-loops=4
)
