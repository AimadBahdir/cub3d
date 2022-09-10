/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abahdir <abahdir@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/21 14:28:56 by abahdir           #+#    #+#             */
/*   Updated: 2020/11/18 09:32:33 by abahdir          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int		validfile(char *file, char *ext)
{
	char	**spfile;
	int		i;
	int		len;

	spfile = ft_split(file, '.');
	len = 0;
	i = -1;
	while (spfile[len])
		len++;
	if (len >= 2)
	{
		while (spfile[len - 1][++i])
			spfile[len - 1][i] = ft_tolower(spfile[len - 1][i]);
		if (ft_strncmp(spfile[len - 1], ext, 4) == 0)
			return (retfreetwo(spfile, 1));
	}
	return (retfreetwo(spfile,
	throwerror(ft_strjoin("Your file extention must be : ", ext))));
}

float	normang(float ang)
{
	if (ang < 0)
		ang += 360;
	if (ang >= 360)
		ang -= 360;
	t_ray.faceup = (ang >= 0 && ang <= 180) ? 0 : 1;
	t_ray.faceleft = (ang >= 90 && ang <= 270) ? 1 : 0;
	return (ang);
}

int		throwerror(char *error)
{
	error = ft_strjoin("\n\033[1;31m(x) Error\n >> \033[0;31m", error);
	write(1, error, ft_strlen(error));
	write(1, "\n", 1);
	free(error);
	return (on_exit());
}

void	defaultsets(void)
{
	t_map.colf = -1;
	t_map.colc = -1;
	t_win.resl.width = 0;
	t_win.resl.height = 0;
}
