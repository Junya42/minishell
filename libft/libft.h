/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmarouf <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/08 23:35:16 by cmarouf           #+#    #+#             */
/*   Updated: 2022/03/17 17:37:47 by anremiki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_H
# define LIBFT_H

# include <unistd.h>
# include <stdlib.h>
# include <stdio.h>

//Fonction de la partie 1
int		ft_isalpha(int c);
int		ft_isdigit(int c);
int		ft_isascii(int c);
int		ft_isprint(int c);
int		ft_isalnum(int c);

int		ft_toupper(int c);
int		ft_tolower(int c);

int		ft_strncmp(const char *s1, const char *s2, size_t n);
int		doc_strncmp(const char *s1, const char *s2, size_t n);
int		ft_memcmp(const void *s1, const void *s2, size_t n);
int		ft_atoi(const char *nptr);

size_t	ft_strlen(const char *s);
size_t	ft_strlcpy(char *dst, const char *src, size_t size);
size_t	ft_strlcat(char *dst, const char *src, size_t size);
char	*ft_strcat(char *dest, char *src);

void	*ft_memset(void *s, int c, size_t n);
void	*ft_memcpy(void *dest, const void *src, size_t n);
void	*ft_memmove(void *dest, const void *src, size_t n);
void	*ft_memchr(const void *s, int c, size_t n);
void	*ft_calloc(size_t nmemb, size_t size);

void	ft_bzero(void *s, size_t n);

char	*ft_strdup(const char *s);
char	*ft_strchr(const char *s, int c);
char	*ft_strrchr(const char *s, int c);
char	*ft_strnstr(const char *big, const char *little, size_t len);

//Fonction de la partie 2
char	*ft_substr(char const *s, unsigned int start, size_t len);
char	*ft_strtrim(char const *s1, char const *set);

char	*ft_itoa(int n);
char	*ft_strmapi(char const *s, char (*f)(unsigned int, char));

void	ft_striteri(char *s, void (*f)(unsigned int, char*));

void	ft_putchar_fd(char c, int fd);
int		ft_putstr_fd(char *s, int fd);
void	ft_putendl_fd(char *s, int fd);
void	ft_putnbr_fd(int n, int fd);

//fonction bonus
typedef struct s_list
{
	void			*content;
	void			*next;
}					t_list;

typedef struct s_dir
{
	void	*in;
	void	*out;
	void	*app;
	void	*doc;
	char	*name;
	void	*next;
}			t_dir;

typedef struct s_pipe
{
	void	*cmd;
	void	*content;
	void	*bin;
	void	*next;
	t_list	*lex;
	t_dir	*dir;
	int		safe;
	int		total;
}			t_pipe;

t_dir	*ft_dirnew(void);
t_list	*ft_lstnew(void *content);
t_list	*ft_lstmnew(void *content);
t_dir	*ft_dirlast(t_dir *lst);
t_list	*ft_lstlast(t_list *lst);
t_pipe	*ft_pipelast(t_pipe *lst);
t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *));
t_list	*ft_lstrevsplit(char **str);

void	ft_lstadd_front(t_list **alst, t_list *new);
void	ft_lstadd_back(t_list **alst, t_list *new);
void	ft_diradd_back(t_dir **alst, t_dir *new);
void	ft_pipeadd_back(t_pipe **alst, t_pipe *new);
void	ft_lstdelone(t_list *lst, void (*del)(void*));
void	ft_lstdelone2(t_list *lst, void (*del)(void*));
void	ft_lstclear(t_list **lst, void (*del)(void *));
void	ft_lstclear2(t_list **lst, void (*del)(void *));
void	ft_lstiter(t_list *lst, void (*f)(void *));

int		ft_lstsize(t_list *lst);
char	**ft_lstsplit(t_list **lst);
char	**ft_lstsplit_dup(t_list **lst);

#endif
