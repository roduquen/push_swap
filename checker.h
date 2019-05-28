/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checker.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: roduquen <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/05 00:59:58 by roduquen          #+#    #+#             */
/*   Updated: 2019/05/27 00:45:53 by roduquen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CHECKER_H
# define CHECKER_H

# include <SDL.h>

typedef struct		s_push_list
{
	int					number;
	struct s_push_list	*next;
}					t_push_list;

typedef struct		s_result
{
	int		reverse;
	int		ra;
	int		rb;
	int		rbb;
	int		actual;
	int		nbr_move_wait;
	int		total_wait;
	int		best_wait;
	int		nbr_move;
	int		total;
	int		best;
}					t_result;

typedef struct		s_check_list
{
	char				type;
	struct s_check_list	*next;
	struct s_check_list	*prev;
}					t_check_list;

typedef struct		s_visual
{
	char			enabled;
	char			color[3];
	int				len;
	int				ret;
	int				win_height;
	t_check_list	*list;
	t_check_list	*begin;
	SDL_Window		*window;
	SDL_Renderer	*renderer;
	SDL_Event		event;
	char			pause;
	char			exit;
	char			end;
	char			start;
}					t_visual;

int					list_size(t_push_list *a);
int					verify_list(t_push_list *a, t_push_list *b);
int					parse_stdin(t_push_list **a, t_push_list **b
	, t_visual *visu);

void				push_elem(t_push_list **a, t_push_list **b);
void				swap_elem(t_push_list **a);
void				rotate_elem(t_push_list **a);
void				reverse_rotate_elem(t_push_list **a);

void				push_write(t_push_list **list, t_push_list **lists
	, char type);
void				swap_write(t_push_list **list, t_push_list **lists
	, char type);
void				rotate_write(t_push_list **list, t_push_list **lists
	, char type);
void				reverse_rotate_write(t_push_list **list, t_push_list **lists
	, char type);

void				sort_list(t_push_list **a, t_push_list **b);
void				chose_right_option(t_push_list **a, t_push_list **b);
void				check_better_num(t_push_list *a, t_push_list *b
	, t_result *res);
int					sort_three_elem(t_push_list **a, int len);
int					sort_four_elem(t_push_list **a, t_push_list **b, int len);

int					fill_the_visual_instruction(t_visual *visu
	, t_check_list *list, int inst);
int					free_visual_list(t_visual *visu);

int					check_do_and_leave_the_visual(t_visual *visu
	, t_push_list **a, t_push_list **b);
void				do_the_instruction(int inst, t_push_list **a
	, t_push_list **b, t_visual *visu);
void				do_the_reverse_instruction(int inst, t_push_list **a
	, t_push_list **b);
int					check_if_stdin_formated(char *buffer);
int					re_init_and_translate_lists(t_check_list *list
	, t_push_list **a, t_push_list **b);
void				commands(t_visual *visu, t_push_list **a, t_push_list **b);
void				create_renderer(t_visual *visu, t_push_list *a
	, t_push_list *b);

#endif
