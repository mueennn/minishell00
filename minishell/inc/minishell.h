/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rradin-m <rradin-m@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/13 15:21:42 by arimoham          #+#    #+#             */
/*   Updated: 2025/05/02 18:39:07 by rradin-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "../libft/libft.h"
# include "get_next_line.h"
# include <dirent.h>
# include <errno.h>
# include <readline/history.h>
# include <readline/readline.h>
# include <signal.h>
# include <sys/wait.h>
# include <termios.h>

# define READ_END 0
# define WRITE_END 1

extern int	g_exit_code;

typedef struct s_prompt
{
	t_list	*cmds;
	char	**envp;
	pid_t	pid;
}			t_prompt;

typedef struct s_mini
{
	char	**full_cmd;
	char	*full_path;
	int		infile;
	int		outfile;
}			t_mini;

enum		e_mini_error
{
	QUOTE = 1,
	NDIR = 2,
	NPERM = 3,
	NCMD = 6,
	DUPERR = 7,
	FORKERR = 8,
	PIPERR = 9,
	PIPENDERR = 10,
	MEM = 11,
	IS_DIR = 12,
	NOT_DIR = 13
};

/* ---- PARSING FUNCTIONS ---- */
/**
 * @brief Its a inbuilt function that replaces the current
 *			line in the readline buffer
 */
void		rl_replace_line(const char *text, int clear_undo);

/**
 * @brief Splits and validates command string into manageable 
 *       format for execution
 * @param out The command string to be validated
 * @param p Pointer to the prompt structure containing shell state
 * @return void* Status of the validation operation
 */
void		*validate_args(char *out, t_prompt *p);

/**
 * @brief Splits command and arguments into an array
 *			while handling quotes properly
 * @param s The input string containing command and arguments
 * @param set String containing characters to use as separators
 * @return char** Array of strings containing the split command and arguments
 */
char		**ft_cmd_trim(char const *s, char *set);

/**
 * @brief Modified split function that preserves
 *  			separators and handles quoted content
 * @param s The input string to split
 * @param set String containing characters to use as separators
 * @return char** Array of strings containing the split elements with separators
 */
char		**ft_cmdsubsplit(char const *s, char *set);

/**
 * @brief Removes all specified quotes from a string
 *
 * @param s1 The input string to be trimmed
 * @param squote Flag indicating if single quotes should be trimmed
 * @param dquote Flag indicating if double quotes should be trimmed
 * @return char* Trimmed string with specified quotes removed
 */
char		*ft_strtrim_all(char const *s1, int squote, int dquote);

/**
 * @brief Creates and fills command nodes for the shell's linked list structure
 *
 * @param args Array of command arguments to process
 * @param i Starting index in the args array
 * @return t_list* Linked list of command nodes
 */
t_list		*fill_nodes(char **args, int i);

/**
 * @brief Expands environment variables in a string when not inside quotes
 *
 * @param str The input string that may contain environment variables
 * @param i Starting index to begin expansion
 * @param quotes Array containing the quote state
 *			[0]=single_quote_state, [1]=double_quote_state
 
 * @param prompt Pointer to the prompt structure containing environment variables
 * @return char* String with environment variables expanded
 */
char		*expand_vars(char *str, int i, int quotes[2], t_prompt *prompt);

/**
 * @brief Expands tilde (~) to home directory path when not inside quotes
 *
 * @param str The input string that may contain tilde
 * @param i Starting index to begin expansion
 * @param quotes Array containing the quote state
 *			[0]=single_quote_state, [1]=double_quote_state
 * @param var The home directory path to substitute
 * @return char* String with tilde expanded to home directory
 */
char		*expand_path(char *str, int i, int quotes[2], char *var);

/**
 * @brief Handles heredoc input, reading from stdin until delimiter is found
 *
 * @param str Array of strings [0]=delimiter, [1]=optional
 * @param aux Auxiliary array for string manipulation
 * @return int Status of the heredoc operation
 */
