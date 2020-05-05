test_that("multiplication works", {
  expect_equal(2 * 2, 4)
})

test_that("sorting works", {
  test_vector <- runif(10) * 10
  sorted_vector <- sort(test_vector)
  mergeSort(test_vector)
  
  expect_equal(test_vector, sorted_vector)
})