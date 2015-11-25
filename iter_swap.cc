#include <iostream>

template <class ForwardIterator1, class ForwardIterator2>
void iter_swap(ForwardIterator1 i1, ForwardIterator2 i2)
{
    typename std::iterator_traits<ForwardIterator1>::value_type tmp = *i1;
    *i1 = *i2;
    *i2 = tmp;
}

int main()
{
    int a=1, b=2;
    int *pa = &a, *pb = &b;

    iter_swap(pa, pb);

    std::cout<<"a="<<a<<"; b="<<b<<std::endl;
}
