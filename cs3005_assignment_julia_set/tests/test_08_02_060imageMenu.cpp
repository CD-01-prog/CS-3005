#include "image_menu.h"
#include "image_menu.h" // Did you #ifndef your file?

#include "gtest/gtest.h"
#include <fstream>
#include <string>

class JuliaSetImageMenuTest : public ::testing::Test {
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


TEST_F( JuliaSetImageMenuTest, usesGrid ) {

  /* Setup */
  mInputStream.str( "grid 250 350 123 fractal-plane-size -1.0 1.5 -0.2 1.2 julia-parameters 0.314 -0.271 fractal-calculate grid-apply write julia-image.ppm quit" );

  /* Stimulus */
  imageMenu( mInputStream, mOutputStream );

  /* Comparison */
  PPM ppm_tmp;
  mInputStream.clear( );
  mInputStream.str( "julia-image.ppm" );
  readUserImage( mInputStream, mOutputStream, ppm_tmp );
  remove( "julia-image.ppm" );
  const PPM& ppm_const = ppm_tmp;

  EXPECT_EQ( 250, ppm_const.getHeight( ) );
  EXPECT_EQ( 350, ppm_const.getWidth( ) );
  EXPECT_EQ( 63, ppm_const.getMaxColorValue( ) );

  EXPECT_EQ( 63, ppm_const.getChannel( 0, 0, 0 ) );
  EXPECT_EQ( 31, ppm_const.getChannel( 0, 0, 1 ) );
  EXPECT_EQ( 31, ppm_const.getChannel( 0, 0, 2 ) );

  EXPECT_EQ( 31, ppm_const.getChannel( 249, 0, 0 ) );
  EXPECT_EQ( 63, ppm_const.getChannel( 249, 0, 1 ) );
  EXPECT_EQ( 31, ppm_const.getChannel( 249, 0, 2 ) );

  EXPECT_EQ( 63, ppm_const.getChannel( 0, 349, 0 ) );
  EXPECT_EQ( 31, ppm_const.getChannel( 0, 349, 1 ) );
  EXPECT_EQ( 31, ppm_const.getChannel( 0, 249, 2 ) );

  EXPECT_EQ( 63, ppm_const.getChannel( 249, 349, 0 ) );
  EXPECT_EQ( 31, ppm_const.getChannel( 249, 349, 1 ) );
  EXPECT_EQ( 31, ppm_const.getChannel( 249, 249, 2 ) );

  EXPECT_EQ( 63, ppm_const.getChannel( 125, 175, 0 ) );
  EXPECT_EQ( 31, ppm_const.getChannel( 125, 175, 1 ) );
  EXPECT_EQ( 31, ppm_const.getChannel( 125, 175, 2 ) );


  /* Tear-down */
  // Done automatically
}
