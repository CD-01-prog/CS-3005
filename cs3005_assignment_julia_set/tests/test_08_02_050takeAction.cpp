#include "image_menu.h"
#include "image_menu.h" // Did you #ifndef your file?

#include "gtest/gtest.h"
#include <fstream>
#include <string>

class JuliaSetTakeActionTest : public ::testing::Test {
protected:

  virtual void SetUp( ) {
    mExpected = "";
    mInputStream.str( "" );
    mOutputStream.str( "" );

    input_image1.setHeight( 1 );
    input_image1.setWidth( 2 );
    input_image1.setMaxColorValue( 3 );
    input_image1.setPixel( 0, 0, 1, 2, 3 );
    input_image1.setPixel( 0, 1, 2, 1, 0 );

    input_image2.setHeight( 2 );
    input_image2.setWidth( 1 );
    input_image2.setMaxColorValue( 4 );
    input_image2.setPixel( 0, 0, 4, 2, 0 );
    input_image2.setPixel( 1, 0, 0, 1, 2 );

    output_image.setHeight( 1 );
    output_image.setWidth( 1 );
    output_image.setMaxColorValue( 5 );
    output_image.setPixel( 0, 0, 5, 3, 1 );

    grid.setGridSize( 3, 2 );
    grid.setMaxNumber( 111 );
    grid.setNumber( 0, 0, 10 );
    grid.setNumber( 0, 1, 20 );
    grid.setNumber( 1, 0, 30 );
    grid.setNumber( 1, 1, 40 );
    grid.setNumber( 2, 0, 50 );
    grid.setNumber( 2, 1, 60 );

  }

  virtual void TearDown( ) {
  }

  /* data members */
  std::string mChoice;
  std::string mExpected;
  std::stringstream mInputStream;
  std::stringstream mOutputStream;
  PPM input_image1, input_image2, output_image;
  JuliaSet grid;
};


TEST_F( JuliaSetTakeActionTest, setsPlaneSize ) {

  /* Setup */
  mExpected = "Min X? Max X? Min Y? Max Y? ";
  mInputStream.str( "-0.1 1.2 0.3 -1.4" );
  mChoice = "fractal-plane-size";

  /* Stimulus */
  takeAction( mInputStream, mOutputStream, mChoice, input_image1, input_image2, output_image, grid );
  const JuliaSet& grid_const = grid;

  /* Comparison */
  // Grid should be updated
  EXPECT_EQ( mExpected, mOutputStream.str( ) );
  EXPECT_EQ( 3, grid_const.getHeight( ) );
  EXPECT_EQ( 2, grid_const.getWidth( ) );
  EXPECT_EQ( 111, grid_const.getMaxNumber( ) );
  EXPECT_EQ( -0.1, grid_const.getMinX( ) );
  EXPECT_EQ(  1.2, grid_const.getMaxX( ) );
  EXPECT_EQ( -1.4, grid_const.getMinY( ) );
  EXPECT_EQ(  0.3, grid_const.getMaxY( ) );
  EXPECT_EQ(  10,  grid_const.getNumber( 0, 0 ) );
  EXPECT_EQ(  20,  grid_const.getNumber( 0, 1 ) );
  EXPECT_EQ(  30,  grid_const.getNumber( 1, 0 ) );
  EXPECT_EQ(  40,  grid_const.getNumber( 1, 1 ) );
  EXPECT_EQ(  50,  grid_const.getNumber( 2, 0 ) );
  EXPECT_EQ(  60,  grid_const.getNumber( 2, 1 ) );
  EXPECT_DOUBLE_EQ(  1.7/2,  grid_const.getDeltaY( ) );
  EXPECT_DOUBLE_EQ(  1.3/1,  grid_const.getDeltaX( ) );

  // images should not have changed
  EXPECT_EQ( 1, input_image1.getHeight( ) );
  EXPECT_EQ( 2, input_image1.getWidth( ) );
  EXPECT_EQ( 3, input_image1.getMaxColorValue( ) );
  EXPECT_EQ( 1, input_image1.getChannel( 0, 0, 0 ) );
  EXPECT_EQ( 2, input_image1.getChannel( 0, 0, 1 ) );
  EXPECT_EQ( 3, input_image1.getChannel( 0, 0, 2 ) );
  EXPECT_EQ( 2, input_image1.getChannel( 0, 1, 0 ) );
  EXPECT_EQ( 1, input_image1.getChannel( 0, 1, 1 ) );
  EXPECT_EQ( 0, input_image1.getChannel( 0, 1, 2 ) );

  EXPECT_EQ( 2, input_image2.getHeight( ) );
  EXPECT_EQ( 1, input_image2.getWidth( ) );
  EXPECT_EQ( 4, input_image2.getMaxColorValue( ) );
  EXPECT_EQ( 4, input_image2.getChannel( 0, 0, 0 ) );
  EXPECT_EQ( 2, input_image2.getChannel( 0, 0, 1 ) );
  EXPECT_EQ( 0, input_image2.getChannel( 0, 0, 2 ) );
  EXPECT_EQ( 0, input_image2.getChannel( 1, 0, 0 ) );
  EXPECT_EQ( 1, input_image2.getChannel( 1, 0, 1 ) );
  EXPECT_EQ( 2, input_image2.getChannel( 1, 0, 2 ) );

  EXPECT_EQ( 1, output_image.getHeight( ) );
  EXPECT_EQ( 1, output_image.getWidth( ) );
  EXPECT_EQ( 5, output_image.getMaxColorValue( ) );
  EXPECT_EQ( 5, output_image.getChannel( 0, 0, 0 ) );
  EXPECT_EQ( 3, output_image.getChannel( 0, 0, 1 ) );
  EXPECT_EQ( 1, output_image.getChannel( 0, 0, 2 ) );

  /* Tear-down */
  // Done automatically
}

