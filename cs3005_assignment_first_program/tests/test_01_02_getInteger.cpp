#include "image_menu.h"
#include "image_menu.h" // Did you #ifndef your file?

#include "gtest/gtest.h"
#include <fstream>
#include <string>

class getIntegerTest : public ::testing::Test {
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
  int mResponse;
};


TEST_F( getIntegerTest, displaysPrompt ) {

  /* Setup */
  mPrompt = "hello world? ";
  mInputStream.str( "12345"  );

  /* Stimulus */
  mResponse = getInteger( mInputStream, mOutputStream, mPrompt );

  /* Comparison */
  EXPECT_EQ( mPrompt, mOutputStream.str( ) );

  /* Tear-down */
  // Done automatically
}

TEST_F( getIntegerTest, displaysDifferentPrompt ) {

  /* Setup */
  mPrompt = "goodbye world? ";
  mInputStream.str( "12345"  );

  /* Stimulus */
  mResponse = getInteger( mInputStream, mOutputStream, mPrompt );

  /* Comparison */
  EXPECT_EQ( mPrompt, mOutputStream.str( ) );

  /* Tear-down */
  // Done automatically
}


TEST_F( getIntegerTest, readsInteger ) {

  /* Setup */
  mPrompt = "Nice? ";
  mInputStream.str( "12345"  );

  /* Stimulus */
  mResponse = getInteger( mInputStream, mOutputStream, mPrompt );

  /* Comparison */
  EXPECT_EQ( mPrompt, mOutputStream.str( ) );
  EXPECT_EQ( 12345, mResponse );

  /* Tear-down */
  // Done automatically
}

TEST_F( getIntegerTest, readsOneInteger ) {

  /* Setup */
  mPrompt = "Nice? ";
  mInputStream.str( "54 32 10"  );

  /* Stimulus */
  mResponse = getInteger( mInputStream, mOutputStream, mPrompt );

  /* Comparison */
  EXPECT_EQ( mPrompt, mOutputStream.str( ) );
  EXPECT_EQ( 54, mResponse );

  /* Tear-down */
  // Done automatically
}


TEST_F( getIntegerTest, readsAnotherSingleInteger ) {

  /* Setup */
  mPrompt = "goodbye world? ";
  mInputStream.str( "987654321 123456789 9292"  );

  /* Stimulus */
  mResponse = getInteger( mInputStream, mOutputStream, mPrompt );

  /* Comparison */
  EXPECT_EQ( mPrompt, mOutputStream.str( ) );
  EXPECT_EQ( 987654321, mResponse );

  /* Tear-down */
  // Done automatically
}
