/* 
 * CS:APP Data Lab 
 * 
 * <Name: 郑欣宜, Userid: duuugh>
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
  4. Interprets integer expressions using the Data Lab 32-bit bit-vector
     model: results outside the signed range retain their low 32 bits.


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
#include "bits.h"

// P1
/* 
 * signMask - return a mask with only the most significant bit set (0x80000000)
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 2
 *   Rating: 1
 */
int signMask(void) {
  /* 00000000 00000000 00000000 00000001左移31位 */
  return 1<<31;
}

// P2
/* 
 * bitXor - x^y using only ~ and & 
 *   Example: bitXor(4, 5) = 1, bitXor(7, 7) = 0
 *   Legal ops: ~ &
 *   Max ops: 8
 *   Rating: 2
 */
int bitXor(int x, int y) {
  /* 排除对应位同为1或同为0的情况 */
  return ~(x&y) & ~(~x&~y);
}

// P3
/*
 * negativePart - return -x if x < 0, otherwise return 0
 *   Examples: negativePart(-10) = 10, negativePart(5) = 0
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 6
 *   Rating: 3
 */
int negativePart(int x){
  /* x>>31：若x非负，结果全0，反之全1 */
  return (x>>31) & (~x+1);
}


// P4
/*
 * copyByteWithin - copy byte src of x to byte dst, leaving all other bytes unchanged
 *   Bytes are numbered from 0 (least significant) to 3 (most significant).
 *   You can assume 0 <= src <= 3 and 0 <= dst <= 3.
 *   Example: copyByteWithin(0x11223344, 0, 2) = 0x11443344
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 12
 *   Rating: 4
 */
int copyByteWithin(int x, int src, int dst) {
  /* copysrc：src挪到最低8位，高位全0
  helpremove：替换的8位全0，其他全1
  0xFF: 00000000 00000000 00000000 11111111 */
  int srcShift=src<<3;
  int copySrc=(x>>srcShift) & 0xFF;
  int dstShift=dst<<3;
  int helpRemove=~(0xFF<<dstShift);
  return (x & helpRemove) | (copySrc<<dstShift);
}

// P5
/* 
 * logicalShift - shift x to the right by n bits, using a logical shift
 *   Can assume that 0 <= n <= 31
 *   Examples: logicalShift(0x87654321,4) = 0x08765432
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 20
 *   Rating: 4
 */
int logicalShift(int x, int n) {
  /* x>>n：算数右移，高位n位全1或0；arithToLog：高位n个0，低位全1 */
  int arithToLog=~(((1<<31)>>n)<<1);
  return (x>>n) & arithToLog;
}

// P6
/*
 * swapNibblePairs - swap the low and high 4 bits within each byte of x
 *   Examples: swapNibblePairs(0xAB) = 0xBA
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 18
 *   Rating: 4
 */
int swapNibblePairs(int x) {
  /* shift：构造0x0F0F0F0F*/
  int A,B;
  int shift=0x0F | (0x0F<<8);
  shift=shift | (shift<<16);
  A=(x & shift)<<4;
  B=(x>>4) & shift;
  return A+B;
}

// P7
/*
 * secondLowestZeroBit - return a mask that marks the position of the second least significant 0 bit
 *   Examples: secondLowestZeroBit(0xFFFFFFFA) = 0x4, secondLowestZeroBit(0x7FFFFFFF) = 0
 *             secondLowestZeroBit(-1) = 0
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 8
 *   Rating: 4
 */
int secondLowestZeroBit(int x) {
  /* 先对x取反，接着研究第二低位的1
  y+~0=y+(-1)=y-1：减去 1 时，最低的 1 会变成 0，它右边的 0 会变成 1，由此清除最低的1
  按位取反再加1：原来最低的1右边先从全0变成全1，加1后又变回全0；原来最低的1本身先变成0，再接到进位变回1；由此保留最低的1（原来第二低的1）*/
  int y=~x;
  int removeLowest=y & (y+~0);
  return removeLowest & (~removeLowest+1);
}

