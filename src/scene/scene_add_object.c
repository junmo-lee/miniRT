#include "structures.h"
#include "trace.h"
#include "scene.h"
#include "draw.h"

void	add_sphere(t_object *world, t_object_p *o_ptr)
{
	printf("SP : \n");
	printf("pos : "); vprint(o_ptr->sphere->coordinates);
	printf("r : %.4lf \n", o_ptr->sphere->diameter / 2.0);
	printf("color : "); vprint(o_ptr->sphere->colors);
	oadd(&world, object(SP, \
		sphere(o_ptr->sphere->coordinates, o_ptr->sphere->diameter / 2.0), \
			vdivide(o_ptr->sphere->colors, RGB_MAX)));
}

void	add_plain(t_object *world, t_object_p *o_ptr)
{
	printf("PL : \n");
	printf("pos : "); vprint(o_ptr->plane->coordinates);
	printf("n : "); vprint(o_ptr->plane->normal_vector);
	printf("color : "); vprint(o_ptr->plane->colors);
	oadd(&world, object(PL, \
		plain(o_ptr->plane->coordinates, o_ptr->plane->normal_vector), \
			vdivide(o_ptr->plane->colors, RGB_MAX)));
}

void	add_cylinder(t_object *world, t_object_p *o_ptr)
{
	printf("CY : \n");
	printf("pos : "); vprint(o_ptr->cylinder->coordinates);
	printf("n : "); vprint(o_ptr->cylinder->normal_vector);
	printf("r : %.4lf \n", o_ptr->cylinder->diameter / 2.0);
	printf("h : %.4lf \n", o_ptr->cylinder->height);
	printf("color : "); vprint(o_ptr->cylinder->colors);
	oadd(&world, object(CY, \
		cylinder(o_ptr->cylinder->coordinates, \
			o_ptr->cylinder->normal_vector, \
				o_ptr->cylinder->diameter / 2.0, o_ptr->cylinder->height), \
					vdivide(o_ptr->cylinder->colors, RGB_MAX)));
}

void	add_cone(t_object *world, t_object_p *o_ptr)
{
	printf("CO : \n");
	printf("pos : "); vprint(o_ptr->cone->coordinates);
	printf("n : "); vprint(o_ptr->cone->normal_vector);
	printf("r : %.4lf \n", o_ptr->cone->diameter / 2.0);
	printf("h : %.4lf \n", o_ptr->cone->height);
	printf("color : "); vprint(o_ptr->cone->colors);
	oadd(&world, object(CO, \
		cone(o_ptr->cone->coordinates, \
			o_ptr->cone->normal_vector, \
				o_ptr->cone->diameter / 2.0, o_ptr->cone->height), \
					vdivide(o_ptr->cone->colors, RGB_MAX)));
}