project(minishell LANGUAGES C)

# set(CMAKE_VERBOSE_MAKEFILE ON)

# add_compile_options(-g -fsanitize=address)
# add_link_options(-g -fsanitize=address)
add_compile_options(-g)
add_link_options(-g)

add_subdirectory(libft)
add_subdirectory(lib)
add_subdirectory(src)
add_subdirectory(test)