int			get_here_doc(char *str[2], char *aux[2]);

/**
 * @brief Performs various checks on a command before execution
 *
 * @param prompt Pointer to the prompt structure containing shell state
 * @param cmd Linked list node containing the command to check
 * @param s Triple pointer typically used for path or environment variables
 * @param path String containing PATH information
 * @return DIR* Directory pointer if command is a directory, NULL otherwise
 */
DIR			*cmd_checks(t_prompt *prompt, t_list *cmd, char ***s, char *path);

/**
 * @brief Locates a command in the PATH environment variable
 *
 * @param env_path Array of directory paths from PATH environment variable
 * @param cmd Command name to locate
 * @param full_path Buffer to store the complete path if found
 * @return char* Full path to the command if found, NULL otherwise
 */
char		*find_command(char **env_path, char *cmd, char *full_path);

/* ---- EXECUTION FUNCTIONS ---- */

/**
 * @brief Executes a non-builtin command according 
 *       to the information in our list
 * @param prompt Pointer to the prompt structure containing shell state
 * @param cmd Linked list containing the command to be executed
 * @return void* Return status of the pipe operation
 */
void		*set_pipe(t_prompt *prompt, t_list *cmd);

/**
 * @brief Checks if conditions are met to perform a fork operation
 *
 * @param prompt Pointer to the prompt structure containing shell state
 * @param cmd Linked list containing the command to be executed
 * @param fd Array containing file descriptors for pipe communication
 * @return void* Status indicating whether fork should proceed
 */
void		*check_to_fork(t_prompt *prompt, t_list *cmd, int fd[2]);

/**
 * @brief Handles operations within the child process after fork
 *
 * @param prompt Pointer to the prompt structure containing shell state
 * @param cmd Linked list containing the command to be executed
 * @param fd Array containing file descriptors for pipe communication
 * @return void* Status of the child process execution
 */
void		*child_process(t_prompt *prompt, t_list *cmd, int fd[2]);

/**
 * @brief Performs fork operation and manages parent/child process execution
 *
 * @param prompt Pointer to the prompt structure containing shell state
 * @param cmd Linked list containing the command to be executed
 * @param fd Array containing file descriptors for pipe communication
 */
void		exec_fork(t_prompt *prompt, t_list *cmd, int fd[2]);

/**
 * @brief Executes a custom command and captures its output to a string
 *
 * @param out Triple pointer to store the command output
 * @param full Full command with path
 * @param args Command arguments
 * @param envp Environment variables array
 */
void		exec_custom(char ***out, char *full, char *args, char **envp);

/**
 * @brief Resolves a command name to its full path
 *			using PATH environment variable
 * @param prompt Pointer to the prompt structure containing shell state
 * @param start Linked list node containing the command
 * @param split_path Array of directories from PATH environment variable
 * @param path String containing the PATH environment variable
 */
void		get_cmd(t_prompt *prompt, t_list *start, char **split_path,
				char *path);

/* ---- BUILTIN FUNCTIONS ---- */

/**
 * @brief Implements the `env` shell command, which displays 
 *        the current environment variables or executes a command
 *        in the current environment.
 * @param prompt Pointer to the prompt structure containing shell state
 * @param cmd Linked list node containing command information
 * @return int Returns 0 on success, or error code on failure
 */
int			mini_env(t_prompt *prompt, t_list *cmd);

/**
 * @brief Executes a command following the `env` builtin with
 *        the current environment variables.
 * @param new_cmd Array of strings containing the command and arguments
 *               to execute (without the leading "env")
 * @return int Returns the exit status of the executed command
 */
int			exec_env_command(char **new_cmd);

/**
 * @brief Prepares a command array by skipping the first argument ("env")
 *        and copying the rest into a new array.
 * @param full_cmd The original command array including "env"
 * @return char** A newly allocated array containing just the command to
 *         execute, or NULL if memory allocation fails
 */
