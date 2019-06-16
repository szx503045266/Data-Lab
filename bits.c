/* 
 * CS:APP Data Lab 
 * 
 * <Please put your name and userid here>
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
 * bitAnd - x&y using only ~ and | 
 *   Example: bitAnd(6, 5) = 4
 *   Legal ops: ~ |
 *   Max ops: 8
 *   Rating: 1
 */
int bitAnd(int x, int y) {
  int tp = (~x) | (~y);
  return ~tp;
}


/* 
 * getByte - Extract byte n from word x
 *   Bytes numbered from 0 (LSB) to 3 (MSB)
 *   Examples: getByte(0x12345678,1) = 0x56
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 6
 *   Rating: 2
 */
int getByte(int x, int n) {
  int m = n << 3;
  return (x >> m) & 255;  //255即11111111，与该数进行与操作后后8位不变，前24位全变为0
}
/* 
 * logicalShift - shift x to the right by n, using a logical shift
 *   Can assume that 0 <= n <= 31
 *   Examples: logicalShift(0x87654321,4) = 0x08765432
 *   Legal ops: ~ & ^ | + << >>
 *   Max ops: 20
 *   Rating: 3 
 */
int logicalShift(int x, int n) {
  int tp = (1 << 31) >> n << 1;  //该数前n位是1，后32-n位都是0
  return (x >> n) & ~tp;
}
/*
 * bitCount - returns count of number of 1's in word
 *   Examples: bitCount(5) = 2, bitCount(7) = 3
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 40
 *   Rating: 4
 */
int bitCount(int x) {
  int count;
  int tpMask1 = 0x55 | (0x55 << 8);
  int mask1 = tpMask1 | (tpMask1 << 16);  //01010101 01010101 01010101 01010101
  int tpMask2 = 0x33 | (0x33 << 8);
  int mask2 = tpMask2 | (tpMask2 << 16);  //00110011 00110011 00110011 00110011
  int tpMask3 = 0x0f | (0x0f << 8);
  int mask3 = tpMask3 | (tpMask3 << 16);  //00001111 00001111 00001111 00001111
  int mask4 = 0xff | (0xff << 16);        //00000000 11111111 00000000 11111111
  int mask5 = 0xff | (0xff << 8);         //00000000 00000000 11111111 11111111
  count = (x & mask1) + ((x>>1) & mask1);  //每两位一组，先计算低位中1的个数，右移1位后再计算高位中1的个数
  count = (count & mask2) + ((count >> 2) & mask2);  //每4位一组，先计算低位的两位，右移2位后再计算高位两位
  //从下面这层开始，可以先将移位前和移位后的数相加再跟掩码进行与操作，原因以8位一组为例：因为8个位上最多能有8个1，二进制8所占位数小于4，能在与操作时被00001111的四位1覆盖,从而得到保留
  count = (count + (count >> 4)) & mask3;  //每8位一组
  count = (count + (count >> 8)) & mask4;  //每16位一组
  count = (count + (count >> 16)) & mask5;  //总共32位为一组，将前16位的结果与后16位的结果相加即得最终答案
  return count;
}
/* 
 * bang - Compute !x without using !
 *   Examples: bang(3) = 0, bang(0) = 1
 *   Legal ops: ~ & ^ | + << >>
 *   Max ops: 12
 *   Rating: 4 
 */
int bang(int x) {
  int y = (~x) + 1;  //得到x的补码
  return ((x | y) >> 31) + 1;  //原码与补码或操作后取其最高位，再加1可得结果
}
/* 
 * tmin - return minimum two's complement integer 
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 4
 *   Rating: 1
 */
int tmin(void) {
  return 1 << 31;  //即0x80000000
}
/* 
 * fitsBits - return 1 if x can be represented as an 
 *  n-bit, two's complement integer.
 *   1 <= n <= 32
 *   Examples: fitsBits(5,3) = 0, fitsBits(-4,3) = 1
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 15
 *   Rating: 2
 */
int fitsBits(int x, int n) {
  x = x >> (~((~n)+1));  //x右移n-1位
  return !(~x) | !x;  //剩余位数全为1或全为0就返回1
}
/* 
 * divpwr2 - Compute x/(2^n), for 0 <= n <= 30
 *  Round toward zero
 *   Examples: divpwr2(15,1) = 7, divpwr2(-33,4) = -2
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 15
 *   Rating: 2
 */
int divpwr2(int x, int n) {
	int mask = ~((1 << 31) >> 31 << n);  //该数后n位是1，前32-n位为0
	int b = (x >> 31) & mask;  //构造偏移量，x为正时偏移量为0，为负时偏移梁为2^n-1
	return (x + b) >> n;  //加上偏移量后再移位
}
/* 
 * negate - return -x 
 *   Example: negate(1) = -1.
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 5
 *   Rating: 2
 */
