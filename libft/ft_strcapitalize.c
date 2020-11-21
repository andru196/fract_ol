/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strcapitalize.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sfalia-f <sfalia-f@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/22 20:02:54 by ycorrupt          #+#    #+#             */
/*   Updated: 2020/11/21 22:09:30 by sfalia-f         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strcapitalize(char *s)
{
	int		i;

	if (s)
	{
		i = 0;
		while (s[i])
		{
			if (i == 0 || (!ft_isalnum(s[i - 1]) && ft_isalpha(s[i])))
				s[i] = ft_toupper(s[i]);
			else
				s[i] = ft_tolower(s[i]);
			++i;
		}
	}
	return (s);
}
