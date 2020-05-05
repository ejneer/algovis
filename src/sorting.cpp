#include <Rcpp.h>
using namespace Rcpp;

void merge(NumericVector x, int left_idx, int mid_idx, int right_idx) {
  // copy the elements to be sorted
  NumericVector Left = x[Range(left_idx, mid_idx)];
  NumericVector Right = x[Range(mid_idx + 1, right_idx)];
  
  NumericVector::iterator left_iter = Left.begin();
  NumericVector::iterator right_iter = Right.begin();
  NumericVector::iterator subset_iter = x.begin() + left_idx;
  
  while (left_iter != Left.end() && right_iter != Right.end()) {
    if (*left_iter < *right_iter) {
      *subset_iter = *left_iter;
      left_iter++;
    }
    else 
    {
      *subset_iter = *right_iter;  
      right_iter++;
    }
    subset_iter++;
  }
  
  while (left_iter != Left.end()) {
    *subset_iter = *left_iter;
    left_iter++;
    subset_iter++;
  }
  
  while (right_iter != Right.end()) {
    *subset_iter = *right_iter;
    right_iter++;
    subset_iter++;
  }
}

void mergeSort(NumericVector x, int left_idx, int right_idx) {
  if (left_idx < right_idx) {
    int mid_idx = (left_idx + right_idx) / 2;
    mergeSort(x, left_idx, mid_idx);
    mergeSort(x, mid_idx + 1, right_idx);
    merge(x, left_idx, mid_idx, right_idx);
  }
}

// [[Rcpp::export]]
void mergeSort(NumericVector x) {
  mergeSort(x, 0, x.size() - 1);
}