// P8
/*
 * oddParity - return the odd parity bit of x, that is,
 *      when the number of 1s in the binary representation of x is even, then the return 1, otherwise return 0.
 *   Examples: oddParity(5) = 1, oddParity(7) = 0
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 56
 *   Rating: 5
 */
int oddParity(int x) {
  /* ^：位异或，是奇函数，有奇数个1结果为1，与题目要求相反
  x ^ (x>>16)：高16位与低16位一一对应做异或，结果的低16位即为所求
  将异或结果对半合并，最终得到1位答案，即为32位相异或的结果*/
  x=x ^ (x>>16);
  x=x ^ (x>>8);
  x=x ^ (x>>4);
  x=x ^ (x>>2);
  x=x ^ (x>>1);
  return !(x&1);
}

// P9
/* 
 * rotateRightBits - rotate x to right by n bits
 *   you can assume n >= 0
 *   Examples: rotateRightBits(0x12345678, 8) = 0x78123456
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 16
 *   Rating: 5
 */
int rotateRightBits(int x, int n) {
  /*shift=n&31：n只保留最低5位，相对于n%32
  ~shift+1=-shift, (-shift)&31相当于32-shift
  return 左边剩余部分|右边移出去到左边的部分*/
  int shift=n & 31;
  int leftShift=(~shift+1) & 31;
  int mask=~(((1<<31)>>shift)<<1);
  return ((x>>shift) & mask) | (x<<leftShift);
}

// P10
/*
 * roundEvenPow2 - round nonnegative x to the nearest multiple of 2^n.
 *   If x is exactly halfway between two multiples, choose the multiple whose
 *   quotient by 2^n is even.
 *   You can assume 0 <= x <= 0x3fffffff and 1 <= n <= 16.
 *   Examples: roundEvenPow2(10, 2) = 8, roundEvenPow2(14, 2) = 16
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 24
 *   Rating: 5
 */
int roundEvenPow2(int x, int n) {
  /* mask=0xFFFFFFFF
  distance=x-below 
  diff=half-distance
  closerToAbove=0时x离below更近，1时反之
  middle=1时x恰好在中间
  below>>n为below除以2^n，belowOdd=1时below为奇数倍
  x离above更近，或x在中间且below是奇数倍above是偶数倍时，选above*/
  int element=1<<n;
  int mask=~0;
  int below=x & mask<<n;
  
  int distance=x+(~below+1);       
  int half=element>>1;
  int diff=half+(~distance+1);

  int closerToAbove=(diff>>31) & 1;   
  int middle=!diff;                     
  int belowOdd=(below>>n) & 1;     

  int chooseAbove = closerToAbove | (middle & belowOdd);  
  return below+(chooseAbove << n);
}

// P11
/* 
 * midpointTowardFirst - return the exact mathematical midpoint (x+y)/2
 *   without overflow. If the exact midpoint lies halfway between two
 *   integers, choose the adjacent integer that is closer to the first
 *   argument x.
 *   Examples: midpointTowardFirst(4, 7) = 5,
 *             midpointTowardFirst(7, 4) = 6
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 32
 *   Rating: 5
 */
int midpointTowardFirst(int x, int y) {
  /* different中的1标记x,y只有一方为1的位
  x&y中的1标记x,y皆为1的位，即相加时发生进位的位；由于x+y=2(x&y)+x^y，中点向下取整lower=x&y+different>>1（表示x^y除以2向下取整）
  signX：x为负时全1，否则全0
  signDiff：x,y异号时全1，同号时全0
  difference：计算y-x
  如果x,y异号，greaterMask=~signX，若x>y则全1，若x<y则全0;
  如果x,y同号，同号相减不会溢出，greaterMask=difference>>31.
  different & greaterMask & 1的结果是1或0，只有在和为奇数，而且x>y时才为1*/
  int different=x ^ y;
  int lower=(x & y)+(different>>1);

  int signX=x>>31;
  int signDiff=different>>31;
  int difference=y+(~x+1);
  int greaterMask=(signDiff & ~signX) | (~signDiff & (difference>>31));
  return lower+(different & greaterMask & 1);
}


