#include "../../include/systems/windows.h"

#include <Windows.h>

int subprocess(const std::string& program,
               const std::vector<std::string>& args) {

    if (!program) {
        return 1;
    }

    std::string cmd(program);

    for (auto& str : args) {
        cmd.push_back(' ');
        cmd += str;
    }

    STARTUPINFO info = {sizeof(info)};
    PROCESS_INFORMATION processInfo;

    if (CreateProcess(NULL, &cmd.front(), NULL, NULL, TRUE, 0, NULL, NULL,
                      &info, &processInfo)) {

        WaitForSingleObject(processInfo.hProcess, INFINITE);
        CloseHandle(processInfo.hProcess);
        CloseHandle(processInfo.hThread);

        return 0;
    }

    return 1;
}
