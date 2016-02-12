#include <Rcpp.h>
using namespace Rcpp;

// define both_non_NA(a, b)
inline bool both_non_NA(double a, double b) {
  return (!ISNAN(a) && !ISNAN(b));
}

// [[Rcpp::export]]
NumericMatrix IBS_kernel_C(NumericMatrix X) {
  int n = X.nrow(), p = X.ncol();
  NumericMatrix out(n, n);
  for (int i = 0; i < n; i++) {
    for (int j = i + 1; j < n; j++) {
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
  return out;
}