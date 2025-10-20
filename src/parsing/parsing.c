#include "cub3D.h"

static void strip_cr(char *line)
{
    int len;

    len = ft_strlen(line);
    if (len > 0 && line[len - 1] == '\r')
        line[len - 1] = '\0';
}

static void parse_texture(t_cub *cub, char **dest, char *line, int i)
{
    int start;

    i += 2;
    while (line[i] == ' ' || line[i] == '\t' || line[i] == '\r')
        i++;
    start = i;
    while (line[i] && line[i] != ' ' && line[i] != '\t'
           && line[i] != '\n' && line[i] != '\r')
        i++;
    *dest = ft_substr(line, start, i - start);
    while (line[i] == ' ' || line[i] == '\t' || line[i] == '\r')
        i++;
    if (line[i] != '\n' && line[i] != '\0')
        ft_exit(cub, "Error\ninvalid texture path\n", PARSEING_TEXTURE_ERROR);
    // printf("%s texture path: %s\n", id, *dest);
}

void parse_line(t_cub *cub, char *line)
{
    int i = 0;

    strip_cr(line);
    while (line[i] == ' ' || line[i] == '\t')
        i++;
    if (line[i] == '\0')
        return;
    if (ft_strncmp(&line[i], "NO", 2) == 0)
        parse_texture(cub, &cub->north_path, line, i);
    else if (ft_strncmp(&line[i], "SO", 2) == 0)
        parse_texture(cub, &cub->south_path, line, i);
    else if (ft_strncmp(&line[i], "WE", 2) == 0)
        parse_texture(cub, &cub->west_path, line, i);
    else if (ft_strncmp(&line[i], "EA", 2) == 0)
        parse_texture(cub, &cub->east_path, line, i);
    else
        return;
}

	 // abeer testing
void parse_map(t_cub *cub)
{
    char    *line;
    t_list  *lines = NULL;
    int     i = 0;

    while ((line = get_next_line(cub->fd)))
    {
        if (ft_strchr(line, '1') || ft_strchr(line, '0'))
            ft_lstadd_back(&lines, ft_lstnew(ft_strdup(line)));
        free(line);
    }
    cub->map_h = ft_lstsize(lines);
    cub->map = malloc(sizeof(char *) * (cub->map_h + 1));
    while (lines)
    {
        cub->map[i++] = lines->content;
        t_list *tmp = lines;
        lines = lines->next;
        free(tmp);
    }
    cub->map[i] = NULL;
}
//

void parsing(t_cub *cub)
{
    if (cub->line)
    {
        strip_cr(cub->line);
        parse_line(cub, cub->line);
        free(cub->line);
        cub->line = NULL;
    }
    while ((cub->line = get_next_line(cub->fd)))
    {
        strip_cr(cub->line);
        parse_line(cub, cub->line);
        free(cub->line);
        cub->line = NULL;
    }
}