char		**prepare_command(char **full_cmd);

/**
 * @brief Handles execution of all builtin shell commands
 *
 * @param prompt Pointer to the prompt structure containing shell state
 * @param cmd Linked list containing the command to be executed
 * @param is_exit Pointer to integer flag that
 * 				will be set if exit command is called
 * @param n Current command index or execution context
 * @return int Return status of the executed builtin command
 */
int			builtin(t_prompt *prompt, t_list *cmd, int *is_exit, int n);

/**
 * @brief Checks if the first element in full_cmd is a builtin command
 *
 * @param n Pointer to the mini shell structure containing command information
 * @return int Returns 1 if command is a builtin, 0 otherwise
 */
int			is_builtin(t_mini *n);

/**
 * @brief C implementation of the cd (change directory) shell command
 *
 * @param prompt Pointer to the prompt structure containing shell state
 * @return int Returns 0 on success, non-zero value on failure
 */
int			mini_cd(t_prompt *prompt);

/**
 * @brief C implementation of the pwd (print working directory) shell command
 *
 * @return int Returns 0 on success, non-zero value on failure
 */
int			mini_pwd(void);

/**
 * @brief C implementation of the echo shell command
 *
 * @param cmd Linked list containing the echo command and its arguments
 * @return int Returns 0 on success, non-zero value on failure
 */
int			mini_echo(t_list *cmd);

/**
 * @brief C implementation of the export shell command
 *
 * @param prompt Pointer to the prompt structure containing shell state
 * @return int Returns 0 on success, non-zero value on failure
 */
int			mini_export(t_prompt *prompt);

/**
 * @brief Checks if a variable exists in the environment
 *
 * @param argv The variable name to check for
 * @param envp Array of environment variables
 * @param ij Array containing indices [i,j] for tracking position
 * @return int Returns index of matching variable if found, or
 * 					in environment appropriate status code
 */
int			var_in_envp(char *argv, char **envp, int ij[2]);

/**
 * @brief Implements the `unset` shell command, which removes environment
 *        variables from the shell's environment.
 * @param prompt A pointer to the `t_prompt` structure, which contains
 *               the shell's state and environment variables.
 * @return Returns 0 on success, or a non-zero value if an error occurs.
 */
int			mini_unset(t_prompt *prompt);

/**
 * @brief Handles the "exit" shell command to terminate the shell.
 * @param cmd A pointer to a t_list structure representing
 * the command and its arguments.
 * @param is_exit A pointer to an integer that will be set to indicate whether
 *             the shell should exit (non-zero value) or continue (zero value).
 * @return An integer representing the exit status of the shell. Typically, 0
 *         indicates success, while non-zero values indicate errors or specific
 *         exit codes.
 */
int			mini_exit(t_list *cmd, int *is_exit);

/* ---- I/O REDIRECTION FUNCTIONS ---- */

/**
 * @brief Opens two sets of pipes and verifies if they are opened correctly.
 * @param fd An array of two integers representing
 * 			the file descriptors for the pipes.
 *           fd[0] is typically used for reading, and fd[1] is used for writing.
 * @return A pointer to a resource or structure related to the opened pipes, or
 *         NULL in case of an error.
 */
void		*mini_here_fd(int fd[2]);

/**
 * @brief Opens a file and associates it with a file descriptor.
 * @param oldfd The existing file descriptor to be replaced, or -1 if a new
 *              file descriptor should be created.
 * @param path The path to the file to be opened.
 * @param flags An array of two integers:
 *              - flags[0]: The access mode flags
 * 					(e.g., O_RDONLY, O_WRONLY, O_RDWR).
 *              - flags[1]: The permission flags (e.g., S_IRUSR, S_IWUSR).
 * @return The new or replaced file descriptor on success, or -1 on failure.
 */
int			get_fd(int oldfd, char *path, int flags[2]);

