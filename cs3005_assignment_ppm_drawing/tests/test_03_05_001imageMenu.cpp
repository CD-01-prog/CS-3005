#include "image_menu.h"
#include "image_menu.h" // Did you #ifndef your file?

#include "gtest/gtest.h"
#include <fstream>
#include <string>
#include <cmath>

class imageMenuTest : public ::testing::Test {
protected:

  virtual void SetUp( ) {
  }

  virtual void TearDown( ) {
  }

  /* data members */
  std::stringstream mInputStream, mOutputStream;
};


TEST_F( imageMenuTest, quits ) {

  /* Setup */
  mInputStream.str( "quit" );

  /* Stimulus */
  imageMenu( mInputStream, mOutputStream );

  /* Comparison */

  /* Tear-down */
  // Done automatically
}


TEST_F( imageMenuTest, doesStuffAndQuits ) {

  /* Setup */
  mInputStream.str( "size 10 20 max 100 quit" );

  /* Stimulus */
  imageMenu( mInputStream, mOutputStream );

  /* Comparison */

  /* Tear-down */
  // Done automatically
}
