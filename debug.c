#include "structures.h"
#include "trace.h"
#include "scene.h"
#include "draw.h"
#include "parse.h"


int	main(int argc, char **argv)
{
	t_parse parsed_struct; // malloc을 최소화 하려함

    if (argc != 2)
    {
        printf("argument error\n");
        return (0);
    }
    else
	{
		init_t_parse(&parsed_struct);
		parse(&parsed_struct, argv[1]);
	}
    // print list
    return (0);
}


// int main(void)
// {
// 	t_vec3 a = vec3(1.0, 2.0, 1.0);
// 	t_vec3 b = vec3(1.0, -2.0, 1.0);

// 	t_vec3 c = vplus(a, b);
// 	(void)c;
// }