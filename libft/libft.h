/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sciftci <sciftci@student.42kocaeli.com.tr> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/06 04:04:52 by sciftci           #+#    #+#             */
/*   Updated: 2023/05/06 05:09:10 by sciftci          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_H
# define LIBFT_H

# include <unistd.h>
# include <fcntl.h>
# include <stdlib.h>

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 1024
# endif

typedef struct s_llist
{
	int				fd;
	char			content[BUFFER_SIZE + 1];
	struct s_llist	*next;
}	t_llist;

int		ft_max(int x, int y);
int		ft_min(int x, int y);
int		ft_isdigit(int c);
int		ft_isspace(int c);
int		ft_isnumber(const char *str);
size_t	ft_strlen(const char *s);
size_t	ft_arrlen(char **arr);
void	ft_bzero(void *s, size_t n);
char	*ft_strcpy(char *dst, const char *src);
char	*ft_strchr(const char *s, int c);
int		ft_strcmp(const char *s1, const char *s2);
char	*ft_strrstr(const char *haystack, const char *needle);
int		ft_atoi(const char *str);
void	*ft_calloc(size_t count, size_t size);
void	*ft_free(void *ptr);
void	*ft_free_2d(char **array);
void	*ft_free_3d(char ***array);
char	*ft_strdup(const char *s1);
char	*ft_substr(char const *s, unsigned int start, size_t len);
char	*ft_strjoin(char const *s1, char const *s2);
char	*ft_strnadd(char const *s1, char const *s2, size_t n);
char	**ft_split(char const *s, char c);
char	**ft_push_str(char **array, char *str);
char	*get_next_line(int fd);

#endif
