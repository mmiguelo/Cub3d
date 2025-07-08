#ifndef CUB3D_H
# define CUB3D_H

# include <unistd.h>
# include <stdlib.h>
# include <sys/time.h>
# include <string.h>
# include <math.h>
# include "../libft/libft.h"

/*=============================================================================#
#                                   DEFINES                                    #
#=============================================================================*/

/*
** ANSI color codes for terminal output
** Usage:
** 		printf(RED "This text is red" RST);
** 		printf(G "This text is green" RST);
** Remember to reset the color after using it with RST.
*/
# define RST	"\033[0m"		// reset color
# define RED	"\033[1;31m"	// bold red
# define G		"\033[1;32m"	// bold green
# define Y		"\033[1;33m"	// bold yellow
# define B		"\033[1;34m"	// bold blue
# define M		"\033[1;35m"	// bold magenta
# define C		"\033[1;36m"	// bold cyan
# define W		"\033[1;37m"	// bold white

/*=============================================================================#
#                                   STRUCTS                                    #
#=============================================================================*/



/*=============================================================================#
#                                   FUNCTIONS                                  #
#=============================================================================*/

void	error_msg(const char *error);

#endif