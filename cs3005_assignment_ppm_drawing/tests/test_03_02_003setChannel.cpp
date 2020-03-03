#include "image_menu.h"
#include "image_menu.h" // Did you #ifndef your file?

#include "gtest/gtest.h"
#include <fstream>
#include <string>

class setChannelTest : public ::testing::Test {
protected:

  virtual void SetUp( ) {
    mPrompt = "";
    mInputStream.str( "" );
    mOutputStream.str( "" );
    mPPM.setHeight( 33 );
    mPPM.setWidth( 67 );
    mPPM.setMaxColorValue( 255 );
  }

  virtual void TearDown( ) {
  }

  /* data members */
  std::string mPrompt;
  std::stringstream mInputStream;
  std::stringstream mOutputStream;
  PPM mPPM;
};


TEST_F( setChannelTest, displaysPrompts ) {

  /* Setup */
  mPrompt = "Row? Column? Channel? Value? ";
  mInputStream.str( "1 2 0 4"  );

  /* Stimulus */
  setChannel( mInputStream, mOutputStream, mPPM );

  /* Comparison */
  EXPECT_EQ( mPrompt, mOutputStream.str( ) );

  /* Tear-down */
  // Done automatically
}



TEST_F( setChannelTest, setsChannel ) {

  /* Setup */
  mPrompt = "Row? Column? Channel? Value? ";
  mInputStream.str( "1 2 0 4"  );

  /* Stimulus */
  setChannel( mInputStream, mOutputStream, mPPM );
  const PPM& ppm_const = mPPM;

  /* Comparison */
  EXPECT_EQ( mPrompt, mOutputStream.str( ) );
  EXPECT_EQ( 4, ppm_const.getChannel( 1, 2, 0 ) );

  /* Tear-down */
  // Done automatically
}

TEST_F( setChannelTest, setsOtherChannel ) {

  /* Setup */
  mPrompt = "Row? Column? Channel? Value? ";
  mInputStream.str( "32 66 2 254"  );

  /* Stimulus */
  setChannel( mInputStream, mOutputStream, mPPM );
  const PPM& ppm_const = mPPM;

  /* Comparison */
  EXPECT_EQ( mPrompt, mOutputStream.str( ) );
  EXPECT_EQ( 254, ppm_const.getChannel( 32, 66, 2 ) );

  /* Tear-down */
  // Done automatically
}


TEST_F( setChannelTest, setsFirstChannel ) {

  /* Setup */
  mPrompt = "Row? Column? Channel? Value? ";
  mInputStream.str( "0 0 0 251"  );

  /* Stimulus */
  setChannel( mInputStream, mOutputStream, mPPM );
  const PPM& ppm_const = mPPM;

  /* Comparison */
  EXPECT_EQ( mPrompt, mOutputStream.str( ) );
  EXPECT_EQ( 251, ppm_const.getChannel( 0, 0, 0 ) );

  /* Tear-down */
  // Done automatically
}
