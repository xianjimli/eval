cmake_minimum_required(VERSION 3.5)

set(SYS_LIBS )
if(APPLE)
    # If OSX
	list(APPEND SYS_LIBS -lm )
    ADD_DEFINITIONS(
        -DMACOS -g -Wunused-variable -Wunused-parameter -Wunused-function -Wunused
        -Wno-deprecated -Woverloaded-virtual -Wwrite-strings
    )
elseif(UNIX)
    # If unix
	list(APPEND SYS_LIBS -lm )
    ADD_DEFINITIONS(
        -DUNIX -g -fPIC -Wunused-variable -Wunused-parameter -Wunused-function -Wunused
        -Wno-deprecated -Woverloaded-virtual -Wwrite-strings
    )
else()
    # If windows
    ADD_DEFINITIONS(-D_CRT_SECURE_NO_WARNINGS -DHAVE_STRUCT_TIMESPEC)
endif()

add_executable(eval main.c eval.c)
target_link_libraries(eval ${SYS_LIBS}) 

add_executable(eval_test test.c eval.c)
target_link_libraries(eval_test ${SYS_LIBS}) 

