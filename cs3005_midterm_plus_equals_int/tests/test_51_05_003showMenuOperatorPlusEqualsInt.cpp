#include "image_menu.h"
#include "image_menu.h" // Did you #ifndef your file?

#include "gtest/gtest.h"
#include <fstream>
#include <string>

class showMenuOperatorPlusEqualsIntTest : public ::testing::Test {
protected:

  virtual void SetUp( ) {
    mExpected = "+=-int) Set input image 1 by adding by an integer.";
    mOutputStream.str( "" );
  }

  virtual void TearDown( ) {
  }

  /* data members */
  std::string mExpected;
  std::stringstream mOutputStream;
};


TEST_F( showMenuOperatorPlusEqualsIntTest, displaysMenu ) {

  /* Setup */
  // automatic

  /* Stimulus */
  showMenu( mOutputStream );

  /* Comparison */
  std::size_t found = mOutputStream.str( ).find( mExpected );
  EXPECT_NE( std::string::npos, found )
    << " Looking for '" << mExpected << "' in the menu, but didn't find it.";

  /* Tear-down */
  // Done automatically
}
