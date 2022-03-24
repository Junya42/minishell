/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmarouf <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/24 16:02:19 by cmarouf           #+#    #+#             */
/*   Updated: 2022/03/24 02:02:47 by anremiki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <errno.h>
# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <fcntl.h>
# include <sys/types.h>
# include <string.h>
# include <sys/wait.h>
# include <signal.h>
# include <dirent.h>
# include "../libft/libft.h"
# include "../gnl/get_next_line.h"

extern t_list	*g_sglt;

typedef struct s_core
{
	char	*tilde;
	char	*tmp;
	int		i;
	int		checker;
	int		ok;
}			t_core;

typedef struct s_wild
{
	int	i;
	int	j;
	int	checker;
}			t_wild;

typedef struct s_child
{
	pid_t	pid;
	int		fd;
	char	**cmd;
	char	*path;
	char	*command;
}			t_child;

typedef struct s_export
{
	int		i;
	int		check;
	char	*ptr;
	int		exit;
	t_list	*tmp;
}			t_export;

typedef struct s_exit
{
	char	**argument;
	int		len;
	int		error;
}				t_exit;

typedef struct s_data
{
	char	*cpath;
	int		child;
	char	*buffer;
	char	**lexer;
	char	*path;
	char	**splittedpath;
	char	*tmppath;
	char	**hope;
	char	**split;
	int		handler;
	int		size;
	int		total;
	int		checker;
	int		safe;
	int		current;
	int		free;
	int		*fd;
	char	*exit_code;
}				t_data;

typedef struct s_parse
{
	pid_t	doc;
	char	*var;
	char	*non_var;
	char	*str;
	char	*aimenv;
	char	*begin;
	int		quote;
	int		dquote;
	int		valid;
	int		i;
	int		k;
}				t_parse;

typedef struct s_redir
{
	int		i;
	int		start;
	char	*final_str;
	char	*temp;
}			t_redir;

typedef struct s_clear
{
	t_data	*data;
	t_pipe	*pipe;
	t_list	**tenv;
	int		do_free;
	int		first;
}			t_clear;

/* PROMPT */
void	upgrade(t_data *data);
char	*choose_prompt(t_clear *clear);
char	*prompt_shell(void);
char	*prompt_sshell(void);
char	*prompt_path(char *line);
char	*prompt_spath(char *line);
char	*get_time(t_clear *clear);
int		check_malloc(char *line, char *ptr);
char	*prompt_time(char *line, char *time);
char	*prompt_stime(char *line, char *time);
char	*check_prompt(t_clear *clear);
char	*join_prompt(char *s1, char *s2);
/* PROMPT */

/* UTILS FONCTION */
void	choose_redir(t_list *lexer, t_dir *redir);
char	*skip_firstwild(char *str);
void	check_colors(t_pipe *elem);
char	*first_wild(char *str);
int		check_wildcard(char	*find);
char	*arg(char *s1, char *cmd);
int		ischarset(char *str, char *set);
t_pipe	*elem_init(void);
void	defaultcmd(t_data *data, t_list **tenv, t_pipe *ptr, t_clear *clear);
int		choose_cmd(t_data *data, t_clear *clear, t_list **tenv, t_pipe *ptr);
void	pipe_loop(t_data *data, t_clear *clear, t_list **tenv, t_pipe *ptr);
void	create_fd(t_pipe *pipe, t_list **tenv, t_data *data, t_clear *clear);
void	do_cmd(t_pipe *pipes, t_list **tenv, t_data *data, t_clear *clear);
t_data	*datalloc(void);
t_clear	*clearalloc(t_list **tenv, t_data *data);
void	printpipe(t_pipe *pipe);
void	clean_loop(int *fd, int total);
void	print_exit(t_pipe *ptr, t_data *data, t_list **tenv, t_clear *clear);
int		update_current(t_data *data, int i);
void	init_var_pipe(t_data *data);
void	clean_lex(t_list *lex);
void	reset_ok(t_data *data, t_pipe *pipes);
void	reset_error(t_data *data, t_pipe *pipes, t_list **tenv, t_clear *clear);
int		*pipefd(int *fd, int i, int total);
char	*free_and_return_null(t_redir *redir);
void	free_all(char **cmd, char *command, char *path);
void	free_all_bis(char **cmd, char *command, char *path, int fd);
char	**ft_split(char const *s);
char	**ft_split_path(char const *s, char c);
char	*ft_strjoin(char *s1, char *s2);
char	*ft_strjoinspace(char *s1, char *s2);
char	*ft_strjoinspace2(char *s1, char *s2);
char	*ft_strjoinspace3(char *s1, char *s2, int space);
char	*ft_strjoin2(char *s1, char *s2);
char	*ft_strjoin3(char *s1, char *s2);
char	*ft_strjoin4(char *s1, char *s2);
char	*get_tenv(t_list **tenv, char *var);
char	*get_tenv2(t_list **tenv, char *var, t_parse *parse);
int		ft_strcmp(char *s1, char *s2);
int		asciistrcmp(char *s1, char *s2);
int		array_size(char **arr);
void	put_error(char *s1, char *s2, char *s3);
int		put_errorint(char *s1, char *s2, char *s3);
void	put_error_bis(DIR *dir, char *s2, char *s3, t_data *data);
char	*r_error(char *s1, char *s2, char *s3);
int		ft_strstr(char *str, char *to_find);
int		ualready_exist(char *content, char *str);
int		already_exist(char *content, t_list *tenv);
void	ft_putstr(char *str);
void	ft_lstadd_new(t_list **alst, void *content);
void	ft_lstadd_mnew(t_list **alst, void *content);
void	ft_lst_remove_if(t_list **tenv, char *content);
t_list	**create_list(char **env);
int		ft_getlen(char *str, int status);
int		is_charset2(char const *str, char charset);
int		is_charset(char i, char c);
void	free_array(char **ptr);
t_pipe	*freepipe(t_pipe *pipe, int flag);
void	signalhandler(void);
void	sigchild(void);
void	sigcallhandler(void);
void	ignoresignals(void);
t_pipe	*pipe_init(t_list *lexer, int size, t_list **tenv);
int		sizepipe(char *str);
t_list	**sglt(void);
char	*treat_pipe(char *str);
void	read_atty(int fd, t_data *data, t_clear *clear, char *cmd);
void	atty_error(t_data *data, DIR *dir, char	*command, t_clear *clear);
void	exit_error(t_list *lex, t_data *data, t_list **tenv, t_clear *clear);
void	free_and_unlink(t_pipe *pipe);
void	free_assign_null(char *str);
int		do_export(char **cnt, t_list **tenv, t_data *data, t_export *export);
int		already_exist(char *content, t_list *tenv);
int		checker(char *s1, char *s2);
char	*cmds_to_cmd(char **cmd);