/**
 * @brief Opens the appropriate file for writing in the case of a single
 * redirection operator ('>') and updates the node with the file descriptor.
 * @param node Pointer to the current t_mini node structure.
 * @param args Array of command-line arguments.
 * @param i Pointer to the index of the current argument being processed.
 * @return Pointer to the updated t_mini node structure.
 * @note This function assumes that the arguments array contains valid
 * redirection syntax and handles only the '>' case.
 */
t_mini		*get_outfile1(t_mini *node, char **args, int *i);

/**
 * @brief Opens or creates a file for appending output (>> redirection case).
 * @param node A pointer to the current t_mini node structure.
 * @param args An array of strings containing the command-line arguments.
 * @param i A pointer to an integer representing the current index in args.
 *          This index will be updated as the function processes the arguments.
 * @return A pointer to the updated t_mini node structure,
 * 			or NULL if an error occurs.
 */
t_mini		*get_outfile2(t_mini *node, char **args, int *i);

/**
 * @brief Tries to open the appropriate file
 *        as the input file (in the case of '<' redirection).
 * @param node A pointer to the current node in the shell's command structure.
 * @param args An array of arguments,
 * where the file name for input redirection is specified.
 * @param i A pointer to the index of the current argument being processed.
 *          This indexwill be updated as the function processes
 *          the input redirection.
 * @return A pointer to the updated node in the shell's command structure.
 */
t_mini		*get_infile1(t_mini *node, char **args, int *i);

/**
 * @brief Tries to open and read a heredoc as an input file
 *      (handles the << case).
 * @param node A pointer to the current t_mini node where the infile will be set.
 * @param args Array of command arguments,
 *            including the heredoc operator and its content.
 * @param i pointer to the current index in the args array,
 * 				which will be updated.
 * @return pointer to the updated t_mini node with the infile set,
 *         or NULL on failure.
 */
t_mini		*get_infile2(t_mini *node, char **args, int *i);

/* ---- UTILITY FUNCTIONS ---- */

/**
 * @brief Prints a custom error message to standard error.
 * @param err_type The type of error to be printed.
 * @param param A string parameter providing additional context for the error.
 * @param err An integer error code to be included in the message.
 * @return A pointer to the error object or NULL,
 * 		depending on the implementation.
 */
void		*mini_perror(int err_type, char *param, int err);

/**
 * @brief Retrieves the value of an environment variable.
 * @param var The name of the environment variable to retrieve.
 * @param envp The environment array (typically passed to main as `envp`).
 * @param n The maximum number of characters to consider for the variable name.
 * @return A pointer to a malloc-allocated string containing the value of
 *         the environment variable, or NULL if the variable is not found.
 */
char		*mini_getenv(char *var, char **envp, int n);

/**
 * @brief Sets a new environment variable or updates an existing one.
 * @param var The name of the environment variable to set or update.
 * @param value The value to assign to the environment variable.
 * @param envp The current environment array.
 * @param n The number of elements in the current environment array.
 * @return A new array of strings representing the updated environment.
 */
char		**mini_setenv(char *var, char *value, char **envp, int n);

/**
 * @brief Generates a string to be used as the prompt for the readline function.
 * @param prompt A structure of type t_prompt containing the necessary
 * 				information to construct the command prompt string.
 * @return A dynamically allocated string representing the command prompt.
 *         The caller is responsible for freeing the returned string.
 */
char		*get_cmd_prompt(t_prompt prompt);

/**
 * @brief Frees all elements in linked list nodes.
 * @param content Pointer to the content of the linked list node to be freed.
 */
void		free_content(void *content);
int			safe_close(int fd);
void		close_all_fds(int *keep_open, int max_fd);

/**
 * @brief Handles the SIGINT signal for the main process.
 *
 * This function is designed to handle the SIGINT signal (typically triggered
 * by pressing Ctrl+C) in the main process. It ensures that the program
 * responds appropriately to the signal, such as cleaning up resources or
 * interrupting the current operation.
 *
 * @param sig The signal number (expected to be SIGINT).
 */
