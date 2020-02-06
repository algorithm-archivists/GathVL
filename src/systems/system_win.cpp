#ifdef _WIN32

#include "../../include/systems/system.h"

#include <windows.h>

int subprocess(const char *program, const std::vector<std::string>& args) {
    std::string cmd;

    for (auto&  str : args) {
        cmd += str;
        cmd.push_back(' ');
    }

    STARTUPINFO info = {sizeof(info)};
    PROCESS_INFORMATION process_info;

    if (CreateProcess(NULL, &cmd.front(), NULL, NULL, FALSE, NULL, NULL, NULL,
                      &info, &process_info)) {

        WaitForSingleObject(process_info.hProcess, INFINITE);
        CloseHandle(process_info.hProcess);
        CloseHandle(process_info.hThread);

        return 0;
    }

    return 1;
}

#endif //Windows
