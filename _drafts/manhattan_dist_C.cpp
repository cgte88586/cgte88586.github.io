#include <RcppArmadillo.h>
// [[Rcpp::depends(RcppArmadillo)]]
#include <algorithm>
using namespace Rcpp;

// helper function for taking the absolute differece of two numbers
inline double abs_diff(double val1, double val2) {
  if(NumericVector::is_na(val1) || NumericVector::is_na(val2)) {
    return 0;
  } else {
    return abs(val1 - val2);
  }
}

// [[Rcpp::export]]
arma::mat manhattan_dist_C(arma::mat A) {
  // allocate the matrix we will return
  int n = A.n_rows, p = A.n_cols;
  arma::mat B(n, n, arma::fill::zeros);
  
  for (int i = 1; i < n; i++) {
    for (int j = 0; j < i; j++) {
      // rows we will operate on
      arma::rowvec row1 = A.row(i);
      arma::rowvec row2 = A.row(j);
      // allocate the absolute difference vector
      arma::rowvec abs_diff_vec(p);
      
      //compute the absolute difference using std::tranform
      std::transform(row1.begin(), row1.end(),  // input range 1
                     row2.begin(),              // input range 2
                     abs_diff_vec.begin(),      // output range 
                     abs_diff);                 // function to apply
      
      // write to output matrix
      B(i,j) = sum(abs_diff_vec);
    }
  }
  
  return B;
}