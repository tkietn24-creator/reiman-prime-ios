#include <iostream>
#include <windows.h>
#include <string>

class PipeClient {
private:
    HANDLE hPipe;
    const char* pipeName = R"(\\.\pipe\ChamsControll)";

public:
    PipeClient() : hPipe(INVALID_HANDLE_VALUE) {}

    ~PipeClient() {
        Disconnect();
    }

    bool Connect() {
        std::cout << "Attempting to connect to FFHDR DLL..." << std::endl;

        while (true) {
            // Try to connect to the pipe
            hPipe = CreateFileA(
                pipeName,
                GENERIC_READ | GENERIC_WRITE,
                0,
                NULL,
                OPEN_EXISTING,
                0,
                NULL
            );

            if (hPipe != INVALID_HANDLE_VALUE) {
                std::cout << "Connected to pipe successfully!" << std::endl;
                return true;
            }

            DWORD error = GetLastError();
            if (error == ERROR_PIPE_BUSY) {
                std::cout << "Pipe is busy, waiting..." << std::endl;
                // Wait for pipe to be available
                if (WaitNamedPipeA(pipeName, 2000)) { // Wait 2 seconds
                    continue; // Try again
                }
            }
            else if (error == ERROR_FILE_NOT_FOUND) {
                std::cout << "Waiting for FFHDR DLL to start pipe server..." << std::endl;
            }
            else {
                std::cout << "Connection error: " << error << ", retrying..." << std::endl;
            }

            // Wait 1 second before retrying
            Sleep(1000);
        }

        return false; // This line should never be reached
    }

    bool SendCommand(const std::string& command) {
        if (hPipe == INVALID_HANDLE_VALUE) {
            std::cerr << "Not connected to pipe!" << std::endl;
            return false;
        }

        DWORD bytesWritten, bytesRead;
        char buffer[1024];

        // Send command
        BOOL result = WriteFile(hPipe, command.c_str(), (DWORD)command.size(), &bytesWritten, NULL);
        if (!result) {
            std::cerr << "Failed to send command. Error: " << GetLastError() << std::endl;
            return false;
        }

        // Read response
        result = ReadFile(hPipe, buffer, sizeof(buffer) - 1, &bytesRead, NULL);
        if (!result) {
            std::cerr << "Failed to read response. Error: " << GetLastError() << std::endl;
            return false;
        }

        buffer[bytesRead] = '\0';
        std::cout << "[Server Response]: " << buffer << std::endl;
        return true;
    }

    void Disconnect() {
        if (hPipe != INVALID_HANDLE_VALUE) {
            CloseHandle(hPipe);
            hPipe = INVALID_HANDLE_VALUE;
            std::cout << "Disconnected from pipe." << std::endl;
        }
    }
};
