// -- Boost Lambda Library - actions.hpp ----------------------------------

// Copyright (C) 1999, 2000 Jaakko J�rvi (jaakko.jarvi@cs.utu.fi)
//
// Permission to copy, use, sell and distribute this software is granted
// provided this copyright notice appears in all copies. 
// Permission to modify the code and to distribute modified code is granted
// provided this copyright notice appears in all copies, and a notice 
// that the code was modified is included with the copyright notice.
//
// This software is provided "as is" without express or implied warranty, 
// and with no claim as to its suitability for any purpose.

// For more information, see www.boost.org

// ----------------------------------------------------------------

#ifndef BOOST_LAMBDA_ACTIONS_HPP
#define BOOST_LAMBDA_ACTIONS_HPP

namespace boost { 
namespace lambda {



template<int Arity, class Act> struct action;

// these need to be defined here, since the corresponding lambda 
// functions are members of lambda_functor classes

class assignment_action {};
class subscript_action {};

class identity_action {};
   
template <class Action> class other_action;

   
// action for specifying the explicit return type
template <class RET> class explicit_return_type_action {};

// action for preventing the expansion of a lambda expression
struct protect_action {};

// action for curried functions, I stands for the number of curried arguments
// (can be 1 or 2)
template <int I> class curry_action {};   

template <class Action> class return_void_action;

  // must be defined here, comma is a special case
struct comma_action {};

namespace detail {
  class unspecified {};
}

  // function action is a special case: bind functions can be called with 
  // the return type specialized explicitly e.g. bind<int>(foo);
  // If this call syntax is used, the return type is stored in the latter
  // argument of function_action template. Otherwise the argument gets the type
  // 'unspecified'.
  // This argument is only relevant in the return type deduction code
template <int I, class Result_type = detail::unspecified> class function_action {};
   



// ---------------------------------------------------------

template<class T> class function_action<1, T> {
public:
  template<class RET, class A1>
  static RET apply(A1& a1) {
    return function_adaptor<typename boost::remove_const<A1>::type>::template apply<RET>(a1);
  }
};

template<class T> class function_action<2, T> {
public:
  template<class RET, class A1, class A2>
  static RET apply(A1& a1, A2& a2) {
    return function_adaptor<typename boost::remove_const<A1>::type>::template apply<RET>
           (a1, a2);
  }
};


template <class T> struct is_lambda_functor;
template<class T> class function_action<3, T> {
public:

  template<class RET, class A1, class A2, class A3>
  static RET apply(A1& a1, A2& a2, A3& a3) {
   
    return function_adaptor<typename boost::remove_const<A1>::type>::template apply<RET>
           (a1, a2, a3);


  }
};

template<class T> class function_action<4, T> {
public:
  template<class RET, class A1, class A2, class A3, class A4>
  static RET apply(A1& a1, A2& a2, A3& a3, A4& a4) {
    return function_adaptor<typename boost::remove_const<A1>::type>::template apply<RET>
           (a1, a2, a3, a4);
  }
};

template<class T> class function_action<5, T> {
public:
  template<class RET, class A1, class A2, class A3, class A4, class A5>
  static RET apply(A1& a1, A2& a2, A3& a3, A4& a4, A5& a5) {
    return function_adaptor<typename boost::remove_const<A1>::type>::template apply<RET>
           (a1, a2, a3, a4, a5);
  }
};

template<class T> class function_action<6, T> {
public:
  template<class RET, class A1, class A2, class A3, class A4, class A5, 
           class A6>
  static RET apply(A1& a1, A2& a2, A3& a3, A4& a4, A5& a5, A6& a6) {
    return function_adaptor<typename boost::remove_const<A1>::type>::template apply<RET>
           (a1, a2, a3, a4, a5, a6);
  }
};

template<class T> class function_action<7, T> {
public:
  template<class RET, class A1, class A2, class A3, class A4, class A5,  
           class A6, class A7>
  static RET apply(A1& a1, A2& a2, A3& a3, A4& a4, A5& a5, A6& a6, A7& a7) {
    return function_adaptor<typename boost::remove_const<A1>::type>::template apply<RET>
           (a1, a2, a3, a4, a5, a6, a7);
  }
};

template<class T> class function_action<8, T> {
public:
  template<class RET, class A1, class A2, class A3, class A4, class A5, 
           class A6, class A7, class A8>
  static RET apply(A1& a1, A2& a2, A3& a3, A4& a4, A5& a5, A6& a6, A7& a7, 
                   A8& a8) {
    return function_adaptor<typename boost::remove_const<A1>::type>::template apply<RET>
           (a1, a2, a3, a4, a5, a6, a7, a8);
  }
};

template<class T> class function_action<9, T> {
public:
  template<class RET, class A1, class A2, class A3, class A4, class A5, 
           class A6, class A7, class A8, class A9>
  static RET apply(A1& a1, A2& a2, A3& a3, A4& a4, A5& a5, A6& a6, A7& a7, 
                   A8& a8, A9& a9) {
    return function_adaptor<typename boost::remove_const<A1>::type>::template apply<RET>
           (a1, a2, a3, a4, a5, a6, a7, a8, a9);
  }
};

template<class T> class function_action<10, T> {
public:
  template<class RET, class A1, class A2, class A3, class A4, class A5, 
           class A6, class A7, class A8, class A9, class A10>
  static RET apply(A1& a1, A2& a2, A3& a3, A4& a4, A5& a5, A6& a6, A7& a7, 
                   A8& a8, A9& a9, A10& a10) {
    return function_adaptor<typename boost::remove_const<A1>::type>::template apply<RET>
           (a1, a2, a3, a4, a5, a6, a7, a8, a9, a10);
  }
};

  // actions, for which the existence of protect is checked in return type 
  // deduction.
class protectable {};

namespace detail {
template<class T> struct is_protectable_action {
  BOOST_STATIC_CONSTANT(bool, value = (boost::is_base_and_derived<protectable, T>::value)); 
};

template<> struct is_protectable_action<other_action<assignment_action> > {
    BOOST_STATIC_CONSTANT(bool, value = true);
  };
template<> struct is_protectable_action<other_action<comma_action> > {
    BOOST_STATIC_CONSTANT(bool, value = true);
  };

} // end detail




} // namespace lambda
} // namespace boost

#endif