void		handle_sigint(int sig);

/**
 * @brief Handles the SIGQUIT(ctrl+\), SIGTSTP(ctrl+z), SIGINT(ctrl+c)
 *        signal for the main process.
 */
void		handle_signals(void);
/**
 * @brief Checks for errors and determines if the first argument is a directory.
 * @param str A double pointer to an array of two strings. The first string
 *            is the target to check, and the second string may contain
 *            additional information or context.
 */
void		cd_error(char **str[2]);

/**
 * @brief Frees a dynamically allocated array of strings.
 * @param m A pointer to a pointer to the array of strings to be freed.
 */
void		ft_free_array(char ***m);

/**
 * @brief Duplicates an array of strings.
 * @param m The array of strings to duplicate. The array must be
 *          NULL-terminated.
 * @return A pointer to the newly allocated duplicate array of strings,
 *         or NULL if memory allocation fails.
 * @note The caller is responsible for freeing the returned array and
 *       its strings to avoid memory leaks.
 */
char		**ft_array_dup(char **m);

/**
 * @brief Adds a new string to an array of strings.
 * @param in The original array of strings. This array must be NULL-terminated.
 *           If NULL, a new array will be created containing only the new string.
 * @param newstr The string to add to the array. This string must not be NULL.
 * @return A new NULL-terminated array of strings containing the original strings
 *         and the new string. Returns NULL if memory allocation fails.
 * @note The caller is responsible for freeing the returned array & its contents.
 */
char		**ft_extend_array(char **in, char *newstr);

/**
 * @brief Counts the occurrences of a specific character in a given string.
 * @param s The string in which to count occurrences of the character.
 * @param c The character to count within the string.
 * @return int The number of times the character appears in the string.
 */
int			ft_countchar(char *s, char c);

/**
 * @brief Prints an array of strings to a specified file descriptor.
 * @param m The array of strings to be printed. Each string in the array
 *          will be printed in order.
 * @param nl If non-zero,
	a newline character will be appended after each string.
 * @param fd The file descriptor to which the strings will be written.
 * @return Returns 0 on success, or a negative value on failure.
 */
int			ft_put_array_fd(char **m, int nl, int fd);

/**
 * @brief Finds first occurrence of any character from a given set in a string.
 * @param s The input string to search.
 * @param set The set of characters to look for in the input string.
 * @return The index of the first occurrence of any character from `set` in `s`,
 *         or -1 if no match is found.
 */
int			ft_strchars_i(const char *s, char *set);

/**
 * @brief Checks if a character is a whitespace character.
 * @param c The character to check.
 * @return Non-zero value if the character is a whitespace, 0 otherwise.
 */
int			ft_isspace(char c);

/**
 * @brief Finds the index of the first occurrence of a character in a string.
 * @param s The string to search in.
 * @param c The character to search for (interpreted as an unsigned char).
 * @return The index of the first occurrence of the character in the string,
 *         or -1 if the character is not found.
 */
int			ft_strchr_i(const char *s, int c);

/**
 * @brief Get the length of a null-terminated array of strings.
 * @param m A pointer to the null-terminated array of strings.
 * @return The number of elements in the array (excluding the null terminator).
 */
int			ft_arraylen(char **m);

/**
 * @brief Replaces elements in a 2D array with elements from another array.
 * @param big A pointer to the 2D array where elements will be replaced.
 * @param small A 2D array containing the replacement elements.
 * @param n The number of elements to replace in the `big` array.
 * @return A pointer to the modified `big` array, or NULL if an error occurs.
 */
char		**ft_array_replace_in(char ***big, char **small, int n);

/**
 * @brief Checks if the given string is a valid identifier.
 * @param str The string to be checked.
 * @return int Returns 1 if the string is a valid identifier,
 *         otherwise returns 0.
 */
int			is_valid_identifier(char *str);

#endif