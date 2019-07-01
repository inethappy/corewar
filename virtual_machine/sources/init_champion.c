/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_champion.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vkryvono <vkryvono@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/18 04:08:00 by vkryvono          #+#    #+#             */
/*   Updated: 2019/06/18 04:08:00 by vkryvono         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

static t_header	*get_header(int fd)
{
	t_header	*header;
	uint32_t	buff;

	header = ft_memalloc(sizeof(t_header));
	header->magic = COREWAR_EXEC_MAGIC;
	error(read(fd, &header->prog_name, PROG_NAME_LENGTH) < PROG_NAME_LENGTH,
		ERR_INVALID_BINARY);
	error(read(fd, &buff, REG_SIZE) < REG_SIZE, ERR_INVALID_BINARY);
	error(buff, "No null 4 bytes");
	error(read(fd, &buff, REG_SIZE) < REG_SIZE, ERR_INVALID_BINARY);
	header->prog_size = ft_swap32(buff);
	error(header->prog_size > CHAMP_MAX_SIZE, "Invalid prog_size");
	error(read(fd, &header->comment, COMMENT_LENGTH) < COMMENT_LENGTH,
		ERR_INVALID_BINARY);
	error(read(fd, &buff, REG_SIZE) < REG_SIZE, ERR_INVALID_BINARY);
	error(buff, "No null 4 bytes");
	return (header);
}

static int		get_file(char *path)
{
	char		*localname;
	char		*extension;
	int			fd;
	uint32_t	header;

	localname = ft_strrchr(path, '/');
	localname == NULL ? path : localname++;
	extension = ft_strrchr(path, '.');
	error(!(*extension), "File extension is not specified");
	error((extension <= localname), "Invalid filename");
	extension = ft_strdup(extension);
	error(ft_strcmp(extension, BINARY_EXTENSION), "Invalid file extension");
	error((fd = open(path, O_RDONLY)) == -1, ERR_OPEN_BINARY);
	error(read(fd, &header, sizeof(uint32_t)) < 0, ERR_READ_BINARY);
	error(header != ft_swap32(COREWAR_EXEC_MAGIC), ERR_INVALID_HEADER);
	ft_strdel(&extension);
	return (fd);
}

int				new_champion(char *path, t_champion *champion)
{
	size_t	size;
	int		fd;

	if (champion == NULL)
		return (1);
	fd = get_file(path);
	champion->header = get_header(fd);
	champion->code = ft_memalloc(champion->header->prog_size * sizeof(uint8_t));
	ft_bzero(champion->code, champion->header->prog_size);
	size = read(fd, champion->code, champion->header->prog_size);
	error(size < champion->header->prog_size, ERR_INVALID_BINARY);
	error(read(fd, NULL, 1) != 0, ERR_INVALID_BINARY);
	close(fd);
	return (0);
}

static void		swap(t_list *a, t_list *b)
{
	t_champion	*champ;

	champ = a->content;
	a->content = b->content;
	b->content = champ;
}

void			sort_champions(void)
{
	int			swapped;
	t_champion	*cht;
	t_champion	*ncht;
	t_list		*tmp;
	t_list		*ltmp;

	ltmp = NULL;
	swapped = 1;
	while (swapped)
	{
		swapped = 0;
		tmp = g_game.players;
		while (tmp->next != ltmp)
		{
			cht = tmp->content;
			ncht = tmp->next->content;
			if (cht->number > ncht->number)
			{
				swap(tmp, tmp->next);
				swapped = 1;
			}
			tmp = tmp->next;
		}
		ltmp = tmp;
	}
}
