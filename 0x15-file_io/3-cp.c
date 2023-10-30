#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include "main.h"

#define BUFFER_SIZE 1024

/**
 * check_arguments - Checks the command-line arguments.
 * @argc: The number of command-line arguments.
 * @argv: An array of strings containing the arguments.
 */
void check_arguments(int argc, char **argv)
{
	if (argc != 3)
	{
		dprintf(STDERR_FILENO, "Usage: cp file_from file_to\n");
		exit(97);
	}
}

/**
 * open_file - Opens a file with the specified mode and permissions.
 * @filename: The name of the file to open.
 * @mode: The mode to open the file (e.g., O_RDONLY, O_WRONLY).
 * @permissions: The file permissions to set.
 * @error_code: The error code to exit with if opening fails.
 * @read_mode: If true, set the file descriptor
 * for reading; otherwise, for writing.
 * @error_message: The error message to print if opening fails.
 *
 * Return: The file descriptor on success;
 * exits with an error code on failure.
 */
int open_file(
		const char *filename,
		int mode, mode_t permissions,
		int error_code,
		int read_mode,
		const char *error_message
		)
{
	int fd = -1;

	fd = open(filename, mode, permissions);
	if (fd == -1)
	{
		dprintf(STDERR_FILENO, "Error: %s %s\n", error_message, filename);
		exit(error_code);
	}

	if (read_mode)
	{
		if (read(fd, NULL, 0) == -1)
		{
			dprintf(STDERR_FILENO, "Error: Can't read from file %s\n", filename);
			close(fd);
			exit(98);
		}
	}
	else
	{
		if (write(fd, NULL, 0) == -1)
		{
			dprintf(STDERR_FILENO, "Error: Can't write to %s\n", filename);
			close(fd);
			exit(99);
		}
	}

	return (fd);
}

/**
 * main - Copies the content of one file to another.
 * @argc: The number of command-line arguments.
 * @argv: An array of strings containing the arguments.
 *
 * Return: 0 on success, or exit with an error code.
 */
int main(int argc, char **argv)
{
	int fd_from, fd_to;
	char buffer[BUFFER_SIZE];
	int bytes_read, bytes_written;

	check_arguments(argc, argv);

	fd_from = open_file(argv[1], O_RDONLY, 0, 98, 1, "Can't read from file");
	fd_to = open_file(
			argv[2],
			O_WRONLY | O_CREAT | O_TRUNC,
			0664, 99, 0, "Can't write to");

	while ((bytes_read = read(fd_from, buffer, BUFFER_SIZE)) > 0)
	{
		bytes_written = write(fd_to, buffer, bytes_read);
		if (bytes_written != bytes_read)
		{
			dprintf(STDERR_FILENO, "Error: Can't write to %s\n", argv[2]);
			close(fd_from);
			close(fd_to);
			exit(99);
		}
	}

	close(fd_from);
	close(fd_to);

	return (0);
}
