#include "NumberGrid.h"
#include "NumberGrid.h" // Did you #ifndef your file?

#include "gtest/gtest.h"
#include <fstream>

class NumberGridNumbersTest : public ::testing::Test {
protected:

  virtual void SetUp( ) {
  }

  virtual void TearDown( ) {
  }

  /* data members */
  NumberGrid grid;
};

TEST_F( NumberGridNumbersTest, fillsWithZeros ) {

  /* Setup */
  int height = 300;
  int width = 400;

  /* Stimulus */
  const NumberGrid& grid_const = grid;

  /* Comparison */
  int row, column;
  for( row = 0; row < height; row++ ) {
    for( column = 0; column < width; column++ ) {
      EXPECT_EQ( 0, grid_const.getNumber( row, column ) )
        << "row: " << row << " column: " << column;
    }
  }

  /* Tear-down */
  // Done automatically
}

TEST_F( NumberGridNumbersTest, storesNumbers ) {

  /* Setup */
  int height = 230;
  int width = 120;
  int row, column;
  int max_number = height*width - 1;
  grid.setGridSize( height, width );
  grid.setMaxNumber( max_number );
  for( row = 0; row < height; row++ ) {
    for( column = 0; column < width; column++ ) {
      grid.setNumber( row, column, (height-row-1)*width + (width-column-1));
    }
  }

  /* Stimulus */
  const NumberGrid& grid_const = grid;

  /* Comparison */
  for( row = 0; row < height; row++ ) {
    for( column = 0; column < width; column++ ) {
      EXPECT_EQ( (height-row-1)*width + (width-column-1), grid_const.getNumber( row, column ) )
        << "row: " << row << " column: " << column;
    }
  }

  /* Tear-down */
  // Done automatically
}

TEST_F( NumberGridNumbersTest, storesNumbers2 ) {

  /* Setup */
  int height = 23;
  int width = 38;
  int row, column;
  int max_number = height*width - 1;
  grid.setGridSize( height, width );
  grid.setMaxNumber( max_number );
  for( row = 0; row < height; row++ ) {
    for( column = 0; column < width; column++ ) {
      grid.setNumber( row, column, (height-row-1)*width + (width-column-1));
    }
  }

  /* Stimulus */
  const NumberGrid& grid_const = grid;

  /* Comparison */
  for( row = 0; row < height; row++ ) {
    for( column = 0; column < width; column++ ) {
      EXPECT_EQ( (height-row-1)*width + (width-column-1), grid_const.getNumber( row, column ) )
        << "row: " << row << " column: " << column;
    }
  }

  /* Tear-down */
  // Done automatically
}
