#pragma once
#include <cstddef>

template<class P, class M>
size_t my_offsetof(M P::*member)
{
    return (size_t) &( reinterpret_cast<P*>(0)->*member);
}

template<class P, class M>
P* container_of_(const M* ptr , M P::*member )
{
    return (P*)((char*)ptr - my_offsetof(member));
}

#define container_of(ptr, type, member) \
     container_of_(ptr, &type::member)

