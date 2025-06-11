/**
 * @file
 * @brief Grid tests
 * @author Erwin Meza Vega <emezav@unicauca.edu.co> <emezav@gmail.com>
 * @copyright MIT License
 */

#include <iostream>
#include <filesystem>
#include <gtest/gtest.h>

#include "geo.h"

namespace fs = std::filesystem;

using std::cout;
using std::endl;

using geo::Grid;
using geo::GridFormat;
using geo::status;

/**
 * @brief Create a Sequential Grid object. grid[i] = 0, grid[1] = 1 and so on
 * @param grid Grid
 * @param rows Grid rows
 * @param columns Grid columns
 * @param x0 Grid X (longitude) origin
 * @param y0 Grid Y (latitude) origin
 * @param dx Grid X resolution in meters
 * @param dy Grid Y resolution in meters
 * @return Grid
 */
Grid createSequentialGrid(GridFormat format, int rows, int columns, double x0, double y0, double dx, double dy);

/**
 * @brief Checks if a grid stores sequential values
 * @param grid Grid
 * @return true If grid is sequential
 * @return false If the grid is not sequential
 */
bool isSequentialGrid(const Grid &grid);

/**
 * @brief Create a Test Grid object
 *
 * @return Grid
 */
Grid createTestGrid();

/**
 * @brief Creates the grid folder
 *
 * @return status
 */
status createGridFolder();

// Grid creation
TEST(GridTest, CreatingGrid)
{

  // Create test grid
  Grid grid = createTestGrid();

  // Check if grid is sequential
  EXPECT_EQ(isSequentialGrid(grid), true);
}

// Save grid to Esri ASCII
TEST(GridTest, SaveEsriAscii)
{
  status status;

  // Create grid folder
  createGridFolder();

  // create "grids/" folder
  fs::path currentPath(fs::current_path() / "grids");

  ASSERT_TRUE(fs::is_directory(currentPath));

  // Create test grid
  Grid grid = createTestGrid();

  // Save ESRI ASCII grid
  status = geo::Esri::saveAscii(grid, (currentPath / "esri.asc").string());

  // Status must be true, grid saved successfully.
  EXPECT_EQ(status, geo::status::SUCCESS);
}

// Save grid to Esri Float
TEST(GridTest, SaveEsriFloat)
{

  status status;

  // Create grid folder
  createGridFolder();

  // create "grids/" folder
  fs::path currentPath(fs::current_path() / "grids");

  ASSERT_TRUE(fs::is_directory(currentPath));

  // Create test grid
  Grid grid = createTestGrid();

  // Save ESRI Float grid
  status = geo::Esri::saveFloat(grid, (currentPath / "esriFloat.bil").string());

  // Status must be true, grid saved successfully.
  EXPECT_EQ(status, geo::status::SUCCESS);
}

// Save grid to Envi Float
TEST(GridTest, SaveEnviFloat)
{

  status status;

  // Create grid folder
  createGridFolder();

  // create "grids/" folder
  fs::path currentPath(fs::current_path() / "grids");

  ASSERT_TRUE(fs::is_directory(currentPath));

  // Create test grid
  Grid grid = createTestGrid();

  // Save ENVI grid float
  status = geo::Envi::saveFloat(grid, (currentPath / "enviFloat.flt").string());
}

// Save grid to Envi Double
TEST(GridTest, SaveEnviDouble)
{

  status status;

  // Create grid folder
  createGridFolder();

  // create "grids/" folder
  fs::path currentPath(fs::current_path() / "grids");

  ASSERT_TRUE(fs::is_directory(currentPath));

  // Create test grid
  Grid grid = createTestGrid();

  // Save ENVI grid double
  status = geo::Envi::saveFloat(grid, (currentPath / "enviDouble.flt").string());

  // Status must be true, grid saved successfully.
  EXPECT_EQ(status, geo::status::SUCCESS);
}

// Save grid to Surfer ASCII
TEST(GridTest, SaveSurferAscii)
{

  status status;

  // Create grid folder
  createGridFolder();

  // create "grids/" folder
  fs::path currentPath(fs::current_path() / "grids");

  ASSERT_TRUE(fs::is_directory(currentPath));

  // Create test grid
  Grid grid = createTestGrid();

  // Save Surfer ASCII grid
  status = geo::Surfer::save(grid, (currentPath / "surferAscii.grd").string(), geo::Surfer::fileType::TEXT);

  // Status must be true, grid saved successfully.
  EXPECT_EQ(status, geo::status::SUCCESS);
}

