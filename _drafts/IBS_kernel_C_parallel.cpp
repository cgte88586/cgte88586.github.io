// [[Rcpp::depends(RcppParallel)]]
#include <Rcpp.h>
#include <RcppParallel.h>
using namespace RcppParallel;

// define both_non_NA(a, b)
inline bool both_non_NA(double a, double b) {
  return (!ISNAN(a) && !ISNAN(b));
}

struct IBSKernel : public Worker
{
  // source matrix
  const RMatrix<double> X;
  
  // destination matrix
  RMatrix<double> out;
  
  // initialize with source and destination
  IBSKernel(const Rcpp::NumericMatrix X, Rcpp::NumericMatrix out) 
  : X(X), out(out) {}
  
  // calculate the IBS kernel of the range of elements requested
  void operator()(std::size_t begin, std::size_t end) {
    int p = X.ncol();
    for (std::size_t i = begin; i < end; i++) {
      for (std::size_t j = 0; j < i; j++) {
        int dist = 0, count = 0;
        for (int k = 0; k < p; k++) {
          double xi = X(i, k), xj = X(j, k);
          if (both_non_NA(xi, xj)) {
            dist += abs(xi - xj);
            count++;
          }
        }
        out(i, j) = 1 - .5 * dist / count;
      }
    }
  }
};

// [[Rcpp::export]]
Rcpp::NumericMatrix IBS_kernel_C_parallel(Rcpp::NumericMatrix X) {
  
  // allocate the output matrix
  Rcpp::NumericMatrix out(X.nrow(), X.nrow());
  
  // IBSKernel functor (pass input and output matrixes)
  IBSKernel ibskernel(X, out);
  
  // call parallelFor to do the work
  parallelFor(0, X.nrow(), ibskernel);
  
  // return the output matrix
  return out;
}