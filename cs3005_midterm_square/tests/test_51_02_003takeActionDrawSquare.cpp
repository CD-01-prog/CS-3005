#include "image_menu.h"
#include "image_menu.h" // Did you #ifndef your file?

#include "gtest/gtest.h"
#include <fstream>
#include <string>
#include <cmath>

class takeActionDrawSquareTest : public ::testing::Test {
protected:

  virtual void SetUp( ) {
    mPrompt = "";
    mInputStream.str( "" );
    mOutputStream.str( "" );

    mHeight = 50;
    mWidth = 60;
    mMaxColorValue = 100;
    input_image1.setHeight( mHeight );
    input_image1.setWidth( mWidth );
    input_image1.setMaxColorValue( mMaxColorValue );
    int row, column;
    for( row = 0; row < mHeight; row++ ) {
      for( column = 0; column < mWidth; column++ ) {
        input_image1.setPixel( row, column, mMaxColorValue, mMaxColorValue, mMaxColorValue );
      }
    }
  }

  virtual void TearDown( ) {
  }

  /* data members */
  int mHeight, mWidth, mMaxColorValue;
  std::string mPrompt;
  std::string mChoice;
  std::stringstream mInputStream;
  std::stringstream mOutputStream;
  int mRed, mGreen, mBlue;
  PPM input_image1, input_image2, output_image;
};

TEST_F( takeActionDrawSquareTest, createsSquare ) {

  /* Setup */
  mPrompt = "Row? Column? Size? Red? Green? Blue? ";
  mChoice = "square";
  mRed = 11;
  mGreen = 12;
  mBlue = 13;
  mInputStream.str( "17 21 12   11 12 13" );

  /* Stimulus */
  takeAction( mInputStream, mOutputStream, mChoice, input_image1, input_image2, output_image );
  const PPM& ppm_const = input_image1;

  /* Comparison */
  EXPECT_EQ( mPrompt, mOutputStream.str( ) );
  EXPECT_EQ( mHeight, ppm_const.getHeight( ) );
  EXPECT_EQ( mWidth, ppm_const.getWidth( ) );
  EXPECT_EQ( mMaxColorValue, ppm_const.getMaxColorValue( ) );

  EXPECT_EQ( mPrompt, mOutputStream.str( ) );
  EXPECT_EQ( mHeight, ppm_const.getHeight( ) );
  EXPECT_EQ( mWidth, ppm_const.getWidth( ) );
  EXPECT_EQ( mMaxColorValue, ppm_const.getMaxColorValue( ) );

  int row, column;
  for( row = 0; row < mHeight; row++ ) {
    for( column = 0; column < mWidth; column++ ) {
      if( row >= 11 && row <= 23 && column >= 15 && column <= 27 ) {
        EXPECT_EQ( mRed, ppm_const.getChannel( row, column, 0 ) )
          << "row: " << row << " column: " << column << " channel: " << 0;
        EXPECT_EQ( mGreen, ppm_const.getChannel( row, column, 1 ) )
          << "row: " << row << " column: " << column << " channel: " << 1;
        EXPECT_EQ( mBlue, ppm_const.getChannel( row, column, 2 ) )
          << "row: " << row << " column: " << column << " channel: " << 2;
      } else {
        EXPECT_EQ( mMaxColorValue, ppm_const.getChannel( row, column, 0 ) )
          << "row: " << row << " column: " << column << " channel: " << 0;
        EXPECT_EQ( mMaxColorValue, ppm_const.getChannel( row, column, 1 ) )
          << "row: " << row << " column: " << column << " channel: " << 1;
        EXPECT_EQ( mMaxColorValue, ppm_const.getChannel( row, column, 2 ) )
          << "row: " << row << " column: " << column << " channel: " << 2;
      }
    }
  }

  /* Tear-down */
  // Done automatically
}
