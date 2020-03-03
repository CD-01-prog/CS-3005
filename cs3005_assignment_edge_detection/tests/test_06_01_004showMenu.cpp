#include "image_menu.h"
#include "image_menu.h" // Did you #ifndef your file?

#include "gtest/gtest.h"
#include <fstream>
#include <string>

class EdgesShowMenuTest : public ::testing::Test {
protected:

  virtual void SetUp( ) {
    mExpected1 = "v-edge) Set output image from input image 1's vertical edge detection";
    mExpected2 = "h-edge) Set output image from input image 1's horizontal edge detection";
    mOutputStream.str( "" );
  }

  virtual void TearDown( ) {
  }

  /* data members */
  std::string mExpected1;
  std::string mExpected2;
  std::stringstream mOutputStream;
};


TEST_F( EdgesShowMenuTest, displaysMenu ) {

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

  /* Tear-down */
  // Done automatically
}
