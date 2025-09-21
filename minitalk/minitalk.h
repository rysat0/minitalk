/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minitalk.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rysato <rysato@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/13 15:19:21 by rysato            #+#    #+#             */
/*   Updated: 2025/09/21 19:36:16 by rysato           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINITALK_H
# define MINITALK_H

# include <signal.h>
# include <stdlib.h>
# include <sys/types.h>
# include <unistd.h>
# include "ft_printf/includes/ft_printf.h"

typedef struct s_state
{
	unsigned char	buf;
	int				bits;
	pid_t			sender;
}					t_state;

# define ACK_BIT 1
# define FIN_BIT 2

#endif