/* BUILT_IN */
void	built_in_cd(char *path, t_list **tenv, t_data *data, int code);
void	built_in_pwd(t_data *data, int code);
void	built_in_env(t_list *tenv, char *argument, t_data *data, int code);
void	built_in_export(t_list **tenv, t_list *lex, t_data *data, int code);
void	built_in_export_bis(t_list **tenv, char *str, t_data *data, int code);
void	built_in_unset(t_list **tenv, t_list *lex, t_data *data, int code);
void	built_in_echo(t_list *lex, int fd, t_data *data, int code);
void	built_in_exit(t_data *data, t_list **tenv, t_clear *clear, int flag);
/* BUILT_IN */

/* PARSING */
void	back_to_normal(char **lexer);
char	**ft_wipe(char **res);
int		gather_input(t_data *data, t_list **tenv, t_clear *clear, int flag);
int		is_built_in(char *command);
char	*parsing(char *str, t_list **tenv, t_data *data);
char	*trim_quotes(char *str, t_parse *parse);
void	parse_dollard(char *cmd, t_parse *parse, t_list **tenv, t_data *data);
char	*handle_dollard(char *str, t_parse *parse, t_list **tenv, t_data *data);
char	*handle_quotes(char *str, t_parse *parse);
int		parse_redir(char **cmd);
int		check_nothing(char *str);
char	*check_redirs(char *str);
char	**check_pipe(char **cmd);
int		alone_dollard(char *cmd);
int		check_quotes(char *str, int len);
int		unclosed_quote(char *str, int len);
int		unclosed_dquote(char *str, int len);
int		unclosed_dquote_d(char *str, int len);
int		re_check_quotes(char *str, char charset);
char	*smart_transform(char *str);
int		no_redir_str(char *cmd);
char	*in_quote_redir(char *str);
char	*fix_quotes(char *str, int i, int j);
int		error_parsing(t_data *data, int flag);
char	*joinfile(char *s1, char *s2);
int		no_equal(char *str);
char	*add_equal(char *str);
void	check_tilde(t_core *c, t_list **lexer);
void	add_dir(t_core *c, t_list **lexer, t_pipe *elem);
void	add_elem(t_pipe *elem, t_pipe **ptr, t_list **lexer);
/* PARSING */

/* EXEC */
void	pid_child(char *path, char **cmd, t_clear *c, int i);
void	read_child_process(t_child *c, t_clear *clear, int i, int x);
char	*build_path(char *newpath, char **allpath, char *command, t_clear *c);
char	*build_path_2(char *newpath, char **allpath, char *command, t_clear *c);
int		get_child(t_data *data, t_list **tenv, t_clear *clear);
int		exec_cmd(char *absolute_path, char **command, char **hope, t_clear *c);
void	exec_built_in(t_data *data, t_clear *c, t_list **tenv, t_pipe *ptr);
void	exec_built_in2(t_data *data, t_clear *c, t_list **tenv, t_pipe *ptr);
void	exec_built_in3(t_clear *clear, char **cmd, char *command);
int		make_redir(t_pipe *pipe, char *error, t_data *data);
void	make_heredoc(t_dir *dir, t_list **tenv, t_data *data, t_clear *clear);
int		which_std(t_dir *dir);
int		which_open(t_dir *dir, char *target);
char	*which_redir(t_dir *dir);
void	read_error(char *s1, char *s2, char *s3, char *error);
void	read_child(char *file, t_data *data, int i, t_clear *clear);
void	child_error(t_data *data, char *error, t_clear *clear, char *command);
char	*fd_name(void);
void	wait_process(t_data *data, int memory, int check, int status);
void	clean_loop(int *fd, int total);
void	atty_error(t_data *data, DIR *dir, char *command, t_clear *clear);
char	*parse_atty(char *cmd, t_data *data, t_list **tenv);
char	*cmds_to_cmd(char **cmd);
int		update_current(t_data *data, int i);
int		errno_check(void);
int		check_cmdpath(char *absol, t_pipe *pipe);
/* EXEC */

/* BONUS */
char	*wildcard(char	*find, int i);
int		explorer(char *find, char *curr);
int		check_last(char	*find, char *curr);
int		check_wild(char *find);
int		skip_wild(char *find, int i);
int		check_empty(char *find);

void	sigdoc(void);
void	sigchild(void);
void	exitdoc(t_data *ata, t_list **tenv, t_clear *clear, int flag);
void	sglt_ci(void *content);
void	clear_doc(void);
void	lst_remove_clear(void);
char	*handle_dollard_2(char *str, t_parse *p, t_list **tenv, t_data *data);
char	*get_tenv3(t_list **tenv, char *var, t_parse *parse);

#endif 
