/* 
 * CS 429H Data Lab 
 * 
 * Bradley Barrios bb32695
 * 
 * bits.c - Source file with your solutions to the Lab.
 *          This is the file you will hand in to your instructor.
 *
 * WARNING: Do not include the <stdio.h> header; it confuses the dlc
 * compiler. You can still use printf for debugging without including
 * <stdio.h>, although you might get a compiler warning. In general,
 * it's not good practice to ignore compiler warnings, but in this
 * case it's OK.  
 */

#if 0
/*
 * Instructions to Students:
 *
 * STEP 1: Read the following instructions carefully.
 */

You will provide your solution to the Data Lab by
editing the collection of functions in this source file.

INTEGER CODING RULES:
 
  Replace the "return" statement in each function with one
  or more lines of C code that implements the function. Your code 
  must conform to the following style:
 
  int Funct(arg1, arg2, ...) {
      /* brief description of how your implementation works */
      int var1 = Expr1;
      ...
      int varM = ExprM;

      varJ = ExprJ;
      ...
      varN = ExprN;
      return ExprR;
  }

  Each "Expr" is an expression using ONLY the following:
  1. Integer constants 0 through 255 (0xFF), inclusive. You are
      not allowed to use big constants such as 0xffffffff.
  2. Function arguments and local variables (no global variables).
  3. Unary integer operations ! ~
  4. Binary integer operations & ^ | + << >>
    
  Some of the problems restrict the set of allowed operators even further.
  Each "Expr" may consist of multiple operators. You are not restricted to
  one operator per line.

  You are expressly forbidden to:
  1. Use any control constructs such as if, do, while, for, switch, etc.
  2. Define or use any macros.
  3. Define any additional functions in this file.
  4. Call any functions.
  5. Use any other operations, such as &&, ||, -, or ?:
  6. Use any form of casting.
  7. Use any data type other than int.  This implies that you
     cannot use arrays, structs, or unions.

 
  You may assume that your machine:
  1. Uses 2s complement, 32-bit representations of integers.
  2. Performs right shifts arithmetically.
  3. Has unpredictable behavior when shifting an integer by more
     than the word size.

EXAMPLES OF ACCEPTABLE CODING STYLE:
  /*
   * pow2plus1 - returns 2^x + 1, where 0 <= x <= 31
   */
  int pow2plus1(int x) {
     /* exploit ability of shifts to compute powers of 2 */
     return (1 << x) + 1;
  }

  /*
   * pow2plus4 - returns 2^x + 4, where 0 <= x <= 31
   */
  int pow2plus4(int x) {
     /* exploit ability of shifts to compute powers of 2 */
     int result = (1 << x);
     result += 4;
     return result;
  }

FLOATING POINT CODING RULES

For the problems that require you to implent floating-point operations,
the coding rules are less strict.  You are allowed to use looping and
conditional control.  You are allowed to use both ints and unsigneds.
You can use arbitrary integer and unsigned constants.

You are expressly forbidden to:
  1. Define or use any macros.
  2. Define any additional functions in this file.
  3. Call any functions.
  4. Use any form of casting.
  5. Use any data type other than int or unsigned.  This means that you
     cannot use arrays, structs, or unions.
  6. Use any floating point data types, operations, or constants.


NOTES:
  1. Use the dlc (data lab checker) compiler (described in the handout) to 
     check the legality of your solutions.
  2. Each function has a maximum number of operators (! ~ & ^ | + << >>)
     that you are allowed to use for your implementation of the function. 
     The max operator count is checked by dlc. Note that '=' is not 
     counted; you may use as many of these as you want without penalty.
  3. Use the btest test harness to check your functions for correctness.
  4. Use the BDD checker to formally verify your functions
  5. The maximum number of ops for each function is given in the
     header comment for each function. If there are any inconsistencies 
     between the maximum ops in the writeup and in this file, consider
     this file the authoritative source.

/*
 * STEP 2: Modify the following functions according the coding rules.
 * 
 *   IMPORTANT. TO AVOID GRADING SURPRISES:
 *   1. Use the dlc compiler to check that your solutions conform
 *      to the coding rules.
 *   2. Use the BDD checker to formally verify that your solutions produce 
 *      the correct answers.
 */


#endif
/*
 * bitParity - returns 1 if x contains an odd number of 0's
 *   Examples: bitParity(5) = 0, bitParity(7) = 1
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 20
 *   Rating: 4
 */