TEST_F( JuliaSetTakeActionTest, calculatesFractal ) {

  /* Setup */
  int expected_width = 350;
  int expected_height = 250;
  double expected_min_x = -1.0;
  double expected_max_x =  1.5;
  double expected_min_y = -0.2;
  double expected_max_y =  1.2;
  double expected_a =  0.314;
  double expected_b = -0.271;
  int expected_max_escape_count = 123;
  grid.setGridSize( expected_height, expected_width );
  grid.setMaxNumber( expected_max_escape_count );
  grid.setPlaneSize( expected_min_x, expected_max_x,
                     expected_min_y, expected_max_y );
  grid.setParameters( expected_a, expected_b );

  mExpected = "";
  mInputStream.str( "" );
  mChoice = "fractal-calculate";

  /* Stimulus */
  takeAction( mInputStream, mOutputStream, mChoice, input_image1, input_image2, output_image, grid );
  const JuliaSet& grid_const = grid;

  /* Comparison */
  // Grid should be updated
  EXPECT_EQ( mExpected, mOutputStream.str( ) );
  EXPECT_EQ( expected_height, grid_const.getHeight( ) );
  EXPECT_EQ( expected_width, grid_const.getWidth( ) );
  EXPECT_EQ( expected_max_escape_count, grid_const.getMaxNumber( ) );
  EXPECT_EQ( expected_min_x, grid_const.getMinX( ) );
  EXPECT_EQ( expected_max_x, grid_const.getMaxX( ) );
  EXPECT_EQ( expected_min_y, grid_const.getMinY( ) );
  EXPECT_EQ( expected_max_y, grid_const.getMaxY( ) );
  EXPECT_DOUBLE_EQ(  (expected_max_y-expected_min_y)/(expected_height-1),  grid_const.getDeltaY( ) );
  EXPECT_DOUBLE_EQ(  (expected_max_x-expected_min_x)/(expected_width-1),  grid_const.getDeltaX( ) );
  EXPECT_EQ( expected_a, grid_const.getA( ) );
  EXPECT_EQ( expected_b, grid_const.getB( ) );


  EXPECT_EQ( 1, grid_const.getNumber( 0, 0 ) )
    << "(row,column) = (" << 0 << "," << 0 << ")" << std::endl;

  EXPECT_EQ( 3, grid_const.getNumber( expected_height-1, 0 ) )
    << "(row,column) = (" << (expected_height-1) << "," << 0 << ")" << std::endl;

  EXPECT_EQ( 1, grid_const.getNumber( 0, expected_width-1 ) )
    << "(row,column) = (" << 0 << "," << (expected_width-1) << ")" << std::endl;

  EXPECT_EQ( 1, grid_const.getNumber( expected_height-1, expected_width-1 ) )
    << "(row,column) = (" << (expected_height-1) << "," << (expected_width-1) << ")" << std::endl;

  EXPECT_EQ( expected_max_escape_count, grid_const.getNumber( expected_height/2, expected_width/2 ) )
    << "(row,column) = (" << (expected_height/2) << "," << (expected_width/2) << ")" << std::endl;

  EXPECT_EQ( -1, grid_const.getNumber( -1, expected_width/2 ) )
    << "(row,column) = (" << -1 << "," << (expected_width/2) << ")" << std::endl;

  EXPECT_EQ( -1, grid_const.getNumber( expected_height, expected_width/2 ) )
    << "(row,column) = (" << (expected_height) << "," << (expected_width/2) << ")" << std::endl;

  EXPECT_EQ( -1, grid_const.getNumber( expected_height/2, -1 ) )
    << "(row,column) = (" << (expected_height/2) << "," << -1 << ")" << std::endl;

  EXPECT_EQ( -1, grid_const.getNumber( expected_height/2, expected_width ) )
    << "(row,column) = (" << (expected_height/2) << "," << (expected_width) << ")" << std::endl;


  // images should not have changed
  EXPECT_EQ( 1, input_image1.getHeight( ) );
  EXPECT_EQ( 2, input_image1.getWidth( ) );
  EXPECT_EQ( 3, input_image1.getMaxColorValue( ) );
  EXPECT_EQ( 1, input_image1.getChannel( 0, 0, 0 ) );
  EXPECT_EQ( 2, input_image1.getChannel( 0, 0, 1 ) );
  EXPECT_EQ( 3, input_image1.getChannel( 0, 0, 2 ) );
  EXPECT_EQ( 2, input_image1.getChannel( 0, 1, 0 ) );
  EXPECT_EQ( 1, input_image1.getChannel( 0, 1, 1 ) );
  EXPECT_EQ( 0, input_image1.getChannel( 0, 1, 2 ) );

  EXPECT_EQ( 2, input_image2.getHeight( ) );
  EXPECT_EQ( 1, input_image2.getWidth( ) );
  EXPECT_EQ( 4, input_image2.getMaxColorValue( ) );
  EXPECT_EQ( 4, input_image2.getChannel( 0, 0, 0 ) );
  EXPECT_EQ( 2, input_image2.getChannel( 0, 0, 1 ) );
  EXPECT_EQ( 0, input_image2.getChannel( 0, 0, 2 ) );
  EXPECT_EQ( 0, input_image2.getChannel( 1, 0, 0 ) );
  EXPECT_EQ( 1, input_image2.getChannel( 1, 0, 1 ) );
  EXPECT_EQ( 2, input_image2.getChannel( 1, 0, 2 ) );

  EXPECT_EQ( 1, output_image.getHeight( ) );
  EXPECT_EQ( 1, output_image.getWidth( ) );
  EXPECT_EQ( 5, output_image.getMaxColorValue( ) );
  EXPECT_EQ( 5, output_image.getChannel( 0, 0, 0 ) );
  EXPECT_EQ( 3, output_image.getChannel( 0, 0, 1 ) );
  EXPECT_EQ( 1, output_image.getChannel( 0, 0, 2 ) );

  /* Tear-down */
  // Done automatically
}


