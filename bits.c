/* WARNING: Do not include any other libraries here,
 * otherwise you will get an error while running test.py
 * You can still use printf for debugging without including
 * <stdio.h>, although you might get a compiler warning. In general,
 * it's not good practice to ignore compiler warnings, but in this
 * case it's OK.
 *
 * Using printf will interfere with our script capturing the execution results.
 * At this point, you can only test correctness with ./btest.
 * After confirming everything is correct in ./btest, remove the printf
 * and run the complete tests with test.py.
 */

 /*
 * bitAnd - x & y using only ~ and |
 * Example: bitAnd(4, 5) = 4
 * Legal ops: ~ |
 * Max ops: 7
 * Difficulty: 1
 */
int bitAnd(int x, int y) {
    return ~(~x | ~y);
}

/*
 * bitXor - x ^ y using only ~ and &
 *   Example: bitXor(4, 5) = 1
 *   Legal ops: ~ &
 *   Max ops: 7
 *   Difficulty: 1
 */
int bitXor(int x, int y) {
    return ~(~x & ~y) & ~(x & y);
}

/*
 * samesign - Determines if two integers have the same sign.
 *   0 is not positive, nor negative
 *   Example: samesign(0, 1) = 0, samesign(0, 0) = 1
 *            samesign(-4, -5) = 1, samesign(-4, 5) = 0
 *   Legal ops: >> << ! ^ && if else &
 *   Max ops: 12
 *   Difficulty: 2
 *
 * Parameters:
 *   x - The first integer.
 *   y - The second integer.
 *
 * Returns:
 *   1 if x and y have the same sign , 0 otherwise.
 */
int samesign(int x, int y) {
/* same class means: same sign-bit AND same zero-ness.
       0 is its own class (not positive, not negative). */
    int sameSign = !((x >> 31) ^ (y >> 31)); /* 1 if same sign bit */
    int sameZero = !(!x ^ !y);               /* 1 if both zero or both nonzero */
    return sameSign && sameZero;
}

/*
 * logtwo - Calculate the base-2 logarithm of a positive integer using bit
 *   shifting. (Think about bitCount)
 *   Note: You may assume that v > 0
 *   Example: logtwo(32) = 5
 *   Legal ops: > < >> << |
 *   Max ops: 25
 *   Difficulty: 4
 */
int logtwo(int v) {
    int result = 0;
    int c;
    /* binary search for the highest set bit. The boolean (x>0) is 0 or 1,
       so c = ((x>>k)>0)<<m is either 2^m or 0, used both as the accumulated
       count and as the right-shift amount for v. */
    c = ((v >> 16) > 0) << 4;   result |= c;  v >>= c;
    c = ((v >> 8)  > 0) << 3;   result |= c;  v >>= c;
    c = ((v >> 4)  > 0) << 2;   result |= c;  v >>= c;
    c = ((v >> 2)  > 0) << 1;   result |= c;  v >>= c;
    c = (v > 1);                result |= c;
    return result;
}

/*
 *  byteSwap - swaps the nth byte and the mth byte
 *    Examples: byteSwap(0x12345678, 1, 3) = 0x56341278
 *              byteSwap(0xDEADBEEF, 0, 2) = 0xDEEFBEAD
 *    Note: You may assume that 0 <= n <= 3, 0 <= m <= 3
 *    Legal ops: ! ~ & ^ | + << >>
 *    Max ops: 17
 *    Difficulty: 2
 */
int byteSwap(int x, int n, int m) {
    int nshift = n << 3;             /* shift amount for byte n */
    int mshift = m << 3;             /* shift amount for byte m */
    int nbyte = (x >> nshift) & 0xFF;/* extract byte n */
    int mbyte = (x >> mshift) & 0xFF;/* extract byte m */
    /* XOR trick: diff has 1-bits where the two bytes differ */
    int diff = nbyte ^ mbyte;
    x = x ^ (diff << nshift);
    x = x ^ (diff << mshift);
    return x;
}

/*
 * reverse - Reverse the bit order of a 32-bit unsigned integer.
 *   Example: reverse(0xFFFF0000) = 0x0000FFFF reverse(0x80000000)=0x1 reverse(0xA0000000)=0x5
 *   Note: You may assume that an unsigned integer is 32 bits long.
 *   Legal ops: << | & - + >> for while ! ~ (You can define unsigned in this function)
 *   Max ops: 30
 *   Difficulty: 3
 */
unsigned reverse(unsigned v) {
    unsigned i = 32;
    unsigned r = 0;
    while (i) {
        r = (r << 1) | (v & 1);  /* take v's lowest bit */
        v >>= 1;                  /* expose the next bit */
        i -= 1;
    }
    return r;
}


/*
 * logicalShift - shift x to the right by n, using a logical shift
 *   Examples: logicalShift(0x87654321,4) = 0x08765432
 *   Note: You can assume that 0 <= n <= 31
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 20
 *   Difficulty: 3
 */
int logicalShift(int x, int n) {
    /* arithmetic shift then mask off the sign-extension bits */
    int shifted = x >> n;
    int mask = ~(((1 << 31) >> n) << 1);
    return shifted & mask;
}

/*
 * leftBitCount - returns count of number of consective 1's in left-hand (most) end of word.
 *   Examples: leftBitCount(-1) = 32, leftBitCount(0xFFF0F0F0) = 12,
 *             leftBitCount(0xFE00FF0F) = 7
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 50
 *   Difficulty: 4
 */