// Save grid to Surfer 6 float
TEST(GridTest, SaveSurferFloat)
{

  status status;

  // Create grid folder
  createGridFolder();

  // create "grids/" folder
  fs::path currentPath(fs::current_path() / "grids");

  ASSERT_TRUE(fs::is_directory(currentPath));

  // Create test grid
  Grid grid = createTestGrid();

  // Save Surfer 6 binary grid
  status = geo::Surfer::save(grid, (currentPath / "surfer6.grd").string(), geo::Surfer::fileType::FLOAT);

  // Status must be true, grid saved successfully.
  EXPECT_EQ(status, geo::status::SUCCESS);
}

// Save grid to Surfer 7 float
TEST(GridTest, SaveSurferDouble)
{

  status status;

  // Create grid folder
  createGridFolder();

  // create "grids/" folder
  fs::path currentPath(fs::current_path() / "grids");

  ASSERT_TRUE(fs::is_directory(currentPath));

  // Create test grid
  Grid grid = createTestGrid();

  // Save Surfer 7 binary grid
  status = geo::Surfer::save(grid, (currentPath / "surfer7.grd").string(), geo::Surfer::fileType::DOUBLE);

  // Status must be true, grid saved successfully.
  EXPECT_EQ(status, geo::status::SUCCESS);
}

// Save grid to TXT
TEST(GridTest, SaveTxt)
{

  status status;

  // Create grid folder
  createGridFolder();

  // create "grids/" folder
  fs::path currentPath(fs::current_path() / "grids");

  ASSERT_TRUE(fs::is_directory(currentPath));

  // Create test grid
  Grid grid = createTestGrid();

  // Save txt grid
  status = geo::SaveGrid(grid, (currentPath / "grid.txt").string(), GridFormat::TEXT);

  // Status must be true, grid saved successfully.
  EXPECT_EQ(status, geo::status::SUCCESS);
}

// Save grid to TXT reversed rows
TEST(GridTest, SaveTxtReverse)
{

  status status;

  // Create grid folder
  createGridFolder();

  // create "grids/" folder
  fs::path currentPath(fs::current_path() / "grids");

  ASSERT_TRUE(fs::is_directory(currentPath));

  // Create test grid
  Grid grid = createTestGrid();

  // Save txt grid
  status = geo::SaveGrid(grid, (currentPath / "gridrReverse.txt").string(), GridFormat::TEXT_REVERSE);

  // Status must be true, grid saved successfully.
  EXPECT_EQ(status, geo::status::SUCCESS);
}

// Load Esri ASCII
TEST(GridTest, LoadEsriAscii)
{
  Grid grid;
  geo::status status;

  // Use "grids/" folder
  fs::path currentPath(fs::current_path() / "grids");

  // Fail and stop if the output directory does not exist
  ASSERT_TRUE(fs::is_directory(currentPath));

  // Load ESRI ASCII grid
  status = geo::Esri::loadAscii(grid, (currentPath / "esri.asc").string());

  // Status must be true, grid loaded successfully.
  EXPECT_EQ(status, geo::status::SUCCESS);

  // Check if grid is sequential
  EXPECT_EQ(isSequentialGrid(grid), true);
}

// Load Esri Float
TEST(GridTest, LoadEsriFloat)
{
  Grid grid;
  geo::status status;

  // Use "grids/" folder
  fs::path currentPath(fs::current_path() / "grids");

  // Fail and stop if the output directory does not exist
  ASSERT_TRUE(fs::is_directory(currentPath));

  // Load ESRI Float grid
  status = geo::Esri::loadFloat(grid, (currentPath / "esriFloat.bil").string());

  // Status must be true, grid saved successfully.
  EXPECT_EQ(status, geo::status::SUCCESS);

  // Check if grid is sequential
  EXPECT_EQ(isSequentialGrid(grid), true);
}

// Load Envi Float
TEST(GridTest, LoadEnviFloat)
{
  Grid grid;
  geo::status status;

  // Use "grids/" folder
  fs::path currentPath(fs::current_path() / "grids");

  // Fail and stop if the output directory does not exist
  ASSERT_TRUE(fs::is_directory(currentPath));

  // Load ENVI float grid
  status = geo::Envi::loadBinary(grid, (currentPath / "enviFloat.flt").string());

  // Status must be true, grid saved successfully.
  EXPECT_EQ(status, geo::status::SUCCESS);

  // Check if grid is sequential
  EXPECT_EQ(isSequentialGrid(grid), true);
}