int bitParity(int x) {
  /*
   *With each ">> = (int)" the number is split in half
   *and the halves are then Xor'ed. With each iteration
   *the parity (even or odd number) of zeroes is maintained
   *until only one bit remains
   */ 

  int num = x;
  num ^= num >> 16;
  num ^= num >> 8;
  num ^= num >> 4;
  num ^= num >> 2;
  num ^= num >>1;
  return num & 1;
}
/* 
 * bitXor - x^y using only ~ and & 
 *   Example: bitXor(4, 5) = 1
 *   Legal ops: ~ &
 *   Max ops: 14
 *   Rating: 1
 */
int bitXor(int x, int y) {
  /*
   *Explain -*Done*
   */

  int regAnd = x & y;
  int inverseAnd = ~x & ~y;
  
  return ~regAnd & ~inverseAnd;
}
/*
 * ezThreeFourths - multiplies by 3/4 rounding toward 0,
 *   Should exactly duplicate effect of C expression (x*3/4),
 *   including overflow behavior.
 *   Examples: ezThreeFourths(11) = 8
 *             ezThreeFourths(-9) = -6
 *             ezThreeFourths(1073741824) = -268435456 (overflow)
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 12
 *   Rating: 3
 */
int ezThreeFourths(int x) {
  /*
   *The first expression multiplies x by 3 by
   *shifting left once and adding x again, and then
   *divides by 4 by shifting right twice
   */
   int num = ((x<<1) + x) >> 2;

   /*
    *If the number is negative you have to round toward
    *zero so the remainder is calculated and a one is added
    *if the sign is negative and there was a remainder
    */
   int neg_sign = !!(num & (1<<31));
   int remainder = !!(x & 3);
   int bias = remainder & neg_sign; 

  return num+bias;
}
/* 
 * float_i2f - Return bit-level equivalent of expression (float) x
 *   Result is returned as unsigned int, but
 *   it is to be interpreted as the bit-level representation of a
 *   single-precision floating point values.
 *   Legal ops: Any integer/unsigned operations incl. ||, &&. also if, while
 *   Max ops: 30
 *   Rating: 4
 */
unsigned float_i2f(int x) {
  return 2;
}
/* 
 * float_neg - Return bit-level equivalent of expression -f for
 *   floating point argument f.
 *   Both the argument and result are passed as unsigned int's, but
 *   they are to be interpreted as the bit-level representations of
 *   single-precision floating point values.
 *   When argument is NaN, return argument.
 *   Legal ops: Any integer/unsigned operations incl. ||, &&. also if, while
 *   Max ops: 10
 *   Rating: 2
 */
unsigned float_neg(unsigned uf) 
{
  /*
   *By Xoring the most significant bit (the sign bit)
   *with 1, the number will essentially be multiplied
   *by -1
   */
  return uf ^ (1<<31);
}
/* 
 * isAsciiDigit - return 1 if 0x30 <= x <= 0x39 (ASCII codes for characters '0' to '9')
 *   Example: isAsciiDigit(0x35) = 1.
 *            isAsciiDigit(0x3a) = 0.
 *            isAsciiDigit(0x05) = 0.
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 15
 *   Rating: 3
 */
int isAsciiDigit(int x) 
{
  /*
   *First I subtracted the lowerbound from x and subtracted
   *x from the upperbound.
   */
   int lb_check = x + (~0x30+1);
   int ub_check = 0x39 + (~x+1);

   /*
    *If the sign bit of either difference is negative, x is not
    *an ASCII character code
    */
   int result = (ub_check | lb_check) & (1<<31);

   return !result;
}
/* 
 * isLessOrEqual - if x <= y  then return 1, else return 0 
 *   Example: isLessOrEqual(4,5) = 1.
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 24
 *   Rating: 3
 */
int isLessOrEqual(int x, int y)
{
  /*
   * Three cases that return 1:
   *   -if x is negative and y is positive
   *   -if the two numbers are the same sign and
   *    y-x has a positive differnce
   *   -if they are equal (y^x)==0
   */
  int xPos = !(x & (1<<31));
  int yPos = !(y & (1<<31));

  int sameSign = !(yPos^xPos);
  int difference = y + (~x + 1);
  int posDifference = !(difference & (0x1<<31));

  int xNegYPos = (!xPos) & yPos;

  int equality = !(x^y);

  return xNegYPos | (sameSign & posDifference) | equality;

}
/*
 * isPower2 - returns 1 if x is a power of 2, and 0 otherwise
 *   Examples: isPower2(5) = 0, isPower2(8) = 1, isPower2(0) = 0
 *   Note that no negative number is a power of 2.
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 20
 *   Rating: 4
 */
