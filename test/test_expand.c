#include "parser.h"
#include "lexer.h"
#include "util.h"
#include "ft_string.h"
#include "expand.h"
#include <criterion/criterion.h>

const char *FAKE_ENVIRONMENT[] = {
	"variable=value",
	"TEST_PROGRAM_ACTUAL=unexpected",
	"TEST_PROGRAM=expected",
	NULL
};

t_string do_expand(const char* word)
{
	return expand_word(word, ft_strlen(word), FAKE_ENVIRONMENT);
}

Test(single_quote, expander) {
	t_string s = do_expand("'abc'");
	cr_assert(strcmp(string_cstr(&s), "abc") == 0);
	string_destroy(&s);
}

Test(double_quotes, expander) {
	t_string s = do_expand("\"abc\"");
	cr_assert(strcmp(string_cstr(&s), "abc") == 0);
	string_destroy(&s);
}

Test(variable, expander) {
	t_string s = do_expand("$variable");
	cr_assert(strcmp(string_cstr(&s), "value") == 0);
	string_destroy(&s);
}

Test(basic, expander) {
	t_string s = do_expand("abc");
	cr_assert(strcmp(string_cstr(&s), "abc") == 0);
	string_destroy(&s);
}

Test(var_in_quote, expander) {
	t_string s = do_expand("'$shouldnotexpand'");
	cr_assert(strcmp(string_cstr(&s), "$shouldnotexpand") == 0);
	string_destroy(&s);
}

Test(no_following, expander) {
	t_string s = do_expand("$");
	cr_assert(strcmp(string_cstr(&s), "$") == 0);
	string_destroy(&s);
}

Test(exit_code, expander) {
	t_string s = do_expand("$?");
	cr_assert(strcmp(string_cstr(&s), "0") == 0);
	string_destroy(&s);
}

Test(non_existing_variable, expander) {
	t_string s = do_expand("$doesntexist");
	cr_assert(strcmp(string_cstr(&s), "") == 0);
	string_destroy(&s);
}

Test(combined_words, expander) {
	t_string s = do_expand("$doesntexist'abcd'$variable \"$variable\"");
	cr_assert(strcmp(string_cstr(&s), "abcdvalue value") == 0);
	string_destroy(&s);
}

Test(combined_words_2, expander) {
	t_string s = do_expand("1234\"$variable test\"'abcde'abcd$?");
	cr_assert(strcmp(string_cstr(&s), "1234value testabcdeabcd0") == 0);
	string_destroy(&s);
}

Test(overlapping_variable_name, expander) {
	t_string s = do_expand("$TEST_PROGRAM");
	cr_assert(strcmp(string_cstr(&s), "expected") == 0);
	string_destroy(&s);
}
