/**
 * @file
 * @brief Grid mosaic
 * Usage: grid_mosaic grid1 grid2 side output
 * Stitches grid1 and grid2 on the defined side into output grid.
 * @author Erwin Meza Vega <emezav@unicauca.edu.co> <emezav@gmail.com>
 * @copyright MIT License
 */

#include <filesystem>
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

using geo::geoStatus;
using geo::Grid;
using geo::GridFormat;
using geo::Options;
using geo::Strings;

namespace fs = std::filesystem;

/**
 * @brief Prints program usage
 * @param program Program
 */
void usage(char *program);

int main(int argc, char *argv[])
{

  if (argc != 5)
  {
    usage(argv[0]);
  }

  // Get grid 1 path
  fs::path grid1Path(argv[1]);
  if (!fs::exists(grid1Path) || !fs::is_regular_file(grid1Path))
  {
    cerr << grid1Path.string() << ": not a valid grid." << endl;
    exit(EXIT_FAILURE);
  }

  // Get grid 2 path
  fs::path grid2Path(argv[2]);
  if (!fs::exists(grid2Path) || !fs::is_regular_file(grid2Path))
  {
    cerr << grid2Path.string() << ": not a valid grid." << endl;
    exit(EXIT_FAILURE);
  }

  // Get side
  string side(argv[3]);

  // Get output grid path
  fs::path outputPath(argv[4]);

  Grid grid1;
  Grid grid2;

  // Load grid 1
  if (geo::LoadGrid(grid1, string(argv[1])) != geoStatus::SUCCESS)
  {
    cerr << "Unable to load grid 1";
    exit(EXIT_FAILURE);
  }

  // Load grid 2
  if (geo::LoadGrid(grid2, string(argv[2])) != geoStatus::SUCCESS)
  {
    cerr << "Unable to load grid 2";
    exit(EXIT_FAILURE);
  }

  Grid output;

  if (side.compare("left") == 0)
  {
    if (!geo::mosaicLeft(grid1, grid2, output))
    {
      cerr << "Unable to mosaic grids left" << endl;
      exit(EXIT_FAILURE);
    }
  }
  else if (side.compare("right") == 0)
  {
    if (!geo::mosaicRight(grid1, grid2, output))
    {
      cerr << "Unable to mosaic grids right" << endl;
      exit(EXIT_FAILURE);
    }
  }
  else if (side.compare("top") == 0)
  {
    if (!geo::mosaicTop(grid1, grid2, output))
    {
      cerr << "Unable to mosaic grids top" << endl;
      exit(EXIT_FAILURE);
    }
  }
  else if (side.compare("bottom") == 0)
  {
    if (!geo::mosaicBottom(grid1, grid2, output))
    {
      cerr << "Unable to mosaic grids bottom" << endl;
      exit(EXIT_FAILURE);
    }
  }

  if (geo::SaveGrid(output, outputPath.string(), output.gridFormat()) != geoStatus::SUCCESS)
  {
    cerr << "Unable to save output grid." << endl;
    exit(EXIT_FAILURE);
  }

  exit(EXIT_SUCCESS);
}

void usage(char *program)
{
  cerr
      << "Usage: "
      << program << " grid1 grid2 side output " << endl
      << " Stitches grid1 and grid2 on the defined side into output grid" << endl
      << " Available formats:" << endl
      << "   esriAscii        ESRI ASCII .asc" << endl
      << "   esri             ESRI binary (float) .bil" << endl
      << "   envi             ENVI binary (float) .flt" << endl
      << "   enviDouble       ENVI binary (double) .flt" << endl
      << "   surferAscii      Surfer 6 ASCII .grd" << endl
      << "   surfer6          Surfer 6 binary (float) .grd" << endl
      << "   surfer7          Surfer 7 binary (double) .grd" << endl;

  exit(EXIT_SUCCESS);
}
