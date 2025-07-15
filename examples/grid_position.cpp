/**
 * @file
 * @brief Position inside a grid
 * Usage: grid_position grid lon lat
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

int main(int argc, char *argv[])
{

  if (argc != 4)
  {
    usage(argv[0]);
  }

  Grid grid;

  if (geo::LoadGrid(grid, string(argv[1])) != geoStatus::SUCCESS) {
    cerr << "Unable to open input grid" << endl;
    exit(EXIT_FAILURE);
  }

  auto [i,j] = grid.position(atof(argv[2]), atof(argv[3]));
  cout << "Input coordinates: " << argv[1] <<"," << argv[2] << endl
       << "Position: " << i<<","<< j<< endl;


  exit(EXIT_SUCCESS);

}

void usage(char *program)
{
  cerr
      << "Usage: "
      << program << " grid lon lat" << endl
      << " Calculates the column (longitude) and row (latitude) position inside a grid for the given lon,lat coordinates" << endl;

    exit(EXIT_SUCCESS);
}