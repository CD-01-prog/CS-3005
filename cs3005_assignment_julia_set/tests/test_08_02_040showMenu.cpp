#include "image_menu.h"
#include "image_menu.h" // Did you #ifndef your file?

#include "gtest/gtest.h"
#include <fstream>
#include <string>

class NumberGridShowMenuTest : public ::testing::Test {
protected:

  virtual void SetUp( ) {
    mExpected1 = "fractal-plane-size) Set the dimensions of the grid in the complex plane.";
    mExpected2 = "fractal-calculate) Calculate the escape values for the fractal.";
    mExpected3 = "julia-parameters) Set the parameters of the Julia Set function.";

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
