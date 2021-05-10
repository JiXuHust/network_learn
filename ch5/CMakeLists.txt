
add_subdirectory(read)
add_executable(tcp_server tcp_server.cpp)

target_link_directories(tcp_server PUBLIC read)

add_executable(tcp_client tcp_client.cpp)
