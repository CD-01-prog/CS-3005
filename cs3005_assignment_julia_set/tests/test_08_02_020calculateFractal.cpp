#include "image_menu.h"
#include "image_menu.h" // Did you #ifndef your file?

#include "gtest/gtest.h"
#include <fstream>

class JuliaSetCalculateFractalTest : public ::testing::Test {
protected:

  virtual void SetUp( ) {
    mExpectedOutput = "";
    mInputStream.str( "" );
    mOutputStream.str( "" );

    expected_width = 350;
    expected_height = 250;
    expected_min_x = -1.0;
    expected_max_x =  1.5;
    expected_min_y = -0.2;
    expected_max_y =  1.2;
    expected_a =  0.314;
    expected_b = -0.271;
    expected_max_escape_count = 123;
    expected_size = 87500;
    js.setGridSize( expected_height, expected_width );
    js.setPlaneSize( expected_min_x, expected_max_x,
                     expected_min_y, expected_max_y );
    js.setParameters( expected_a, expected_b );
    js.setMaxNumber( expected_max_escape_count );

  }

  virtual void TearDown( ) {
  }

  /* data members */
  std::string mExpectedOutput;
  std::stringstream mInputStream;
  std::stringstream mOutputStream;
  JuliaSet js;

  int expected_width, expected_height;
  double expected_min_x, expected_max_x;
  double expected_min_y, expected_max_y;
  double expected_a, expected_b;
  int expected_max_escape_count;
  int expected_size;
};



TEST_F( JuliaSetCalculateFractalTest, setsNumbers ) {

  /* Setup */
  mInputStream.str( "" );
  mExpectedOutput = "";

  /* Stimulus */
  calculateFractal( mInputStream, mOutputStream, js );
  const JuliaSet& js_const = js;

  /* Comparison */
  EXPECT_EQ( mExpectedOutput, mOutputStream.str( ) );
  EXPECT_EQ( 1, js_const.getNumber( 0, 0 ) )
    << "(row,column) = (" << 0 << "," << 0 << ")" << std::endl;

  EXPECT_EQ( 3, js_const.getNumber( expected_height-1, 0 ) )
    << "(row,column) = (" << (expected_height-1) << "," << 0 << ")" << std::endl;

  EXPECT_EQ( 1, js_const.getNumber( 0, expected_width-1 ) )
    << "(row,column) = (" << 0 << "," << (expected_width-1) << ")" << std::endl;

  EXPECT_EQ( 1, js_const.getNumber( expected_height-1, expected_width-1 ) )
    << "(row,column) = (" << (expected_height-1) << "," << (expected_width-1) << ")" << std::endl;

  EXPECT_EQ( expected_max_escape_count, js_const.getNumber( expected_height/2, expected_width/2 ) )
    << "(row,column) = (" << (expected_height/2) << "," << (expected_width/2) << ")" << std::endl;

  EXPECT_EQ( -1, js_const.getNumber( -1, expected_width/2 ) )
    << "(row,column) = (" << -1 << "," << (expected_width/2) << ")" << std::endl;

  EXPECT_EQ( -1, js_const.getNumber( expected_height, expected_width/2 ) )
    << "(row,column) = (" << (expected_height) << "," << (expected_width/2) << ")" << std::endl;

  EXPECT_EQ( -1, js_const.getNumber( expected_height/2, -1 ) )
    << "(row,column) = (" << (expected_height/2) << "," << -1 << ")" << std::endl;

  EXPECT_EQ( -1, js_const.getNumber( expected_height/2, expected_width ) )
    << "(row,column) = (" << (expected_height/2) << "," << (expected_width) << ")" << std::endl;


  /* Tear-down */
  // Done automatically
}
