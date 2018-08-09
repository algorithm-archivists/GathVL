#if (defined(__unix__) || defined(__unix)) && (!defined(__APPLE__))

#include "../../include/systems/system.h"

#include <cstdlib>
#include <fcntl.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

int subprocess(const char *program, const std::vector<std::string>& args) {
    std::vector<char *> argv;

    for (auto& str : args) {
        argv.push_back(&(char&)str.front());
    }
    argv.push_back(NULL);

    pid_t pid = fork();
    int status = 0;

    if (pid == 0) {
        int fd = open("/dev/null", O_WRONLY);
        dup2(fd, 1);
        dup2(fd, 2);
        close(fd);

        execv(program, argv.data());
        std::exit(127);
    } else {
        waitpid(pid, &status, 0);
        if (WIFEXITED(status) && (WEXITSTATUS(status) == 0)) {
            return 0;
        }
    }

    return 1;
}

#endif //UNIX
