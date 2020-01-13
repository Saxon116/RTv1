/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lucmarti <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/18 14:07:36 by lucmarti          #+#    #+#             */
/*   Updated: 2019/11/06 13:18:54 by lucmarti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

static int	get_act(char *line, struct s_display *dp)
{
	int		i;

	if (line && line[0] == '#')
		return (3);
	i = ft_strchr(line, ':') ? ft_strchr(line, ':') - line : -1;
	if (i != -1 && line[i + 1] == '\0')
		return (0);
	if (ft_strnequ(line, "cam", i - 1))
		return (parse_camera(line + i + 1, dp));
	else if (ft_strnequ(line, "light", i - 1))
		return (parse_light(line + i + 1, dp));
	else if (ft_strnequ(line, "sphere", i - 1))
		return (parse_sphere(line + i + 1, dp));
	else if (ft_strnequ(line, "plane", i - 1))
		return (parse_plane(line + i + 1, dp));
	else if (ft_strnequ(line, "cone", i - 1))
		return (parse_cone(line + i + 1, dp));
	else if (ft_strnequ(line, "cylinder", i - 1))
		return (parse_cylinder(line + i + 1, dp));
	else
		return (0);
	return (2);
}

static void	parse_data_end(struct s_parser *data, struct s_display *dp, int err)
{
	ft_lstfree_all(&(data->lines));
	if (err)
	{
		free_obj(dp);
		ft_printf("%sError found in execution. Aborting...%s\n", LRED, LRES);
		exit(1);
	}
}

static void	parse_data(struct s_parser *data, struct s_display *dp)
{
	t_list	*node;
	int		i;
	int		err[2];

	err[0] = 0;
	i = 0;
	node = data->lines;
	while (node)
	{
		ft_printf("[Object %s%3i%s] Status : %s\\%s", LGRE, i, LRES, "\x1b[33m"
				, LRES);
		if ((err[1] = get_act(node->content, dp)) == 0)
		{
			ft_printf("\r[Object %s%3i%s] Status : %sError%s -> `%s`\n", LRED, i
					, LRES, LRED, LRES, node->content);
			err[0] = 1;
			break ;
		}
		err[1] == 1 ? ft_printf("\r[Object %s%3i%s] Status : %sOK%s\n", LGRE, i
				, LRES, LGRE, LRES) : ft_printf("\r");
		node = node->next;
		++i;
	}
	ft_printf("\x1b[33mAll objects have been processed%s\n", LRES);
	parse_data_end(data, dp, err[0]);
}

static void	end_parser(struct s_display *dp, struct s_parser data)
{
	int	i;

	i = 0;
	if (data.size == 0)
	{
		ft_printf("%sError no data. Aborting...%s\n", LRED, LRES);
		exit(1);
	}
	dp->objs = malloc(sizeof(struct s_obj **) * (data.size + 1));
	dp->lights = malloc(sizeof(struct s_obj **) * (data.size + 1));
	while (i < data.size)
	{
		dp->objs[i] = NULL;
		dp->lights[i++] = NULL;
	}
	dp->objs[data.size - 1] = NULL;
	dp->lights[data.size - 1] = NULL;
	dp->light_count = 0;
	parse_data(&data, dp);
}

void		init_parser(char *file, struct s_display *dp)
{
	struct s_parser data;
	char			*input;
	int				fd;

	data.lines = NULL;
	data.size = 0;
	input = NULL;
	if ((fd = open(file, O_RDONLY)) < 3)
		error("Reading failed");
	while (get_next_line(fd, &input) > 0)
	{
		if (!data.lines)
			data.lines = ft_lstnew(input, sizeof(input));
		else if (input[0] != '\0')
			ft_lstadd_back(&(data.lines), ft_lstnew(input, sizeof(input)));
		data.size += input[0] != '\0' ? 1 : 0;
		ft_memdel((void **)&input);
	}
	if (close(fd))
		error("Closing file failed");
	ft_memdel((void **)&input);
	end_parser(dp, data);
}