// P12
/* 
 * isBetweenEitherOrder - return 1 when x lies in the inclusive interval whose
 *   endpoints are a and b. The endpoints may be given in either order.
 *   Example: isBetweenEitherOrder(5, 8, 3) = 1.
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 48
 *   Rating: 7
 */
int isBetweenEitherOrder(int x, int a, int b) {
  /* 不用判断a和b谁大，判断x的位置：比两个端点都小、在两个端点之间、比两个端点都大
  x与a比大小：异号时看x的符号；同号时看差值x-a的符号
  signA：符号相同为0，不同为~0
  compareA：当x<a时为全1，否则为全0
  !(x ^ a)：x=a时为1*/
  int distanceA=x+(~a+1);
  int signA=(x>>31) ^ (a>>31);
  int compareA=(signA & (x>>31)) | (~signA & (distanceA>>31));

  int distanceB=x+(~b+1);
  int signB=(x>>31) ^ (b>>31);
  int compareB=(signB & (x>>31)) | (~signB & (distanceB>>31));

  return ((compareA ^ compareB) & 1) | !(x ^ a) | !(x ^ b);
}

// P13
/* 
 * mul5Sat - return x*5, and if x*5 overflow, change the result to 
 * INT_MAX(0x7fffffff) or INT_MIN(0x80000000) correspondingly
 *   Examples: mul5Sat(1) = 0x5, mul5Sat(0x40000000) = 0x7fffffff
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 30
 *   Rating: 7
 */
int mul5Sat(int x) {
  /* signNeg：x为负数时全1
  distanceNeg=x-min
  negOverflow：x为负数且x<min时全1，此外全0
  不溢出时，normalMask全1，正常计算*/
  int part=(0x33<<8) | 0x33;
  int max=((part<<16) | part)>>1;
  int min=~max+1;

  int signNeg=x>>31;
  int signPos=~signNeg;
  int distanceNeg=x+(~min+1);
  int distancePos=max+(~x+1);
  int negOverflow=signNeg&(distanceNeg>>31);
  int posOverflow=signPos&(distancePos>>31);

  int INT_MIN=1<<31;
  int INT_MAX=~INT_MIN;
  int normalMask=~(negOverflow | posOverflow);
  return (negOverflow & INT_MIN) | (posOverflow & INT_MAX) | (normalMask & ((x<<2)+x));
}

// P14
/* 
 * classifyAdd3 - classify the exact mathematical sum x+y+z.
 *   Return 1 if the sum is greater than INT_MAX, -1 if it is less than
 *   INT_MIN, and 0 otherwise. You may not use a wider integer type.
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 52
 *   Rating: 7
 */
int classifyAdd3(int x, int y, int z) {
  /* x=4*(x>>2)+(x&3)：
  (1)x>>2即除以4，既能保证和不溢出（-2^31<=x,y,z<=2^31-1, -2^29<=(x>>2),(y>>2),(z>>2)<=2^29-1, INT_MIN<-3*2^29<3*2^29-3<INT_MAX），又能用算数右移实现
  (2)x&3表示x除以4的余数，原理是余数是最低两位，以3=0011为mask取x的最低两位
  totalHigh：把余数中凑够的4进到高部分
  min：INT_MIN除以4向下取整
  比较min, max和totalHigh即比较INT_MIN, INT_MAX和x+y+z
  比min小时negOverflow全1，否则全0*/
  int high=(x>>2)+(y>>2)+(z>>2);
  int low=(x & 3)+(y & 3)+(z & 3);
  int totalHigh=high+(low>>2);

  int element=1<<29;
  int min=~element+1;      
  int max=element+~0; 

  int distanceMin=totalHigh+(~min+1);
  int distanceMax=max+(~totalHigh+1);

  int negOverflow=distanceMin>>31;
  int posOverflow=(distanceMax>>31) & 1;
  return negOverflow | posOverflow;
}

