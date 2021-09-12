/* a function that accepts two BigIntegers as function parameters and returns 0 if both BigIntegers are equal,
* -1 if BigInt1 is lesser than BigInt2 and 1 if BigInt2 is lesser than BigInt1. */
int compareBigInt(const char* BigInt1, const char* BigInt2);

/* a function which adds two BigIntegers and returns their sum. */
char* BigInt_Add(const char* BigInt1, const char* BigInt2);

/* a function that accepts two BigIntegers as function parameters and returns their difference. */
char* BigInt_Sub(const char* BigInt1, const char* BigInt2);

/* a function which multiplies two BigIntegers and returns their product. */
char* BigInt_Multiply(const char* BigInt1, const char* BigInt2);

/* a function which returns BigInt1 % BigInt2 */
char* BigInt_Mod(const char* BigInt1, const char* BigInt2);

/* a function which returns BigInt1^(BigInt2) */
char* BigInt_Pow(const char* BigInt1, unsigned int n);

/* a function which returns Greatest Common Divisor of BigInt1 and BigInt2 */
char* BigInt_GCD(const char* BigInt1, const char* BigInt2);

/* a function which returns the nth Fibonacci BigInt. */
char* BigInt_fibonacci(unsigned int n);

/* a function which returns the factorial of n. */
char* BigInt_factorial(unsigned int n);
