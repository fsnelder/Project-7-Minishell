set(NAME minishell)

add_executable(${NAME}
	main.c
)

target_compile_options(${NAME} PRIVATE -Werror -Wall -Wextra)
target_compile_options(${NAME} PRIVATE -Wno-unused -Wno-unused-parameter) # TODO: remove

target_link_libraries(${NAME} PRIVATE minishell_utils)
target_link_libraries(${NAME} PRIVATE ft)
