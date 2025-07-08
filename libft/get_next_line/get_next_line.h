/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmiguelo <mmiguelo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/25 14:26:12 by mmiguelo          #+#    #+#             */
/*   Updated: 2024/12/03 12:27:51 by mmiguelo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 42
# endif

# include <stdlib.h> //malloc
# include <stdio.h> //print
# include <unistd.h> //read
# include <fcntl.h> // open files

char	*ft_strchr_gnl(char *str, char c);
char	*ft_strjoin_gnl(char *s1, char *s2);
char	*ft_strndup(char *s, int len);
char	*free_data(char *storage, char *buffer);
char	*read_text(int fd, char *storage);
char	*save_remaining(char *storage);
char	*get_next_line(int fd);
int		ft_strclen(char *str, char c);

#endif
