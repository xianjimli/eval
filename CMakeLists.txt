add_executable(eval
    main.c
    eval.c
)
ADD_DEFINITIONS(-g)
target_link_libraries(eval m)
