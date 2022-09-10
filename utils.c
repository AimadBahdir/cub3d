/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abahdir <abahdir@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/13 20:07:35 by abahdir           #+#    #+#             */
/*   Updated: 2020/11/12 17:56:13 by abahdir          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	checkforin(int c, char *str)
{
	int i;

	i = 0;
	while (str[i])
	{
		if (str[i] == c)
			return (1);
		i++;
	}
	return (0);
}

int	retfree(char *tmp1, char *tmp2, int ret)
{
	if (tmp1 != NULL)
	{
		free(tmp1);
		tmp1 = NULL;
	}
	if (tmp2 != NULL)
	{
		free(tmp2);
		tmp2 = NULL;
	}
	return (ret);
}

int	retfreetwo(char **tmp1, int ret)
{
	int i;

	i = 0;
	if (tmp1)
	{
		while (tmp1[i] != 0)
		{
			free(tmp1[i]);
			tmp1[i] = NULL;
			i++;
		}
		free(tmp1);
		tmp1 = NULL;
	}
	return (ret);
}

int	ft_lentwop(char **s)
{
	int len;

	len = 0;
	while (s[len])
		len++;
	return (len);
}

int	rgbtoint(int r, int g, int b)
{
	return ((r & 0xff) << 16) + ((g & 0xff) << 8) + (b & 0xff);
}
