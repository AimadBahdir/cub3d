/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_map.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abahdir <abahdir@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/14 14:00:46 by abahdir           #+#    #+#             */
/*   Updated: 2020/11/12 17:13:49 by abahdir          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	set_player(char dir, float x, float y)
{
	if (!t_player.dir)
	{
		t_player.dir = dir;
		t_player.pos.y = (y * TILE_SIZE) + (TILE_SIZE / 2);
		t_player.pos.x = (x * TILE_SIZE) + (TILE_SIZE / 2);
		if (dir == 'N')
			t_player.ang = 270;
		else if (dir == 'S')
			t_player.ang = 90;
		else if (dir == 'W')
			t_player.ang = 180;
		else if (dir == 'E')
			t_player.ang = 0;
	}
	else
	{
		t_map.map = NULL;
		throwerror("You must define one player only !");
	}
}

int			checkmap(int lenx, int leny)
{
	int x;
	int y;

	y = -1;
	while (t_map.map[++y])
	{
		x = -1;
		while (t_map.map[y][++x] != '\0')
		{
			if ((x > 0 && y > 0 && x < lenx && y < leny)
			&& checkforin(t_map.map[y][x], "0234WESN")
			&& (t_map.map[y + 1][x] == ' ' || t_map.map[y][x + 1] == ' ' ||
			t_map.map[y - 1][x] == ' ' || t_map.map[y][x - 1] == ' '))
				return (throwerror("Map Invalid"));
			if (checkforin(t_map.map[y][x], "WESN"))
				set_player(t_map.map[y][x], x, y);
			if (t_map.map[y][x] == '2' || t_map.map[y][x] == '3')
				set_sprite(x, y);
		}
	}
	return (1);
}

static int	addlinemap(int index, char *line, int lenx, int leny)
{
	int i;
	int j;

	j = 0;
	i = 0;
	while (i < lenx)
	{
		if (checkforin(line[j], "0234WESN")
		&& (index == 0 || index == (leny - 1)
		|| i == 0 || i == (lenx - 1)))
			return (throwerror("Map must be closed"));
		if (line[j])
		{
			t_map.map[index][i] = line[j];
			j++;
		}
		else
			t_map.map[index][i] = ' ';
		if (!checkforin(t_map.map[index][i], " 01234WESN"))
			return (throwerror("Character invalid in map"));
		i++;
	}
	t_map.map[index][lenx] = '\0';
	return (1);
}

static int	mapsets(char *cubfile, int lenx, int leny)
{
	char	*line;
	int		nr;
	int		index;
	int		fd;
	int		i;

	t_map.map = malloc((leny + 1) * sizeof(char*));
	t_map.map[leny] = 0;
	nr = -1;
	while (++nr < leny)
		t_map.map[nr] = malloc((lenx + 1) * sizeof(char));
	if ((fd = open(cubfile, O_RDONLY)) < 0)
		return (-1);
	index = 0;
	while (((nr = get_next_line(fd, &line)) >= 0) && index < leny)
	{
		i = 0;
		while (line[i] == ' ')
			i++;
		if (line[i] == '1')
			nr = addlinemap(index++, line, lenx, leny);
		if (retfree(NULL, line, nr) <= 0)
			break ;
	}
	return ((retfree(NULL, line, nr) >= 0) ? checkmap(lenx, leny) : -1);
}

int			set_map(char *cubfile, int fd, char *line)
{
	int nr;
	int i;

	nr = 0;
	t_map.len.height = 1;
	t_map.len.width = ft_strlen(line);
	while ((nr = get_next_line(fd, &line)) >= 0)
	{
		i = 0;
		while (line[i] == ' ')
			i++;
		if (line[i] == '1')
		{
			nr = ft_strlen(line);
			t_map.len.width = (t_map.len.width < nr) ? nr : t_map.len.width;
			t_map.len.height++;
		}
		else
			nr = (nr == 0 && !line[i]) ? 0
				: throwerror("MAP must be in file End & have '1' around it.");
		if (retfree(line, NULL, nr) == 0)
			break ;
	}
	return ((nr == 0)
		? mapsets(cubfile, t_map.len.width, t_map.len.height) : -1);
}
