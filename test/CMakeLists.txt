set(NAME test)

add_executable(${NAME}
	test_lexer.c
	test_parser.c
	test_expand.c
)

target_link_libraries(${NAME} PRIVATE ft)
target_link_libraries(${NAME} PRIVATE minishell_utils)
target_link_directories(${NAME} PRIVATE /Users/fsnelder/.brew/lib)
target_include_directories(${NAME} PRIVATE /Users/fsnelder/.brew/include)
target_link_libraries(${NAME} PRIVATE criterion)
