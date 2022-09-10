/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   setup.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abahdir <abahdir@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/13 15:45:34 by abahdir           #+#    #+#             */
/*   Updated: 2020/11/18 09:20:18 by abahdir          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

char	*ft_resps(char *str, char c, short o)
{
	int		i;

	i = 0;
	c = (o) ? c : 27;
	while (str[i] != c && o)
		i++;
	while (str[i] == c && o)
		i++;
	while (str[i] != '\0')
	{
		if (str[i] == c)
			str[i] = (o) ? 27 : ' ';
		i++;
	}
	return (str);
}

char	*clearspc(char *str)
{
	int		i;
	int		j;

	i = 1;
	j = 1;
	while (str[++i] != '\0')
	{
		if (str[i] != ' ')
			str[++j] = str[i];
		if (str[i] == ' ' && ft_isdigit(str[i - 1]))
			throwerror("RGB params must be followed by comma!");
	}
	str[++j] = '\0';
	return (str);
}
