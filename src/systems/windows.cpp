#include "../../include/systems/windows.h"

#include <Windows.h>

int subprocess(const char *program, const std::vector<std::string>& args) {
    std::string cmd;

    for (auto& str : args) {
        cmd += str;
        cmd.push_back(' ');
    }

    STARTUPINFO info = {sizeof(info)};
    PROCESS_INFORMATION processInfo;

    if (CreateProcess(program, &cmd.front(), NULL, NULL, TRUE, 0, NULL,
                      NULL, &info, &processInfo)) {

        WaitForSingleObject(processInfo.hProcess, INFINITE);
        CloseHandle(processInfo.hProcess);
        CloseHandle(processInfo.hThread);

        return 0;
    }

    return 1;
}
