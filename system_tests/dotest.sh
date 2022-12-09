MINISHELL=../debug/src/minishell

FAIL='\033[91m'
PASS='\033[32m'
ENDC='\033[0m'

testcase() {
	echo "Executing: $@"
	echo "$@" | bash &> bash.txt
	bash_code=$?
	echo "$@" | $MINISHELL &> minishell.txt
	minishell_code=$?
	# remove first and last line
	tail -n+2 minishell.txt | sed '$d' > minishell.txt.cp
	mv minishell.txt.cp minishell.txt
	cmp -s bash.txt minishell.txt
	if [ "$?" != 0 ]
	then
		echo -e "[ $FAIL FAIL $ENDC ]: $@: output differs"
		echo "-- TEST CASE $@ --" >> result.log
		echo "-- Bash: --" >> result.log
		cat bash.txt >> result.log
		echo >> result.log
		echo "-- Minishell: --" >> result.log
		cat minishell.txt >> result.log
		echo >> result.log
		echo "-- Diff: --" >> result.log
		diff minishell.txt bash.txt >> result.log
		echo >> result.log
	else
		if [ "$bash_code" != "$minishell_code" ]
		then
			echo -e "[ $FAIL FAIL $ENDC ]: $@: non matching exit code: got($minishell_code) expected($bash_code)"
		else
			echo -e "[ $PASS PASS $ENDC ]"
		fi
	fi
}

echo > result.log
testcase echo 1234
testcase echo '$USER'
testcase echo '-n 1 2 3'
testcase exit 1 2 3
testcase exit $?
testcase exit 5 a 2
testcase 'cat Makefile | grep bla | more'
testcase 'filethatdoesntexist | grep bla | more'
testcase kaas >> Makefile
testcase echo '"$PWD"'
testcase pwd
testcase expr $? + $?
testcase ls
testcase echo "cat lol.c | cat > lol.c" 
testcase unset '$USER'
testcase ls ../../..
testcase dsbksdgbksdghsd
testcase $?
testcase echo -
