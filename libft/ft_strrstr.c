/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sciftci <sciftci@student.42kocaeli.com.tr> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/06 04:02:42 by sciftci           #+#    #+#             */
/*   Updated: 2023/05/06 04:02:45 by sciftci          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrstr(const char *haystack, const char *needle)
{
	int	i;
	int	j;

	if (needle[0] == '\0')
		return ((char *)haystack);
	i = ft_strlen(haystack) - 1;
	while (i >= 0)
	{
		j = ft_strlen(needle) - 1;
		while (i - ((int)ft_strlen(needle) - 1 - j) >= 0
			&& haystack[i - ((int)ft_strlen(needle) - 1 - j)] == needle[j])
		{
			if (j == 0)
				return ((char *)&haystack
					[i - ((int)ft_strlen(needle) - 1 - j)]);
			j --;
		}
		i --;
	}
	return (0);
}
