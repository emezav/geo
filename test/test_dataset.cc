#include <iostream>
#include <filesystem>
#include <gtest/gtest.h>

#include "geo.h"

namespace fs = std::filesystem;

using std::cout;
using std::endl;

using FloatDataSet = geo::DataSet<float>;

/**
 * @brief Create a Sequential Data object
 *
 * @param n Number of elements
 * @return float* Dataset with sequential data
 */
float * createSequentialData(int n);

/**
 * @brief Checks if an array stores sequential values
 * @param data Data array
 * @param n Element count
 * @return true If the array is sequential
 * @return false If the array is not sequential
 */
bool isSequentialData(const float  * data, int n);

// Saving datasets from disk
TEST(DataSetTest, SavingDataSets)
{

  int n = 250000;
  int lineSize = 500;

  float * data = createSequentialData(n);
  geo::status status;

  // Use "data/" folder
  fs::path currentPath(fs::current_path() / "data");

  /// Fail and stop if the output directory could not be created
  fs::create_directories(currentPath);
  ASSERT_TRUE(fs::is_directory(currentPath));

  const string strPath = (currentPath / "test.txt").string();

  status = FloatDataSet::saveText(strPath, data, n, lineSize);

  EXPECT_EQ(status, geo::status::SUCCESS);
}

// Loading datasets from disk
TEST(DataSetTest, LoadingDatasets)
{

  // Use "data/" folder
  fs::path currentPath(fs::current_path() / "data");
  ASSERT_TRUE(fs::is_directory(currentPath));

  const string strPath = (currentPath / "test.txt").string();
  auto [status, count, data] = FloatDataSet::loadText(strPath);

  EXPECT_TRUE(isSequentialData(data, count));

  EXPECT_TRUE(true);
}


float * createSequentialData(int n) {
  float * data = (float*)malloc(n * sizeof(float));

  if (data == nullptr) {
    return data;
  }

  for (size_t i=0; i < n; i++) {
    data[i] = (float)i;
  }

  return data;
}


bool isSequentialData(const float * data, int n) {

  int i;
  for (i = 0; i < n && data[i] == (float)i; i++);

  return (i == n);

  return true;
}