/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   controls.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/06 18:30:27 by marvin            #+#    #+#             */
/*   Updated: 2025/01/06 18:30:27 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#ifndef CONTROLS_H
# define CONTROLS_H

# ifdef __linux__

enum e_keysyms
{
	MOUSE_LMB = 1,
	MSCROLL_UP = 4,
	MSCROLL_DOWN,
	KEY_W = 119,
	KEY_A = 97,
	KEY_S = 115,
	KEY_D = 100,
	KEY_R = 114,
	KEY_LCTRL = 65507,
	KEY_LSHIFT = 65505,
	KEY_SPACE = 32,
	AKEY_L = 65361,
	AKEY_U,
	AKEY_R,
	AKEY_D,
	KEY_ESC = 65307
};
# endif // !__linux__

# ifdef __MACH__

enum e_keysyms
{
	MSCROLL_UP = 4,
	MSCROLL_DOWN,
	KEY_ESC = 53,
	KEY_A = 0,
	KEY_S = 1,
	KEY_D = 2,
	KEY_W = 13,
	KEY_R = 15,
	KEY_SPACE = 49,
	KEY_LCTRL = 256,
	KEY_LSHIFT = 257,
	AKEY_L = 123,
	AKEY_R,
	AKEY_D,
	AKEY_U
};

enum e_mouse
{
	MOUSE_LMB = 1
};

# endif

enum e_events
{
	ON_KEYDOWN = 2,
	ON_KEYUP,
	ON_MOUSEDOWN,
	ON_MOUSEUP,
	ON_MOUSEMOVE,
	ON_EXPOSE = 12,
	ON_DESTROY = 17
};

#endif // !KEYS_H
