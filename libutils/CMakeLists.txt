file(GLOB_RECURSE HEADERS "*.h")
file(GLOB_RECURSE SRC_LIST "./*.cpp")

add_library(utils ${SRC_LIST} ${HEADERS})

target_link_libraries(utils Cryptopp dl)

target_link_libraries(utils TASSL)
target_include_directories(utils PUBLIC ${TASSL_INCLUDE_DIRS})
