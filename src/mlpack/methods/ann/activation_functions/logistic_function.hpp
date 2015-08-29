/**
 * @file logistic_function.hpp
 * @author Marcus Edel
 *
 * Definition and implementation of the logistic function.
 */
#ifndef __MLPACK_METHODS_ANN_ACTIVATION_FUNCTIONS_LOGISTIC_FUNCTION_HPP
#define __MLPACK_METHODS_ANN_ACTIVATION_FUNCTIONS_LOGISTIC_FUNCTION_HPP

#include <mlpack/core.hpp>

namespace mlpack {
namespace ann /** Artificial Neural Network. */ {

/**
 * The logistic function, defined by
 *
 * @f{eqnarray*}{
 * f(x) &=& \frac{1}{1 + e^{-x}} \\
 * f'(x) &=& f(x) * (1 - f(x)) \\
 * f^{-1}(y) &=& ln(\frac{y}{1-y})
 * @f}
 */
class LogisticFunction
{
  public:
  /**
   * Computes the logistic function.
   *
   * @param x Input data.
   * @return f(x).
   */
  template<typename eT>
  static double fn(const eT x)
  {
    if(x < arma::Math<eT>::log_max())
    {
      if (x > -arma::Math<eT>::log_max())
        return 1.0 /  (1.0 + std::exp(-x));

      return 0.0;
    }

    return 1.0;
  }

  /**
   * Computes the logistic function.
   *
   * @param x Input data.
   * @param y The resulting output activation.
   */
  template<typename InputVecType, typename OutputVecType>
  static void fn(const InputVecType& x, OutputVecType& y)
  {
    y = x;

    for (size_t i = 0; i < x.n_elem; i++)
      y(i) = fn(x(i));
  }

  /**
   * Computes the first derivative of the logistic function.
   *
   * @param x Input data.
   * @return f'(x)
   */
  static double deriv(const double y)
  {
    return y * (1.0 - y);
  }

  /**
   * Computes the first derivatives of the logistic function.
   *
   * @param y Input activations.
   * @param x The resulting derivatives.
   */
  template<typename InputVecType, typename OutputVecType>
  static void deriv(const InputVecType& y, OutputVecType& x)
  {
    x = y % (1.0 - y);
  }

  /**
   * Computes the inverse of the logistic function.
   *
   * @param y Input data.
   * @return f^{-1}(y)
   */
  static double inv(const double y)
  {
    return arma::trunc_log(y / (1 - y));
  }

  /**
   * Computes the inverse of the logistic function.
   *
   * @param y Input data.
   * @return  x The resulting inverse of the input data.
   */
  template<typename InputVecType, typename OutputVecType>
  static void inv(const InputVecType& y, OutputVecType& x)
  {
    x = arma::trunc_log(y / (1 - y));
  }
}; // class LogisticFunction

}; // namespace ann
}; // namespace mlpack

#endif
