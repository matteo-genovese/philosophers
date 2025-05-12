/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checks.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgenoves <mgenoves@student.42roma.it>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/23 22:16:19 by mgenoves          #+#    #+#             */
/*   Updated: 2025/01/23 22:20:25 by mgenoves         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CHECKS_H
# define CHECKS_H

typedef struct s_data	t_data;

int	check_args(int argc, char **argv, t_data *data);
int	ft_atoi(char *str);
int	ft_isdigit(int c);
int	ft_is_string_digits(char *str);

#endif
