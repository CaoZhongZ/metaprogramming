#include <boost/mpl/vector_c.hpp>
#include <boost/mpl/transform.hpp>
#include <boost/mpl/equal.hpp>
#include <boost/static_assert.hpp>
#include <boost/mpl/placeholders.hpp>
#include <iostream>

using namespace boost::mpl::placeholders;

typedef boost::mpl::vector_c<int,1,0,0,0,0,0,0> mass;
typedef boost::mpl::vector_c<int,0,1,0,0,0,0,0> length;  // or position
typedef boost::mpl::vector_c<int,0,0,1,0,0,0,0> t;
typedef boost::mpl::vector_c<int,0,0,0,1,0,0,0> charge;
typedef boost::mpl::vector_c<int,0,0,0,0,1,0,0> temperature;
typedef boost::mpl::vector_c<int,0,0,0,0,0,1,0> intensity;
typedef boost::mpl::vector_c<int,0,0,0,0,0,0,1> amount_of_substance;

typedef boost::mpl::vector_c<int,0,1,-1,0,0,0,0> velocity;     // l/t
typedef boost::mpl::vector_c<int,0,1,-2,0,0,0,0> acceleration; // l/(t2)
typedef boost::mpl::vector_c<int,1,1,-1,0,0,0,0> momentum;     // ml/t
typedef boost::mpl::vector_c<int,1,1,-2,0,0,0,0> force;

template <class T, class dimentions>
class quantity {
public:
    explicit quantity(T x): value_(x) {}
    T value() const { return value_; }

template <class OtherDimensions>
    quantity(quantity<T,OtherDimensions> const& rhs)
      : value_(rhs.value()) {
      BOOST_STATIC_ASSERT((
         boost::mpl::equal<dimentions, OtherDimensions>::type::value
      ));
    }
private:
    T value_;
};

struct plus_f {
    template <class T1, class T2>
    struct apply {
       typedef typename boost::mpl::plus<T1,T2>::type type;
    };
};

struct minus_f {
    template <class T1, class T2>
    struct apply : boost::mpl::minus<T1, T2> {
    };
};

template <class T, class D1, class D2>
quantity <T, typename boost::mpl::transform<D1,D2,boost::mpl::plus<_1,_2> >::type>
operator *(quantity<T, D1> x, quantity<T, D2> y)
{
    typedef typename boost::mpl::transform<D1,D2,boost::mpl::plus<_1,_2> >::type dim;
    return quantity<T, dim>(x.value() * y.value());
}

template <class T, class D1, class D2>
quantity <T, typename boost::mpl::transform<D1,D2,plus_f>::type>
operator /(quantity<T, D1> x, quantity<T, D2> y)
{
    typedef typename boost::mpl::transform<D1,D2,minus_f>::type dim;
    return quantity<T, dim>(x.value() * y.value());
}


int main()
{
    quantity<double, acceleration> a(0.1);
    quantity<double, mass> m(2.0);
    quantity<double, force> f = (m * a);
    std::cout<<f.value()<<std::endl;
}
