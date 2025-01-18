# minishell
Well, that's a minishell.
## About minishell
**minishell** is a stripped-down version of POSIX shell.
<br>
It's a student project in a *42 School*.
<br>
<br>
minishell implements only a ***subset of the POSIX shell standard***.

## Differences from bash
Things that are different from bash (however compilant with *subject.pdf*):
* Exit codes in case of syntax errors.
* Error messages.
* Child process spawning (that's also the reason why "$ cat | cat | ls"
    works differently).

## Final score
**101/100**, as of December 17th, 2024.