TEST_F( JuliaSetTakeActionTest, setsJuliaParameters ) {

  /* Setup */
  int expected_width = 350;
  int expected_height = 250;
  double expected_min_x = -1.0;
  double expected_max_x =  1.5;
  double expected_min_y = -0.2;
  double expected_max_y =  1.2;
  double expected_a =  0.314;
  double expected_b = -0.271;
  int expected_max_escape_count = 123;
  grid.setGridSize( expected_height, expected_width );
  grid.setMaxNumber( expected_max_escape_count );
  grid.setPlaneSize( expected_min_x, expected_max_x,
                     expected_min_y, expected_max_y );
  grid.setParameters( 0.0, 0.0 );

  mExpected = "Parameter a? Parameter b? ";
  mInputStream.str( "0.314 -0.271" );
  mChoice = "julia-parameters";

  /* Stimulus */
  takeAction( mInputStream, mOutputStream, mChoice, input_image1, input_image2, output_image, grid );
  const JuliaSet& grid_const = grid;

  /* Comparison */
  // Grid should be updated
  EXPECT_EQ( mExpected, mOutputStream.str( ) );
  EXPECT_EQ( expected_height, grid_const.getHeight( ) );
  EXPECT_EQ( expected_width, grid_const.getWidth( ) );
  EXPECT_EQ( expected_max_escape_count, grid_const.getMaxNumber( ) );
  EXPECT_EQ( expected_min_x, grid_const.getMinX( ) );
  EXPECT_EQ( expected_max_x, grid_const.getMaxX( ) );
  EXPECT_EQ( expected_min_y, grid_const.getMinY( ) );
  EXPECT_EQ( expected_max_y, grid_const.getMaxY( ) );
  EXPECT_DOUBLE_EQ(  (expected_max_y-expected_min_y)/(expected_height-1),  grid_const.getDeltaY( ) );
  EXPECT_DOUBLE_EQ(  (expected_max_x-expected_min_x)/(expected_width-1),  grid_const.getDeltaX( ) );
  EXPECT_EQ( expected_a, grid_const.getA( ) );
  EXPECT_EQ( expected_b, grid_const.getB( ) );

  // images should not have changed
  EXPECT_EQ( 1, input_image1.getHeight( ) );
  EXPECT_EQ( 2, input_image1.getWidth( ) );
  EXPECT_EQ( 3, input_image1.getMaxColorValue( ) );
  EXPECT_EQ( 1, input_image1.getChannel( 0, 0, 0 ) );
  EXPECT_EQ( 2, input_image1.getChannel( 0, 0, 1 ) );
  EXPECT_EQ( 3, input_image1.getChannel( 0, 0, 2 ) );
  EXPECT_EQ( 2, input_image1.getChannel( 0, 1, 0 ) );
  EXPECT_EQ( 1, input_image1.getChannel( 0, 1, 1 ) );
  EXPECT_EQ( 0, input_image1.getChannel( 0, 1, 2 ) );

  EXPECT_EQ( 2, input_image2.getHeight( ) );
  EXPECT_EQ( 1, input_image2.getWidth( ) );
  EXPECT_EQ( 4, input_image2.getMaxColorValue( ) );
  EXPECT_EQ( 4, input_image2.getChannel( 0, 0, 0 ) );
  EXPECT_EQ( 2, input_image2.getChannel( 0, 0, 1 ) );
  EXPECT_EQ( 0, input_image2.getChannel( 0, 0, 2 ) );
  EXPECT_EQ( 0, input_image2.getChannel( 1, 0, 0 ) );
  EXPECT_EQ( 1, input_image2.getChannel( 1, 0, 1 ) );
  EXPECT_EQ( 2, input_image2.getChannel( 1, 0, 2 ) );

  EXPECT_EQ( 1, output_image.getHeight( ) );
  EXPECT_EQ( 1, output_image.getWidth( ) );
  EXPECT_EQ( 5, output_image.getMaxColorValue( ) );
  EXPECT_EQ( 5, output_image.getChannel( 0, 0, 0 ) );
  EXPECT_EQ( 3, output_image.getChannel( 0, 0, 1 ) );
  EXPECT_EQ( 1, output_image.getChannel( 0, 0, 2 ) );

  /* Tear-down */
  // Done automatically
}
