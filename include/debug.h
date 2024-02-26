/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   debug.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: antoda-s <antoda-s@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/04 18:49:28 by antoda-s          #+#    #+#             */
/*   Updated: 2024/02/26 02:08:33 by antoda-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef DEBUG_H
# define DEBUG_H

/* ************************************************************************** */
///	CONSTANTS DEBUG
/* ************************************************************************** */
# ifndef _PRINT
#  define _PRINT 1
#  define _NOPRINT 0
# endif
# ifndef _SHOW_VARS_
#  define _SHOW_VARS_ 0
# endif
# ifndef _SHOW_MATRIX_
#  define _SHOW_MATRIX_ 1
# endif
# ifndef _SHOW_KEY_
#  define _SHOW_KEY_ 0
# endif
# ifndef MY_DEBUG
#  define MY_DEBUG 0
# endif
# ifndef MY_DEBUG_COLOR
#  define MY_DEBUG_COLOR 0
# endif
# ifndef MY_START
#  define MY_START 255
# endif
# ifndef MY_DEBUGMALLOC_
#  define MY_DEBUGMALLOC_ 0
# endif
# ifndef _MLX_TEST_
#  define _MLX_TEST_ 1
# endif
# ifndef _MOUSE_TEST_
#  define _MOUSE_TEST_ 1
# endif
# ifndef DEBUG_FREE
#  define DEBUG_FREE 1
# endif
# ifndef DEBUG_ALL
#  define DEBUG_ALL 0
# endif
# ifndef DEBUG_COLOR
#  define DEBUG_COLOR 1
# endif
# ifndef DEBUG_ARRAY
#  define DEBUG_ARRAY 0
# endif


/* ************************************************************************** */
typedef struct s_debug_msg
{
	const char		*msg;
	int				status;
	int				len;
	const char		*msg_header;
	char			*color;
}				t_debug_msg;
#endif