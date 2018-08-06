#include "../../include/systems/unix.h"

#include <cstdlib>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

int subprocess(const std::string& program,
               const std::vector<std::string>& args) {

    std::vector<char *> argv;

    for (auto& str : args) {
        argv.push_back(&str.front());
    }
    argv.push_back(NULL);

    pid_t pid = fork();
    int status = 0;

    if (pid == 0) {
        execv(program.data(), argv.data());
        std::exit(127);
    } else {
        waitpid(pid, &status, 0);
        if (WIFEXITED(status) && (WEXITSTATUS(status) == 0)) {
            return 0;
        }
    }

    return 1;
}