int negate(int x) {
  return (~x) + 1;  //计算-x的补码
}
/* 
 * isPositive - return 1 if x > 0, return 0 otherwise 
 *   Example: isPositive(-1) = 0.
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 8
 *   Rating: 3
 */
int isPositive(int x) {
  return (!x) ^ !(x >> 31);  //先要确保x<>0，然后再移位判断是大于0还是小于0
}
/* 
 * isLessOrEqual - if x <= y  then return 1, else return 0 
 *   Example: isLessOrEqual(4,5) = 1.
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 24
 *   Rating: 3
 */
int isLessOrEqual(int x, int y) {
  int a = y + (~x) + 1;  //计算y-x
  int xs = x >> 31;  //得到x的符号
  int ys = y >> 31;  //得到y的符号
  int sf = !(xs ^ ys);  //判断x与y的符号是否相同，相同为1，不同为0
  int as = a >> 31;  //得到y-x结果的符号
  return ((!sf) & xs) | (sf & !(as));  //若x与y符号不同，结果取决于x的符号；若相同，结果取决于求得的差的符号
}
/*
 * ilog2 - return floor(log base 2 of x), where x > 0
 *   Example: ilog2(16) = 4
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 90
 *   Rating: 4
 */
int ilog2(int x) {
  int count;
  count = (!!(x >> 16)) << 4;  //判断前16位中是否有1，若有，则count记为1<<4，否则为0
  count = count + ((!!(x >> (count + 8))) << 3);  //若前16位中有1，则判断前16位中的前8位是否有1，若前16位中无1，则判断后16位中的前8位是否有1；若有1，则count加8
  count = count + ((!!(x >> (count + 4))) << 2);  //后面同理，根据前面的结果选择一个区域的前4位判断是否有1
  count = count + ((!!(x >> (count + 2))) << 1);
  count = count + (!!(x >> (count + 1)));  //最终确定1所在的最高位置
  return count;
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
unsigned float_neg(unsigned uf) {
  unsigned int tp1 = 0xff000000;
  unsigned int tp2 = 0x80000000;
  unsigned int uuf = uf << 1;
  unsigned int ans;
  if(((uuf & tp1) == tp1) && (uuf != tp1)){  //若该数为NaN
	ans = uf;  //返回原数
  }else{
	ans = tp2 + uf;  //改变符号位
  } 
  return ans;
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
  unsigned symb = x & 0x80000000;  //symb符号位
  unsigned count = 0, exp;  //exp阶码
  unsigned frac, tail, flag = 0;  //frag小数字段，tail为x中23位小数后的数，flag记录舍入时尾数是否进了位
  if(x == 0) return symb;  //若为0，直接输出0
  if(x < 0) x = -x;  //若x为负数，先变为正数
  while((x & 0x80000000) != 0x80000000){  //用while循环找到最高位的1，从而得到exp的值
	x = x << 1;
	count++;
  }
  exp = 158 - count;

  tail = x << 24;  //tail取24位尾数（包括首位的1）之后的数，即要被舍入的数
  x = x >> 8;  //尾数部分重新移动至x的后24位
  if(tail == 0x80000000){  //需要向偶数舍入
	if(x & 1){  //若x尾数最后一位为1
		frac = x + 1;  //进位
		flag = 1;
	}else  //若x尾数最后一位为0
		frac = x;  //不进位
  }
  else if(tail < 0x80000000){  //需要向下舍入，即不进位
	frac = x;
  }else{  //需要向上舍入，即进位
	frac = x + 1;
	flag = 1;
  }
  if(flag && !(frac & 0x007fffff)) exp++;  //若尾数进了位并且进位后尾数为全0，则需要向阶码进位，即阶码+1

  return symb + (exp << 23) + (frac & 0x007fffff);  //将符号位、阶码位和尾数位相加
}
/* 
 * float_twice - Return bit-level equivalent of expression 2*f for
 *   floating point argument f.
 *   Both the argument and result are passed as unsigned int's, but
 *   they are to be interpreted as the bit-level representation of
 *   single-precision floating point values.
 *   When argument is NaN, return argument
 *   Legal ops: Any integer/unsigned operations incl. ||, &&. also if, while
 *   Max ops: 30
 *   Rating: 4
 */
unsigned float_twice(unsigned uf) {
  unsigned symb = uf & 0x80000000;  //符号
  unsigned exp = uf & 0x7f800000;  //阶码字段
  unsigned frac = uf & 0x007fffff;  //小数字段
  if(exp == 0x7f800000) return uf;  //若阶码为全1，直接返回uf
  if(exp != 0)  //若阶码不为全0
	exp = exp + 0x00800000;  //阶码加1
  else  //若阶码为全0
	frac = frac << 1;  //小数字段乘2
  return symb + exp + frac;
}
