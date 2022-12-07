set(NAME minishell_utils)

add_library(${NAME}
	utils.c
	./lexer/lexer.c
	./lexer/lexer_utils.c
	./lexer/lexer_parse_functions.c
	./parser/parser.c
	"./string/ft_string.c"
	./expander/expand.c
	./executor/executor.c
)

target_compile_options(${NAME} PRIVATE -Werror -Wall -Wextra)
target_compile_options(${NAME} PRIVATE -Wno-unused -Wno-unused-parameter) # TODO: remove

target_include_directories(${NAME} PUBLIC ../include)

target_link_libraries(${NAME} PUBLIC readline)
target_include_directories(${NAME} PUBLIC $ENV{HOME}/.brew/opt/readline/include)
target_link_directories(${NAME} PUBLIC $ENV{HOME}/.brew/opt/readline/lib)
target_link_libraries(${NAME} PRIVATE ft)
