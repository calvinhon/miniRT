/******************************************************************************/
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   macros.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nthoach <nthoach@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/02 11:53:43 by honguyen          #+#    #+#             */
/*   Updated: 2024/12/18 22:13:43 by nthoach          ###   ########.fr       */
/*                                                                            */
/******************************************************************************/

#ifndef MACROS_H
# define MACROS_H

# include "structs.h"

// C libraries
# include <stdio.h>
# include <stdlib.h>
# include <stdbool.h>
# include <unistd.h>
# include <fcntl.h>
# include <sys/types.h>
# include <sys/stat.h>
# include <math.h>

// bonus
# ifndef BONUS
#  define BONUS 0 // Default to normal mode
# endif


// define assets
# define S      "data/xpm/S100.xpm"
# define W	    "data/xpm/W100.xpm"
# define W0     "data/xpm/W0100.xpm"
# define P      "data/xpm/P100.xpm"
# define P_F	"data/xpm/P_F100.xpm"
# define P_B	"data/xpm/P_B100.xpm"
# define P_R	"data/xpm/P_R100.xpm"
# define P_L	"data/xpm/P_L100.xpm"
# define C      "data/xpm/C100.xpm"
# define E      "data/xpm/E100.xpm"
# define G      "data/xpm/G.xpm"

// math define
# define PI             3.1415926535f
# define MAX_LIGHT		100

//define error codes
# define OK         0
# define NOK        1
# define ER_AGC     2
# define ER_MLX     3
# define ER_FILE    4
# define ER_NOT_RT  5
# define ER_OPEN_FILE  	5
# define ER_MALLOC  	6
# define ER_EMPTY_MAP 	7
# define ER_ONE_CAMERA 	8
# define ER_ONE_AMBIENT 9
# define ER_NO_LIGHT  	10
# define ER_MAX_LIGHT 	11
# define ER_NO_OBJ		12
# define ER_OBJ_TYPE		12
# define ER_OTHERS  	100




# define MS_COLOR_A		"Wrong color syntax for ambient lightning."
# define MS_COLOR_L		"Wrong color syntax for light source."
# define MS_SYNTAX		"Syntax: file format misconfiguration."
# define MS_NOT_RT		"File extension is not '.rt'."
# define MS_OPEN_FILE	"Couldn't open requested file"
# define MS_EMPTY_MAP	"Empty map"
# define MS_NO_CAMERA	"No camera in the map"
# define MS_TOO_MANY	"Found more than 1 A, C or L entities"
# define MS_USAGE 		 "Usage: ./miniRT <scene>.rt \n"
# define MS_MALLOC 		 "Can not allocate dynami memory \n"
# define MS_OBJ_TYPE	 "Undefied object type \n"
# define MS_OTHERS 		 "Other errors. \n"

//Window sizes
# ifdef __APPLE__
#  define WIDTH 1440
#  define HEIGHT 810
# else
#  define WIDTH 1920
#  define HEIGHT 1080
# endif

// color define


// Keyboard define
# ifdef __APPLE__
#  define KEY_A         0
#  define KEY_D		    2
#  define KEY_W		    13
#  define KEY_S		    1	
#  define KEY_LEFT	    123
#  define KEY_RIGHT	    124
#  define KEY_UP		126
#  define KEY_DOWN	    125
#  define KEY_ESC       53
#  define KEY_Q		    12
#  define KEY_C         8
#  define KEY_V         9
#  define KEYPRESS    	2
#  define DESTROYNOTIFY 17
# else // Linux
#  define KEY_A        97      
#  define KEY_D        100
#  define KEY_W        119
#  define KEY_S        115
#  define KEY_LEFT     65361
#  define KEY_RIGHT    65363
#  define KEY_UP       65362
#  define KEY_DOWN     65364
#  define KEY_ESC      65307
#  define KEY_Q        113
#  define KEY_C        99
#  define KEY_V        118
# endif

#endif
