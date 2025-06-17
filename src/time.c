/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msokolov <msokolov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/17 15:10:32 by msokolov          #+#    #+#             */
/*   Updated: 2025/06/17 17:38:04 by msokolov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <philo.h>

long long	set_time(void)
{
	struct timeval time;

	if (gettimeofday(&time, NULL) == -1)
		return (printf(RED"ERROR [gettimeofday]\n"RESET), 0);
	return((time.tv_sec * 1000) + (time.tv_usec / 1000));
}
