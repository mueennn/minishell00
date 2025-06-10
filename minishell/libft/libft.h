/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rradin-m <rradin-m@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/06 15:58:09 by rradin-m          #+#    #+#             */
/*   Updated: 2025/02/07 17:59:03 by rradin-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_H
# define LIBFT_H

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <limits.h>
# include <stdint.h>

typedef struct s_list
{
	void			*content;
	struct s_list	*next;
}	t_list;

/* @brief libft Function*/
int		ft_atoi(const char *str);
/* @brief libft Function*/
void	ft_bzero(void *s, size_t n);
/* @brief libft Function*/
void	*ft_calloc(size_t count, size_t size);
/* @brief libft Function*/
int		ft_isalnum(int c);
/* @brief libft Function*/
int		ft_isalpha(int c);
/* @brief libft Function*/
int		ft_isascii(int c);
/* @brief libft Function*/
int		ft_isdigit(int c);
/* @brief libft Function*/
int		ft_isprint(int c);
/* @brief libft Function*/
void	*ft_memchr(const void *s, int c, size_t n);
/* @brief libft Function*/
int		ft_memcmp(const void *s1, const void *s2, size_t n);
/* @brief libft Function*/
void	*ft_memcpy(void *dest, void const *src, size_t n);
/* @brief libft Function*/
void	*ft_memmove(void *dest, const void *src, size_t n);
/* @brief libft Function*/
void	*ft_memset(void *str, int c, size_t n);
/* @brief libft Function*/
char	*ft_strchr(const char *s, int c);
/* @brief libft Function*/
char	*ft_strjoin(char const *s1, char const *s2);
/* @brief libft Function*/
char	*ft_strdup(const char *s);
/* @brief libft Function*/
size_t	ft_strlcat(char *dst, const char *src, size_t size);
/* @brief libft Function*/
size_t	ft_strlen(const char *s);
/* @brief libft Function*/
int		ft_strncmp(const char *s1, const char *s2, size_t n);
/* @brief libft Function*/
char	*ft_strnstr(const char *haystack, const char *needle, size_t len);
/* @brief libft Function*/
char	*ft_strrchr(const char *s, int c);
/* @brief libft Function*/
int		ft_tolower(int c);
/* @brief libft Function*/
int		ft_toupper(int c);
/* @brief libft Function*/
char	*ft_strtrim(char const *s1, char const *set);
/* @brief libft Function*/
char	**ft_split(const char *s, char c);
/* @brief libft Function*/
char	*ft_substr(char const *s, unsigned int start, size_t len);
/* @brief libft Function*/
char	*ft_itoa(int n);
/* @brief libft Function*/
char	*ft_strmapi(char const *s, char (*f)(unsigned int, char));
/* @brief libft Function*/
void	ft_striteri(char *s, void (*f)(unsigned int, char*));
/* @brief libft Function*/
void	ft_putchar_fd(char c, int fd);
/* @brief libft Function*/
int		ft_putstr_fd(char *s, int fd);
/* @brief libft Function*/
int		ft_putendl_fd(char *s, int fd);
/* @brief libft Function*/
void	ft_putnbr_fd(int n, int fd);
/*libft linked-list functions*/
t_list	*ft_lstnew(void *content);
/*libft linked-list functions*/
void	ft_lstadd_front(t_list **lst, t_list *new);
/*libft linked-list functions*/
int		ft_lstsize(t_list *lst);
/*libft linked-list functions*/
t_list	*ft_lstlast(t_list *lst);
/*libft linked-list functions*/
void	ft_lstadd_back(t_list **lst, t_list *new);
/*libft linked-list functions*/
void	ft_lstclear(t_list **lst, void (*del)(void *));
/*libft linked-list functions*/
void	ft_lstiter(t_list *lst, void (*f)(void *));
/*libft linked-list functions*/
t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *));
/*libft linked-list functions*/
void	ft_lstdelone(t_list *lst, void (*del)(void *));

#endif