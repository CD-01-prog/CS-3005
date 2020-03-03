#include "image_menu.h"
#include "image_menu.h" // Did you #ifndef your file?

#include "gtest/gtest.h"
#include <fstream>
#include <string>
#include <cmath>

class drawCircleTest : public ::testing::Test {
protected:

  virtual void SetUp( ) {
    mHeight = 40;
    mWidth = 30;
    mPrompt = "";
    mInputStream.str( "" );
    mOutputStream.str( "" );
    mPPM.setHeight( mHeight );
    mPPM.setWidth( mWidth );
    mPPM.setMaxColorValue( 111 );
    int row, column;
    for( row = 0; row < mHeight; row++ ) {
      for( column = 0; column < mWidth; column++ ) {
        mPPM.setPixel( row, column, 100, 101, 102 );
      }
    }
  }

  virtual void TearDown( ) {
  }

  /* data members */
  int mHeight, mWidth;
  std::string mPrompt;
  std::stringstream mInputStream;
  std::stringstream mOutputStream;
  PPM mPPM;
  int mRed, mGreen, mBlue;
};


TEST_F( drawCircleTest, displaysPrompts ) {

  /* Setup */
  mPrompt = "Center Row? Center Column? Radius? Red? Green? Blue? ";
  mRed = 11;
  mGreen = 33;
  mBlue = 22;
  mInputStream.str( "15 20 0 11 33 22" );

  /* Stimulus */
  drawCircle( mInputStream, mOutputStream, mPPM );

  /* Comparison */
  EXPECT_EQ( mPrompt, mOutputStream.str( ) );

  /* Tear-down */
  // Done automatically
}



TEST_F( drawCircleTest, setsSizeZeroCircle ) {

  /* Setup */
  mPrompt = "Center Row? Center Column? Radius? Red? Green? Blue? ";
  mRed = 11;
  mGreen = 33;
  mBlue = 22;
  mInputStream.str( "15 20 0 11 33 22" );

  /* Stimulus */
  drawCircle( mInputStream, mOutputStream, mPPM );
  const PPM& ppm_const = mPPM;

  /* Comparison */
  EXPECT_EQ( mPrompt, mOutputStream.str( ) );

  int row, column;
  for( row = 0; row < mHeight; row++ ) {
    for( column = 0; column < mWidth; column++ ) {
      if( row != 15 || column != 20 ) {
        EXPECT_EQ( 100, ppm_const.getChannel( row, column, 0 ) )
          << "row: " << row << " column: " << column << " channel: " << 0;
        EXPECT_EQ( 101, ppm_const.getChannel( row, column, 1 ) )
          << "row: " << row << " column: " << column << " channel: " << 1;
        EXPECT_EQ( 102, ppm_const.getChannel( row, column, 2 ) )
          << "row: " << row << " column: " << column << " channel: " << 2;
      } else {
        EXPECT_EQ( mRed, ppm_const.getChannel( row, column, 0 ) )
          << "row: " << row << " column: " << column << " channel: " << 0;
        EXPECT_EQ( mGreen, ppm_const.getChannel( row, column, 1 ) )
          << "row: " << row << " column: " << column << " channel: " << 1;
        EXPECT_EQ( mBlue, ppm_const.getChannel( row, column, 2 ) )
          << "row: " << row << " column: " << column << " channel: " << 2;
      }
    }
  }

  /* Tear-down */
  // Done automatically
}

TEST_F( drawCircleTest, setsSizeOneCircle ) {

  /* Setup */
  mPrompt = "Center Row? Center Column? Radius? Red? Green? Blue? ";
  mRed = 55;
  mGreen = 44;
  mBlue = 92;
  mInputStream.str( "20 15 1 55 44 92" );

  /* Stimulus */
  drawCircle( mInputStream, mOutputStream, mPPM );
  const PPM& ppm_const = mPPM;

  /* Comparison */
  EXPECT_EQ( mPrompt, mOutputStream.str( ) );

  int row, column;
  for( row = 0; row < mHeight; row++ ) {
    for( column = 0; column < mWidth; column++ ) {
      if( ( (row-20)*(row-20) + (column-15)*(column-15) ) > 1 ) {
        EXPECT_EQ( 100, ppm_const.getChannel( row, column, 0 ) )
          << "row: " << row << " column: " << column << " channel: " << 0;
        EXPECT_EQ( 101, ppm_const.getChannel( row, column, 1 ) )
          << "row: " << row << " column: " << column << " channel: " << 1;
        EXPECT_EQ( 102, ppm_const.getChannel( row, column, 2 ) )
          << "row: " << row << " column: " << column << " channel: " << 2;
      } else {
        EXPECT_EQ( mRed, ppm_const.getChannel( row, column, 0 ) )
          << "row: " << row << " column: " << column << " channel: " << 0;
        EXPECT_EQ( mGreen, ppm_const.getChannel( row, column, 1 ) )
          << "row: " << row << " column: " << column << " channel: " << 1;
        EXPECT_EQ( mBlue, ppm_const.getChannel( row, column, 2 ) )
          << "row: " << row << " column: " << column << " channel: " << 2;
      }
    }
  }


  /* Tear-down */
  // Done automatically
}

