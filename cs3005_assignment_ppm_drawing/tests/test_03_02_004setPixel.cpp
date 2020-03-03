#include "image_menu.h"
#include "image_menu.h" // Did you #ifndef your file?

#include "gtest/gtest.h"
#include <fstream>
#include <string>

class setPixelTest : public ::testing::Test {
protected:

  virtual void SetUp( ) {
    mPrompt = "";
    mInputStream.str( "" );
    mOutputStream.str( "" );
    mPPM.setHeight( 24 );
    mPPM.setWidth( 47 );
    mPPM.setMaxColorValue( 150 );
  }

  virtual void TearDown( ) {
  }

  /* data members */
  std::string mPrompt;
  std::stringstream mInputStream;
  std::stringstream mOutputStream;
  PPM mPPM;
};


TEST_F( setPixelTest, displaysPrompts ) {

  /* Setup */
  mPrompt = "Row? Column? Red? Green? Blue? ";
  mInputStream.str( "1 2 4 5 6"  );

  /* Stimulus */
  setPixel( mInputStream, mOutputStream, mPPM );

  /* Comparison */
  EXPECT_EQ( mPrompt, mOutputStream.str( ) );

  /* Tear-down */
  // Done automatically
}



TEST_F( setPixelTest, setsPixel ) {

  /* Setup */
  mPrompt = "Row? Column? Red? Green? Blue? ";
  mInputStream.str( "1 2 4 5 6"  );

  /* Stimulus */
  setPixel( mInputStream, mOutputStream, mPPM );
  const PPM& ppm_const = mPPM;

  /* Comparison */
  EXPECT_EQ( mPrompt, mOutputStream.str( ) );
  EXPECT_EQ( 4, ppm_const.getChannel( 1, 2, 0 ) );
  EXPECT_EQ( 5, ppm_const.getChannel( 1, 2, 1 ) );
  EXPECT_EQ( 6, ppm_const.getChannel( 1, 2, 2 ) );

  /* Tear-down */
  // Done automatically
}

TEST_F( setPixelTest, setsOtherPixel ) {

  /* Setup */
  mPrompt = "Row? Column? Red? Green? Blue? ";
  mInputStream.str( "23 46 150 75 37"  );

  /* Stimulus */
  setPixel( mInputStream, mOutputStream, mPPM );
  const PPM& ppm_const = mPPM;

  /* Comparison */
  EXPECT_EQ( mPrompt, mOutputStream.str( ) );
  EXPECT_EQ( 150, ppm_const.getChannel( 23, 46, 0 ) );
  EXPECT_EQ( 75, ppm_const.getChannel( 23, 46, 1 ) );
  EXPECT_EQ( 37, ppm_const.getChannel( 23, 46, 2 ) );

  /* Tear-down */
  // Done automatically
}


TEST_F( setPixelTest, setsFirstPixel ) {

  /* Setup */
  mPrompt = "Row? Column? Red? Green? Blue? ";
  mInputStream.str( "0 0 1 150 2"  );

  /* Stimulus */
  setPixel( mInputStream, mOutputStream, mPPM );
  const PPM& ppm_const = mPPM;

  /* Comparison */
  EXPECT_EQ( mPrompt, mOutputStream.str( ) );
  EXPECT_EQ( 1, ppm_const.getChannel( 0, 0, 0 ) );
  EXPECT_EQ( 150, ppm_const.getChannel( 0, 0, 1 ) );
  EXPECT_EQ( 2, ppm_const.getChannel( 0, 0, 2 ) );

  /* Tear-down */
  // Done automatically
}
