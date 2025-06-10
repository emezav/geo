# Geospatial classes and functions

This single-file header allows reading/writing geospatial grids in several formats.

See examples/ and test/ for usage.

## ESRI ASCII Grid - .asc

https://desktop.arcgis.com/en/arcmap/10.3/manage-data/raster-and-images/esri-ascii-raster-format.htm

Grid format

```txt
NCOLS xxx
NROWS xxx
XLLCENTER xxx
YLLCENTER xxx
CELLSIZE xxx or DX xxx DY xxxx for non-squared cells
NODATA_VALUE xxx
row 1
row 2
...
row n
```

The lower left corner of the lower left cell

```txt
NCOLS xxx
NROWS xxx
XLLCORNER xxx
YLLCORNER xxx
CELLSIZE xxx DX xxx DY xxxx for non-squared cells
NODATA_VALUE xxx
row 1
row 2
...
row n
```

## ESRI .bil, .hdr

Header structure:

https://desktop.arcgis.com/en/arcmap/10.3/manage-data/raster-and-images/bil-bip-and-bsq-raster-files.htm

```txt
Keyword       Acceptable Value	      Default
nrows         Any integer > 0          None
ncols         Any integer > 0          None
nbands        Any integer > 0          1
nbits         1, 4, 8, 16, 32          8
pixeltype     signedint|float          None
byteorder     I = Intel; M = Motorola  Same as host machine
layout        bil, bip, bsq            bil
skipbytes     Any integer ≥ 0          0
ulxmap        Any real number          0           x0ll + (dx/2)
ulymap        Any real number          nrows - 1   y0ll + (dy * rows) - (dy/2)
xdim          Any real number          1
ydim          Any real number          1
bandrowbytes  Any integer > 0          Smallest integer ≥ (ncols x nbits) / 8
totalrowbytes Any integer > 0          For bil: nbands x bandrowbytes; for bip: smallest integer ≥ (ncols x nbands x nbits) / 8
bandgapbytes  Any integer ≥ 0          0
```

Example

```txt
byteorder      i
layout         bil
nrows          2560
ncols          1800
nbands         1
nbits          32
bandrowbytes   7200
totalrowbytes  7200
pixeltype      float
ulxmap         -83.25493265
ulymap         6.52826405
xdim           0.0041427
ydim           0.0041599
nodata         nan
```

## ENVI binary grid (float32)

x, y: upper left pixel of the grid

Example:

```txt
ENVI
description = {
testxx.flt}
samples = 1800
lines   = 2560
bands   = 1
header offset = 0
file type = ENVI Standard
data type = 4
interleave = bsq
byte order = 0
map info = {Geographic Lat/Lon, 1, 1, -83.257004, 6.530344, 0.0041427, 0.0041599,WGS-84}
band names = {
Band 1}
data ignore value = nan
```

## Surfer 6 Text grid

First row first
nodata value: 1.70141e+38

https://grapherhelp.goldensoftware.com/subsys/ascii_grid_file_format.htm

```txt
DSAA 'Surfer ASCII GRD ID
nCols nRows 'number of columns and rows
xMin xMax 'XYZ min max
yMin yMax
zMin zMax
z11 z21 z31 ... 'List of Z values

```

The SG ASCII format requires the XYZ min max. Calculate the XY max from the XY min, the number of rows and
columns, and the cellsize.
xMax = xMin + (0.5*cellsize) + (cellsize * (ncols-1))
yMax = yMin + (0.5*cellsize) + (cellsize * (nrows-1))

## Surfer 6 binary grid

https://grapherhelp.goldensoftware.com/subsys/surfer_6_grid_file_format.htm

First row first
nodata value: 1.70141e+38

Grid corner positioning:

https://people.wou.edu/~taylors/g473/convert_esri_ascii_grid_surfer_grd.pdf

## Surfer 7 grid

[Reference](https://surferhelp.goldensoftware.com/topics/surfer_7_grid_file_format.htm?tocpath=File%20Types%7CFile%20Formats%7C_____45)

A Surfer 7 grid is a binary file, divided in sections. Each section begins with a 4-char not null-terminated string:

```txt
0x42525344
  BRSD  (DSRBB File header)
0x44495247
  DIRG (GRID - Grid definition)
0x41544144
  ATAD (DATA - Grid data - double values)
0x49544c46
  ITLF (FLTI Fault register.)
```
