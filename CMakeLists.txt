project(minishell LANGUAGES C)

# set(CMAKE_VERBOSE_MAKEFILE ON)

# add_compile_options(-g -fsanitize=address)
# add_link_options(-g -fsanitize=address)

add_subdirectory(libft)
add_subdirectory(src)
