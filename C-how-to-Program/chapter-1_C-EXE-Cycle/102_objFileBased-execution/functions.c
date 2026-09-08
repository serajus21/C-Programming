// functions.c
// Arithmetic functions to use in main.c.

int add(int a, int b) //function to add two numbers
{
    return a + b;
}

int subtract(int a, int b) //function to subtract two numbers
{
    return a - b;
}

int multiply(int a, int b) //function to multiply two numbers
{
    return a * b;
}

int divide(int a, int b) //function to divide two numbers
{
    if (b == 0)
    {
        // printf("Error: cannot divide by zero.\n");
        return 0;
    }

    return a / b;
}
