/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   component_surroundings.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sciftci <sciftci@student.42kocaeli.com.tr> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/06 04:14:01 by sciftci           #+#    #+#             */
/*   Updated: 2023/05/06 04:14:03 by sciftci          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

static int	is_component_surrounded(char **map, int i, int j)
{
	if (map[i][j + 1]
		&& ft_strchr("0NSEWC", map[i][j + 1]))
		return (1);
	else if (j - 1 >= 0
		&& ft_strchr("0NSEWC", map[i][j - 1]))
		return (1);
	else if (map[i + 1]
		&& j < (int)ft_strlen(map[i + 1])
		&& ft_strchr("0NSEWC", map[i + 1][j]))
		return (1);
	else if (i - 1 >= 0
		&& j < (int)ft_strlen(map[i - 1])
		&& ft_strchr("0NSEWC", map[i - 1][j]))
		return (1);
	return (0);
}

static int	is_space_surrounded(char **map, int i, int j)
{
	if (!map[i][j + 1]
		|| (map[i][j + 1]
			&& map[i][j + 1] == SPACE))
		return (1);
	else if (j - 1 < 0
		|| (j - 1 >= 0
			&& map[i][j - 1] == SPACE))
		return (1);
	else if (!map[i + 1]
		|| (map[i + 1]
			&& j >= (int)ft_strlen(map[i + 1]))
		|| (map[i + 1]
			&& j < (int)ft_strlen(map[i + 1])
			&& map[i + 1][j] == SPACE))
		return (1);
	else if (i - 1 < 0
		|| (i - 1 >= 0
			&& j >= (int)ft_strlen(map[i - 1]))
		|| (i - 1 >= 0
			&& j < (int)ft_strlen(map[i - 1])
			&& map[i - 1][j] == SPACE))
		return (1);
	return (0);
}

static int	wall_right_placed(char **map, int i, int j)
{
	if (map[i][j + 1] && map[i][j + 1] == WALL
		&& j - 1 >= 0 && map[i][j - 1] == WALL
		&& map[i + 1] && map[i + 1][j] && map[i + 1][j] != SPACE
		&& i - 1 >= 0 && map[i - 1][j] && map[i - 1][j] != SPACE)
		return (1);
	if (map[i + 1] && j < (int)ft_strlen(map[i + 1]) && map[i + 1][j] == WALL
		&& i - 1 >= 0 && j < (int)ft_strlen(map[i - 1]) && map[i - 1][j] == WALL
		&& map[i][j + 1] && map[i][j + 1] != SPACE
		&& j - 1 >= 0 && map[i][j - 1] != SPACE)
		return (1);
	return (0);
}

int	component_surroundings(char **map, int i, int j)
{
	if (map[i][j] == SPACE && is_component_surrounded(map, i, j))
		return (perror("Error\nInvalid map: misplaced spaces.\n"), 0);
	else if (ft_strchr("0NSEWC", map[i][j]))
	{
		if (is_space_surrounded(map, i, j))
		{
			if (map[i][j] == EMPTY_SPACE)
				perror("Error\nInvalid map: misplaced empty space.\n");
			else
				perror("Error\nInvalid map: misplaced player position.\n");
			return (0);
		}
	}
	else if ((map[i][j] == C_DOOR || map[i][j] == O_DOOR)
		&& !wall_right_placed(map, i, j))
		return (perror("Error\nInvalid map: misplaced wall.\n"), 0);
	return (1);
}
