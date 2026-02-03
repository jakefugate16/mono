#include <iostream>
#include <numeric> //for gcd

constexpr class Fraction
{
public:
    constexpr Fraction(int num=0, int den=1)
        : m_num{ num }, m_den{ den }
    {
        
        reduce();
        if(m_den < 0)
        {
            m_den *= -1;
            m_num *= -1;
        }
    }

    constexpr void reduce()
    {
        for(int gcd{std::gcd(m_num, m_den) }; gcd != 1; gcd = std::gcd(m_num, m_den))
        {
            m_num /= gcd;
            m_den /= gcd;
        }
    }

    void print() const
    {
        if(m_num == m_den)
            std::cout << 1 << '\n';
        else if(m_den == 0)
            std::cout << "NaN" << '\n';
        else
            std::cout << m_num << '/' << m_den << '\n';
        return;
    }

    constexpr friend Fraction operator+(const Fraction& f1, const Fraction& f2);
    constexpr friend Fraction operator+(const Fraction& f1, int val);
    constexpr friend Fraction operator+(int val, const Fraction& f1);

    constexpr friend Fraction operator*(const Fraction& f1, const Fraction& f2);
    constexpr friend Fraction operator*(const Fraction& f, const int n);
    constexpr friend Fraction operator*(const int n, const Fraction& f);

    constexpr friend bool operator==(const Fraction& f1, const Fraction& f2);
    constexpr friend bool operator<(const Fraction& f1, const Fraction& f2);
    constexpr friend bool operator>(const Fraction& f1, const Fraction& f2);
    constexpr friend bool operator>=(const Fraction& f1, const Fraction& f2);
    constexpr friend bool operator<=(const Fraction& f1, const Fraction& f2);
    constexpr friend bool operator!=(const Fraction& f1, const Fraction& f2);

    friend std::ostream& operator<<(std::ostream& out, const Fraction& f);
    friend std::istream& operator>>(std::istream& in, Fraction& f);

private:
    int m_num{ 0 };
    int m_den{ 1 };
};

constexpr Fraction operator+(const Fraction& f1, const Fraction& f2)
{ return Fraction{ (f1.m_num*f2.m_den + f2.m_num*f1.m_den), (f1.m_den*f2.m_den) }; }

constexpr Fraction operator+(const Fraction& f, int val)
{ return Fraction{ (f.m_num + (f.m_den*val)), f.m_den }; }

constexpr Fraction operator+(int val, const Fraction& f)
{ return Fraction{ (f.m_num + (f.m_den*val)), f.m_den }; }

constexpr Fraction operator*(const Fraction& f1, const Fraction& f2)
{ return Fraction {f1.m_num*f2.m_num, f1.m_den*f2.m_den}; }

constexpr Fraction operator*(const Fraction& f, const int n)
{ return {f.m_num * n, f.m_den}; }

constexpr Fraction operator*(const int n, const Fraction& f)
{ return {f.m_num * n, f.m_den}; }

constexpr bool operator ==(const Fraction& f1, const Fraction& f2){ return (f1.m_num == f2.m_num) && (f1.m_den == f2.m_den); }
constexpr bool operator !=(const Fraction& f1, const Fraction& f2){ return !(f1==f2); }
constexpr bool operator <(const Fraction& f1, const Fraction& f2){ return f1.m_num*f2.m_den < f2.m_num*f1.m_den; }
constexpr bool operator >(const Fraction& f1, const Fraction& f2){ return f2 < f1; }
constexpr bool operator <=(const Fraction& f1, const Fraction& f2){ return !(f1 > f2); }
constexpr bool operator >=(const Fraction& f1, const Fraction& f2){ return !(f1 < f2); }


std::ostream& operator<<(std::ostream& out, const Fraction& f)
{
    if(f.m_den == 0)
        out << "NaN";
    else if(f.m_den == 1)
        out << f.m_num;
    else
        out << f.m_num << '/' << f.m_den;
    return out;
}

std::istream& operator>>(std::istream& in, Fraction& f)
{
    int num{ 0 }, den{ 1 };
    char ignore{};

    in >> num >> ignore >> den;
    if(den == 0)
        in.setstate(std::ios_base::failbit);
    if(in)
        f = Fraction {num, den};
    return in;
}

static_assert((Fraction {2, 3} + Fraction{2, 3}) == Fraction { 4, 3});
static_assert((Fraction {2, 3} * Fraction{2, 3}) == Fraction{8, 18} );
static_assert((Fraction{2, 3} < Fraction{5,6}));
static_assert(Fraction{2, 3} > Fraction{1,2});
static_assert(Fraction{5, 10} == Fraction {1,2});
static_assert(Fraction{-2, 3} == Fraction {2, -3});
static_assert((Fraction{2, 3} <= Fraction {2, 3}) && (Fraction{3, 27} <= Fraction{99,100}));
static_assert((Fraction{2, 3} >= Fraction{2, 3}) && (Fraction{4,5} >= Fraction{1,2}));
static_assert(Fraction{1, 3} != Fraction{1, 4});

int main()
{

    Fraction f1{ 3, 2 };
    Fraction f2{ 5, 8 };
    
    std::cout << f1 << ((f1 == f2) ? " == " : " not == ") << f2 << '\n';
    std::cout << f1 << ((f1 != f2) ? " != " : " not != ") << f2 << '\n';
    std::cout << f1 << ((f1 < f2) ? " < " : " not < ") << f2 << '\n';
    std::cout << f1 << ((f1 > f2) ? " > " : " not > ") << f2 << '\n';
    std::cout << f1 << ((f1 <= f2) ? " <= " : " not <= ") << f2 << '\n';
    std::cout << f1 << ((f1 >= f2) ? " >= " : " not >= ") << f2 << '\n';
    return 0;
}