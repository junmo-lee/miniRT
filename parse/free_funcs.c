#include "parse.h"

void	free_ambient_struct(t_ambient_p **ambient_struct)
{
	if ((*ambient_struct)->colors != NULL)
		free((*ambient_struct)->colors);
}

void	free_camera_strcut(t_camera_p	**camera_strcut)
{
	if ((*camera_strcut)->coordinates != NULL)
		free((*camera_strcut)->coordinates);
	if ((*camera_strcut)->normal_vector != NULL)
		free((*camera_strcut)->normal_vector);
}