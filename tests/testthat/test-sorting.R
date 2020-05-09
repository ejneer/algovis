test_that("sorting works", {
  test_vector <-
    c(
      7.095809,
      2.825275,
      1.128111,
      6.599878,
      4.230301,
      2.535363,
      4.921699,
      2.825585,
      3.312714,
      3.237771
    )
  sorted_vector <- sort(test_vector)
  test_vector <- mergeSort(test_vector, snapshot = FALSE)
  
  expect_equal(test_vector, sorted_vector)
})