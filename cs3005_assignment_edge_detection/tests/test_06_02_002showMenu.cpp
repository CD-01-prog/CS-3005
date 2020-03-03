#include "image_menu.h"
#include "image_menu.h" // Did you #ifndef your file?

#include "gtest/gtest.h"
#include <fstream>
#include <string>

class RunFileShowMenuTest : public ::testing::Test {
protected:

  virtual void SetUp( ) {
    mExpected1 = "run) Run commands from another file";
    mOutputStream.str( "" );
  }

  virtual void TearDown( ) {
  }

  /* data members */
  std::string mExpected1;
  std::stringstream mOutputStream;
};


TEST_F( RunFileShowMenuTest, displaysMenu ) {

  /* Setup */
  // automatic

  /* Stimulus */
  showMenu( mOutputStream );

  /* Comparison */
  std::size_t found = mOutputStream.str( ).find( mExpected1 );
  EXPECT_NE( std::string::npos, found )
    << " Looking for '" << mExpected1 << "' in the menu, but didn't find it.";

  /* Tear-down */
  // Done automatically
}
