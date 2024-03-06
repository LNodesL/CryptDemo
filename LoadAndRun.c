#include <tchar.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <windows.h>
#include <wchar.h>

int main() {
    WCHAR tempPath[MAX_PATH] = {0};
    WCHAR tempFileName[MAX_PATH] = {0};

    // Get the temporary file path
    if (!GetTempPathW(MAX_PATH, tempPath) || !GetTempFileNameW(tempPath, L"TMP", 0, tempFileName)) {
        printf("Failed to get temp file name\n");
        return -1;
    }

    // Open 'helloworld.exe' for reading
    HANDLE hFileRead = CreateFileW(L"helloworld.exe", GENERIC_READ, FILE_SHARE_READ, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);
    if (hFileRead == INVALID_HANDLE_VALUE) {
        printf("Failed to open helloworld.exe for reading\n");
        return -1;
    }

    // Determine the file size
    DWORD fileSize = GetFileSize(hFileRead, NULL);
    if (fileSize == INVALID_FILE_SIZE) {
        printf("Failed to get the size of helloworld.exe\n");
        CloseHandle(hFileRead);
        return -1;
    }

    // Allocate a buffer for the file contents
    BYTE* binaryData = (BYTE*)malloc(fileSize);
    if (binaryData == NULL) {
        printf("Failed to allocate memory for file contents\n");
        CloseHandle(hFileRead);
        return -1;
    }

    // Read the file into the buffer
    DWORD bytesRead = 0;
    if (!ReadFile(hFileRead, binaryData, fileSize, &bytesRead, NULL) || bytesRead != fileSize) {
        printf("Failed to read helloworld.exe\n");
        free(binaryData);
        CloseHandle(hFileRead);
        return -1;
    }

    // Close the file after reading
    CloseHandle(hFileRead);

    // Write binary data to the temporary file
    HANDLE hFileWrite = CreateFileW(tempFileName, GENERIC_WRITE, 0, NULL, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);
    if (hFileWrite == INVALID_HANDLE_VALUE) {
        printf("Failed to create temp file\n");
        free(binaryData);
        return -1;
    }

    DWORD written = 0;
    if (!WriteFile(hFileWrite, binaryData, fileSize, &written, NULL)) {
        printf("Failed to write to temp file\n");
        CloseHandle(hFileWrite);
        free(binaryData);
        return -1;
    }

    // Clean up
    CloseHandle(hFileWrite);
    free(binaryData);

    // Execute the temporary file
    STARTUPINFOW si = {0};
    PROCESS_INFORMATION pi = {0};
    si.cb = sizeof(si);

    if (!CreateProcessW(tempFileName, NULL, NULL, NULL, FALSE, 0, NULL, NULL, &si, &pi)) {
        printf("Failed to create process\n");
        return -1;
    }

    // Close process and thread handles
    CloseHandle(pi.hProcess);
    CloseHandle(pi.hThread);

    printf("Executed the process successfully\n");

    return 0;
}