// Load Envi Double
TEST(GridTest, LoadEnviDouble)
{
  Grid grid;
  geo::status status;

  // Use "grids/" folder
  fs::path currentPath(fs::current_path() / "grids");

  // Fail and stop if the output directory does not exist
  ASSERT_TRUE(fs::is_directory(currentPath));

  // Load ENVI double grid
  status = geo::Envi::loadBinary(grid, (currentPath / "enviDouble.flt").string());

  // Status must be true, grid saved successfully.
  EXPECT_EQ(status, geo::status::SUCCESS);

  // Check if grid is sequential
  EXPECT_EQ(isSequentialGrid(grid), true);
}

// Load Surfer Ascii
TEST(GridTest, LoadSurferAscii)
{
  Grid grid;
  geo::status status;

  // Use "grids/" folder
  fs::path currentPath(fs::current_path() / "grids");

  // Fail and stop if the output directory does not exist
  ASSERT_TRUE(fs::is_directory(currentPath));

  // Load Surfer ASCII grid
  status = geo::Surfer::load(grid, (currentPath / "surferAscii.grd").string());

  // Status must be true, grid saved successfully.
  EXPECT_EQ(status, geo::status::SUCCESS);
}

// Load Surfer 6 Float
TEST(GridTest, LoadSurferFloat)
{
  Grid grid;
  geo::status status;

  // Use "grids/" folder
  fs::path currentPath(fs::current_path() / "grids");

  // Fail and stop if the output directory does not exist
  ASSERT_TRUE(fs::is_directory(currentPath));

  // Load Surfer 6 binary grid
  status = geo::Surfer::load(grid, (currentPath / "surfer6.grd").string());

  // Status must be true, grid saved successfully.
  EXPECT_EQ(status, geo::status::SUCCESS);

  // Check if grid is sequential
  EXPECT_EQ(isSequentialGrid(grid), true);
}

// Load Surfer 7 double
TEST(GridTest, LoadSurferDouble)
{
  Grid grid;
  geo::status status;

  // Use "grids/" folder
  fs::path currentPath(fs::current_path() / "grids");

  // Fail and stop if the output directory does not exist
  ASSERT_TRUE(fs::is_directory(currentPath));

  // Check if grid is sequential
  EXPECT_EQ(isSequentialGrid(grid), true);

  // Load Surfer 7 binary grid
  status = geo::Surfer::load(grid, (currentPath / "surfer7.grd").string());

  // Status must be true, grid saved successfully.
  EXPECT_EQ(status, geo::status::SUCCESS);

  // Check if grid is sequential
  EXPECT_EQ(isSequentialGrid(grid), true);
}

Grid createSequentialGrid(geo::GridFormat format, int rows, int columns, double x0, double y0, double dx, double dy)
{

  int n = rows * columns;

  float *data = (float *)malloc(n * sizeof(float));

  if (data == nullptr)
  {
    return geo::Grid();
  }

  // Create a sequential data grid
  // at 0,0 = 0
  // at 0, columns - 1 = columns -1
  // at rows - 1, columns = (rows - 1) * columns
  // at rows -1, columns 1 = n - 1

  for (int i = 0; i < n; i++)
  {
    data[i] = i;
  }

  return geo::Grid(format, data, rows, columns, x0, y0, dx, dy, NAN);
}

bool isSequentialGrid(const Grid &grid)
{

  // Get grid dimensions
  auto [rows, columns] = grid.dimensions();

  // Calculate total of elements
  int n = rows * columns;
  int i = 0;
  const float *start = grid.c_float();
  const float *ptr = start;

  while (i < n)
  {
    // cout << i << " = " << *ptr << endl;
    //  Element at position i must be equal to i
    if (*ptr != (float)i)
    {
      cout << i << " != " << *ptr << endl;
      return false;
    }
    i++;
    ptr++;
  }

  return true;
}

Grid createTestGrid()
{
  double x0{-76.67744};
  double y0{2.41596};
  int rows = 500;
  int columns = 500;
  double dx = 270.0f;
  double dy = 270.0f;

  // Create a sequential grid
  Grid grid = createSequentialGrid(GridFormat::ESRI_ASCII, rows, columns, x0, y0, dx, dy);

  return grid;
}

status createGridFolder()
{
  // create "grids/" folder
  fs::path currentPath(fs::current_path() / "grids");

  // Fail and stop if the output directory could not be created
  if (fs::create_directories(currentPath))
  {
    return status::SUCCESS;
  }

  return status::FAILURE;
}