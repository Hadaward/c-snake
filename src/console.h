#define WIN32_LEAN_AND_MEAN
#include <windows.h>

void ConsoleClear() {
    HANDLE hStdOut;
    CONSOLE_SCREEN_BUFFER_INFO csbi;
    DWORD count;
    DWORD cellCount;
    COORD homeCoords = { 0, 0 };

    hStdOut = GetStdHandle( STD_OUTPUT_HANDLE );
    if (hStdOut == INVALID_HANDLE_VALUE) return;

    /* Get the number of cells in the current buffer */
    if (!GetConsoleScreenBufferInfo(hStdOut, &csbi)) return;
    cellCount = csbi.dwSize.X *csbi.dwSize.Y;

    /* Fill the entire buffer with spaces */
    if (!FillConsoleOutputCharacter(
        hStdOut,
        (TCHAR) ' ',
        cellCount,
        homeCoords,
        &count
    )) return;

    /* Fill the entire buffer with the current colors and attributes */
    if (!FillConsoleOutputAttribute(
        hStdOut,
        csbi.wAttributes,
        cellCount,
        homeCoords,
        &count
    )) return;

    /* Move the cursor home */
    SetConsoleCursorPosition(hStdOut, homeCoords);
}

void ConsoleClearAt(int x, int y) {
    HANDLE hStdOut;
    DWORD count;
    DWORD cellCount = 2;
    COORD homeCoords = {x, y};

    hStdOut = GetStdHandle( STD_OUTPUT_HANDLE );
    if (hStdOut == INVALID_HANDLE_VALUE) return;

    /* Fill the entire buffer with spaces */
    if (!FillConsoleOutputCharacter(
        hStdOut,
        (TCHAR) ' ',
        cellCount,
        homeCoords,
        &count
    )) return;
}

int ConsoleDrawCharAt(char *chr, int x, int y) {
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);

    if (hConsole == INVALID_HANDLE_VALUE) {
        return 1; // Failed to get console handle
    }

    COORD coord = {x, y};
    DWORD charsWritten;

    if (!WriteConsoleOutputCharacterA(hConsole, chr, 1, coord, &charsWritten)) {
        return 3; // Failed to write to console
    }

    return 0;
}

int ConsoleDrawWCharAt(WCHAR *chr, int x, int y) {
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);

    if (hConsole == INVALID_HANDLE_VALUE) {
        return 1; // Failed to get console handle
    }

    COORD coord = {x, y};
    DWORD charsWritten;

    if (!WriteConsoleOutputCharacterW(hConsole, chr, 1, coord, &charsWritten)) {
        return 3; // Failed to write to console
    }

    return 0;
}

int ConsoleDrawTextAt(WCHAR *text, int x, int y) {
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);

    if (hConsole == INVALID_HANDLE_VALUE) {
        return 1; // Failed to get console handle
    }

    COORD coord = {x, y};
    DWORD charsWritten;

    if (!WriteConsoleOutputCharacterW(hConsole, text, wcslen(text), coord, &charsWritten)) {
        return 3; // Failed to write to console
    }

    return 0;
}