file(GLOB HEADERS "*.h")
file(GLOB SRC_LIST "./*.cpp")

if (BUILD_GM)
    file(GLOB_RECURSE SUB_SRC_LIST "gm/*.cpp") 
else ()
    file(GLOB SUB_SRC_LIST "origin/*.cpp")
endif()

list(APPEND SRC_LIST ${SUB_SRC_LIST})

add_library(utils ${SRC_LIST} ${HEADERS})

target_link_libraries(utils Cryptopp dl)

if (BUILD_GM)
target_link_libraries(utils TASSL)
target_include_directories(utils PUBLIC ${TASSL_INCLUDE_DIRS})
endif()
