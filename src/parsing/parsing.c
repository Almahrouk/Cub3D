#include "cub3D.h"

static void map_error(t_cub *cub, char *message)
{
    ft_exit(cub, message, MAP_ERROR);
}

static void strip_line_end(char *line)
{
    int len;

    len = ft_strlen(line);
    while (len > 0 && (line[len - 1] == '\n' || line[len - 1] == '\r'))
        line[--len] = '\0';
}

static void normalize_tabs(char *line)
{
    int i;

    i = 0;
    while (line[i])
    {
        if (line[i] == '\t')
            line[i] = ' ';
        i++;
    }
}

static int is_line_empty(char *line)
{
    int i;

    i = 0;
    while (line[i])
    {
        if (line[i] != ' ' && line[i] != '\t')
            return (0);
        i++;
    }
    return (1);
}

static int is_map_char(char c)
{
    return (c == '0' || c == '1' || c == 'N'
        || c == 'S' || c == 'E' || c == 'W' || c == ' ');
}

static int is_map_line(char *line)
{
    int i;
    int has_tile;

    i = 0;
    has_tile = 0;
    while (line[i])
    {
        if (!is_map_char(line[i]))
            return (0);
        if (line[i] != ' ')
            has_tile = 1;
        i++;
    }
    return (has_tile);
}

static void parse_texture(t_cub *cub, char **dest, char *line, int i)
{
    int start;

    if (line[i + 2] != ' ' && line[i + 2] != '\t')
        ft_exit(cub, "Error\ninvalid texture path\n", PARSEING_TEXTURE_ERROR);
    i += 2;
    while (line[i] == ' ' || line[i] == '\t')
        i++;
    if (line[i] == '\0')
        ft_exit(cub, "Error\nmissing texture path\n", PARSEING_TEXTURE_ERROR);
    start = i;
    while (line[i] && line[i] != ' ' && line[i] != '\t')
        i++;
    *dest = ft_substr(line, start, i - start);
    while (line[i] == ' ' || line[i] == '\t')
        i++;
    if (line[i] != '\0')
        ft_exit(cub, "Error\ninvalid texture path\n", PARSEING_TEXTURE_ERROR);
}

static void parse_color(t_cub *cub, char **dest, char *line, int i)
{
    int start;
    int end;

    if (line[i + 1] != ' ' && line[i + 1] != '\t')
        ft_exit(cub, "Error\ninvalid color format\n", PARSEING_TEXTURE_ERROR);
    i += 1;
    while (line[i] == ' ' || line[i] == '\t')
        i++;
    if (line[i] == '\0')
        ft_exit(cub, "Error\nmissing color value\n", PARSEING_TEXTURE_ERROR);
    start = i;
    end = ft_strlen(line);
    while (end > start && (line[end - 1] == ' ' || line[end - 1] == '\t'))
        end--;
    *dest = ft_substr(line, start, end - start);
}

static int parse_header_line(t_cub *cub, char *line)
{
    int i;

    i = 0;
    while (line[i] == ' ' || line[i] == '\t')
        i++;
    if (line[i] == '\0')
        return (1);
    if (ft_strncmp(&line[i], "NO", 2) == 0)
        parse_texture(cub, &cub->north_path, line, i);
    else if (ft_strncmp(&line[i], "SO", 2) == 0)
        parse_texture(cub, &cub->south_path, line, i);
    else if (ft_strncmp(&line[i], "WE", 2) == 0)
        parse_texture(cub, &cub->west_path, line, i);
    else if (ft_strncmp(&line[i], "EA", 2) == 0)
        parse_texture(cub, &cub->east_path, line, i);
    else if (line[i] == 'F')
        parse_color(cub, &cub->floor_color, line, i);
    else if (line[i] == 'C')
        parse_color(cub, &cub->ceiling_color, line, i);
    else
        return (0);
    return (1);
}

