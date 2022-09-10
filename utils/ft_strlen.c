/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlen.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abahdir <abahdir@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/09 22:08:10 by abahdir           #+#    #+#             */
/*   Updated: 2020/03/08 15:19:46 by abahdir          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

size_t	ft_strlen(const char *s)
{
	size_t len;

	len = 0;
	while (s[len] != '\0')
		len++;
	return (len);
}

size_t	ft_lenfrom(int c, char *s)
{
	size_t	len;
	int		i;

	i = 0;
	len = 0;
	while (s[i] != '\0')
	{
		if (s[i] == c)
			len++;
		i++;
	}
	return (len);
}
