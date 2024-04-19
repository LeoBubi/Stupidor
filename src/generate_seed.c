#include "includes.h"

long long generate_seed(void) {
    int fd;
    uint64_t num;
    long long min = 1000000000LL, max = 9999999999LL, result;

    fd = open("/dev/urandom", O_RDONLY);
    if (fd == -1)
        return 0;

    while (1) {
        if (read(fd, &num, sizeof(num)) != sizeof(num)) {
            close(fd);
            return 0;
        }

        // Scale the number to the 10-digit range
        result = min + num % (max - min + 1);
        if (result >= min && result <= max) {
            break; // Ensure we are within the 10-digit range
        }
    }

    close(fd);
    return result;
}