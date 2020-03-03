#include "image_menu.h"
#include "image_menu.h" // Did you #ifndef your file?

#include "gtest/gtest.h"
#include <fstream>
#include <string>
#include <cmath>

class drawSquareTest : public ::testing::Test {
protected:

  virtual void SetUp( ) {
    mPrompt = "";
    mInputStream.str( "" );
    mOutputStream.str( "" );

    mHeight = 50;
    mWidth = 60;
    mMaxColorValue = 100;
    mPPM.setHeight( mHeight );
    mPPM.setWidth( mWidth );
    mPPM.setMaxColorValue( mMaxColorValue );
    int row, column;
    for( row = 0; row < mHeight; row++ ) {
      for( column = 0; column < mWidth; column++ ) {
        mPPM.setPixel( row, column, mMaxColorValue, mMaxColorValue, mMaxColorValue );
      }
    }
  }

  virtual void TearDown( ) {
  }

  /* data members */
  int mHeight, mWidth, mMaxColorValue;
  std::string mPrompt;
  std::stringstream mInputStream;
  std::stringstream mOutputStream;
  PPM mPPM;
  int mRed, mGreen, mBlue;
};


TEST_F( drawSquareTest, displaysPrompts ) {

  /* Setup */
  mPrompt = "Row? Column? Size? Red? Green? Blue? ";
  mRed = 1;
  mGreen = 2;
  mBlue = 3;
  mInputStream.str( "10 20 9 1 2 3" );

  /* Stimulus */
  drawSquare( mInputStream, mOutputStream, mPPM );

  /* Comparison */
  EXPECT_EQ( mPrompt, mOutputStream.str( ) );

  /* Tear-down */
  // Done automatically
}



TEST_F( drawSquareTest, leavesMetaData ) {

  /* Setup */
  mPrompt = "Row? Column? Size? Red? Green? Blue? ";
  mRed = 1;
  mGreen = 2;
  mBlue = 3;
  mInputStream.str( "10 20 9 1 2 3" );

  /* Stimulus */
  drawSquare( mInputStream, mOutputStream, mPPM );
  const PPM& ppm_const = mPPM;

  /* Comparison */
  EXPECT_EQ( mPrompt, mOutputStream.str( ) );
  EXPECT_EQ( mHeight, ppm_const.getHeight( ) );
  EXPECT_EQ( mWidth, ppm_const.getWidth( ) );
  EXPECT_EQ( mMaxColorValue, ppm_const.getMaxColorValue( ) );

}

TEST_F( drawSquareTest, setsPixels ) {

  /* Setup */
  mPrompt = "Row? Column? Size? Red? Green? Blue? ";
  mRed = 1;
  mGreen = 2;
  mBlue = 3;
  mInputStream.str( "10 20 9 1 2 3" );

  /* Stimulus */
  drawSquare( mInputStream, mOutputStream, mPPM );
  const PPM& ppm_const = mPPM;

  /* Comparison */
  EXPECT_EQ( mPrompt, mOutputStream.str( ) );
  EXPECT_EQ( mHeight, ppm_const.getHeight( ) );
  EXPECT_EQ( mWidth, ppm_const.getWidth( ) );
  EXPECT_EQ( mMaxColorValue, ppm_const.getMaxColorValue( ) );

  int row, column;
  for( row = 0; row < mHeight; row++ ) {
    for( column = 0; column < mWidth; column++ ) {
      if( row >= 6 && row <= 14 && column >= 16 && column <= 24 ) {
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

}

TEST_F( drawSquareTest, setsPixelsOtherSize ) {

  /* Setup */
  mPrompt = "Row? Column? Size? Red? Green? Blue? ";
  mRed = 11;
  mGreen = 12;
  mBlue = 13;
  mInputStream.str( "17 21 12   11 12 13" );

  /* Stimulus */
  drawSquare( mInputStream, mOutputStream, mPPM );
  const PPM& ppm_const = mPPM;

  /* Comparison */
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

}
