First the input string given by the user is parsed.

The parsing is pipe-separated i.e. my parser will output tokens in a string, in the order they were given by the user but just without the intermediate pipes.

Then a vector of strings is formed where all the tokens are pushed.

Then each token is iterated over and passed to execute function which performs the required task.

Functionalities implemented

1.	shell built in
2.	other commands using execvp
3.	Pipes between various commands
4.	Input Output Redirection
5. 	! operator
6.	history command