// P15
/*
 * floatScaleThreeHalves - Return bit-level equivalent of expression f*3/2 for
 *   floating point argument f.
 *   Both the argument and result are passed as unsigned int's, but
 *   they are to be interpreted as the bit-level representation of
 *   single-precision floating point values.
 *   Use round-to-nearest-even. Preserve the sign of both +0 and -0.
 *   When argument is NaN, return argument.
 *   Legal ops: Any integer / unsigned operations incl. ||, &&. also if, while
 *   Max ops: 60
 *   Rating: 7
 */
unsigned floatScaleThreeHalves(unsigned uf) {
  /* 浮点数的位表示（科学计数法）：1位符号位s+8位指数位exp+23位小数位frac（正规化数1<=M<2，frac=M-1)
  NaN和正负无穷都原样返回
  正规化数不回省略的1，0不需要补
  shift默认为1，因为题目是除以2
  realFrac>2时，需要额外右移1位使1<=realFrac<2，同时指数加1
  if(result>=0x800000)：非规格化数可能变为正规格化数
  else if(result>=0x1000000)：舍入可能使有效数再次进位
  if(exp>=0xFF)：指数溢出，返回对应符号的无穷
  return s | (exp<<23) | (result & 0x7FFFFF)：去掉隐含位，拼回三个字段 */
  unsigned s=uf & 0x80000000;
  unsigned exp=(uf>>23) & 0xFF;
  unsigned frac=uf & 0x7FFFFF;
  unsigned realFrac, triple, shift, result, remainder, half;
    
  if(exp==0xFF) 
    return uf;

  realFrac=frac;
  if(exp!=0) 
    realFrac=realFrac | 0x800000;
  triple=(realFrac<<1)+realFrac;

  shift=1;
  if(triple>=0x2000000) 
  {
    shift=2;
    exp=exp+1;
  }
  result=triple>>shift;

  remainder=triple & ((1u<<shift)-1);
  half=1u<<(shift-1);
  if((remainder>half)||((remainder==half)&&(result & 1)))
    result=result+1;

  if(exp==0) 
  {
    if(result>=0x800000) 
      exp=1;
  } 
  else if(result>=0x1000000) 
  {
        result=result>>1;
        exp=exp+1;
  }
  if(exp>=0xFF) 
    return s | 0x7F800000;

  return s | (exp<<23) | (result & 0x7FFFFF);
}

// P16
/* 
 * floatRoundEven - round the floating-point value represented by uf to the
 *   nearest integer, with halfway cases rounded to the even integer. Return
 *   the bit-level representation of that integer as a single-precision float.
 *   If rounding produces zero, preserve the input sign; thus a negative
 *   value that rounds to zero returns -0. When uf is NaN or infinity,
 *   return uf unchanged.
 *   Legal ops: Any integer / unsigned operations incl. ||, &&. also if, while
 *   Max ops: 65
 *   Rating: 10
 */
unsigned floatRoundEven(unsigned uf) {
  /* if(exp>=150)：实际指数=exp-127，当实际指数>23时f已经是整数了，直接返回（包含NaN和无穷）
  if(exp<126)：|f|<0.5，返回带符号的0
  if(exp==126)：if(frac!=0)即0.5<|f|<1，取1；反之即|f|=0.5，取0
  接下来处理126<exp<150，即-1<指数<23，即0<=指数<=22，即1<=|f|<2^23
  1u：无符号的1
  remainder：f不用科学记数法、用正常二进制浮点数表示时的小数部分，但现在还是记为科学计数法中的形式
  half：0.5的、与f指数相同的科学计数法表示
  result=uf & ~mask：清除小数
  if((remainder>half) || ((remainder==half) && ((uf>>shift) & 1)))：超过一半，或恰好一半且整数部分为奇数时，绝对值增加1*/
  unsigned sign=uf & 0x80000000;
  unsigned exp=(uf>>23) & 0xFF;
  unsigned frac=uf & 0x7FFFFF;
  unsigned shift, mask, remainder, half, result;

  if(exp>=150)
    return uf;

  if(exp<126)
    return sign;

  if(exp==126)
  {
    if(frac!=0)
      return sign | 0x3F800000;
    return sign;                 
  }

  shift=150-exp;
  mask=(1u<<shift)-1;
  remainder=uf & mask;
  half=1u<<(shift-1);

  result=uf & ~mask;

  if((remainder>half) || ((remainder==half) && ((uf>>shift) & 1)))
    result=result+(1u<<shift);

  return result;
}

