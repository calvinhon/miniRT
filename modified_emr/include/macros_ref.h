/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   macros.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/02 11:53:43 by honguyen          #+#    #+#             */
/*   Updated: 2025/01/14 09:39:27 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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
# include <limits.h>

// bonus
# ifndef BONUS
#  define BONUS 0 // Default to normal mode
# endif


// Define assets
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

//
# define STEP 3

// Define error codes
#define OK              0
#define NOK             1
#define ER_AGC          2
#define ER_MLX          3
#define ER_FILE         4
#define ER_NOT_RT       5
#define ER_OPEN_FILE    6
#define ER_MALLOC       7
#define ER_EMPTY_MAP    8
#define ER_ONE_CAMERA   9
#define ER_ONE_AMBIENT  10
#define ER_NO_LIGHT     11
#define ER_MAX_LIGHT    12
#define ER_NO_OBJ       13
#define ER_OBJ_TYPE     14
#define ER_COLOR_A      15
#define ER_COLOR_L      16
#define ER_SYNTAX       17
#define ER_OTHERS       100

// Define error messages
#define MS_AGC          "Usage: ./miniRT <scene>.rt, one argument needed\n"
#define MS_USAGE        "Usage: ./miniRT <scene>.rt\n"
#define MS_MLX          "Cannot initialize MLX\n"
#define MS_FILE         "Error File Name '.rt'\n"
#define MS_OPEN_FILE    "Couldn't open requested file\n"
#define MS_NOT_RT       "File extension is not '.rt'.\n"
#define MS_MALLOC       "Cannot allocate dynamic memory\n"
#define MS_EMPTY_MAP    "Empty map\n"
#define MS_ONE_CAMERA   "One camera needed\n"
#define MS_ONE_AMBIENT  "One ambient light needed\n"
#define MS_NO_LIGHT     "No light found\n"
#define MS_MAX_LIGHT    "Too many light sources\n"
#define MS_NO_OBJ       "No object found\n"
#define MS_OBJ_TYPE     "Undefined object type\n"
#define MS_COLOR_A      "Wrong color syntax for ambient lighting\n"
#define MS_COLOR_L      "Wrong color syntax for light source\n"
#define MS_SYNTAX       "Syntax: file format misconfiguration\n"
#define MS_OTHERS       "Other errors\n"

// Create an array of error messages
const char *MS_ER[] = 
{
    [OK] = "Operation completed successfully\n",
    [NOK] = "General error\n",
    [ER_AGC] = MS_AGC,
    [ER_MLX] = MS_MLX,
    [ER_FILE] = MS_FILE,
    [ER_NOT_RT] = MS_NOT_RT,
    [ER_OPEN_FILE] = MS_OPEN_FILE,
    [ER_MALLOC] = MS_MALLOC,
    [ER_EMPTY_MAP] = MS_EMPTY_MAP,
    [ER_ONE_CAMERA] = MS_ONE_CAMERA,
    [ER_ONE_AMBIENT] = MS_ONE_AMBIENT,
    [ER_NO_LIGHT] = MS_NO_LIGHT,
    [ER_MAX_LIGHT] = MS_MAX_LIGHT,
    [ER_NO_OBJ] = MS_NO_OBJ,
    [ER_OBJ_TYPE] = MS_OBJ_TYPE,
    [ER_COLOR_A] = MS_COLOR_A,
    [ER_COLOR_L] = MS_COLOR_L,
    [ER_SYNTAX] = MS_SYNTAX,
    [ER_OTHERS] = MS_OTHERS
};

// Window sizes
# ifdef __APPLE__
#  define WIDTH 1440
#  define HEIGHT 810
# else
#  define WIDTH 1920
#  define HEIGHT 1080
# endif

# define HALF_W WIDTH / 2
# define HALF_H HEIGHT / 2

// Define raytracing parameters 
# define _RT_MAX_ITX 200

// Define the number of threads
# define _RT_NUM_THREADS 4

// Define colors
# define WHITE 0xFFFFFF
# define GOLD 0xFFD700
# define OLIVE 0x808000
# define LIME 0x32CD32
# define PURPLE 0x800080
# define BLACK 0x000000

// Keyboard define
# ifdef __APPLE__
#  define MOUSE_LB      1
#  define MSCROLL_UP    4
#  define MSCROLL_DOWN  5
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
#  define KEY_R         15
#  define KEY_C         8
#  define KEY_V         9
#  define KEYPRESS    	2
#  define DESTROYNOTIFY 17
#  define KEY_SPACE     49
#  define KEY_LCTRL     256
#  define KEY_LSHIFT    257
#  define AKEY_L        123
#  define AKEY_R        124
#  define AKEY_D        125
#  define AKEY_U        126
# else
#  define MOUSE_LB     1
#  define MSCROLL_UP   4
#  define MSCROLL_DOWN 5
#  define KEY_A        97      
#  define KEY_D        100
#  define KEY_W        119
#  define KEY_S        115
#  define KEY_R        114
#  define KEY_LEFT     65361
#  define KEY_RIGHT    65363
#  define KEY_UP       65362
#  define KEY_DOWN     65364
#  define KEY_ESC      65307
#  define KEY_Q        113
#  define KEY_C        99
#  define   KEY_V      118
#  define   KEY_LCTRL  65507
#  define   KEY_LSHIFT 65505
#  define	KEY_SPACE  32
#  define	AKEY_L     65361
#  define	AKEY_U     65362
#  define	AKEY_R     65363
#  define	AKEY_D     65364
#  define	KEY_ESC    65307
# endif

// hook events
enum e_events
{
	KEY_PRESS = 2,
	KEY_RELEASE,
	MOUSEDOWN,
	MOUSEUP,
	MOUSEMOVE,
	EXPOSE = 12,
	KEY_DESTROY = 17
};

#endif
