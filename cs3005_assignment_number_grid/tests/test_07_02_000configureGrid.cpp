#include "image_menu.h"
#include "image_menu.h" // Did you #ifndef your file?

#include "gtest/gtest.h"
#include <fstream>

class NumberGridConfigureGridTest : public ::testing::Test {
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



TEST_F( NumberGridConfigureGridTest, setsGridMetaData ) {

  /* Setup */
  mInputStream.str( "32 45 12" );
  mExpectedOutput = "Grid Height? Grid Width? Grid Max Value? ";

  /* Stimulus */
  configureGrid( mInputStream, mOutputStream, grid );
  const NumberGrid& grid_const = grid;

  /* Comparison */
  EXPECT_EQ( mExpectedOutput, mOutputStream.str( ) );
  EXPECT_EQ( 32, grid_const.getHeight( ) );
  EXPECT_EQ( 45, grid_const.getWidth( ) );
  EXPECT_EQ( 12, grid_const.getMaxNumber( ) );

  /* Tear-down */
  // Done automatically
}


TEST_F( NumberGridConfigureGridTest, setsGridMetaData2 ) {

  /* Setup */
  mInputStream.str( "24 88 120" );
  mExpectedOutput = "Grid Height? Grid Width? Grid Max Value? ";

  /* Stimulus */
  configureGrid( mInputStream, mOutputStream, grid );
  const NumberGrid& grid_const = grid;

  /* Comparison */
  EXPECT_EQ( mExpectedOutput, mOutputStream.str( ) );
  EXPECT_EQ( 24, grid_const.getHeight( ) );
  EXPECT_EQ( 88, grid_const.getWidth( ) );
  EXPECT_EQ( 120, grid_const.getMaxNumber( ) );

  /* Tear-down */
  // Done automatically
}
