#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include "main.h"
#include <string.h>

/**
 * append_text_to_file - Appends text to the end of a file.
 * @filename: The name of the file.
 * @text_content: The text content to append.
 *
 * Return: 1 on success, -1 on failure.
 */
int append_text_to_file(const char *filename, char *text_content)
{
	int fd, write_status;
	mode_t mode = S_IRUSR | S_IWUSR;

	if (filename == NULL)
		return (-1);

	fd = open(filename, O_WRONLY | O_APPEND, mode);
	if (fd == -1)
		return (-1);

	if (text_content != NULL)
	{
		write_status = write(fd, text_content, strlen(text_content));
		if (write_status == -1)
		{
			close(fd);
			return (-1);
		}
	}

	close(fd);
	return (1);
}
