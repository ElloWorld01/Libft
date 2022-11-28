/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elombard <elombard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/29 08:29:24 by elombard          #+#    #+#             */
/*   Updated: 2022/11/26 10:40:15 by elombard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static char	**free_all(char **split, char *current)
{
	size_t	i;

	i = 0;
	if (split)
	{
		while (!split[i])
		{
			free(split[i]);
			++i;
		}
		if (split)
			free(split);
	}
	if (current)
		free(current);
	return (NULL);
}

static size_t	z(char *str, char c, size_t is_full)
{
	unsigned int	i;
	size_t			size;

	i = 0;
	if (is_full)
	{
		size = 0;
		if (!str)
			return (0);
		while (str[i])
		{
			if (str[i] != c)
			{
				++size;
				while (str[i] && str[i] != c)
					++i;
			}
			++i;
		}
		return (size);
	}
	while (str[i] && str[i] != c)
		++i;
	return (i);
}

static char	*add_string(size_t i, char *str, char c)
{
	size_t	j;
	char	*split_str;

	if (z(str + (i + 1), c, 0) == 0)
		return (NULL);
	j = 0;
	split_str = malloc(sizeof(char) * (z(str + (i + 1), c, 0) + 1));
	if (!split_str)
	{
		free(split_str);
		return (NULL);
	}
	while (str[i + 1 + j] && str[i + 1 + j] != c)
	{
		split_str[j] = str[i + j + 1];
		++j;
	}
	split_str[j] = '\0';
	return (split_str);
}

static void	after(char **split, char *str, char c)
{
	size_t		i;
	size_t		k;
	char		*current;

	i = -1;
	k = 0;
	while (str[++i] && k < z(str, c, 1))
	{
		if (str[i] == c)
		{
			current = add_string(i, str, c);
			if (current)
			{
				split[k] = malloc(sizeof(char) * (z(str + (i + 1), c, 0) + 1));
				if (!split[k])
				{
					free_all(split, current);
					return ;
				}
				ft_strlcpy(split[k++], current, ft_strlen(current) + 1);
				free(current);
			}
		}
	}
	split[k] = 0;
}

char	**ft_split(char *str, char c)
{
	char		**split;
	char		*current;

	split = malloc(sizeof(char *) * (z(str, c, 1) + 1));
	if (split == NULL || str == NULL || (c != '\0' && c == 0))
		return (NULL);
	if (z(str, c, 1) == 0)
	{
		split[0] = 0;
		return (split);
	}
	current = add_string(-1, str, c);
	if (current)
	{
		split[0] = malloc(sizeof(char) * (z(str, c, 0) + 1));
		if (!split[0])
			return (free_all(split, current));
		ft_strlcpy(split[0], current, z(str, c, 0) + 1);
		after(split + 1, str, c);
		free(current);
	}
	else
		after(split, str, c);
	return (split);
}
