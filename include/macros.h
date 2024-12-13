#ifndef MACROS_H
# define MACROS_H

#ifdef __APPLE__
	# define ESC 53
#else
	# define ESC 65307
	# define LEFT 65361
	# define UP 65362
	# define RIGHT 65363
	# define DOWN 65364
	# define W 119
	# define A 97
	# define S 115
	# define D 100
#endif

#endif