#include "image_menu.h"
#include "image_menu.h" // Did you #ifndef your file?

#include "gtest/gtest.h"
#include <fstream>
#include <string>

class NumberGridImageMenuTest : public ::testing::Test {
protected:

  virtual void SetUp( ) {
    mInputStream.str( "" );
    mOutputStream.str( "" );
  }

  virtual void TearDown( ) {
  }

  /* data members */
  std::stringstream mInputStream;
  std::stringstream mOutputStream;
};


TEST_F( NumberGridImageMenuTest, usesGrid ) {

  /* Setup */
  mInputStream.str( "grid 3 4 15 grid-set 1 2 5 grid-set 0 1 7 grid-apply write grid-image.ppm quit" );

  /* Stimulus */
  imageMenu( mInputStream, mOutputStream );

  /* Comparison */
  PPM ppm_tmp;
  mInputStream.clear( );
  mInputStream.str( "grid-image.ppm" );
  readUserImage( mInputStream, mOutputStream, ppm_tmp );
  remove( "grid-image.ppm" );
  const PPM& ppm_const = ppm_tmp;

  EXPECT_EQ( 3, ppm_const.getHeight( ) );
  EXPECT_EQ( 4, ppm_const.getWidth( ) );
  EXPECT_EQ( 63, ppm_const.getMaxColorValue( ) );
  EXPECT_EQ( 31, ppm_const.getChannel( 1, 2, 0 ) );
  EXPECT_EQ( 63, ppm_const.getChannel( 1, 2, 1 ) );
  EXPECT_EQ( 63, ppm_const.getChannel( 1, 2, 2 ) );
  EXPECT_EQ( 63, ppm_const.getChannel( 0, 1, 0 ) );
  EXPECT_EQ( 31, ppm_const.getChannel( 0, 1, 1 ) );
  EXPECT_EQ( 63, ppm_const.getChannel( 0, 1, 2 ) );

  /* Tear-down */
  // Done automatically
}
