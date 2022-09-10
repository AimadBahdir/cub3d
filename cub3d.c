/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abahdir <abahdir@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/09 16:31:58 by abahdir           #+#    #+#             */
/*   Updated: 2020/11/17 17:56:37 by abahdir          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	pixput(int x, int y, int color)
{
	int *add;

	add = (int *)mlx_get_data_addr(t_win.img.img, &t_win.img.bits_per_pixel,
			&t_win.img.line_length, &t_win.img.endian);
	if (x < t_win.resl.width && y < t_win.resl.height && x >= 0 && y >= 0)
		add[y * (int)t_win.resl.width + x] = color;
}

void	set_textures(void)
{
	if (!(t_tex.no_img.img = mlx_xpm_file_to_image(t_win.mlx_ptr,
		t_tex.no_img.path, &t_tex.no_img.xpm.width, &t_tex.no_img.xpm.height)))
		throwerror("NO Texture not found");
	t_tex.no_img.addr = (int *)mlx_get_data_addr(t_tex.no_img.img,
					&t_win.img.bits_per_pixel, &t_win.img.line_length,
					&t_win.img.endian);
	if (!(t_tex.so_img.img = mlx_xpm_file_to_image(t_win.mlx_ptr,
		t_tex.so_img.path, &t_tex.so_img.xpm.width, &t_tex.so_img.xpm.height)))
		throwerror("SO Texture not found");
	t_tex.so_img.addr = (int *)mlx_get_data_addr(t_tex.so_img.img,
					&t_win.img.bits_per_pixel, &t_win.img.line_length,
					&t_win.img.endian);
	if (!(t_tex.we_img.img = mlx_xpm_file_to_image(t_win.mlx_ptr,
		t_tex.we_img.path, &t_tex.we_img.xpm.width, &t_tex.we_img.xpm.height)))
		throwerror("WE Texture not found");
	t_tex.we_img.addr = (int *)mlx_get_data_addr(t_tex.we_img.img,
					&t_win.img.bits_per_pixel, &t_win.img.line_length,
					&t_win.img.endian);
	if (!(t_tex.ea_img.img = mlx_xpm_file_to_image(t_win.mlx_ptr,
		t_tex.ea_img.path, &t_tex.ea_img.xpm.width, &t_tex.ea_img.xpm.height)))
		throwerror("EA Texture not found");
	t_tex.ea_img.addr = (int *)mlx_get_data_addr(t_tex.ea_img.img,
					&t_win.img.bits_per_pixel, &t_win.img.line_length,
					&t_win.img.endian);
}

int		initialise(void)
{
	if (!t_win.resl.width || !t_win.resl.height)
		return (throwerror("Please set Resolution of screen"));
	if (!(t_sprt.wall_dst = malloc((t_win.resl.width + 1) * sizeof(float))))
		return (throwerror("Wall Dests Not Alloced"));
	t_sprt.wall_dst[t_win.resl.width] = '\0';
	t_win.mlx_ptr = mlx_init();
	t_win.win_ptr = mlx_new_window(t_win.mlx_ptr,
					t_win.resl.width, t_win.resl.height, "CUB3D");
	t_win.img.img = mlx_new_image(t_win.mlx_ptr,
					t_win.resl.width, t_win.resl.height);
	t_win.img.addr = mlx_get_data_addr(t_win.img.img,
					&t_win.img.bits_per_pixel, &t_win.img.line_length,
					&t_win.img.endian);
	set_textures();
	printmap();
	return (1);
}

short	checkargs(int argc, char **argv)
{
	if (argc < 2)
		return (throwerror("Please set configuration file (.cub)!"));
	if (argc > 3)
		return (throwerror("Number of inputs invalid!"));
	if (setup(argv[1]))
	{
		if (argc == 3 && ft_strncmp(argv[2], "--save", 7) == 0)
			return (ft_screenshot());
		else if (argc == 2)
			return (1);
		else
			return (throwerror("Invalid inputs!"));
	}
	return (-1);
}

int		main(int argc, char **argv)
{
	defaultsets();
	if (checkargs(argc, argv) == 1)
	{
		if (initialise() != 1)
			return (0);
		mlx_hook(t_win.win_ptr, 2, 0, on_keypress, NULL);
		mlx_hook(t_win.win_ptr, 3, 0, on_keyup, NULL);
		mlx_hook(t_win.win_ptr, 17, 0, on_exit, NULL);
		mlx_loop_hook(t_win.mlx_ptr, on_update, NULL);
		mlx_put_image_to_window(t_win.mlx_ptr,
			t_win.win_ptr, t_win.img.img, 0, 0);
		mlx_loop(t_win.mlx_ptr);
	}
	return (0);
}
