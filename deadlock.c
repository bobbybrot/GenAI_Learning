#include <stdio.h>
#include <windows.h>

// A mutex for the SPI bus
CRITICAL_SECTION spi_mutex;

// A mutex for the UART bus
CRITICAL_SECTION uart_mutex;


// Thread 1: Reads from SPI, then writes to UART
DWORD WINAPI sensor_thread(LPVOID lpParam) {
    printf("[Sensor Thread] Trying to lock SPI...\n");
    EnterCriticalSection(&spi_mutex);
    printf("[Sensor Thread] Locked SPI!\n");

    // Simulate work with the SPI bus
    Sleep(500);

    printf("[Sensor Thread] Trying to lock UART...\n");
    EnterCriticalSection(&uart_mutex);
    printf("[Sensor Thread] Locked UART!\n");

    // --- Critical Work ---
    printf("[Sensor Thread] Reading from sensor and printing to UART...\n");
    // --- End Critical Work ---

    printf("[Sensor Thread] Unlocking UART.\n");
    LeaveCriticalSection(&uart_mutex);
    printf("[Sensor Thread] Unlocking SPI.\n");
    LeaveCriticalSection(&spi_mutex);

    return 0;
}

// Thread 2: Reads from UART, then writes to SPI
DWORD WINAPI command_thread(LPVOID lpParam) {
    
    printf("[Command Thread] Trying to lock SPI...\n");
    EnterCriticalSection(&spi_mutex);
    printf("[Command Thread] Locked SPI!\n");
    
    printf("[Command Thread] Trying to lock UART...\n");
    EnterCriticalSection(&uart_mutex);
    printf("[Command Thread] Locked UART!\n");

    // Simulate work with the UART bus
    Sleep(500);

    // --- Critical Work ---
    printf("[Command Thread] Receiving command and writing status to SPI...\n");
    // --- End Critical Work ---

    printf("[Command Thread] Unlocking SPI.\n");
    LeaveCriticalSection(&spi_mutex);
    printf("[Command Thread] Unlocking UART.\n");
    LeaveCriticalSection(&uart_mutex);

    return 0;
}


int main() {
    HANDLE threads[2];

    InitializeCriticalSection(&spi_mutex);
    InitializeCriticalSection(&uart_mutex);

    printf("Starting sensor and command threads...\n");

    threads[0] = CreateThread(NULL, 0, sensor_thread, NULL, 0, NULL);
    threads[1] = CreateThread(NULL, 0, command_thread, NULL, 0, NULL);

    // Wait for both threads to finish.
    // If a deadlock occurs, the program will hang here forever.
    WaitForMultipleObjects(2, threads, TRUE, INFINITE);

    printf("Both threads finished successfully.\n");

    DeleteCriticalSection(&spi_mutex);
    DeleteCriticalSection(&uart_mutex);

    return 0;
}