int isPower2(int x) {
  return 2;
}
/*
 * isTmax - returns 1 if x is the maximum, two's complement number,
 *     and 0 otherwise 
 *   Legal ops: ! ~ & ^ | +
 *   Max ops: 10
 *   Rating: 1
 */

int isTmax(int x) 
{
  /*
   * ~(0xefffffff) == 0x80000000
   * Therefore I flip the bits of x,
   * then add the resulting number to itself.
   *  If this equals 0, it could be TMax, 0 or
   *  -1. Therefore I check for the case where
   *  x == 0 (using !!x) and x == -1 (using !!flipX)
   */
  int flipX = ~x;
  int overflow = !(flipX + flipX);

  return overflow & !!x & !!flipX;

}
/* 
 * negate - return -x 
 *   Example: negate(1) = -1.
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 5
 *   Rating: 2
 */
int negate(int x) 
{
  /*
   *Return the two's complement of the number
   */
   return ~x + 1;
}
/* 
 * rempwr2 - Compute x%(2^n), for 0 <= n <= 30
 *   Negative arguments should yield negative remainders
 *   Examples: rempwr2(15,2) = 3, rempwr2(-35,3) = -3
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 20
 *   Rating: 3
 */
int rempwr2(int x, int n) 
{
  /*
   *In order to find 
   */
   //int sign = (x & (1<<31));
   //POSITIVES
   //int remainder = x & ((1 << n)+(~1+1));
   
   //remainder |= (sign>>(31-n));

   // remainder |= 1<<31;
   //printf("%x %x %x %x\n", x, n, sign, remainder);

    //return remainder;
   return 2;
}
/* 
 * reverseBytes - reverse the bytes of x
 *   Example: reverseBytes(0x01020304) = 0x04030201
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 25
 *   Rating: 3
 */
int reverseBytes(int x) 
{
  /*
   *First I use 0xFF to mask each byte and then shift
   *it to the correct location for the new number. I then
   *OR all of the bytes together to get reverse number
   */
  int first_byte = (x >> 24) & 0xFF;
  int second_byte = (x >> 8) & (0xFF<<8);
  int third_byte = (x << 8) & (0xFF<<16);
  int fourth_byte = (x & 0xFF) << 24;

  return first_byte | second_byte | third_byte | fourth_byte;
}
/* 
 * subOK - Determine if can compute x-y without overflow
 *   Example: subOK(0x80000000,0x80000000) = 1,
 *            subOK(0x80000000,0x70000000) = 0, 
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 20
 *   Rating: 3
 */
int subOK(int x, int y) {

  return 2;
}
/* 
 * tc2sm - Convert from two's complement to sign-magnitude 
 *   where the MSB is the sign bit
 *   You can assume that x > TMin
 *   Example: tc2sm(-5) = 0x80000005.
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 15
 *   Rating: 4
 */
int tc2sm(int x) {
  /*
   *In order to change the negative number, you can negate the
   *number and then flip the sign bit to indicate it is negative
   *Using the sign of the number, I created a mask that will
   *return the altered number if x is negative or just return x
   * if it is positive
   */
  int negate = ~x+1;
  int sign_magnitude =  negate ^ (1<<31);

  int isNegative = !!(x & (1<<31));
  int negMask = ~isNegative+1;

  return (negMask & sign_magnitude) | (~negMask & x);
 
}
/*
 * trueThreeFourths - multiplies by 3/4 rounding toward 0,
 *   avoiding errors due to overflow
 *   Examples: trueThreeFourths(11) = 8
 *             trueThreeFourths(-9) = -6
 *             trueThreeFourths(1073741824) = 805306368 (no overflow)
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 20
 *   Rating: 4
 */
int trueThreeFourths(int x)
{
  /*
   * In order to avoid overflow errors, I divided by
   * four first and then add the number 3 times. If the
   * number is negative and there is a remainder, a 1 must
   * be added so that the number is rounded to 0
   */
  int num = x >> 2;
  int remainder = x & 3;
  int neg_sign = !!(x & (1<<31));
  int result = num + num + num + (((remainder<<1) + remainder)>>2);

  int bias = ((!!remainder) & neg_sign);

  return result+bias;
}
