add_subdirectory(read)

add_executable(tcp_server tcp_server.cpp)

target_link_libraries(tcp_server PUBLIC READ)

# target_include_directories(tcp_server PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}/read")

add_executable(tcp_client tcp_client.cpp)
