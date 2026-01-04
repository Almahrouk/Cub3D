#include "cub3D.h"

int check_invalid_char(char c)
{
    if (c == '0' || c == '1' || c == ' ' || c == 'N' || c == 'S'
        || c == 'E' || c == 'W')
        return (1);
    return (0);
}