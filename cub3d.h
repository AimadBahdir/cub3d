/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abahdir <abahdir@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/09 16:32:30 by abahdir           #+#    #+#             */
/*   Updated: 2020/11/17 19:25:00 by abahdir          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H
# include <fcntl.h>
# include <stdlib.h>
# include <stdarg.h>
# include <unistd.h>
# include <errno.h>
# include <math.h>
# include <mlx.h>
# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 42
# endif
# define TILE_SIZE 64
# define FOV 60.0
# define RAD (M_PI / 180)
# define STEP 10

void	*g_freetmp;
int		g_updown;
typedef struct	s_position
{
	float	x;
	float	y;
}				t_pos;

typedef struct	s_resolution
{
	int	width;
	int	height;
}				t_res;

typedef struct	s_windata
{
	void	*img;
	char	*addr;
	int		bits_per_pixel;
	int		line_length;
	int		endian;
}				t_windata;

typedef struct	s_texturedata
{
	char	*path;
	void	*img;
	int		*addr;
	t_res	xpm;
}				t_texdata;

typedef	struct	s_object
{
	t_pos			p;
	float			dest;
	t_texdata		*sp_img;
	struct s_object	*next;
}				t_obj;

struct			s_screenshot
{
	unsigned char	header[55];
	t_res			res;
	unsigned short	bitcount;
	unsigned int	width_in_bytes;
	unsigned int	img_size;
	unsigned int	file_size;
	unsigned int	fbits_size;
	unsigned int	binfo_size;
	unsigned short	nb_planes;
	unsigned char	*buffer;
}				t_save;

struct			s_sprite
{
	char		*sp_file;
	char		*sp_file1;
	float		*wall_dst;
	t_obj		*lstobj;
}				t_sprt;

struct			s_keys
{
	short	up;
	short	down;
	short	left;
	short	right;
	short	faceleft;
	short	faceright;
	short	faceup;
	short	facedown;
	short	opendoor;
	short	esc;
}				t_key;

struct			s_texture
{
	t_texdata	no_img;
	t_texdata	so_img;
	t_texdata	we_img;
	t_texdata	ea_img;
	int			offset;
	int			color;
}				t_tex;

struct			s_ray
{
	float	ang;
	short	faceup;
	short	faceleft;
	float	xstep;
	float	ystep;
	short	horay;
}				t_ray;

struct			s_player
{
	char	dir;
	float	ang;
	t_pos	pos;
}				t_player;

struct			s_map
{
	char	**map;
	int		colf;
	int		colc;
	t_res	len;
}				t_map;

struct			s_window
{
	void		*mlx_ptr;
	void		*win_ptr;
	t_windata	img;
	t_res		resl;
}				t_win;

size_t			ft_strlen(const char *s);
size_t			ft_lenfrom(int c, char *s);
int				ft_isdigit(int c);
int				ft_isnumber(char *s);
int				ft_isnbrcol(char *s);
int				ft_tolower(int c);
int				ft_toupper(int c);
int				ft_atoi(const char *str);
char			*ft_strdup(const char *s1);
char			*ft_substr(char const *s, unsigned int start, size_t len);
char			*ft_strjoin(char const *s1, char const *s2);
char			*ft_strtrim(const char *s1, const char *set);
char			**ft_split(char const *s, char c);
int				ft_strncmp(const void *s1, const void *s2, size_t n);
void			*ft_memcpy(void *dst, const void *src, size_t n);
int				chr_bn(char *was_read);
int				get_next_line(int fd, char **line);
int				chck_save(char **save, char **line);
int				read_fd(char **was_read, int *len_read, int fd);
char			*join_last_cs(char **was_read, char **new_lin, char **save);
char			*new_line(int fd, char **was_read, int *len_read, char **save);
char			*last_cs_save(int *len_read, char **save,
						char **line, char **was_read);
int				initialise();
void			defaultsets();
void			resetimg(void);
int				ft_lentwop(char **s);
int				on_keypress(int key);
int				on_keyup(int key);
int				on_exit();
int				on_update();
int				opendoor(void);
float			normang(float ang);
int				checkforwall(t_pos p, int h);
int				checkbeforstep(void);
int				validfile(char *file, char *ext);
void			pixput(int x, int y, int color);
int				throwerror(char *error);
int				retfree(char *tmp1, char *tmp2, int ret);
int				retfreetwo(char **tmp1, int ret);
int				checkforin(int c, char *str);
int				setup(char *cubfile);
char			*ft_resps(char *str, char c, short o);
char			*clearspc(char *str);
void			set_textures(void);
int				set_map(char *cubfile, int fd, char *line);
int				rgbtoint(int r, int g, int b);
t_obj			*ft_lstnewobj(float x, float y, float dest, char *tex);
void			ft_lstaddobj(t_obj **objlst, t_obj *newobj);
void			sortlst(t_obj **objlst);
int				shadow(int color, float dest);
void			setdests(void);
void			getlifebar(void);
void			ft_sprite(t_obj *obj);
void			set_sprite(int x, int y);
void			print_sprite(void);
float			get_dest(t_pos *p);
float			getcol(float stp, t_texdata img, float wallheight);
int				printmap(void);
short			ft_screenshot(void);
#endif
