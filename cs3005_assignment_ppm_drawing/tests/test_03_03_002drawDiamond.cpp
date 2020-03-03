#include "image_menu.h"
#include "image_menu.h" // Did you #ifndef your file?

#include "gtest/gtest.h"
#include <fstream>
#include <string>
#include <cmath>

class drawDiamondTest : public ::testing::Test {
protected:

  virtual void SetUp( ) {
    mHeight = 25;
    mWidth = 30;
    mPrompt = "";
    mInputStream.str( "" );
    mOutputStream.str( "" );
    mPPM.setHeight( mHeight );
    mPPM.setWidth( mWidth );
    mPPM.setMaxColorValue( 173 );
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


TEST_F( drawDiamondTest, displaysPrompts ) {

  /* Setup */
  mPrompt = "Center Row? Center Column? Size? Red? Green? Blue? ";
  mRed = 77;
  mGreen = 97;
  mBlue = 71;
  mInputStream.str( "10 20 0 77 97 71" );

  /* Stimulus */
  drawDiamond( mInputStream, mOutputStream, mPPM );

  /* Comparison */
  EXPECT_EQ( mPrompt, mOutputStream.str( ) );

  /* Tear-down */
  // Done automatically
}



TEST_F( drawDiamondTest, setsSizeZeroDiamond ) {

  /* Setup */
  mPrompt = "Center Row? Center Column? Size? Red? Green? Blue? ";
  mRed = 77;
  mGreen = 97;
  mBlue = 71;
  mInputStream.str( "10 20 0 77 97 71" );

  /* Stimulus */
  drawDiamond( mInputStream, mOutputStream, mPPM );
  const PPM& ppm_const = mPPM;

  /* Comparison */
  EXPECT_EQ( mPrompt, mOutputStream.str( ) );

  int row, column;
  for( row = 0; row < mHeight; row++ ) {
    for( column = 0; column < mWidth; column++ ) {
      if( row != 10 || column != 20 ) {
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

TEST_F( drawDiamondTest, setsSizeOneDiamond ) {

  /* Setup */
  mPrompt = "Center Row? Center Column? Size? Red? Green? Blue? ";
  mRed = 77;
  mGreen = 97;
  mBlue = 71;
  mInputStream.str( "10 20 1 77 97 71" );

  /* Stimulus */
  drawDiamond( mInputStream, mOutputStream, mPPM );
  const PPM& ppm_const = mPPM;

  /* Comparison */
  EXPECT_EQ( mPrompt, mOutputStream.str( ) );

  int row, column;
  for( row = 0; row < mHeight; row++ ) {
    for( column = 0; column < mWidth; column++ ) {
      if( ( std::abs(row-10) + std::abs(column-20) ) > 1 ) {
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

TEST_F( drawDiamondTest, setsSizeTenDiamond ) {

  /* Setup */
  mPrompt = "Center Row? Center Column? Size? Red? Green? Blue? ";
  mRed = 78;
  mGreen = 79;
  mBlue = 17;
  mInputStream.str( "18 7 10 78 79 17" );

  /* Stimulus */
  drawDiamond( mInputStream, mOutputStream, mPPM );
  const PPM& ppm_const = mPPM;

  /* Comparison */
  EXPECT_EQ( mPrompt, mOutputStream.str( ) );

  int row, column;
  for( row = 0; row < mHeight; row++ ) {
    for( column = 0; column < mWidth; column++ ) {
      if( ( std::abs(row-18) + std::abs(column-7) ) > 10 ) {
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

TEST_F( drawDiamondTest, setsSizeFiveDiamond ) {

  /* Setup */
  mPrompt = "Center Row? Center Column? Size? Red? Green? Blue? ";
  mRed = 88;
  mGreen = 44;
  mBlue = 55;
  mInputStream.str( "15 10 5 88 44 55" );

  /* Stimulus */
  drawDiamond( mInputStream, mOutputStream, mPPM );
  const PPM& ppm_const = mPPM;

  /* Comparison */
  EXPECT_EQ( mPrompt, mOutputStream.str( ) );

  int row, column;
  for( row = 0; row < mHeight; row++ ) {
    for( column = 0; column < mWidth; column++ ) {
      if( ( std::abs(row-15) + std::abs(column-10) ) > 5 ) {
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
