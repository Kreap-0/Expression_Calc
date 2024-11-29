#include "BigNum.h"
#include <string>
#include <algorithm>
#include <cstdlib>

using std::string;

BigNum::BigNum()
{
    a.clear();
    l = 0;
    sign = false;
}

BigNum::BigNum(string S)
{
    int len = S.length();
    reverse(S.begin(), S.end());
    if (S.back() == '-')
    {
        sign = true;
        len--;
    }
    else
        sign = false;
    l = (len - 1) / 9 + 1;
    a.resize(l);
    for (int i = 0, x = 0; i < l; i++)
    {
        x = 0;
        const int lim = 9 * i;
        for (int j = ((i == l - 1) ? len : 9 * (i + 1)) - 1; j >= lim; j--)
            x = x * 10 + S[j] - '0';
        a[i] = x;
    }
    while (l && !a[l - 1])
        l--;
}

BigNum BigNum::operator+(const BigNum &X) const
{
    if (!X.l)
        return (*this);
    BigNum c(*this);
    if (sign == X.sign)
        c.sign = sign;
    else if (sign)
    {
        this->sign = false;
        BigNum tmp(X - (*this));
        this->sign = true;
        return tmp;
    }
    else
    {
        X.sign = false;
        BigNum tmp((*this) - X);
        X.sign = true;
        return tmp;
    }
    c.a.resize(c.l = std::max(l, X.l) + 1);
    for (int i = 0; i < c.l; i++)
    {
        if (i < X.l)
            c.a[i] += X.a[i];
        c.a[i + 1] += c.a[i] / Bs;
        if (c.a[i] >= Bs)
            c.a[i] -= Bs;
    }
    if (c.l && !c.a[c.l - 1])
        c.a.resize(--c.l);
    return c;
}

BigNum BigNum::operator-(const BigNum &X) const
{
    if (!X.l)
        return (*this);
    if (sign == X.sign)
    {
        BigNum c;
        bool tag = sign;
        if (tag)
        {
            sign = false;
            X.sign = false;
        }
        if ((*this) < X)
        {
            c = X - (*this);
            c.sign = true ^ tag;
        }
        else
        {
            c = (*this);
            for (int i = 0; i < c.l; i++)
            {
                if (i < X.l)
                    c.a[i] -= X.a[i];
                if (c.a[i] < 0)
                    c.a[i] += Bs, c.a[i + 1]--;
            }
            while (c.l && !c.a[c.l - 1])
                c.l--;
            c.a.resize(c.l);
            c.sign = false ^ tag;
        }
        if (tag)
        {
            sign = true;
            X.sign = true;
        }
        return c;
    }
    else
    {
        bool tag = sign;
        sign = X.sign = false;
        BigNum tmp((*this) + X);
        (tag ? sign : X.sign) = tag;
        tmp.sign = tag;
        return tmp;
    }
}

BigNum BigNum::operator*(const BigNum &X) const
{
    BigNum c;
    if (!X.l || !l)
        return c;
    c.l = l + X.l;
    c.a.resize(c.l);
    c.sign = sign ^ X.sign;
    for (int i = 0; i < l; i++)
        for (int j = 0; j < X.l; j++)
        {
            c.a[i + j] += a[i] * X.a[j];
            c.a[i + j + 1] += c.a[i + j] / Bs;
            c.a[i + j] %= Bs;
        }
    while (c.l && !c.a[c.l - 1])
        c.l--;
    c.a.resize(c.l);
    return c;
}

BigNum BigNum::operator/(const BigNum &X) const
{
    if (!X.l)
    {
        cout << "Integer divided by zero.\n";
        exit(0);
    }
    static const BigNum Two("2");
    BigNum c, tmp((*this));
    if ((*this) < X)
        return c;
    c.l = l - X.l + 1;
    c.a.resize(c.l);
    c.sign = sign ^ X.sign;
    static BigNum pw[30];
    pw[0] = X;
    for (int i = 1; i < 30; i++)
        pw[i] = pw[i - 1] * Two;
    for (int i = l - X.l, tp = l - 1; ~i; i--)
        for (int j = 29; ~j; j--)
        {
            bool tag = false;
            const int len = tp - i + 1;
            if (len > pw[j].l)
                tag = true;
            else if (len == pw[j].l)
            {
                bool flag = true;
                for (int k = len - 1; ~k; k--)
                    if (pw[j].a[k] < tmp.a[k + i])
                        break;
                    else if (pw[j].a[k] > tmp.a[k + i])
                    {
                        flag = false;
                        break;
                    }
                tag |= flag;
            }
            if (tag)
            {
                c.a[i] += 1 << j;
                for (int k = 0; k < pw[j].l; k++)
                {
                    tmp.a[k + i] -= pw[j].a[k];
                    if (tmp.a[k + i] < 0)
                        tmp.a[k + i] += Bs, tmp.a[k + i + 1]--;
                }
                while (~tp && !tmp.a[tp])
                    tp--;
            }
        }
    while (c.l && !c.a[c.l - 1])
        c.l--;
    return c;
}

bool BigNum::operator<(const BigNum &X) const
{
    if (a.size() != X.a.size())
        return a.size() < X.a.size();
    for (int i = a.size() - 1; ~i; i--)
        if (a[i] != X.a[i])
            return a[i] < X.a[i];
    return 0;
}

bool BigNum::operator==(const BigNum &X) const
{
    if (a.size() != X.a.size())
        return 0;
    for (int i = a.size() - 1; ~i; i--)
        if (a[i] != X.a[i])
            return 0;
    return 1;
}

bool BigNum::operator<=(const BigNum &X) const
{
    return ((*this) < X) || ((*this) == X);
}

void BigNum::print() const
{
    if (!l)
        cout << "0";
    else
    {
        if (sign)
            cout << "-";
        cout << a[l - 1];
        for (int i = l - 2; ~i; i--)
            cout << a[i];
    }
}

const string BigNum::printString() const
{
    if (!l)
        return "0";
    else
    {
        string tmp = "";
        if (sign)
            tmp += "-";
        for (int i = l - 1; ~i; i--)
            tmp += std::to_string(a[i]);
        return tmp;
    }
}
