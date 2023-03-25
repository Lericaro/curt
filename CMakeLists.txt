cmake_minimum_required(VERSION 3.20)

project(cuda_study
    VERSION   0.1
    LANGUAGES CXX CUDA
)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

foreach(lang CXX CUDA)
    set(CMAKE_${lang}_STANDARD          17)
    set(CMAKE_${lang}_STANDARD_REQUIRED ON)
    set(CMAKE_${lang}_EXTENSIONS        OFF)
endforeach()

include_directories(${CMAKE_CURRENT_SOURCE_DIR}/include)


function(ADD_CUDA_TARGET T P)
    add_executable(${T} ${P})
    set_property(TARGET ${T} PROPERTY CUDA_ARCHITECTURES 75)
endfunction()



function(ADD_TARGET T P)
    add_executable(${T} ${P})
endfunction()


ADD_CUDA_TARGET(test src/test.cu)
ADD_TARGET(main src/main.cc)
