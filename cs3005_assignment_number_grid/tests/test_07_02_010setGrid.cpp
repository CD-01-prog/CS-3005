#include "image_menu.h"
#include "image_menu.h" // Did you #ifndef your file?

#include "gtest/gtest.h"
#include <fstream>

class NumberGridSetGridTest : public ::testing::Test {
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



TEST_F( NumberGridSetGridTest, setsNumber ) {

  /* Setup */
  grid.setGridSize( 55, 22 );
  grid.setMaxNumber( 100 );
  mInputStream.str( "44 11 80" );
  mExpectedOutput = "Grid Row? Grid Column? Grid Value? ";

  /* Stimulus */
  setGrid( mInputStream, mOutputStream, grid );
  const NumberGrid& grid_const = grid;

  /* Comparison */
  EXPECT_EQ( mExpectedOutput, mOutputStream.str( ) );
  EXPECT_EQ( 80, grid_const.getNumber( 44, 11 ) );

  /* Tear-down */
  // Done automatically
}



TEST_F( NumberGridSetGridTest, setsNumber2 ) {

  /* Setup */
  grid.setGridSize( 55, 22 );
  grid.setMaxNumber( 100 );
  mInputStream.str( "12 13 14" );
  mExpectedOutput = "Grid Row? Grid Column? Grid Value? ";

  /* Stimulus */
  setGrid( mInputStream, mOutputStream, grid );
  const NumberGrid& grid_const = grid;

  /* Comparison */
  EXPECT_EQ( mExpectedOutput, mOutputStream.str( ) );
  EXPECT_EQ( 14, grid_const.getNumber( 12, 13 ) );

  /* Tear-down */
  // Done automatically
}
