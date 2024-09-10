#include "structures.h"
#include "trace.h"
#include "scene.h"
#include "draw.h"

double clamp(double x)
{
	if (x < 0.0)
		return (0.0);
	if (x > 1.0)
		return (1.0);
	return (x);
}

// [0,1] 로 되어있는 rgb 값을 각각 [0,255]에 맵핑 해서 출력.
void    write_color(t_color3 pixel_color)
{
	printf("%d %d %d\n", (int)(255.999 * clamp(pixel_color.x)),
		(int)(255.999 * clamp(pixel_color.y)),
		(int)(255.999 * clamp(pixel_color.z)));
}

unsigned int color_to_int(t_color3 pixel_color)
{
	unsigned char r = (unsigned char)(255.999 * clamp(pixel_color.x));
	unsigned char g = (unsigned char)(255.999 * clamp(pixel_color.y));
	unsigned char b = (unsigned char)(255.999 * clamp(pixel_color.z));

	return (RGB_T << 24 | r << 16 | g << 8 | b);
}

void	my_mlx_pixel_put(t_vmlx *data, int x, int y, unsigned int color)
{
	char	*dst;

	dst = data->addr + (y * data->line_length + x * (data->bits_per_pixel / 8));
	*(unsigned int *)dst = color;
}

void	draw_pixel(t_vmlx *vmlx, int i, int j, t_MT19937 *state)
{
	t_scene 	*scene = vmlx->scene;
	int			sample;
	double      u;
	double      v;
	t_color3    pixel_color;

	sample = 0;
	pixel_color = color3(0, 0, 0);
	while (sample < SAMPLES_PER_PIXEL)
	{
		u = ((double)i + genrand_real3(state) + 0.5) / (scene->canvas.width - 1);
		v = ((double)j + genrand_real3(state) + 0.5) / (scene->canvas.height - 1);
		scene->ray = ray_primary(&scene->camera, u, v);
		pixel_color = vplus(pixel_color, ray_color(scene));
		sample++;
	}
	my_mlx_pixel_put(vmlx, i, scene->canvas.height - j - 1, color_to_int(vscalar(pixel_color, 1.0 / SAMPLES_PER_PIXEL)));
}

int	draw_img(t_vmlx *vmlx)
{
	int			i;
	int			j;
	t_scene 	*scene;
	t_MT19937	state;

	scene = vmlx->scene;
	init_genrand(&state, RAND_SEED);
	j = scene->canvas.height - 1;
	while (j >= 0)
	{
		i = 0;
		while (i < scene->canvas.width)
		{
			draw_pixel(vmlx, i, j, &state);
			i++;
		}
		j--;
	}
	return (EXIT_SUCCESS);
}