int leftBitCount(int x) {
/* Binary search: a block of leading bits in x is all 1s iff the same
       block of ~x is all 0s. Each level adds 16,8,4,2,1 leading ones and
       shifts x left so the next block moves into the top position. */
    int result = 0;
    int cond;
    cond = (!((~x) >> 16)) << 4;  result += cond;  x <<= cond;
    cond = (!((~x) >> 24)) << 3;  result += cond;  x <<= cond;
    cond = (!((~x) >> 28)) << 2;  result += cond;  x <<= cond;
    cond = (!((~x) >> 30)) << 1;  result += cond;  x <<= cond;
    cond = (!((~x) >> 31));       result += cond;  x <<= cond;
    result += (x >> 31) & 1;      /* the very last bit */
    return result;
}

/*
 * float_i2f - Return bit-level equivalent of expression (float) x
 *   Result is returned as unsigned int, but it is to be interpreted as
 *   the bit-level representation of a single-precision floating point values.
 *   Legal ops: if else while for & | ~ + - >> << < > ! ==
 *   Max ops: 30
 *   Difficulty: 4
 */
unsigned float_i2f(int x) {
    unsigned sign = 0;
    unsigned abx = x;
    unsigned exp, frac, t, pos;

    if (x == 0) return 0;
    if (x < 0) { sign = 0x80000000; abx = ~abx + 1; }

    t = abx;
    pos = 0;
    while (t > 1) { t >>= 1; pos++; }

    exp = pos + 127;

    if (pos < 24) {
        frac = (abx << (23 - pos)) & 0x7FFFFF;
    } else {
        unsigned drop = pos - 23;
        unsigned rest = abx & ((1u << drop) - 1);
        unsigned roundbit = 1u << (drop - 1);
        frac = abx >> drop;
        if (rest > roundbit) frac++;
        else if (rest == roundbit) if (frac & 1) frac++;
        if (frac & 0x1000000) { exp++; frac = 0; }
        else frac = frac & 0x7FFFFF;
    }
    return sign | (exp << 23) | frac;
}


/*
 * floatScale2 - Return bit-level equivalent of expression 2*f for
 *   floating point argument f.
 *   Both the argument and result are passed as unsigned int's, but
 *   they are to be interpreted as the bit-level representation of
 *   single-precision floating point values.
 *   When argument is NaN, return argument
 *   Legal ops: & >> << | if > < >= <= ! ~ else + ==
 *   Max ops: 30
 *   Difficulty: 4
 */
unsigned floatScale2(unsigned uf) {
    unsigned sign = uf & 0x80000000;
    unsigned exp = (uf >> 23) & 0xFF;
    unsigned frac = uf & 0x7FFFFF;

    if (exp == 0xFF) return uf;      /* NaN or Inf: unchanged */

    if (exp == 0) {
        /* denormalized: double the fraction */
        frac = frac << 1;
        if (frac & 0x800000) {       /* spills into exponent -> min normal */
            exp = 1;
            frac = frac & 0x7FFFFF;  /* keep the tail, don't zero it */
        }
        return sign | (exp << 23) | frac;
    } else {

        /* normalized: increment exponent */
        exp = exp + 1;
        if (exp == 0xFF) return sign | 0x7F800000;  /* overflow -> Inf */
        return sign | (exp << 23) | frac;
    }
}

/*
 * float64_f2i - Convert a 64-bit IEEE 754 floating-point number to a 32-bit signed integer.
 *   The conversion rounds towards zero.
 *   Note: Assumes IEEE 754 representation and standard two's complement integer format.
 *   Parameters:
 *     uf1 - The lower 32 bits of the 64-bit floating-point number.
 *     uf2 - The higher 32 bits of the 64-bit floating-point number.
 *   Returns:
 *     The converted integer value, or 0x80000000 on overflow, or 0 on underflow.
 *   Legal ops: >> << | & ~ ! + - > < >= <= if else
 *   Max ops: 60
 *   Difficulty: 3
 */
int float64_f2i(unsigned uf1, unsigned uf2) {
    unsigned sign = uf2 >> 31;
    unsigned exp = (uf2 >> 20) & 0x7FF;
    unsigned val = 0x80000000u | ((uf2 & 0xFFFFF) << 11) | (uf1 >> 21);

    if (exp < 1023) return 0;             /* |value| < 1 */
    if (exp > 1054) return 0x80000000u;   /* overflow sentinel */

    val = val >> (1054 - exp);

    if (sign) {
        if (val > 0x80000000u) return 0x80000000u;
        else return -val;
    } else {
        if (val > 0x7FFFFFFF) return 0x80000000u;
        else return val;
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
 *   Legal ops: < > <= >= << >> + - & | ~ ! if else &&
 *   Max ops: 30
 *   Difficulty: 4
 */
unsigned floatPower2(int x) {
    if (x < -149) return 0;            /* underflow to 0 */
    if (x > 127) return 0x7F800000;    /* overflow to +INF */
    if (x >= -126) {
        unsigned e = x + 127;          /* implicit int->unsigned, no explicit cast */
        return e << 23;                /* normal number */
    } else {
        return 1u << (23 + (x + 126)); /* denormal number */
    }
}
