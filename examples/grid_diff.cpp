/**
 * @file
 * @brief Grid diff
 * Usage: grid_diff file1 file2
 * @author Erwin Meza Vega <emezav@unicauca.edu.co> <emezav@gmail.com>
 * @copyright MIT License
 */

#include <iostream>
#include <map>
#include <string>
#include <vector>
#include "geo.h"

using std::cout;
using std::endl;
using std::map;
using std::string;
using std::vector;

using geo::Grid;
using geo::Options;
using geo::GridFormat;
using geo::Strings;
using geo::geoStatus;

/**
 * @brief Prints program usage
 * @param program Program
 */
void usage(char *program);

/**
 * @brief Compares the specified positions on the grid
 * @param gridA first grid
 * @param gridB second grid
 * @param rpe Relative Percent Error (maximum allowed difference, percent)
 */
void diff(const Grid & gridA, const Grid & gridB, float rpe=1.0f);

int main(int argc, char *argv[])
{

  if (argc < 3)
  {
    usage(argv[0]);
  }

  string pathA(argv[1]);
  string pathB(argv[2]);

  float rpe{1.0f};
  if (argc == 4) {
    rpe = std::strtof(argv[3], nullptr);
  }

  Grid gridA, gridB;

  // Load first grid
  geoStatus status = geo::LoadGrid(gridA, pathA);

  if (status != geoStatus::SUCCESS) {
    cerr << "Unable to load the first grid";
    exit(EXIT_FAILURE);
  }

  // Load second grid
  status = geo::LoadGrid(gridB, pathB);

  if (status != geoStatus::SUCCESS) {
    cerr << "Unable to load the second grid";
    exit(EXIT_FAILURE);
  }

  diff(gridA, gridB, rpe);

  exit(EXIT_SUCCESS);

}

void usage(char *program)
{
  cerr
      << "Usage: "
      << program << " gridA gridB [rpe(1-100), defaults to 1%]" << endl
      << " Compares two grids and prints differences: row,column,valueA,valueB" << endl
      << " rpe is desired Relative Percent Error, defaults to 1 percent." << endl
      << " Grid format will be deduced from the file extension.";

    exit(EXIT_SUCCESS);
}

void diff(const Grid & gridA, const Grid & gridB, float rpe) {

  if (!gridA.equalDimensions(gridB)) {
    cout << "Dimensions are different." << endl;
    return;
  }

  auto [rows, columns] = gridA.dimensions();

  int count = 0;
  for (int i = 0; i < rows; i++) {
    for (int j = 0; j < columns; j++) {
      if (!gridA.equalsAt(gridB, i, j, rpe)) {
        if (count++ < 100) {
        cout << i << "," << j <<","<<gridA(i,j) << "," << gridB(i,j) << " Reverse row: " << rows - i << "," << j<< endl;
        }
      }
    }
  }

  if (count > 100) {
    cout << "..." << endl;
  }

  if (count) {
    cout << count <<" total positions are different." << endl;
  }

}