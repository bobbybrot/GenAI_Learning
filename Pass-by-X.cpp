#include <stdio.h>

/**
 * @brief This function receives a COPY of an integer.
 * @param num The integer copy.
 */
void attempt_to_modify_by_value(int num) {
    // YOUR TASK:
    // "Modify" the variable 'num' by assigning it a new value, e.g., 99.
    // Notice that this will only change the local copy.
    num = 99;
}

/**
 * @brief This function receives a POINTER to an integer.
 * @param num_ptr A pointer to the original integer.
 */
void modify_via_pointer(int* num_ptr) {
    // YOUR TASK:
    // Use the pointer 'num_ptr' to change the value of the
    // original variable it points to, e.g., to 101.
    *num_ptr = 101;
}


int main() {
    int my_variable = 25;

    printf("Original value: %d\n\n", my_variable);

    // Call the pass-by-value function
    attempt_to_modify_by_value(my_variable);
    printf("Value after attempt_to_modify_by_value: %d\n", my_variable);
    printf("(Notice the value did not change)\n\n");


    // Call the pass-by-pointer function
    modify_via_pointer(&my_variable);
    printf("Value after modify_via_pointer: %d\n", my_variable);
    printf("(Notice the value has now changed)\n");

    return 0;
}