// P17
/*
 * float_i2f - Return bit-level equivalent of expression (float) x.
 *   Result is returned as unsigned int, but
 *   it is to be interpreted as the bit-level representation of a
 *   single-precision floating point values.
 *   Legal ops: Any integer / unsigned operations incl. ||, &&. also if, while
 *   Max ops: 40
 *   Rating: 10
 */
unsigned float_i2f(int x) {
  /* 先提取符号并用无符号运算求绝对值，再将最高位的1移到第31位并调整指数，取第30～8位作为尾数，利用最低8位进行最近偶数舍入，最后通过加法拼接符号、指数和尾数，使尾数舍入产生的进位能够进入指数 */
  unsigned sign, magnitude, exp, frac, remainder;

  if(x==0) 
    return 0;

  magnitude=x;
  sign=magnitude & 0x80000000;

  if(sign)
    magnitude=~magnitude+1;

  exp=158;
  while(!(magnitude & 0x80000000)) 
  {
    magnitude=magnitude<<1;
    exp=exp-1;
  }

  frac=(magnitude>>8) & 0x7FFFFF;
  remainder=magnitude & 0xFF;

  if((remainder>0x80)||((remainder==0x80)&&(frac & 1)))
    frac=frac+1;

  return sign+(exp<<23)+frac;
}



// P18
/*
 * bitCount - return count of number of 1's in the binary representation of x
 *   Examples: bitCount(5) = 2, bitCount(7) = 3
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 40
 *   Rating: 10
 */
int bitCount(int x) {
  /* 构造三个掩码，先统计每2位中1的个数，再逐步合并得到每4位、每8位的计数，随后通过右移和相加汇总四个字节的计数，最终保留最低6位，得到整个32位二进制表示中1的总数 */
  int mask1=0x55 | (0x55<<8);
  int mask2=0x33 | (0x33<<8);
  int mask4=0x0F | (0x0F<<8);

  mask1=mask1 | (mask1<<16);
  mask2=mask2 | (mask2<<16);
  mask4=mask4 | (mask4<<16);

  x=(x & mask1)+((x>>1) & mask1);
  x=(x & mask2)+((x>>2) & mask2);
  x=(x & mask4)+((x>>4) & mask4);

  x=x+(x>>8);
  x=x+(x>>16);

  return x & 0x3F;
}


// P19
/*
 * bitReverse - Reverse bits in an 32-bit integer
 *   Examples: bitReverse(0x80000004) = 0x20000001
 *             bitReverse(0x7FFFFFFF) = 0xFFFFFFFE
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 34
 *   Rating: 10
 */
int bitReverse(int x){
  /* 先构造各级掩码，再依次交换相邻的1位、2位、4位、8位分组，最后交换高低16位，实现全部32位的逆序。每次右移后用掩码清除符号扩展产生的高位，保证负数也能正确处理。共34次运算，符合题目限制 */
  int mask16=(0xFF<<8) | 0xFF;
  int mask8=mask16^(mask16<<8);
  int mask4=mask8^(mask8<<4);
  int mask2=mask4^(mask4<<2);
  int mask1=mask2^(mask2<<1);

  x=((x>>1) & mask1) | ((x & mask1)<<1);
  x=((x>>2) & mask2) | ((x & mask2)<<2);
  x=((x>>4) & mask4) | ((x & mask4)<<4);
  x=((x>>8) & mask8) | ((x & mask8)<<8);
  x=(x<<16) | ((x>>16) & mask16);

  return x;
}