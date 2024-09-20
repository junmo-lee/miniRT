#include "structures_bonus.h"
#include "trace_bonus.h"
#include "scene_bonus.h"
#include "draw_bonus.h"

void	add_sphere(t_object *world, t_object_p *o_ptr)
{
	t_attribute	attrib;

	attrib.albedo = vdivide(o_ptr->sphere->colors, RGB_MAX);
	attrib.ksn = o_ptr->sphere->ksn;
	attrib.cd = o_ptr->sphere->cd;
	printf("SP : \n");
	printf("pos : "); vprint(o_ptr->sphere->coordinates);
	printf("r : %.4lf \n", o_ptr->sphere->diameter / 2.0);
	printf("color : "); vprint(o_ptr->sphere->colors);
	printf("ks : %.4lf, cd : %d\n", o_ptr->sphere->ksn, o_ptr->sphere->cd);
	oadd(&world, object(SP, \
		sphere(o_ptr->sphere->coordinates, o_ptr->sphere->diameter / 2.0), \
			attrib));
}

void	add_plain(t_object *world, t_object_p *o_ptr)
{
	t_attribute	attrib;

	attrib.albedo = vdivide(o_ptr->plane->colors, RGB_MAX);
	attrib.ksn = o_ptr->plane->ksn;
	attrib.cd = o_ptr->plane->cd;
	printf("PL : \n");
	printf("pos : "); vprint(o_ptr->plane->coordinates);
	printf("n : "); vprint(o_ptr->plane->normal_vector);
	printf("color : "); vprint(o_ptr->plane->colors);
	printf("ks : %.4lf, cd : %d\n", o_ptr->plane->ksn, o_ptr->plane->cd);
	oadd(&world, object(PL, \
		plain(o_ptr->plane->coordinates, o_ptr->plane->normal_vector), \
			attrib));
}

void	add_cylinder(t_object *world, t_object_p *o_ptr)
{
	t_attribute	attrib;

	attrib.albedo = vdivide(o_ptr->cylinder->colors, RGB_MAX);
	attrib.ksn = o_ptr->cylinder->ksn;
	attrib.cd = o_ptr->cylinder->cd;
	printf("CY : \n");
	printf("pos : "); vprint(o_ptr->cylinder->coordinates);
	printf("n : "); vprint(o_ptr->cylinder->normal_vector);
	printf("r : %.4lf \n", o_ptr->cylinder->diameter / 2.0);
	printf("h : %.4lf \n", o_ptr->cylinder->height);
	printf("color : "); vprint(o_ptr->cylinder->colors);
	printf("ks : %.4lf, cd : %d\n", o_ptr->cylinder->ksn, o_ptr->cylinder->cd);
	oadd(&world, object(CY, \
		cylinder(o_ptr->cylinder->coordinates, \
			o_ptr->cylinder->normal_vector, \
				o_ptr->cylinder->diameter / 2.0, o_ptr->cylinder->height), \
					attrib));
}

void	add_cone(t_object *world, t_object_p *o_ptr)
{
	t_attribute	attrib;

	attrib.albedo = vdivide(o_ptr->cone->colors, RGB_MAX);
	attrib.ksn = o_ptr->cone->ksn;
	attrib.cd = o_ptr->cone->cd;
	printf("CO : \n");
	printf("pos : "); vprint(o_ptr->cone->coordinates);
	printf("n : "); vprint(o_ptr->cone->normal_vector);
	printf("r : %.4lf \n", o_ptr->cone->diameter / 2.0);
	printf("h : %.4lf \n", o_ptr->cone->height);
	printf("color : "); vprint(o_ptr->cone->colors);
	printf("ks : %.4lf, cd : %d\n", o_ptr->cone->ksn, o_ptr->cone->cd);
	oadd(&world, object(CO, \
		cone(o_ptr->cone->coordinates, \
			o_ptr->cone->normal_vector, \
				o_ptr->cone->diameter / 2.0, o_ptr->cone->height), \
					attrib));
}
