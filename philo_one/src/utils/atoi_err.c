/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   atoi_err.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Sergey <mrserjy@gmail.com>                 +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/13 14:26:10 by Sergey            #+#    #+#             */
/*   Updated: 2021/12/13 14:53:52 by Sergey           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/philosophers.h"

static const char	*skipspaces(const char *nptr)
{
	while (*nptr == ' ' || *nptr == '\f' || *nptr == '\n'
		|| *nptr == '\r' || *nptr == '\t' || *nptr == '\v')
		nptr++;
	return (nptr);
}

static const char	*getsign(const char *nptr, int *minuses)
{
	if (*nptr == '-' || *nptr == '+')
	{
		if (*nptr == '-')
			*minuses = -1;
		nptr++;
	}
	return (nptr);
}

int	ft_atoi_err(const char *nptr, int *status)
{
	int				minuses;
	int				rank;
	long long int	r;

	r = 0;
	*status |= 0;
	rank = 0;
	minuses = 1;
	nptr = skipspaces(nptr);
	nptr = getsign(nptr, &minuses);
	while (*nptr >= '0' && *nptr <= '9')
	{
		r = r * 10 + (*nptr++ - ('0'));
		rank++;
		if ((r * minuses) > INT_MAX || (r * minuses) < INT_MIN)
		{
			*status |= 1;
			return (0);
		}
	}
	return (r * (minuses));
}