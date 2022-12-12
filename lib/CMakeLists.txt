set(NAME minishell_utils)

add_library(${NAME}
	utils.c
	utils2.c
	./lexer/lexer.c
	./lexer/lexer_utils.c
	./lexer/lexer_parse_functions.c
	./parser/parser.c
	./parser/parse_files.c
	./parser/parser_utils.c
	./parser/parse_word_pipe.c
	"./string/ft_string.c"
	"./string/ft_string_2.c"
	./expander/expand.c
	./expander/expander_expand_functions.c
	./expander/expand_word_token.c
	./executor/executor.c
	./executor/heredoc.c
	./builtins/ft_cd.c
	./builtins/ft_echo.c
	./builtins/ft_env.c
	./builtins/ft_exit.c
	./builtins/ft_export.c
	./builtins/ft_pwd.c
	./builtins/ft_unset.c
	./environment/environment.c
	./environment/environment_utils.c
	./environment/environment_utils2.c
	./expander/expand_command.c
	./executor/execute_builtins.c
	./executor/execute_pipe.c
	./executor/execute_redirections.c
	./executor/execute_command.c
	./executor/execute_std.c
	./executor/heredoc_expand.c
)

target_compile_options(${NAME} PRIVATE -Werror -Wall -Wextra)
target_compile_options(${NAME} PRIVATE -Wno-unused -Wno-unused-parameter) # TODO: remove

target_include_directories(${NAME} PUBLIC ../include)

target_link_libraries(${NAME} PUBLIC readline)
target_include_directories(${NAME} PUBLIC $ENV{HOME}/.brew/opt/readline/include)
target_link_directories(${NAME} PUBLIC $ENV{HOME}/.brew/opt/readline/lib)
target_link_libraries(${NAME} PRIVATE ft)
