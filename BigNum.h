#ifndef _BIGNUM_H_
#define _BIGNUM_H_

#include <vector>
#include <iostream>
#include <string>

using std::string;
using std::vector;

class BigNum
{
    int l;
    mutable bool sign;
    vector<long long> a;
    static const int Bs = 1e9;

public:
    BigNum();
    BigNum(string);
    ~BigNum() {}
    BigNum operator+(const BigNum &X) const;
    BigNum operator-(const BigNum &X) const;
    BigNum operator*(const BigNum &X) const;
    BigNum operator/(const BigNum &X) const;
    bool operator<(const BigNum &X) const;
    bool operator==(const BigNum &X) const;
    bool operator<=(const BigNum &X) const;
    void print() const;
    const string printString() const;
};

#endif
