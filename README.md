# INTAL
Develop a C library for the integers of arbitrary length (intal).
Introduction

An Intal is a nonnegative integer of arbitrary length. The integer is stored as a null-terminated string of decimal digits 
(from 0 to 9) characters. In our implementation, the most significant digit is at the head of the string. General integer/long 
type in C cannot support intal as intal is of arbitrary length and can exceed largest value that can be stored as a long long int 
in C. Applications of intal includes programming with huge number such as cryptography, encryption, stocks, research, etc.


Approach

All extra pointers and variables in every function have been freed to save apce and avoid memory leaks.

Intal_add
The function takes two strings as input. The larger and the smaller strings are stored respectively. The coinciding digits from 
the larger the larger string are added and stored into result. The remaining digits from the larger string are then copied into 
result. Then the whole result string is checked to see if any number crosses the value 9. If yes then a carry is added to the next 
digit(going from right to left). If the most significant value is greater than 9, then all values are shifted to the right by one 
and a carry is added at the most significant position.

Intal_compare
The function takes two strings as input. The lengths are compared and a corresponding answer is returned. If the lengths are same 
then each digit is compared starting from the most significant one. 

Intal_diff
The function takes two strings as input. The larger and the smaller strings are stored respectively. The coinciding digits from
 the larger the larger string are added and stored into result with the help of the borrow variable. If any difference comes 
negative then borrow is set to one and it is subtracted from the next value. If any preceding 0’s are stored as a result of the 
subtraction, then the values are shifted left till no preceding 0’s exist.

Intal_multiply
The function takes two strings as input. If any of the strings hold the value zero, then the result is returned as 0. The variable 
‘k’ helps add 0’s(Ones place, tens place and so on). The two for loops help iterate through each of the strings. Intal1 is 
multiplied with each of the digits of intal2 and added to result. The result is filled from the last index during each intermediate 
multiplication. After each intermediate multiplication, the whole string is shifted to start from index 0 and then for addition.

Intal_mod
The function takes two strings as input. If intal1 is already smaller than intal2 then the result is returned as intal1. If intal1 
is greater than intal2 then intal1 is stored in result and 0’s are padded to intal2 until it is lesser than equal to intal1(This 
padded intal2 is stored as temp). Then temp is repeatedly subtracted from result until result is greater then equal to temp. The 
whole process is repeated with the new result. Every new result has a new temp. When result becomes lesser than intal2, it is 
returned.

Intal_pow
The function takes one string and an unsigned integer as input. If the string hold the value 0, then the result is returned as the 
other 0. If n is 0 then the result is returned as 1.The function is recursively called by passing (intal1,n/2). Based on the value 
on n(even or odd) in each call, the corresponding multiplication value is returned.

Intal_gcd
The function takes two strings as input. If both the strings hold the value zero, then the result is returned as 0. If any one of 
the string is 0, then the other string is returned as the result. If both the strings are non-zero then, using Euclid’s algorithm, 
the gcd of the two intals is found.

Intal_fibonacci
The function takes an unsigned integer as input. If n is 0 then 0 is returned as the result. The first two terms are 1 and 1. 
Using a for starting from 2 till n, the nth fibinacci number is found as returned.

Intal_factorial
The function takes an unsigned integer as input. Using a for loop from 2 to n, each value is converted to a string. Result is 
initialized as 1. Then the intal_multiply function is called to multiply result with i and its stored back into result. Finally 
result is returned.

Intal_bincoeff
The function takes two unsigned integers as input. A binomial coefficient C(n, k) can be defined as the coefficient of X^k in the 
expansion of (1 + X)^n.
All elements of array C of size (k+1) are initialized to ZERO. Then C[0] is set to 1. At any time, every element of array C will 
have some value (ZERO or more) and in next iteration, value for those elements comes from previous iteration. So here every loop 
on i, builds i’th row of pascal triangle, using (i-1)th row using the statement C[j] = C[j] + C[j-1].

Intal_max
The function takes an array of strings and the array length as input. Result is initialized to arr[0]. Using a for loop result to 
compared to every string in the array using the intal_compare function. Finally the index of the maximum value is returned.

Intal_min
The function takes an array of strings and the array length as input. Result is initialized to arr[0]. Using a for loop result to 
compared to every string in the array using the intal_compare function. Finally the index of the minimum value is returned. 

Intal_search
The function takes an array of strings, the array length and the search key as input. Using linear search algorithm each string in 
the array is compared to the key. If found, the index is returned else -1 is returned.

Intal_binsearch
The function takes an array of strings, the array length and the search key as input. Using helper function binarysearch() the 
index of the key in the array is returned if found(using the binary search algorithm) else -1 is returned.

Intal_sort
The function takes an array of strings and the array length as input. Using the helper functions mergesort() and merge(), the array 
is sorted suing merge sort algorithm. Merge() helps to merge the two intermediate arrays. Mergesort() is a recursive function which 
calls merge() also.

Coin_row_problem
The function takes an array of strings and the array length as input. To solve this problem using Dynamic Programming first we will 
have to define recurrence relation.
If we assume F[n] as the array which will contain the maximum sum at n for any given n. The recurrence relation will be.
F(n) = max{Coins[n] + F[n − 2], F[n − 1]} for n > 1,
F(0) = 0, F(1) = Coins[1].
This is very easy to understand. While calculating F[n] we are taking maximum of coins[n]+the previous of preceding element and the 
previous element. But instead of using a DP table of size n+1, I used just three variables and kept changing their values.


Scope of improvement
The current method only takes care of decimal digits. It can be extended to different bases, floating numbers. Additional functions can be created 
for doing larger calculations such as division, approximate square root, approximate division, series of intals etc.  
