#ifndef FLAGS_H
#define FLAGS_H

#include <Core/Types.h>

namespace uLib {

template<typename Enum>
class Flags
{
    int i;
public:
    typedef Enum enum_type;
    CONSTEXPR inline Flags(const Flags &f) : i(f.i) {}
    CONSTEXPR inline Flags(Enum f) : i(f) {}
    CONSTEXPR inline Flags() : i(0) {}

    inline Flags &operator=(const Flags &f) { i = f.i; return *this; }
    inline Flags &operator&=(int mask) { i &= mask; return *this; }
    inline Flags &operator&=(uint mask) { i &= mask; return *this; }
    inline Flags &operator|=(Flags f) { i |= f.i; return *this; }
    inline Flags &operator|=(Enum f) { i |= f; return *this; }
    inline Flags &operator^=(Flags f) { i ^= f.i; return *this; }
    inline Flags &operator^=(Enum f) { i ^= f; return *this; }

    CONSTEXPR  inline operator int() const { return i; }

    CONSTEXPR inline Flags operator|(Flags f) const { return Flags(Enum(i | f.i)); }
    CONSTEXPR inline Flags operator|(Enum f) const { return Flags(Enum(i | f)); }
    CONSTEXPR inline Flags operator^(Flags f) const { return Flags(Enum(i ^ f.i)); }
    CONSTEXPR inline Flags operator^(Enum f) const { return Flags(Enum(i ^ f)); }
    CONSTEXPR inline Flags operator&(int mask) const { return Flags(Enum(i & mask)); }
    CONSTEXPR inline Flags operator&(uint mask) const { return Flags(Enum(i & mask)); }
    CONSTEXPR inline Flags operator&(Enum f) const { return Flags(Enum(i & f)); }
    CONSTEXPR inline Flags operator~() const { return Flags(Enum(~i)); }

    CONSTEXPR inline bool operator!() const { return !i; }

    inline bool testFlag(Enum f) const { return (i & f) == f && (f != 0 || i == int(f) ); }
};

#define ULIB_OPERATORS_FOR_FLAGS(Flags) \
CONSTEXPR inline QFlags<Flags::enum_type> operator|(Flags::enum_type f1, Flags::enum_type f2) \
{ return QFlags<Flags::enum_type>(f1) | f2; } \
CONSTEXPR inline QFlags<Flags::enum_type> operator|(Flags::enum_type f1, QFlags<Flags::enum_type> f2) \
{ return f2 | f1; }


} // uLib




#endif // FLAGS_H
