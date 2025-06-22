/**
 * @file
 * @brief Grid conversion
 * Usage: grid_convert -if=INPUT_FORMAT -of=OUTPUT_FORMAT -input=IPUT_GRID -output=OUTPUT_GRID
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

  if (argc == 1)
  {
    usage(argv[0]);
  }
  string argString;

  for (int i = 1; i < argc; i++)
  {
    string arg(argv[i]);
    arg = geo::Strings::replace(arg, "--", "");
    arg = geo::Strings::replace(arg, "-", "");
    argString += arg + "\n";
  }

  // Parse command line options
  Options options(argString);

  // Get input file
  string inputFile = options.get("input");
  if (!inputFile.length()) {
    inputFile = options.get("i");
  }

  // Get input format
  string inputFormat = options.get("if");

  // Get output file
  string outputFile = options.get("output");
  if (!outputFile.length()) {
    outputFile = options.get("o");
  }

  // Get output format
  string outputFormat = options.get("of");

  if (!inputFile.length() || ! outputFile.length() || ! inputFormat.length() || !outputFormat.length()) {
    usage(argv[0]);
  }

  // Get parameters
  GridFormat iFormat = geo::getFormat(inputFormat);
  GridFormat oFormat = geo::getFormat(outputFormat);

  if (iFormat == GridFormat::UNKNOWN) {
    cerr << "Unknown input format " << inputFormat << endl;
    exit(EXIT_FAILURE);
  }

   if (oFormat == GridFormat::UNKNOWN) {
    cerr << "Unknown output format " << outputFormat << endl;
    exit(EXIT_FAILURE);
  }

  Grid grid;

  // Load input grid
  geoStatus status = geo::LoadGrid(grid, inputFile, iFormat);

  if (status != geoStatus::SUCCESS) {
    cerr << "Unable to load input grid";
    exit(EXIT_FAILURE);
  }

  // Save output grid
  status = geo::SaveGrid(grid, outputFile, oFormat);

  if (status != geoStatus::SUCCESS) {
    cerr << "Unable to create output grid " << outputFile << endl;
  }

  exit(EXIT_SUCCESS);

}

void usage(char *program)
{
  cerr
      << "Usage: "
      << program << " -if|--if=INPUT_FORMAT -of|--of=OUTPUT_FORMAT -i|--input=INPUT_GRID -o|--output=OUTPUT_FILE" << endl
      << " Converts INPUT_GRID (INPUT_FORMAT) to OUTPUT_GRID(OUTPUT_FORMAT)" << endl
      << " Available formats:" << endl
      << "   esriAscii        ESRI ASCII .asc" << endl
      << "   esri             ESRI binary (float) .bil" << endl
      << "   envi             ENVI binary (float) .flt" << endl
      << "   enviDouble       ENVI binary (double) .flt" << endl
      << "   surferAscii      Surfer 6 ASCII .grd" << endl
      << "   surfer6          Surfer 6 binary (float) .grd" << endl
      << "   surfer7          Surfer 7 binary (double) .grd" << endl
      << "   txt              Headerless first row first .txt" << endl
      << "   txtReverse       Headerless last row first .txt" << endl;

    exit(EXIT_SUCCESS);
}