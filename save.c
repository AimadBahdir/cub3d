/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   save.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abahdir <abahdir@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/14 14:00:46 by abahdir           #+#    #+#             */
/*   Updated: 2020/11/17 19:11:33 by abahdir          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int		set_bmpheader(void)
{
	t_save.res.width = t_win.resl.width;
	t_save.res.height = t_win.resl.height;
	t_save.bitcount = 24;
	t_save.width_in_bytes = ((t_save.res.width * t_save.bitcount + 31)
							/ 32) * 4;
	t_save.img_size = t_save.width_in_bytes * --t_save.res.height;
	t_save.fbits_size = 54;
	t_save.file_size = 54 + t_save.img_size;
	t_save.nb_planes = 1;
	t_save.binfo_size = 40;
	ft_memcpy(t_save.header, "BM", 2);
	ft_memcpy(t_save.header + 2, &t_save.file_size, 4);
	ft_memcpy(t_save.header + 10, &t_save.fbits_size, 4);
	ft_memcpy(t_save.header + 14, &t_save.binfo_size, 4);
	ft_memcpy(t_save.header + 18, &t_save.res.width, 4);
	ft_memcpy(t_save.header + 22, &t_save.res.height, 4);
	ft_memcpy(t_save.header + 26, &t_save.nb_planes, 2);
	ft_memcpy(t_save.header + 28, &t_save.bitcount, 2);
	ft_memcpy(t_save.header + 34, &t_save.img_size, 4);
	t_save.header[t_save.fbits_size] = '\0';
	return (initialise());
}

void	set_bmpix(int row, int col)
{
	int *add;
	int color;

	add = (int *)mlx_get_data_addr(t_win.img.img, &t_win.img.bits_per_pixel,
			&t_win.img.line_length, &t_win.img.endian);
	color = add[((t_win.resl.height - 1) - row) * t_win.resl.width + col];
	t_save.buffer[row * t_save.width_in_bytes + col * 3 + 0] = fmod(color, 256);
	t_save.buffer[row * t_save.width_in_bytes + col * 3 + 1] = fmod(color / 256,
																256);
	t_save.buffer[row * t_save.width_in_bytes + col * 3 + 2] = fmod(color / 256
																/ 256, 256);
}

short	ft_screenshot(void)
{
	int		row;
	int		col;
	int		scrn_file;

	if (set_bmpheader())
	{
		t_save.buffer = malloc(t_save.img_size);
		row = -1;
		while (++row < t_save.res.height)
		{
			col = -1;
			while (++col < t_save.res.width)
				set_bmpix(row, col);
		}
		t_save.buffer[t_save.img_size] = '\0';
		if ((scrn_file = open("screenshot.bmp", O_CREAT | O_RDWR, 500)) < 0)
			throwerror("Opss can't open bmp file :( !");
		write(scrn_file, t_save.header, t_save.fbits_size);
		write(scrn_file, t_save.buffer, t_save.img_size);
		close(scrn_file);
		free(t_save.buffer);
	}
	return (on_exit());
}
