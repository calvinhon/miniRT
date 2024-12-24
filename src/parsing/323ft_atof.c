/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   323ft_atof.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
<<<<<<< HEAD:src/parsing/323ft_atof.c
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/16 18:52:25 by honguyen          #+#    #+#             */
/*   Updated: 2024/12/20 13:48:52 by marvin           ###   ########.fr       */
=======
/*   By: honguyen <honguyen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/16 18:52:25 by honguyen          #+#    #+#             */
/*   Updated: 2024/12/21 14:39:18 by honguyen         ###   ########.fr       */
>>>>>>> fac9762a1543c7c015675c63cef213e9d71331ec:src/parsing/ft_atof.c
/*                                                                            */
/* ************************************************************************** */


#include <stdbool.h>
#include <stdio.h>

static void	skip_whitespace(const char **str)
{
	while (**str == ' ' || **str == '\t' || **str == '\n')
		(*str)++;
}

static int	parse_sign(const char **str)
{
	if (**str == '-')
	{
		(*str)++;
		return (-1);
	}
	else if (**str == '+')
	{
		(*str)++;
	}
	return (1);
}

static float	parse_integer_part(const char **str)
{
	float	result;

	result = 0.0;

	while (**str >= '0' && **str <= '9')
	{
		result = result * 10 + (**str - '0');
		(*str)++;
	}
	return (result);
}

static float	parse_fractional_part(const char **str)
{
	float	fraction;
	float	divisor;

	fraction = 0;
	divisor = 10.0;
	if (**str == '.')
	{
		(*str)++;
		while (**str >= '0' && **str <= '9')
		{
			fraction += (**str - '0') / divisor;
			divisor *= 10;
			(*str)++;
		}
	}
	return (fraction);
}

float	ft_atof(const char *str)
{
	float	result;
	int		sign;

	skip_whitespace(&str);
	sign = parse_sign(&str);
	result = parse_integer_part(&str);
	result += parse_fractional_part(&str);
	return (result * sign);
}
