/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_array.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rradin-m <rradin-m@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/13 15:55:45 by arimoham          #+#    #+#             */
/*   Updated: 2025/04/29 13:53:04 by rradin-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

int	ft_arraylen(char **m)
{
	int	i;

	i = 0;
	while (m && m[i])
		i++;
	return (i);
}

int	ft_put_array_fd(char **m, int nl, int fd)
{
	int	i;
	int	count;

	count = 0;
	i = 0;
	while (m && m[i])
	{
		if (nl)
		{
			if (ft_strchr(m[i], '='))
				count += ft_putendl_fd(m[i], fd);
		}
		else
			count += ft_putstr_fd(m[i], fd);
		i++;
	}
	return (count);
}

char	**ft_array_dup(char **m)
{
	char	**out;
	int		n_rows;
	int		i;

	i = 0;
	n_rows = ft_arraylen(m);
	out = malloc(sizeof(char *) * (n_rows + 1));
	if (!out)
		return (NULL);
	while (m[i])
	{
		out[i] = ft_strdup(m[i]);
		if (!out[i])
		{
			ft_free_array(&out);
			return (NULL);
		}
		i++;
	}
	out[i] = NULL;
	return (out);
}

char	**ft_extend_array(char **in, char *newstr)
{
	char	**out;
	int		len;
	int		i;

	i = -1;
	out = NULL;
	if (!newstr)
		return (in);
	len = ft_arraylen(in);
	out = malloc(sizeof(char *) * (len + 2));
	out[len + 1] = NULL;
	if (!out)
		return (in);
	while (++i < len)
	{
		out[i] = ft_strdup(in[i]);
		if (!out[i])
		{
			ft_free_array(&in);
			ft_free_array(&out);
		}
	}
	out[i] = ft_strdup(newstr);
	ft_free_array(&in);
	return (out);
}

char	**ft_array_replace_in(char ***big, char **small, int n)
{
	char	**aux;
	int		i[3];

	i[0] = -1;
	i[1] = -1;
	i[2] = -1;
	if (!big || !*big || n < 0 || n >= ft_arraylen(*big))
		return (NULL);
	aux = ft_calloc(ft_arraylen(*big) + ft_arraylen(small), sizeof(char *));
	while (aux && big[0][++i[0]])
	{
		if (i[0] != n)
			aux[++i[2]] = ft_strdup(big[0][i[0]]);
		else
		{
			while (small && small[++i[1]])
				aux[++i[2]] = ft_strdup(small[i[1]]);
		}
	}
	ft_free_array(big);
	*big = aux;
	return (*big);
}
