file(GLOB HEADERS "*.h")
file(GLOB SRC_LIST "./*.cpp")

if (BUILD_GM)
    file(GLOB_RECURSE SUB_SRC_LIST "gm/*.cpp") 
else ()
    file(GLOB SUB_SRC_LIST "origin/*.cpp")
endif()

list(APPEND SRC_LIST ${SUB_SRC_LIST})

add_library(utils ${SRC_LIST} ${HEADERS})
message(${SRC_LIST})

target_link_libraries(utils TASSL Cryptopp dl)

target_include_directories(utils PUBLIC ${BOOST_INCLUDE_DIR} ${TASSL_INCLUDE_DIRS})
