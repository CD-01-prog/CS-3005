#include "image_menu.h"
#include "image_menu.h" // Did you #ifndef your file?

#include "gtest/gtest.h"
#include <fstream>
#include <string>

class clearAllTest : public ::testing::Test {
protected:

  virtual void SetUp( ) {
    mHeight = 20;
    mWidth = 10;
    mPrompt = "";
    mInputStream.str( "" );
    mOutputStream.str( "" );
    mPPM.setHeight( mHeight );
    mPPM.setWidth( mWidth );
    mPPM.setMaxColorValue( 101 );
    int row, column;
    for( row = 0; row < mHeight; row++ ) {
      for( column = 0; column < mWidth; column++ ) {
        mPPM.setPixel( row, column, 100, 50, 75 );
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
};


TEST_F( clearAllTest, displaysNoPrompts ) {

  /* Setup */
  mPrompt = "";
  mInputStream.str( ""  );

  /* Stimulus */
  clearAll( mPPM );

  /* Comparison */
  EXPECT_EQ( mPrompt, mOutputStream.str( ) );

  /* Tear-down */
  // Done automatically
}



TEST_F( clearAllTest, setsPixelsToZero ) {

  /* Setup */
  mPrompt = "";
  mInputStream.str( ""  );

  /* Stimulus */
  clearAll( mPPM );
  const PPM& ppm_const = mPPM;

  /* Comparison */
  EXPECT_EQ( mPrompt, mOutputStream.str( ) );
  int row, column, channel;
  for( row = 0; row < mHeight; row++ ) {
    for( column = 0; column < mWidth; column++ ) {
      for( channel = 0; channel < 3; channel++ ) {
        EXPECT_EQ( 0, ppm_const.getChannel( row, column, channel ) )
          << "row: " << row << " column: " << column << " channel: " << channel;
      }
    }
  }

  /* Tear-down */
  // Done automatically
}
