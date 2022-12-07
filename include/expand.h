/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fsnelder <fsnelder@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/07 13:29:40 by fsnelder          #+#    #+#             */
/*   Updated: 2022/12/07 13:34:10 by fsnelder         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXPAND_H
# define EXPAND_H

// 1234"$variable test"'abcde'abcd$?
// -> 1234value testabcdeabcd0
t_string	expand_word(const char *src, const char **envp);

#endif
