#include <stdio.h>
#include <windows.h>

// The shared variable that will be corrupted by the race condition
volatile long long counter = 0;

// TODO: Define a Critical Section here
CRITICAL_SECTION my_critical_section;


// The function that each thread will run (Windows API format)
DWORD WINAPI thread_function(LPVOID lpParam) {
    for (int i = 0; i < 1000000; i++) {
        // --- CRITICAL SECTION START ---
        // TODO: Lock the critical section here
        EnterCriticalSection(&my_critical_section);

        counter++; // The race condition happens here!

        // TODO: Unlock the critical section here
        LeaveCriticalSection(&my_critical_section);
        // --- CRITICAL SECTION END ---
    }
    return 0;
}


int main() {
    HANDLE thread1, thread2;
    HANDLE threads[2];

    // TODO: Initialize the critical section here
    InitializeCriticalSection(&my_critical_section);

    printf("Starting threads...\n");

    // Create and start the two threads
    thread1 = CreateThread(NULL, 0, thread_function, NULL, 0, NULL);
    thread2 = CreateThread(NULL, 0, thread_function, NULL, 0, NULL);

    threads[0] = thread1;
    threads[1] = thread2;

    // Wait for both threads to finish
    WaitForMultipleObjects(2, threads, TRUE, INFINITE);

    // TODO: Destroy the critical section here
    DeleteCriticalSection(&my_critical_section);

    printf("Threads have finished.\n");
    printf("Expected final counter value: 2000000\n");
    printf("Actual final counter value:   %lld\n", counter);

    if (counter == 2000000) {
        printf("Success! The result is correct.\n");
    } else {
        printf("Failure! A race condition occurred.\n");
    }

    return 0;
}