TEST_F( drawCircleTest, setsSizeTenCircle ) {

  /* Setup */
  mPrompt = "Center Row? Center Column? Radius? Red? Green? Blue? ";
  mRed = 78;
  mGreen = 79;
  mBlue = 17;
  mInputStream.str( "32 23 10 78 79 17" );

  /* Stimulus */
  drawCircle( mInputStream, mOutputStream, mPPM );
  const PPM& ppm_const = mPPM;

  /* Comparison */
  EXPECT_EQ( mPrompt, mOutputStream.str( ) );

  int row, column;
  for( row = 0; row < mHeight; row++ ) {
    for( column = 0; column < mWidth; column++ ) {
      if( ( (row-32)*(row-32) + (column-23)*(column-23) ) > 100 ) {
        EXPECT_EQ( 100, ppm_const.getChannel( row, column, 0 ) )
          << "row: " << row << " column: " << column << " channel: " << 0;
        EXPECT_EQ( 101, ppm_const.getChannel( row, column, 1 ) )
          << "row: " << row << " column: " << column << " channel: " << 1;
        EXPECT_EQ( 102, ppm_const.getChannel( row, column, 2 ) )
          << "row: " << row << " column: " << column << " channel: " << 2;
      } else {
        EXPECT_EQ( mRed, ppm_const.getChannel( row, column, 0 ) )
          << "row: " << row << " column: " << column << " channel: " << 0;
        EXPECT_EQ( mGreen, ppm_const.getChannel( row, column, 1 ) )
          << "row: " << row << " column: " << column << " channel: " << 1;
        EXPECT_EQ( mBlue, ppm_const.getChannel( row, column, 2 ) )
          << "row: " << row << " column: " << column << " channel: " << 2;
      }
    }
  }


  /* Tear-down */
  // Done automatically
}

TEST_F( drawCircleTest, setsSizeFiveCircle ) {

  /* Setup */
  mPrompt = "Center Row? Center Column? Radius? Red? Green? Blue? ";
  mRed = 88;
  mGreen = 44;
  mBlue = 55;
  mInputStream.str( "25 15 5 88 44 55" );

  /* Stimulus */
  drawCircle( mInputStream, mOutputStream, mPPM );
  const PPM& ppm_const = mPPM;

  /* Comparison */
  EXPECT_EQ( mPrompt, mOutputStream.str( ) );

  int row, column;
  for( row = 0; row < mHeight; row++ ) {
    for( column = 0; column < mWidth; column++ ) {
      if( ( (row-25)*(row-25) + (column-15)*(column-15) ) > 25 ) {
        EXPECT_EQ( 100, ppm_const.getChannel( row, column, 0 ) )
          << "row: " << row << " column: " << column << " channel: " << 0;
        EXPECT_EQ( 101, ppm_const.getChannel( row, column, 1 ) )
          << "row: " << row << " column: " << column << " channel: " << 1;
        EXPECT_EQ( 102, ppm_const.getChannel( row, column, 2 ) )
          << "row: " << row << " column: " << column << " channel: " << 2;
      } else {
        EXPECT_EQ( mRed, ppm_const.getChannel( row, column, 0 ) )
          << "row: " << row << " column: " << column << " channel: " << 0;
        EXPECT_EQ( mGreen, ppm_const.getChannel( row, column, 1 ) )
          << "row: " << row << " column: " << column << " channel: " << 1;
        EXPECT_EQ( mBlue, ppm_const.getChannel( row, column, 2 ) )
          << "row: " << row << " column: " << column << " channel: " << 2;
      }
    }
  }


  /* Tear-down */
  // Done automatically
}
