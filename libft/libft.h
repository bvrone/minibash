/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aglady <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/28 20:43:06 by aglady            #+#    #+#             */
/*   Updated: 2020/11/27 18:53:52 by aglady           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_H
# define LIBFT_H

# include <stdlib.h>
# include <unistd.h>

typedef struct s_list
{
	void			*data;
	struct s_list	*next;
}					t_list;

void				*ft_memset(void *b, int c, size_t len);
void				ft_bzero(void *s, size_t n);
void				*ft_memcpy(void *dest, const void *source, size_t count);
void				*ft_memccpy(void *dest, const void *source, int ch,
						size_t count);
void				*ft_memmove(void *dest, const void *source, size_t count);
void				*ft_memchr(const void *source, int ch, size_t count);
int					ft_memcmp(const void *s1, const void *s2, size_t n);
size_t				ft_strlen(const char *s);
size_t				ft_strlcpy(char *dst, const char *src, size_t dstsize);
size_t				ft_strlcat(char *dst, const char *src, size_t dstsize);
void				ft_strcat(char *dst, const char *src);
char				*ft_strchr(const char *s, int c);
char				*ft_strrchr(const char *str, int ch);
char				*ft_strnstr(const char *big, const char *little,
						size_t len);
int					ft_strncmp(const char *s1, const char *s2, size_t n);
int					ft_strcmp(const char *s1, const char *s2);
int					ft_atoi(const char *str);
int					ft_atoi_s(char **str);
int					ft_isalpha(int c);
int					ft_isdigit(int c);
int					ft_isalnum(int c);
int					ft_isascii(int c);
int					ft_isprint(int c);
int					ft_toupper(int c);
int					ft_tolower(int c);
void				*ft_calloc(size_t count, size_t size);
char				*ft_strdup(const char *s1);
char				*ft_substr(char const *s, unsigned int start, size_t len);
char				*ft_strjoin(char const *s1, char const *s2);
char				*ft_strtrim(char const *s1, char const *set);
char				**ft_split(char const *s, char c);
char				**ft_split_clear(char **res);
char				*ft_itoa(int n);
char				*ft_strmapi(char const *s, char (*f)(unsigned int, char));
void				ft_putchar_fd(char c, int fd);
void				ft_putstr_fd(char *s, int fd);
void				ft_putnstr_fd(char *s, int fd, size_t len);
void				ft_putendl_fd(char *s, int fd);
void				ft_putnbr_fd(int nb, int fd);
void				ft_putnnbr_fd(int nb, int sign, int n, int fd);
void				ft_putunbr_fd(unsigned int nb, int fd);
void				ft_putnunbr_fd(unsigned int nb, int n, int fd);
void				ft_putxnbr_fd(unsigned int nb, int fd, char xx);
void				ft_putnxnbr_fd(unsigned int nbr, int n, int fd, char xx);
void				ft_putptr_fd(uintptr_t nb, int fd);
void				ft_putnptr_fd(uintptr_t nb, int n, int fd);
t_list				*ft_lstnew(void *data);
void				ft_lstadd_front(t_list **lst, t_list *n);
int					ft_lstsize(t_list *lst);
t_list				*ft_lstlast(t_list *lst);
void				ft_lstadd_back(t_list **lst, t_list *n);
void				ft_lstdelone(t_list *lst, void (*del)(void *));
void				ft_lstclear(t_list **lst, void (*del)(void *));
void				ft_lstiter(t_list *lst, void (*f)(void *));
t_list				*ft_lstmap(t_list *lst, void *(*f)(void *),
						void (*del)(void *));
int					ft_nbrlen(int nb);
int					ft_unbrlen(unsigned int nb);
int					ft_xnbrlen(unsigned int nb);
int					ft_ptrlen(uintptr_t nb);
int					ft_max(int a, int b);
int					get_next_line(int fd, char **line);

#endif
