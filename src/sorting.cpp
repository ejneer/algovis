#include <Rcpp.h>
#include <string.h>
using namespace Rcpp;

class MergeSorter
{
public:
  NumericVector data;
  DataFrame dataSnapshots;
  int iterationCount;
  bool snapshot;

  MergeSorter(NumericVector data, bool snapshot)
  {
    this->iterationCount = 0;
    this->snapshot = false;
    this->data = clone(data);
    this->snapshot = snapshot;
    if (snapshot)
    {
      this->dataSnapshots = DataFrame::create(Named(this->getIterationCount()) = clone(data));
    }
  }

  std::string getIterationCount()
  {
    return std::to_string(this->iterationCount);
  }

  void mergeSort(int left_idx, int right_idx)
  {
    if (left_idx < right_idx)
    {
      int mid_idx = (left_idx + right_idx) / 2;
      mergeSort(left_idx, mid_idx);
      mergeSort(mid_idx + 1, right_idx);
      merge(left_idx, mid_idx, right_idx);
    }
  }

  void merge(int left_idx, int mid_idx, int right_idx)
  {
    // copy the elements to be sorted
    NumericVector Left = this->data[Range(left_idx, mid_idx)];
    NumericVector Right = this->data[Range(mid_idx + 1, right_idx)];

    NumericVector::iterator left_iter = Left.begin();
    NumericVector::iterator right_iter = Right.begin();
    NumericVector::iterator subset_iter = this->data.begin() + left_idx;

    while (left_iter != Left.end() && right_iter != Right.end())
    {
      if (*left_iter < *right_iter)
      {
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

    while (left_iter != Left.end())
    {
      *subset_iter = *left_iter;
      left_iter++;
      subset_iter++;
    }

    while (right_iter != Right.end())
    {
      *subset_iter = *right_iter;
      right_iter++;
      subset_iter++;
    }
    if (this->snapshot)
      this->takeSnapshot();
  }

  void takeSnapshot()
  {
    this->iterationCount++;
    this->dataSnapshots.push_back(clone(data), this->getIterationCount());
  }
};

// [[Rcpp::plugins(cpp11)]]
// [[Rcpp::export]]
NumericVector mergeSort(NumericVector x)
{
  MergeSorter sorter(x, false);
  sorter.mergeSort(0, x.size() - 1);
  return sorter.data;
}

// [[Rcpp::export]]
DataFrame mergeSortSnapshot(NumericVector x)
{
  MergeSorter sorter(x, true);
  sorter.mergeSort(0, x.size() - 1);
  return sorter.dataSnapshots;
}