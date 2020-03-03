#include "image_menu.h"
#include "image_menu.h" // Did you #ifndef your file?

#include "gtest/gtest.h"
#include <fstream>
#include <string>

class NumberGridShowMenuTest : public ::testing::Test {
protected:

  virtual void SetUp( ) {
    mExpected1 = "grid) Configure the grid.";
    mExpected2 = "grid-set) Set a single value in the grid.";
    mExpected3 = "grid-apply) Use the grid values to set colors in the output image.";
    mOutputStream.str( "" );
  }

  virtual void TearDown( ) {
  }

  /* data members */
  std::string mExpected1;
  std::string mExpected2;
  std::string mExpected3;
  std::stringstream mOutputStream;
};


TEST_F( NumberGridShowMenuTest, displaysMenu ) {

  /* Setup */
  // automatic

  /* Stimulus */
  showMenu( mOutputStream );

  /* Comparison */
  std::size_t found = mOutputStream.str( ).find( mExpected1 );
  EXPECT_NE( std::string::npos, found )
    << " Looking for '" << mExpected1 << "' in the menu, but didn't find it.";

  found = mOutputStream.str( ).find( mExpected2 );
  EXPECT_NE( std::string::npos, found )
    << " Looking for '" << mExpected2 << "' in the menu, but didn't find it.";

  mOutputStream.str( ).find( mExpected3 );
  EXPECT_NE( std::string::npos, found )
    << " Looking for '" << mExpected3 << "' in the menu, but didn't find it.";

  /* Tear-down */
  // Done automatically
}
