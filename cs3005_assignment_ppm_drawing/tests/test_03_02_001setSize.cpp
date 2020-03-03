#include "image_menu.h"
#include "image_menu.h" // Did you #ifndef your file?

#include "gtest/gtest.h"
#include <fstream>
#include <string>

class setSizeTest : public ::testing::Test {
protected:

  virtual void SetUp( ) {
    mPrompt = "";
    mInputStream.str( "" );
    mOutputStream.str( "" );
    mPPM.setHeight( 0 );
    mPPM.setWidth( 0 );
  }

  virtual void TearDown( ) {
  }

  /* data members */
  std::string mPrompt;
  std::stringstream mInputStream;
  std::stringstream mOutputStream;
  PPM mPPM;
};


TEST_F( setSizeTest, displaysPrompts ) {

  /* Setup */
  mPrompt = "Height? Width? ";
  mInputStream.str( "13 17"  );

  /* Stimulus */
  setSize( mInputStream, mOutputStream, mPPM );

  /* Comparison */
  EXPECT_EQ( mPrompt, mOutputStream.str( ) );

  /* Tear-down */
  // Done automatically
}



TEST_F( setSizeTest, setsHeight ) {

  /* Setup */
  mPrompt = "Height? Width? ";
  mInputStream.str( "13 17"  );

  /* Stimulus */
  setSize( mInputStream, mOutputStream, mPPM );
  const PPM& ppm_const = mPPM;

  /* Comparison */
  EXPECT_EQ( mPrompt, mOutputStream.str( ) );
  EXPECT_EQ( 13, ppm_const.getHeight( ) );

  /* Tear-down */
  // Done automatically
}

TEST_F( setSizeTest, setsWidth ) {

  /* Setup */
  mPrompt = "Height? Width? ";
  mInputStream.str( "13 17"  );

  /* Stimulus */
  setSize( mInputStream, mOutputStream, mPPM );
  const PPM& ppm_const = mPPM;

  /* Comparison */
  EXPECT_EQ( mPrompt, mOutputStream.str( ) );
  EXPECT_EQ( 13, ppm_const.getHeight( ) );
  EXPECT_EQ( 17, ppm_const.getWidth( ) );

  /* Tear-down */
  // Done automatically
}


TEST_F( setSizeTest, setsOtherSize ) {

  /* Setup */
  mPrompt = "Height? Width? ";
  mInputStream.str( "19 75"  );

  /* Stimulus */
  setSize( mInputStream, mOutputStream, mPPM );
  const PPM& ppm_const = mPPM;

  /* Comparison */
  EXPECT_EQ( mPrompt, mOutputStream.str( ) );
  EXPECT_EQ( 19, ppm_const.getHeight( ) );
  EXPECT_EQ( 75, ppm_const.getWidth( ) );

  /* Tear-down */
  // Done automatically
}


TEST_F( setSizeTest, setsZeroSize ) {

  /* Setup */
  mPPM.setHeight( 100 );
  mPPM.setWidth( 200 );
  mPrompt = "Height? Width? ";
  mInputStream.str( "0 0"  );

  /* Stimulus */
  setSize( mInputStream, mOutputStream, mPPM );
  const PPM& ppm_const = mPPM;

  /* Comparison */
  EXPECT_EQ( mPrompt, mOutputStream.str( ) );
  EXPECT_EQ( 0, ppm_const.getHeight( ) );
  EXPECT_EQ( 0, ppm_const.getWidth( ) );

  /* Tear-down */
  // Done automatically
}
