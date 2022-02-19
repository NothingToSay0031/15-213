/*
 * CS:APP Data Lab
 *
 * Christina0031
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
  3. Has unpredictable behavior when shifting if the shift amount
     is less than 0 or greater than 31.


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

For the problems that require you to implement floating-point operations,
the coding rules are less strict.  You are allowed to use looping and
conditional control.  You are allowed to use both ints and unsigneds.
You can use arbitrary integer and unsigned constants. You can use any arithmetic,
logical, or comparison operations on int or unsigned data.

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
  2. Each function has a maximum number of operations (integer, logical,
     or comparison) that you are allowed to use for your implementation
     of the function.  The max operator count is checked by dlc.
     Note that assignment ('=') is not counted; you may use as many of
     these as you want without penalty.
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
// 1
/*
 * bitXor - x^y using only ~ and &
 *   Example: bitXor(4, 5) = 1
 *   Legal ops: ~ &
 *   Max ops: 14
 *   Rating: 1
 */
int bitXor(int x, int y) {
    int m = x & ~y;
    int n = ~x & y;
    return ~(~m & ~n);
}
/*
 * tmin - return minimum two's complement integer
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 4
 *   Rating: 1
 */
int tmin(void) { return 0x80 << 24; }
// 2
/*
 * isTmax - returns 1 if x is the maximum, two's complement number,
 *     and 0 otherwise
 *   Legal ops: ! ~ & ^ | +
 *   Max ops: 10
 *   Rating: 1
 */
int isTmax(int x) {
    int m = ~(x ^ (x + 1));
    int n = !!(~x);
    return (!m) & n;
}
/*
 * allOddBits - return 1 if all odd-numbered bits in word set to 1
 *   where bits are numbered from 0 (least significant) to 31 (most significant)
 *   Examples allOddBits(0xFFFFFFFD) = 0, allOddBits(0xAAAAAAAA) = 1
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 12
 *   Rating: 2
 */
int allOddBits(int x) {
    int m = 0x55 | 0x55 << 8;
    m = m << 16 | m;
    return !(~(m | x));
}
/*
 * negate - return -x
 *   Example: negate(1) = -1.
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 5
 *   Rating: 2
 */
int negate(int x) { return ~x + 1; }
// 3
/*
 * isAsciiDigit - return 1 if 0x30 <= x <= 0x39 (ASCII codes for characters '0'
 * to '9') Example: isAsciiDigit(0x35) = 1. isAsciiDigit(0x3a) = 0.
 *            isAsciiDigit(0x05) = 0.
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 15
 *   Rating: 3
 */
int isAsciiDigit(int x) {
    x = x ^ 0x38;
    return !(x >> 1) | !((x >> 3) ^ 0x01);
}
/*
 * conditional - same as x ? y : z
 *   Example: conditional(2,4,5) = 4
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 16
 *   Rating: 3
 */
int conditional(int x, int y, int z) {
    int cond = ~!x + 1;
    return ((~cond) & y) | (cond & z);
}
/*
 * isLessOrEqual - if x <= y  then return 1, else return 0
 *   Example: isLessOrEqual(4,5) = 1.
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 24
 *   Rating: 3
 */
int isLessOrEqual(int x, int y) {
    int min = 0x80 << 24;
    int result1 = !(x ^ min);
    int sign_x = ((x ^ y) & x) >> 31;
    int sign_y = ((x ^ y) & y) >> 31;
    int result2 = !(~sign_x | sign_y);
    int result3 = !((sign_x ^ sign_y) | ((~x + 1) + y) >> 31);
    return result1 | result2 | result3;
}
// 4
/*
 * logicalNeg - implement the ! operator, using all of
 *              the legal operators except !
 *   Examples: logicalNeg(3) = 0, logicalNeg(0) = 1
 *   Legal ops: ~ & ^ | + << >>
 *   Max ops: 12
 *   Rating: 4
 */
int logicalNeg(int x) {
    int bit = x >> 16 | x;
    bit = bit >> 8 | bit;
    bit = bit >> 4 | bit;
    bit = bit >> 2 | bit;
    bit = bit >> 1 | bit;
    return 0x01 & (~bit);
    // OR
    // return ((x | (~x + 1)) >> 31) + 1;
}
/* howManyBits - return the minimum number of bits required to represent x in
 *             two's complement
 *  Examples: howManyBits(12) = 5
 *            howManyBits(298) = 10
 *            howManyBits(-5) = 4
 *            howManyBits(0)  = 1
 *            howManyBits(-1) = 1
 *            howManyBits(0x80000000) = 32
 *  Legal ops: ! ~ & ^ | + << >>
 *  Max ops: 90
 *  Rating: 4
 */
