#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>

#define DEVICE_FILE "/dev/metallica"
#define COMMAND_BUFFER_SIZE 2048

int main()
{
    int fd;
    char command[COMMAND_BUFFER_SIZE];
    ssize_t bytes_read;

    fd = open(DEVICE_FILE, O_RDONLY);
    if (fd < 0)
    {
        perror("Failed to open the device file");
        return 1;
    }

    while (1)
    {
        bytes_read = read(fd, command, COMMAND_BUFFER_SIZE - 1);
        if (bytes_read < 0)
        {
            perror("Failed to read the device file");
            close(fd);
            return 1;
        }

        command[bytes_read] = '\0';

        if (strlen(command) > 0)
        {
            char play_command[COMMAND_BUFFER_SIZE + 50];
            snprintf(play_command, sizeof(play_command), "aplay %s", command);
            system(play_command);
            memset(command, 0, sizeof(command));
        }

        sleep(1);  // Poll every second
    }

    close(fd);
    return 0;
}
