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

static char	**chkparams(char **pr)
{
	int		len;
	char	**col;

	len = ft_lentwop(pr);
	if (len >= 2)
	{
		ft_resps(pr[1], ' ', 0);
		if (((!ft_strncmp(pr[0], "NO", 3) || !ft_strncmp(pr[0], "SO", 3)
			|| !ft_strncmp(pr[0], "WE", 3) || !ft_strncmp(pr[0], "EA", 3)
			|| !ft_strncmp(pr[0], "S", 2) || !ft_strncmp(pr[0], "S1", 3))
			&& len == 2) || (!ft_strncmp(pr[0], "R", 2) && len == 3))
			return (pr);
		if (!ft_strncmp(pr[0], "F", 2) || !ft_strncmp(pr[0], "C", 2))
		{
			col = ft_split(pr[1], ',');
			len = ft_lentwop(col);
			retfreetwo(col, 0);
			if (len == 3 && ft_lenfrom(',', pr[1]) == 2)
				return (pr);
			else
				throwerror("Number of color parametres invalid !");
		}
	}
	throwerror("Number of parametres invalid  !");
	return (NULL);
}

static int	set_resolution(char **params)
{
	if (t_win.resl.width || t_win.resl.height)
		throwerror("Resolution duplicated");
	if (ft_isnumber(params[1]) && ft_isnumber(params[2]))
	{
		t_win.resl.width = ft_atoi(params[1]);
		t_win.resl.height = ft_atoi(params[2]);
		if (t_win.resl.width < 0 || t_win.resl.height < 0)
			throwerror("Resolution must be great than (1x1)");
		t_win.resl.width = (t_win.resl.width > 2560)
							? 2560 : t_win.resl.width;
		t_win.resl.height = (t_win.resl.height > 1440)
							? 1440 : t_win.resl.height;
		return (retfreetwo(params, 1));
	}
	throwerror("Resolution parametrs must be a numbers!");
	return (retfreetwo(params, -1));
}

static int	set_colors(char fp, char **params)
{
	g_freetmp = params;
	params = ft_split(params[1], ',');
	retfreetwo(g_freetmp, 0);
	if (ft_isnbrcol(params[0]) && ft_isnbrcol(params[1])
		&& ft_isnbrcol(params[2]))
	{
		if (ft_toupper(fp) == 'F')
		{
			if (t_map.colf > -1)
				throwerror("(F) Color Params are duplicated.");
			t_map.colf = rgbtoint(ft_atoi(params[0]),
						ft_atoi(params[1]), ft_atoi(params[2]));
			return (retfreetwo(params, 1));
		}
		else if (ft_toupper(fp) == 'C')
		{
			if (t_map.colc > -1)
				throwerror("(C) Color Params are duplicated.");
			t_map.colc = rgbtoint(ft_atoi(params[0]),
						ft_atoi(params[1]), ft_atoi(params[2]));
			return (retfreetwo(params, 1));
		}
	}
	return (retfreetwo(params,
			throwerror("RGB color must be a numbers between 0 and 255!")));
}

static int	set_texprite(char **params)
{
	if (ft_strncmp(params[0], "NO", 3) == 0 && !t_tex.no_img.path
		&& validfile(params[1], "xpm"))
		t_tex.no_img.path = ft_strdup(params[1]);
	else if (ft_strncmp(params[0], "SO", 3) == 0 && !t_tex.so_img.path
		&& validfile(params[1], "xpm"))
		t_tex.so_img.path = ft_strdup(params[1]);
	else if (ft_strncmp(params[0], "WE", 3) == 0 && !t_tex.we_img.path
		&& validfile(params[1], "xpm"))
		t_tex.we_img.path = ft_strdup(params[1]);
	else if (ft_strncmp(params[0], "EA", 3) == 0 && !t_tex.ea_img.path
		&& validfile(params[1], "xpm"))
		t_tex.ea_img.path = ft_strdup(params[1]);
	else if (ft_strncmp(params[0], "S", 2) == 0 && !t_sprt.sp_file
		&& validfile(params[1], "xpm"))
		t_sprt.sp_file = ft_strdup(params[1]);
	else if (ft_strncmp(params[0], "S1", 3) == 0 && !t_sprt.sp_file1
		&& validfile(params[1], "xpm"))
		t_sprt.sp_file1 = ft_strdup(params[1]);
	else
	{
		return (retfreetwo(params,
			throwerror("Sum Texture Params are invalid or duplicated.")));
	}
	return (retfreetwo(params, 1));
}

int			setup(char *cubfile)
{
	char	*line;
	int		nr;
	int		fd;

	if ((fd = open(cubfile, O_RDONLY)) < 0 || !validfile(cubfile, "cub"))
		return (throwerror(ft_strjoin("No such file with name : ", cubfile)));
	while ((nr = get_next_line(fd, &line)) >= 0)
	{
		g_freetmp = line;
		line = ft_strtrim(line, " \t");
		free(g_freetmp);
		if (line[0] == 'R')
			nr = set_resolution(chkparams(ft_split(line, ' ')));
		else if (checkforin(line[0], "NSWE"))
			nr = set_texprite(chkparams(ft_split(ft_resps(line, ' ', 1), ' ')));
		else if (line[0] == 'F' || line[0] == 'C')
			nr = set_colors(line[0], chkparams(ft_split(clearspc(line), ' ')));
		else if (line[0] == '1')
			nr = set_map(cubfile, fd, line);
		else if (line[0])
			throwerror("FILE (.cub) Invalid.");
		if (retfree(line, NULL, nr) <= 0)
			break ;
	}
	return ((nr == -1) ? -1 : 1);
}
