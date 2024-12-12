#include "minirt.h"

char *read_file(t_minirt *minirt, char *file)
{
    int     fd;
    char    *line;
    char    *data;
    size_t  total_size;
    size_t  line_len;

    total_size = 0;
    data = NULL;

    // Open the file
    fd = open(file, O_RDONLY);
    if (fd < 0)
        errors(ER_OPEN_FILE, minirt);
    while (1)
    {
        // Read the next line
        line = get_next_line(fd);
        if (!line)
            break;
        // Skip comments (#) and blank lines
        if (!ft_strchr("\n#", line[0]))
        {
            line_len = ft_strlen(line);
            // Reallocate memory for the new line
            data = realloc(data, total_size + line_len + 1);
            if (!data)
            {
                free(line);
                close(fd);
                errors(ER_MALLOC("realloc"), minirt);
            }

            // Append the line to `data`
            ft_memcpy(data + total_size, line, line_len);
            total_size += line_len;
            data[total_size] = '\0'; // Null-terminate the data buffer
        }
        free(line); // Free the line after processing
    }
    close(fd);
    // Handle empty files
    if (!data || !ft_strlen(data))
        errors(ER_EMPTY_MAP, minirt);
    return (data);
}
