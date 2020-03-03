#include "image_menu.h"
#include "image_menu.h" // Did you #ifndef your file?

#include "gtest/gtest.h"
#include <fstream>
#include <string>

class setMaxColorValueTest : public ::testing::Test {
protected:

  virtual void SetUp( ) {
    mPrompt = "";
    mInputStream.str( "" );
    mOutputStream.str( "" );
    mPPM.setHeight( 0 );
    mPPM.setWidth( 0 );
    mPPM.setMaxColorValue( 0 );
  }

  virtual void TearDown( ) {
  }

  /* data members */
  std::string mPrompt;
  std::stringstream mInputStream;
  std::stringstream mOutputStream;
  PPM mPPM;
};


TEST_F( setMaxColorValueTest, displaysPrompts ) {

  /* Setup */
  mPrompt = "Max color value? ";
  mInputStream.str( "198"  );

  /* Stimulus */
  setMaxColorValue( mInputStream, mOutputStream, mPPM );

  /* Comparison */
  EXPECT_EQ( mPrompt, mOutputStream.str( ) );

  /* Tear-down */
  // Done automatically
}



TEST_F( setMaxColorValueTest, setsMaxColorValue ) {

  /* Setup */
  mPrompt = "Max color value? ";
  mInputStream.str( "198"  );

  /* Stimulus */
  setMaxColorValue( mInputStream, mOutputStream, mPPM );
  const PPM& ppm_const = mPPM;

  /* Comparison */
  EXPECT_EQ( mPrompt, mOutputStream.str( ) );
  EXPECT_EQ( 198, ppm_const.getMaxColorValue( ) );

  /* Tear-down */
  // Done automatically
}


TEST_F( setMaxColorValueTest, setsOtherMaxColorValue ) {

  /* Setup */
  mPrompt = "Max color value? ";
  mInputStream.str( "14"  );

  /* Stimulus */
  setMaxColorValue( mInputStream, mOutputStream, mPPM );
  const PPM& ppm_const = mPPM;

  /* Comparison */
  EXPECT_EQ( mPrompt, mOutputStream.str( ) );
  EXPECT_EQ( 14, ppm_const.getMaxColorValue( ) );

  /* Tear-down */
  // Done automatically
}


TEST_F( setMaxColorValueTest, setsZeroMaxColorValue ) {

  /* Setup */
  mPPM.setMaxColorValue( 100 );
  mPrompt = "Max color value? ";
  mInputStream.str( "0"  );

  /* Stimulus */
  setMaxColorValue( mInputStream, mOutputStream, mPPM );
  const PPM& ppm_const = mPPM;

  /* Comparison */
  EXPECT_EQ( mPrompt, mOutputStream.str( ) );
  EXPECT_EQ( 0, ppm_const.getMaxColorValue( ) );

  /* Tear-down */
  // Done automatically
}
