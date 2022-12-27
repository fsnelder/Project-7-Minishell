# Project-7-Minishell

The seventh project is creating a (mini) version of the shell.
The program must handle the following thins:

-  ’ (single quote) which should prevent the shell from interpreting the metacharacters in the quoted sequence.
•  " (double quote) which should prevent the shell from interpreting the metacharacters in the quoted sequence except for $ (dollar sign) 
• Implement redirections:
◦ < should redirect input.
◦ > should redirect output.
◦ << should be given a delimiter, then read the input until a line containing the delimiter is seen. However, it doesn’t have to update the history!
◦ >> should redirect output in append mode.
• Implement pipes (| character). The output of each command in the pipeline is connected to the input of the next command via a pipe.
• Handle environment variables ($ followed by a sequence of characters) which should expand to their values.
• Handle $? which should expand to the exit status of the most recently executed foreground pipeline.
• Handle ctrl-C, ctrl-D and ctrl-\ which should behave like in bash.
• In interactive mode:
◦ ctrl-C displays a new prompt on a new line.
◦ ctrl-D exits the shell.
◦ ctrl-\ does nothing.
• The shell must implement the following builtins:
◦ echo with option -n
◦ cd with only a relative or absolute path
◦ pwd with no options
◦ export with no options
◦ unset with no options
◦ env with no options or arguments
◦ exit with no options

Thanks to my Minishell-partner https://github.com/mraasvel , I also learned the basics on CMake, Dockerfiles, Systemtesting and proper (header)file-management in larger projects.