int howManyBits(int x) {
    int sign = x >> 31;
    int result = 1;
    int flag, half;
    x = (~sign & x) | (sign & ~x);
    flag = (~!(x >> 16) + 1);
    half = 0xff << 8 | 0xff;
    result += ~flag & 16;
    x = (flag & x & half) | (~flag & (x >> 16));
    flag = (~!(x >> 8) + 1);
    half = 0xff;
    result += ~flag & 8;
    x = (flag & x & half) | (~flag & (x >> 8));
    flag = (~!(x >> 4) + 1);
    half = 0x0f;
    result += ~flag & 4;
    x = (flag & x & half) | (~flag & (x >> 4));
    flag = (~!(x >> 2) + 1);
    half = 0x03;
    result += ~flag & 2;
    x = (flag & x & half) | (~flag & (x >> 2));

    flag = (~!(x >> 1) + 1);
    half = 0x01;
    result += ~flag & 1;
    x = (flag & x & half) | (~flag & (x >> 1));
    return result + x;

    // OR
    // int b16, b8, b4, b2, b1, b0;
    // int sign = x >> 31;
    // x = (sign & ~x) |(~sign & x);
    // b16 = !!(x >> 16) << 4; //高十六位是否有1
    // x = x >> b16;           //如果有，则将原数右移16位
    // b8 = !!(x >> 8) << 3;
    // x = x >> b8;
    // b4 = !!(x >> 4) << 2;
    // x = x >> b4;
    // b2 = !!(x >> 2) << 1;
    // x = x >> b2;
    // b1 = !!(x >> 1);
    // x = x >> b1;
    // b0 = x;
    // return b16 + b8 + b4 + b2 + b1 + b0 + 1; //+1表示加上符号位
}
// float
/*
 * floatScale2 - Return bit-level equivalent of expression 2*f for
 *   floating point argument f.
 *   Both the argument and result are passed as unsigned int's, but
 *   they are to be interpreted as the bit-level representation of
 *   single-precision floating point values.
 *   When argument is NaN, return argument
 *   Legal ops: Any integer/unsigned operations incl. ||, &&. also if, while
 *   Max ops: 30
 *   Rating: 4
 */
unsigned floatScale2(unsigned uf) {
    int pos = (0x7f << 24) | (0x80 << 16);
    int exp = (uf & pos) >> 23;
    int sign;

    if (exp == 0xff || !(uf & (~(0x01 << 31)))) {
        return uf;
    } else if (exp == 0x00) {
        sign = (uf >> 31) << 31;
        return ((uf & ~sign) << 1) | sign;
    } else {
        exp += 1;
        return (uf & ~pos) | (exp << 23);
    }
}
/*
 * floatFloat2Int - Return bit-level equivalent of expression (int) f
 *   for floating point argument f.
 *   Argument is passed as unsigned int, but
 *   it is to be interpreted as the bit-level representation of a
 *   single-precision floating point value.
 *   Anything out of range (including NaN and infinity) should return
 *   0x80000000u.
 *   Legal ops: Any integer/unsigned operations incl. ||, &&. also if, while
 *   Max ops: 30
 *   Rating: 4
 */
int floatFloat2Int(unsigned uf) {
    int pos = (0x7f << 24) | (0x80 << 16);
    int exp = (uf & pos) >> 23;
    int frac = ~((0xff << 24) | (0x80 << 16)) & uf;
    int sign = (uf >> 31) << 31;
    int bias = 0x7f;
    int e = exp - bias;

    if (exp >= bias + 31) {
        return 0x80 << 24;
    } else if (bias >= exp + 1) {
        return 0;
    } else {
        frac = frac | (0x01 << 23);
        if (e < 23) {
            frac = frac >> (23 - e);
        } else {
            frac = frac << (e - 23);
        }
        if (sign) {
            return -frac;
        } else {
            return frac;
        }
    }
}
/*
 * floatPower2 - Return bit-level equivalent of the expression 2.0^x
 *   (2.0 raised to the power x) for any 32-bit integer x.
 *
 *   The unsigned value that is returned should have the identical bit
 *   representation as the single-precision floating-point number 2.0^x.
 *   If the result is too small to be represented as a denorm, return
 *   0. If too large, return +INF.
 *
 *   Legal ops: Any integer/unsigned operations incl. ||, &&. Also if, while
 *   Max ops: 30
 *   Rating: 4
 */
unsigned floatPower2(int x) {
    int exp = 0x7f;
    int frac = 0x00;
    int flag = 1;
    while (x != 0) {
        if (x == (0x80 << 24)) {
            return 0;
        }
        if (x > 0)
            if (exp == 0xff) {
                break;
            } else {
                exp += 1;
                x = x - 1;
            }
        else {
            if (exp == 0x00) {
                if (frac == 0x00 && flag) {
                    frac = 0x80 << 24;
                    x = x + 1;
                } else if (frac == 0x00) {
                    break;
                } else {
                    frac - frac >> 1;
                    x = x + 1;
                    flag = 0;
                }
            } else {
                exp -= 1;
                x = x + 1;
            }
        }
    }
    return exp << 23 | frac;
    //   int INF = 0xff << 23;
    //   int exp = x + 0x7f;
    //   if (exp < 0 && exp > -24)  // 23 是frac部分的位数
    //     return 0x00040000 >> (~exp + 1);
    //   else if (exp < -23)
    //     return 0;
    //   if (exp >= 0xff) return INF;
    //   return exp << 23;
}
