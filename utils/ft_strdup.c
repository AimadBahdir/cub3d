/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abahdir <abahdir@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/13 13:30:26 by abahdir           #+#    #+#             */
/*   Updated: 2019/11/02 21:31:08 by abahdir          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

char	*ft_strdup(const char *s1)
{
	char	*ns;
	int		i;

	i = ft_strlen(s1);
	ns = malloc((i * sizeof(char)) + 1);
	if (ns == NULL)
		return (NULL);
	i = 0;
	while (s1[i])
	{
		ns[i] = s1[i];
		i++;
	}
	ns[i] = '\0';
	return (ns);
}
