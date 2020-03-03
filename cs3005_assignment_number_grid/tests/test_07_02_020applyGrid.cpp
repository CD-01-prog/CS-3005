#include "image_menu.h"
#include "image_menu.h" // Did you #ifndef your file?

#include "gtest/gtest.h"
#include <fstream>

class NumberGridApplyGridTest : public ::testing::Test {
protected:

  virtual void SetUp( ) {
    mExpectedOutput = "";
    mInputStream.str( "" );
    mOutputStream.str( "" );
  }

  virtual void TearDown( ) {
  }

  /* data members */
  std::string mExpectedOutput;
  std::stringstream mInputStream;
  std::stringstream mOutputStream;
  NumberGrid grid;
};



TEST_F( NumberGridApplyGridTest, setsPPM ) {

  /* Setup */
  int height = 5;
  int width = 7;
  int max_number = 13;
  grid.setGridSize( height, width );
  grid.setMaxNumber( max_number );
  int row, column;
  for( row = 0; row < height; row++ ) {
    for( column = 0; column < width; column++ ) {
      grid.setNumber( row, column, ( row * width + column ) % ( max_number + 1 ) );
    }
  }
  mInputStream.str( "" );
  mExpectedOutput = "";

  /* Stimulus */
  PPM ppm;
  applyGrid( mInputStream, mOutputStream, grid, ppm );
  const NumberGrid& grid_const = grid;
  const PPM& ppm_const = ppm;

  /* Comparison */
  EXPECT_EQ( mExpectedOutput, mOutputStream.str( ) );
  EXPECT_EQ( height, ppm_const.getHeight( ) );
  EXPECT_EQ( width, ppm_const.getWidth( ) );
  EXPECT_EQ( 63, ppm_const.getMaxColorValue( ) );
  int n;
  for( row = 0; row < height; row++ ) {
    for( column = 0; column < width; column++ ) {
      n = grid_const.getNumber( row, column );
      if( n == 0 ) {
        EXPECT_EQ( 0, ppm_const.getChannel( row, column, 0 ) );
      } else if( n == max_number ) {
        EXPECT_EQ( 63, ppm_const.getChannel( row, column, 0 ) );
      } else if( n % 8 == 0 ) {
        EXPECT_EQ( 63, ppm_const.getChannel( row, column, 0 ) );
      } else if( n % 8 == 1 ) {
        EXPECT_EQ( 63, ppm_const.getChannel( row, column, 0 ) );
      } else if( n % 8 == 2 ) {
        EXPECT_EQ( 63, ppm_const.getChannel( row, column, 0 ) );
      } else if( n % 8 == 3 ) {
        EXPECT_EQ( 31, ppm_const.getChannel( row, column, 0 ) );
      } else if( n % 8 == 4 ) {
        EXPECT_EQ( 0, ppm_const.getChannel( row, column, 0 ) );
      } else if( n % 8 == 5 ) {
        EXPECT_EQ( 31, ppm_const.getChannel( row, column, 0 ) );
      } else if( n % 8 == 6 ) {
        EXPECT_EQ( 31, ppm_const.getChannel( row, column, 0 ) );
      } else if( n % 8 == 7 ) {
        EXPECT_EQ( 63, ppm_const.getChannel( row, column, 0 ) );
      }
      if( n == 0 ) {
        EXPECT_EQ( 0, ppm_const.getChannel( row, column, 1 ) );
      } else if( n == max_number ) {
        EXPECT_EQ( 31, ppm_const.getChannel( row, column, 1 ) );
      } else if( n % 8 == 0 ) {
        EXPECT_EQ( 63, ppm_const.getChannel( row, column, 1 ) );
      } else if( n % 8 == 1 ) {
        EXPECT_EQ( 31, ppm_const.getChannel( row, column, 1 ) );
      } else if( n % 8 == 2 ) {
        EXPECT_EQ( 63, ppm_const.getChannel( row, column, 1 ) );
      } else if( n % 8 == 3 ) {
        EXPECT_EQ( 63, ppm_const.getChannel( row, column, 1 ) );
      } else if( n % 8 == 4 ) {
        EXPECT_EQ( 0, ppm_const.getChannel( row, column, 1 ) );
      } else if( n % 8 == 5 ) {
        EXPECT_EQ( 63, ppm_const.getChannel( row, column, 1 ) );
      } else if( n % 8 == 6 ) {
        EXPECT_EQ( 31, ppm_const.getChannel( row, column, 1 ) );
      } else if( n % 8 == 7 ) {
        EXPECT_EQ( 31, ppm_const.getChannel( row, column, 1 ) );
      }
      if( n == 0 ) {
        EXPECT_EQ( 0, ppm_const.getChannel( row, column, 2 ) );
      } else if( n == max_number ) {
        EXPECT_EQ( 31, ppm_const.getChannel( row, column, 2 ) );
      } else if( n % 8 == 0 ) {
        EXPECT_EQ( 63, ppm_const.getChannel( row, column, 2 ) );
      } else if( n % 8 == 1 ) {
        EXPECT_EQ( 31, ppm_const.getChannel( row, column, 2 ) );
      } else if( n % 8 == 2 ) {
        EXPECT_EQ( 31, ppm_const.getChannel( row, column, 2 ) );
      } else if( n % 8 == 3 ) {
        EXPECT_EQ( 31, ppm_const.getChannel( row, column, 2 ) );
      } else if( n % 8 == 4 ) {
        EXPECT_EQ( 0, ppm_const.getChannel( row, column, 2 ) );
      } else if( n % 8 == 5 ) {
        EXPECT_EQ( 63, ppm_const.getChannel( row, column, 2 ) );
      } else if( n % 8 == 6 ) {
        EXPECT_EQ( 63, ppm_const.getChannel( row, column, 2 ) );
      } else if( n % 8 == 7 ) {
        EXPECT_EQ( 63, ppm_const.getChannel( row, column, 2 ) );
      }
    }
  }

  /* Tear-down */
  // Done automatically
}
