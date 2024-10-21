target_sources(conftools PRIVATE
    database.cpp
    endpoint.cpp
    filesystem.cpp
    netcore.cpp
    timber.cpp
    unix.cpp
)

if(PROJECT_TESTING)
    target_sources(conftools.test PRIVATE
        unix_socket.test.cpp
    )
endif()
