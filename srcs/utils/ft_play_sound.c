/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_play_sound.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sciftci <sciftci@student.42kocaeli.com.tr> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/15 09:44:02 by hel-makh          #+#    #+#             */
/*   Updated: 2023/04/15 16:53:32 by sciftci          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

void	ft_play_sound(char *path)
{
	pid_t	pid;
	char	*argv[4];

	pid = fork();
	if (pid == 0)
	{
		# if defined(__linux__)
			argv[0] = ft_strdup("/usr/bin/aplay");
			argv[1] = ft_strdup("-q");
			argv[2] = ft_strdup(path);
			argv[3] = NULL;
		# elif defined(__APPLE__) && defined(__MACH__)
			argv[0] = ft_strdup("/usr/bin/afplay");
			argv[1] = ft_strdup(path);
			argv[2] = NULL;
		# endif
		execve(argv[0], argv, NULL);
	}
}