rm(list = ls())
gc()
library(Rcpp)
library(RcppArmadillo)
library(microbenchmark)

cppFunction("NumericMatrix mdC(NumericMatrix X) {
int n = X.nrow(), p = X.ncol();
NumericMatrix out(n, n), out_c(n, n);
for (int i = 0; i < n; i++) {
  for (int j = i + 1; j < n; j++) {
    double total = 0, total_c = 0;
    for (int k = 0; k < p; k++) {
      double xi = X(i, k), xj = X(j, k);
      if (!NumericVector::is_na(xi) && !NumericVector::is_na(xj)) {
        total += abs(xi - xj);
        total_c++;
      }
    }
    out(i, j) = 1 - .5 * total / total_c;
  }
}
return out;
}")

cppFunction("arma::mat mdC2(arma::mat X) {
int n = X.n_rows, p = X.n_cols;
arma::mat out(n, n, arma::fill::zeros), out_c(n, n, arma::fill::zeros);
for (int i = 0; i < n; i++) {
  for (int j = i + 1; j < n; j++) {
    double total = 0, total_c = 0;
    for (int k = 0; k < p; k++) {
      double xi = X(i, k), xj = X(j, k);
      if (!NumericVector::is_na(xi) && !NumericVector::is_na(xj)) {
        total += abs(xi - xj);
        total_c++;
      }
    }
    out(i, j) = 1 - .5 * total / total_c * p;
  }
}
return out;
}", depends="RcppArmadillo")

cppFunction("
  NumericVector sss(NumericVector x) {
    return x(NumericVector::is_na(x));
  }
")
abs_diff(1,NA)


setwd('E:/Documents/cgte88586.github.io/_drafts')
sourceCpp("manhattan_dist_C.cpp")



see <- matrix(sample(c(0:2, NA), 10e6, replace=T), 10)
see
manhattan_dist_C(see)
1 - as.matrix(dist(see, method='manhattan') * .5 /max(1, ncol(see)) )
mdC(see)
mdC2(see)

microbenchmark(
  mdC(see),
  1 - as.matrix(dist(see, method='manhattan') * .5 /max(1, ncol(see)) ),
times=1)
