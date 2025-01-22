/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   macros.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nth <nth@student.42abudhabi.ae>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/04 19:57:40 by nth          #+#    #+#             */
/*   Updated: 2024/10/07 05:44:38 by nth         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MACROS_H
# define MACROS_H

# define FRAME_W 1600
# define FRAME_H  900

# define OS_MACOS 	0
# define LIGHTS_MAX 100
# define SHAPES_MAX 100

# define STEP_SKIP 3
# define INTP_THRES 20

# ifndef _RT_REFLECTION_DEPTH
#  define _RT_REFLECTION_DEPTH 4
# endif // !_RT_REFLECTION_DEPTH

# ifndef SPOTLIGHT_FALLOFF
#  define SPOTLIGHT_FALLOFF 2.0f
# endif // !SPOTLIGHT_FALLOFF

# define _RT_NUM_THREADS 10

# define _RT_MAX_ITX 200
# define _RT_MIN_INTENSITY 0.05f

# define MOVE_SPEED 2.f
# define PITCH_SPEED 0.1f
# define YAW_SPEED 0.1f

# ifdef __MACH__
#  undef OS_MACOS
#  define OS_MACOS 1
# endif // !__MACH__

//---------------------------------//
//----------- ERROR CODES ---------//
//---------------------------------//

// Define error codes using enum
typedef enum e_error_code
{
    CER_OK = 0,
    CER_NOK,
    CER_AGC,
    CER_MLX,
    CER_MLX_WIN,
    CER_FILE,
    CER_NOT_RT,
    CER_NO_FILE,
    CER_OPEN_FILE,
    CER_MALLOC,
    CER_EMPTY_MAP,
    CER_ONE_CAMERA,
    CER_ONE_AMBIENT,
    CER_NO_LIGHT,
    CER_MAX_LIGHT,
    CER_NO_OBJ,
    CER_OBJ_TYPE,
    CER_COLOR_A,
    CER_COLOR_L,
    CER_SYNTAX,
    CER_AMBIENT_DEFINED,
    CER_AMBIENT_FORMAT,
    CER_AMBIENT_VALUE,
    CER_AMBIENT_COLOR,
    CER_AMBIENT_COLOR_VALUE,
    CER_MAX_LIGHTS,
    CER_LIGHT_FORMAT,
    CER_LIGHT_VALUE,
    CER_LIGHT_COLOR,
    CER_LIGHT_COLOR_VALUE,
    CER_CAM_DEFINED,
    CER_CAM_FORMAT,
    CER_CAM_FOV,
    CER_MAX_SHAPES,
    CER_OBJ_FORMAT,
    CER_OBJ_VALUE,
    CER_VEC4_FORMAT,
    CER_COLOR_FORMAT,
    CER_COLOR_VALUE,
    CER_FLOAT_VALUE,
    CER_M_FORMAT,
    CER_M_VALUE,
    CER_M_BUMP_FORMAT,
    CER_M_CHECKER,
    CER_EXPECT_CHECKER,
    CER_EXPECT_XPM,
    CER_EXPECT_M,
    CER_EM2,
    CER_EXPECT_M_TRAIT,
    CER_EMT2,
    CER_EXPECT_FLOAT,
    CER_EXPECT_INT,
    CER_EXPECT_TUPLE,
    CER_EXPECT_F_RANGE,
    CER_EXPECT_COLOR_RANGE,
    CER_EXPECT_COLOR_FORMAT,
    CER_E_FOV_RANGE,
    CER_EXPECT_TYPE_A,
    CER_EXPECT_TYPE_C,
    CER_EXPECT_TYPE_L,
    CER_EXPECT_TYPE_SL,
    CER_ESL,
    CER_E_TYPE_SP,
    CER_E_T_PL,
    CER_EXPECT_TYPE_CY,
    CER_ECY,
    CER_EXPECT_TYPE_CU,
    CER_ECU,
    CER_EXPECT_TYPE_CO,
    CER_ECO,
    CER_OTHERS = 100
} t_error_code;

// Define error messages as constants
# define ER_OK "No error\n"
# define ER_NOK "General error\n"
# define ER_AGC "Usage: ./miniRT <scene>.rt, one argument needed\n"
# define ER_MLX "Cannot initialize MLX\n"
# define ER_MLX_WIN "Cannot initialize MLX window\n"
# define ER_FILE "Error File Name '.rt'\n"
# define ER_NOT_RT "File extension is not '.rt'.\n"
# define ER_NO_FILE "Input file not existed.\n"
# define ER_OPEN_FILE "Couldn't open requested file\n"
# define ER_MALLOC "Cannot allocate dynamic memory\n"
# define ER_EMPTY_MAP "Empty map\n"
# define ER_ONE_CAMERA "One camera needed\n"
# define ER_ONE_AMBIENT "One ambient light needed\n"
# define ER_NO_LIGHT "No light found\n"
# define ER_MAX_LIGHT "Too many light sources\n"
# define ER_NO_OBJ "No object found\n"
# define ER_OBJ_TYPE "Undefined object type\n"
# define ER_COLOR_A "Wrong color syntax for ambient lighting\n"
# define ER_COLOR_L "Wrong color syntax for light source\n"
# define ER_SYNTAX "Syntax: file format misconfiguration\n"
# define ER_AMBIENT_DEFINED "Ambient light already set\n"
# define ER_AMBIENT_FORMAT "Invalid format for Ambient Light ratio\n"
# define ER_AMBIENT_VALUE "Invalid value for Ambient Light ratio\n"
# define ER_AMBIENT_COLOR "Invalid format for Ambient Light color\n"
# define ER_AMBIENT_COLOR_VALUE "Invalid value for Ambient Light color\n"
# define ER_MAX_LIGHTS "Maximum number of lights reached\n"
# define ER_LIGHT_FORMAT "Invalid format for Light Object\n"
# define ER_LIGHT_VALUE "Invalid value for Light Object\n"
# define ER_LIGHT_COLOR "Invalid format for Light Object color\n"
# define ER_LIGHT_COLOR_VALUE "Invalid value for Light Object color\n"
# define ER_CAM_DEFINED "Camera is already defined\n"
# define ER_CAM_FORMAT "Invalid format for Camera Object\n"
# define ER_CAM_FOV "Invalid value for Camera FOV\n"
# define ER_MAX_SHAPES "Maximum number of shapes reached\n"
# define ER_OBJ_FORMAT "Invalid format for Object\n"
# define ER_OBJ_VALUE "Invalid value for Object Attribute\n"
# define ER_VEC4_FORMAT "Invalid format for Vector4\n"
# define ER_COLOR_FORMAT "Invalid format for Color\n"
# define ER_COLOR_VALUE "Invalid value for Color\n"
# define ER_FLOAT_VALUE "Invalid value for floating-point number\n"
# define ER_M_FORMAT "Invalid format for Material\n"
# define ER_M_VALUE "Invalid value for Material Attribute\n"
# define ER_M_BUMP_FORMAT "Invalid format for Bump Map\n"
# define ER_M_CHECKER "Invalid format for Checker Map\n"
# define ER_EXPECT_CHECKER "Expected: checker=<yes/no>\n"
# define ER_EXPECT_XPM "Expected: XPM file\n"
# define ER_EXPECT_M "Expected: M <material.trait>=<float>,<material.trait>\n"
# define ER_EM2 "=<float>,<etc>\n\tUsing default values...\n"
# define ER_EXPECT_M_TRAIT "Expected: Valid Material Trait: [ambient, diffuse, specular, sheen]\n"
# define ER_EMT2 "diffuse, specular, sheen]\n\tUsing default values...\n"
# define ER_EXPECT_FLOAT "Expected: valid floating-point number.\n"
# define ER_EXPECT_INT "Expected: valid integer number.\n"
# define ER_EXPECT_TUPLE "Expected: Tuple in the format <x>,<y>,<z>\n"
# define ER_EXPECT_F_RANGE "Expected: floating-point value in range [0.0, 1.0]\n"
# define ER_EXPECT_COLOR_RANGE "Expected: integer value in range [0, 255]\n"
# define ER_EXPECT_COLOR_FORMAT "Expected: Color in the format <R>,<G>,<B>\n"
# define ER_E_FOV_RANGE "Expected: floating-point value in range [0.0, 180.0]\n"
# define ER_EXPECT_TYPE_A "Expected:\n\tA <ratio> <R>,<G>,<B>\n"
# define ER_EXPECT_TYPE_C "Expected:\n\tC <x>,<y>,<z> <ox>,<oy>,<oz> <FOV>\n"
# define ER_EXPECT_TYPE_L "Expected:\n\tL <x>,<y>,<z> <ratio> [<R>,<G>,<B>]\n"
# define ER_EXPECT_TYPE_SL "Expected:\n\tSL <x>,<y>,<z> <ox>,<oy>,<oz> <ratio> <spot_angle> [<R>,<G>,<B>]\n"
# define ER_ESL "<ratio> <spot_angle> [<R>,<G>,<B>]\n"
# define ER_E_TYPE_SP "Expected:\n\tsp <x>,<y>,<z> <diameter> [<R>,<G>,<B>]\n"
# define ER_E_T_PL "Expected:\n\tpl <x>,<y>,<z> <ox>,<oy>,<oz> [<R>,<G>,<B>]\n"
# define ER_EXPECT_TYPE_CY "Expected:\n\tcy <x>,<y>,<z> <ox>,<oy>,<oz> <diameter> <height> [<R>,<G>,<B>]\n"
# define ER_ECY "<diameter> <height> [<R>,<G>,<B>]\n"
# define ER_EXPECT_TYPE_CU "Expected:\n\tcu <x>,<y>,<z> <ox>,<oy>,<oz> <side> [<R>,<G>,<B>]\n"
# define ER_ECU "<side> [<R>,<G>,<B>]\n"
# define ER_EXPECT_TYPE_CO "Expected:\n\tco <x>,<y>,<z> <ox>,<oy>,<oz> <diameter> <height> [<R>,<G>,<B>]\n"
# define ER_ECO "<diameter> <height> [<R>,<G>,<B>]\n"
# define ER_OTHERS "Other errors\n"

#endif // !MACROS_H