static void flood_fill(t_cub *cub, int start_x, int start_y)
{
    int w;
    int h;
    int max;
    int *stack_x;
    int *stack_y;
    char *visited;
    int top;

    w = cub->map_w;
    h = cub->map_h;
    max = w * h;
    stack_x = malloc(sizeof(int) * max);
    stack_y = malloc(sizeof(int) * max);
    visited = ft_calloc(max, sizeof(char));
    if (!stack_x || !stack_y || !visited)
        map_error(cub, "Error\nmemory allocation failed\n");
    top = 0;
    stack_x[top] = start_x;
    stack_y[top] = start_y;
    top++;
    while (top > 0)
    {
        int x = stack_x[--top];
        int y = stack_y[top];
        int idx = y * w + x;

        if (x < 0 || y < 0 || x >= w || y >= h)
            map_error(cub, "Error\nmap is not closed\n");
        if (visited[idx])
            continue;
        if (cub->map[y][x] == ' ')
            map_error(cub, "Error\nmap is not closed\n");
        if (cub->map[y][x] == '1')
            continue;
        visited[idx] = 1;
        if (x + 1 >= w || cub->map[y][x + 1] == ' ')
            map_error(cub, "Error\nmap is not closed\n");
        if (x - 1 < 0 || cub->map[y][x - 1] == ' ')
            map_error(cub, "Error\nmap is not closed\n");
        if (y + 1 >= h || cub->map[y + 1][x] == ' ')
            map_error(cub, "Error\nmap is not closed\n");
        if (y - 1 < 0 || cub->map[y - 1][x] == ' ')
            map_error(cub, "Error\nmap is not closed\n");
        if (cub->map[y][x + 1] != '1' && !visited[y * w + (x + 1)])
        {
            stack_x[top] = x + 1;
            stack_y[top] = y;
            top++;
        }
        if (cub->map[y][x - 1] != '1' && !visited[y * w + (x - 1)])
        {
            stack_x[top] = x - 1;
            stack_y[top] = y;
            top++;
        }
        if (cub->map[y + 1][x] != '1' && !visited[(y + 1) * w + x])
        {
            stack_x[top] = x;
            stack_y[top] = y + 1;
            top++;
        }
        if (cub->map[y - 1][x] != '1' && !visited[(y - 1) * w + x])
        {
            stack_x[top] = x;
            stack_y[top] = y - 1;
            top++;
        }
    }
    free(stack_x);
    free(stack_y);
    free(visited);
}

static void validate_map(t_cub *cub)
{
    int x;
    int y;
    int player_count;

    if (!cub->map || cub->map_h == 0 || cub->map_w == 0)
        map_error(cub, "Error\nempty map\n");
    player_count = 0;
    y = 0;
    while (y < cub->map_h)
    {
        x = 0;
        while (x < cub->map_w)
        {
            char c = cub->map[y][x];

            if (!is_map_char(c))
                map_error(cub, "Error\ninvalid map character\n");
            if (c == 'N' || c == 'S' || c == 'E' || c == 'W')
            {
                player_count++;
                cub->player_x = x;
                cub->player_y = y;
                cub->player_dir = c;
                cub->map[y][x] = '0';
            }
            x++;
        }
        y++;
    }
    if (player_count != 1)
        map_error(cub, "Error\ninvalid player count\n");
    y = 0;
    while (y < cub->map_h)
    {
        if (cub->map[y][0] == '0' || cub->map[y][cub->map_w - 1] == '0')
            map_error(cub, "Error\nmap is not closed\n");
        y++;
    }
    x = 0;
    while (x < cub->map_w)
    {
        if (cub->map[0][x] == '0' || cub->map[cub->map_h - 1][x] == '0')
            map_error(cub, "Error\nmap is not closed\n");
        x++;
    }
    flood_fill(cub, cub->player_x, cub->player_y);
}

static void build_map(t_cub *cub, t_list *lines)
{
    t_list  *tmp;
    int     i;
    int     max_w;

    if (!lines)
        map_error(cub, "Error\nmissing map\n");
    max_w = 0;
    tmp = lines;
    while (tmp)
    {
        int len = ft_strlen((char *)tmp->content);

        if (len > max_w)
            max_w = len;
        tmp = tmp->next;
    }
    cub->map_h = ft_lstsize(lines);
    cub->map_w = max_w;
    cub->map = malloc(sizeof(char *) * (cub->map_h + 1));
    if (!cub->map)
        map_error(cub, "Error\nmemory allocation failed\n");
    i = 0;
    while (lines)
    {
        char *src = (char *)lines->content;
        int len = ft_strlen(src);
        char *row = malloc(sizeof(char) * (cub->map_w + 1));

        if (!row)
            map_error(cub, "Error\nmemory allocation failed\n");
        ft_memset(row, ' ', cub->map_w);
        ft_memcpy(row, src, len);
        row[cub->map_w] = '\0';
        cub->map[i++] = row;
        free(src);
        tmp = lines;
        lines = lines->next;
        free(tmp);
    }
    cub->map[i] = NULL;
}

void parse_map(t_cub *cub)
{
    char    *line;
    t_list  *lines;

    lines = NULL;
    line = cub->line;
    cub->line = NULL;
    while (line)
    {
        strip_line_end(line);
        normalize_tabs(line);
        if (is_line_empty(line))
            map_error(cub, "Error\nempty line in map\n");
        ft_lstadd_back(&lines, ft_lstnew(line));
        line = get_next_line(cub->fd);
    }
    build_map(cub, lines);
    validate_map(cub);
}

void parsing(t_cub *cub)
{
    char *line;

    line = cub->line;
    cub->line = NULL;
    while (1)
    {
        if (!line)
            line = get_next_line(cub->fd);
        if (!line)
            map_error(cub, "Error\nmissing map\n");
        strip_line_end(line);
        normalize_tabs(line);
        if (is_line_empty(line))
        {
            free(line);
            line = NULL;
            continue;
        }
        if (is_map_line(line))
        {
            cub->line = line;
            return;
        }
        if (!parse_header_line(cub, line))
            map_error(cub, "Error\ninvalid header line\n");
        free(line);
        line = NULL;
    }
}
