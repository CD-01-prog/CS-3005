#include "image_menu.h"
#include "image_menu.h" // Did you #ifndef your file?

#include "gtest/gtest.h"
#include <fstream>
#include <string>
#include <cmath>

class drawBoxTest : public ::testing::Test {
protected:

  virtual void SetUp( ) {
    mHeight = 25;
    mWidth = 30;
    mPrompt = "";
    mInputStream.str( "" );
    mOutputStream.str( "" );
    mPPM.setHeight( mHeight );
    mPPM.setWidth( mWidth );
    mPPM.setMaxColorValue( 137 );
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


TEST_F( drawBoxTest, displaysPrompts ) {

  /* Setup */
  mPrompt = "Top Row? Left Column? Bottom Row? Right Column? Red? Green? Blue? ";
  mRed = 77;
  mGreen = 97;
  mBlue = 71;
  mInputStream.str( "2 3 2 3 77 97 71" );

  /* Stimulus */
  drawBox( mInputStream, mOutputStream, mPPM );

  /* Comparison */
  EXPECT_EQ( mPrompt, mOutputStream.str( ) );

  /* Tear-down */
  // Done automatically
}



TEST_F( drawBoxTest, setsSizeZeroBox ) {

  /* Setup */
  mPrompt = "Top Row? Left Column? Bottom Row? Right Column? Red? Green? Blue? ";
  mRed = 77;
  mGreen = 97;
  mBlue = 71;
  mInputStream.str( "2 3 2 3 77 97 71" );

  /* Stimulus */
  drawBox( mInputStream, mOutputStream, mPPM );
  const PPM& ppm_const = mPPM;

  /* Comparison */
  EXPECT_EQ( mPrompt, mOutputStream.str( ) );

  int row, column;
  for( row = 0; row < mHeight; row++ ) {
    for( column = 0; column < mWidth; column++ ) {
      if( row != 2 || column != 3 ) {
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

TEST_F( drawBoxTest, setsSizeOneBox ) {

  /* Setup */
  mPrompt = "Top Row? Left Column? Bottom Row? Right Column? Red? Green? Blue? ";
  mRed = 77;
  mGreen = 97;
  mBlue = 71;
  mInputStream.str( "2 3 3 4 77 97 71" );

  /* Stimulus */
  drawBox( mInputStream, mOutputStream, mPPM );
  const PPM& ppm_const = mPPM;

  /* Comparison */
  EXPECT_EQ( mPrompt, mOutputStream.str( ) );

  int row, column;
  for( row = 0; row < mHeight; row++ ) {
    for( column = 0; column < mWidth; column++ ) {
      if( row < 2 || row > 3 || column < 3 || column > 4 ) {
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

TEST_F( drawBoxTest, setsSizeTenBox ) {

  /* Setup */
  mPrompt = "Top Row? Left Column? Bottom Row? Right Column? Red? Green? Blue? ";
  mRed = 78;
  mGreen = 79;
  mBlue = 17;
  mInputStream.str( "20 10 35 16 78 79 17" );

  /* Stimulus */
  drawBox( mInputStream, mOutputStream, mPPM );
  const PPM& ppm_const = mPPM;

  /* Comparison */
  EXPECT_EQ( mPrompt, mOutputStream.str( ) );

  int row, column;
  for( row = 0; row < mHeight; row++ ) {
    for( column = 0; column < mWidth; column++ ) {
      if( row < 20 || row > 35 || column < 10 || column > 16 ) {
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

TEST_F( drawBoxTest, setsSizeFiveBox ) {

  /* Setup */
  mPrompt = "Top Row? Left Column? Bottom Row? Right Column? Red? Green? Blue? ";
  mRed = 88;
  mGreen = 44;
  mBlue = 55;
  mInputStream.str( "11 7 19 13 88 44 55" );

  /* Stimulus */
  drawBox( mInputStream, mOutputStream, mPPM );
  const PPM& ppm_const = mPPM;

  /* Comparison */
  EXPECT_EQ( mPrompt, mOutputStream.str( ) );

  int row, column;
  for( row = 0; row < mHeight; row++ ) {
    for( column = 0; column < mWidth; column++ ) {
      if( row < 11 || row > 19 || column < 7 || column > 13 ) {
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
