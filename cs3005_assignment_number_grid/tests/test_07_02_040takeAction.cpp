#include "image_menu.h"
#include "image_menu.h" // Did you #ifndef your file?

#include "gtest/gtest.h"
#include <fstream>
#include <string>

class NumberGridTakeActionTest : public ::testing::Test {
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

  }

  virtual void TearDown( ) {
  }

  /* data members */
  std::string mChoice;
  std::string mExpected;
  std::stringstream mInputStream;
  std::stringstream mOutputStream;
  PPM input_image1, input_image2, output_image;
  NumberGrid grid;
};


TEST_F( NumberGridTakeActionTest, configuresGrid ) {

  /* Setup */
  mExpected = "Grid Height? Grid Width? Grid Max Value? ";
  mInputStream.str( "33 44 13" );
  mChoice = "grid";

  /* Stimulus */
  takeAction( mInputStream, mOutputStream, mChoice, input_image1, input_image2, output_image, grid );
  const NumberGrid& grid_const = grid;

  /* Comparison */
  // Grid should be updated
  EXPECT_EQ( mExpected, mOutputStream.str( ) );
  EXPECT_EQ( 33, grid_const.getHeight( ) );
  EXPECT_EQ( 44, grid_const.getWidth( ) );
  EXPECT_EQ( 13, grid_const.getMaxNumber( ) );

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

TEST_F( NumberGridTakeActionTest, setsGrid ) {

  /* Setup */
  mExpected = "Grid Height? Grid Width? Grid Max Value? Grid Row? Grid Column? Grid Value? Grid Row? Grid Column? Grid Value? ";
  mInputStream.str( "2 3 11 1 2 5 0 1 7" );
  mChoice = "grid";

  /* Stimulus */
  takeAction( mInputStream, mOutputStream, mChoice, input_image1, input_image2, output_image, grid );
  mChoice = "grid-set";
  takeAction( mInputStream, mOutputStream, mChoice, input_image1, input_image2, output_image, grid );
  mChoice = "grid-set";
  takeAction( mInputStream, mOutputStream, mChoice, input_image1, input_image2, output_image, grid );
  const NumberGrid& grid_const = grid;

  /* Comparison */
  // Grid should be updated
  EXPECT_EQ( mExpected, mOutputStream.str( ) );
  EXPECT_EQ( 2, grid_const.getHeight( ) );
  EXPECT_EQ( 3, grid_const.getWidth( ) );
  EXPECT_EQ( 11, grid_const.getMaxNumber( ) );
  EXPECT_EQ( 5, grid_const.getNumber( 1, 2 ) );
  EXPECT_EQ( 7, grid_const.getNumber( 0, 1 ) );

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

TEST_F( NumberGridTakeActionTest, appliesGrid ) {

  /* Setup */
  mExpected = "Grid Height? Grid Width? Grid Max Value? Grid Row? Grid Column? Grid Value? Grid Row? Grid Column? Grid Value? ";
  mInputStream.str( "3 4 15 1 2 5 0 1 7" );
  mChoice = "grid";

  /* Stimulus */
  takeAction( mInputStream, mOutputStream, mChoice, input_image1, input_image2, output_image, grid );
  mChoice = "grid-set";
  takeAction( mInputStream, mOutputStream, mChoice, input_image1, input_image2, output_image, grid );
  mChoice = "grid-set";
  takeAction( mInputStream, mOutputStream, mChoice, input_image1, input_image2, output_image, grid );
  mChoice = "grid-apply";
  takeAction( mInputStream, mOutputStream, mChoice, input_image1, input_image2, output_image, grid );
  const NumberGrid& grid_const = grid;

  /* Comparison */
  // Grid should be updated
  EXPECT_EQ( mExpected, mOutputStream.str( ) );
  EXPECT_EQ( 3, grid_const.getHeight( ) );
  EXPECT_EQ( 4, grid_const.getWidth( ) );
  EXPECT_EQ( 15, grid_const.getMaxNumber( ) );
  EXPECT_EQ( 5, grid_const.getNumber( 1, 2 ) );
  EXPECT_EQ( 7, grid_const.getNumber( 0, 1 ) );

  // output image should have changed
  EXPECT_EQ( 3, output_image.getHeight( ) );
  EXPECT_EQ( 4, output_image.getWidth( ) );
  EXPECT_EQ( 63, output_image.getMaxColorValue( ) );
  EXPECT_EQ( 31, output_image.getChannel( 1, 2, 0 ) );
  EXPECT_EQ( 63, output_image.getChannel( 1, 2, 1 ) );
  EXPECT_EQ( 63, output_image.getChannel( 1, 2, 2 ) );
  EXPECT_EQ( 63, output_image.getChannel( 0, 1, 0 ) );
  EXPECT_EQ( 31, output_image.getChannel( 0, 1, 1 ) );
  EXPECT_EQ( 63, output_image.getChannel( 0, 1, 2 ) );

  // input images should not have changed
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

  /* Tear-down */
  // Done automatically
}
