#include "image_menu.h"
#include "image_menu.h" // Did you #ifndef your file?

#include "gtest/gtest.h"
#include <fstream>
#include <string>

class getDoubleTest : public ::testing::Test {
protected:

  virtual void SetUp( ) {
    mInputStream.str( "" );
    mOutputStream.str( "" );
  }

  virtual void TearDown( ) {
  }

  /* data members */
  std::string mPrompt;
  std::stringstream mInputStream;
  std::stringstream mOutputStream;
  double mResponse;
};


TEST_F( getDoubleTest, displaysPrompt ) {

  /* Setup */
  mPrompt = "hello world? ";
  mInputStream.str( "12.345"  );

  /* Stimulus */
  mResponse = getDouble( mInputStream, mOutputStream, mPrompt );

  /* Comparison */
  EXPECT_EQ( mPrompt, mOutputStream.str( ) );

  /* Tear-down */
  // Done automatically
}

TEST_F( getDoubleTest, displaysDifferentPrompt ) {

  /* Setup */
  mPrompt = "goodbye world? ";
  mInputStream.str( "1234.5"  );

  /* Stimulus */
  mResponse = getDouble( mInputStream, mOutputStream, mPrompt );

  /* Comparison */
  EXPECT_EQ( mPrompt, mOutputStream.str( ) );

  /* Tear-down */
  // Done automatically
}


TEST_F( getDoubleTest, readsDouble ) {

  /* Setup */
  mPrompt = "Nice? ";
  mInputStream.str( "1.2345"  );

  /* Stimulus */
  mResponse = getDouble( mInputStream, mOutputStream, mPrompt );

  /* Comparison */
  EXPECT_EQ( mPrompt, mOutputStream.str( ) );
  EXPECT_DOUBLE_EQ( 1.2345, mResponse );

  /* Tear-down */
  // Done automatically
}

TEST_F( getDoubleTest, readsOneDouble ) {

  /* Setup */
  mPrompt = "Nice? ";
  mInputStream.str( "5.4 0.32 1.0"  );

  /* Stimulus */
  mResponse = getDouble( mInputStream, mOutputStream, mPrompt );

  /* Comparison */
  EXPECT_EQ( mPrompt, mOutputStream.str( ) );
  EXPECT_DOUBLE_EQ( 5.4, mResponse );

  /* Tear-down */
  // Done automatically
}


TEST_F( getDoubleTest, readsAnotherSingleDouble ) {

  /* Setup */
  mPrompt = "goodbye world? ";
  mInputStream.str( "987.654321 123456789 9292"  );

  /* Stimulus */
  mResponse = getDouble( mInputStream, mOutputStream, mPrompt );

  /* Comparison */
  EXPECT_EQ( mPrompt, mOutputStream.str( ) );
  EXPECT_DOUBLE_EQ( 987.654321, mResponse );

  /* Tear-down */
  // Done automatically
}
