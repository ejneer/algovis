#include <Rcpp.h>
using namespace Rcpp;

void merge(NumericVector x, int left_idx, int mid_idx, int right_idx) {
  int n1 = mid_idx - left_idx + 1;
  int n2 = right_idx - mid_idx;
  
  NumericVector Left(n1);
  NumericVector Right(n2);
  
  // copy the elements to be sorted
  for (int i = 0; i <= n1; i++) Left[i] = x[left_idx + i];
  for (int i = 0; i <= n2; i++) Right[i] = x[mid_idx + 1 + i];
  
  int i = 0;
  int j = 0;
  int k = left_idx;
  
  while (i < n1 && j < n2) {
    if (Left[i] <= Right[j]) {
      x[k] = Left[i];
      i++;
    }
    else 
    {
      x[k] = Right[j];
      j++;
    }
    k++;
  }
  
  while (i < n1) {
    x[k] = Left[i];
    i++;
    k++;
  }
  
  while (j < n2) {
    x[k] = Right[j];
    j++;
    k++;
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