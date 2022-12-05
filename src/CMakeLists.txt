set(NAME minishell)

add_executable(${NAME}
	main.c
	utils.c
	./lexer/lexer.c
)

target_compile_options(${NAME} PRIVATE -Werror -Wall -Wextra)
target_compile_options(${NAME} PRIVATE -Wno-unused -Wno-unused-parameter) # TODO: remove

target_link_libraries(${NAME} PRIVATE readline)
target_include_directories(${NAME} PRIVATE ../include)
target_include_directories(${NAME} PRIVATE $ENV{HOME}/.brew/opt/readline/include)
target_link_directories(${NAME} PRIVATE $ENV{HOME}/.brew/opt/readline/lib)
target_link_libraries(${NAME} PRIVATE ft)
