#include "image_menu.h"
#include "image_menu.h" // Did you #ifndef your file?

#include "gtest/gtest.h"
#include <fstream>
#include <string>

class getStringTest : public ::testing::Test {
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
  std::string mResponse;
};


TEST_F( getStringTest, displaysPrompt ) {

  /* Setup */
  mPrompt = "hello world? ";
  mInputStream.str( "one-word-here"  );

  /* Stimulus */
  mResponse = getString( mInputStream, mOutputStream, mPrompt );

  /* Comparison */
  EXPECT_EQ( mPrompt, mOutputStream.str( ) );

  /* Tear-down */
  // Done automatically
}

TEST_F( getStringTest, displaysDifferentPrompt ) {

  /* Setup */
  mPrompt = "goodbye world? ";
  mInputStream.str( "one-word-here"  );

  /* Stimulus */
  mResponse = getString( mInputStream, mOutputStream, mPrompt );

  /* Comparison */
  EXPECT_EQ( mPrompt, mOutputStream.str( ) );

  /* Tear-down */
  // Done automatically
}


TEST_F( getStringTest, readsWord ) {

  /* Setup */
  mPrompt = "Nice? ";
  mInputStream.str( "one-word-here"  );

  /* Stimulus */
  mResponse = getString( mInputStream, mOutputStream, mPrompt );

  /* Comparison */
  EXPECT_EQ( mPrompt, mOutputStream.str( ) );
  EXPECT_EQ( mInputStream.str( ), mResponse );

  /* Tear-down */
  // Done automatically
}

TEST_F( getStringTest, readsOneWord ) {

  /* Setup */
  mPrompt = "Nice? ";
  mInputStream.str( "many words here"  );

  /* Stimulus */
  mResponse = getString( mInputStream, mOutputStream, mPrompt );

  /* Comparison */
  EXPECT_EQ( mPrompt, mOutputStream.str( ) );
  EXPECT_EQ( "many", mResponse );

  /* Tear-down */
  // Done automatically
}


TEST_F( getStringTest, readsAnotherSingleWord ) {

  /* Setup */
  mPrompt = "goodbye world? ";
  mInputStream.str( "0123456789 yes that's a word"  );

  /* Stimulus */
  mResponse = getString( mInputStream, mOutputStream, mPrompt );

  /* Comparison */
  EXPECT_EQ( mPrompt, mOutputStream.str( ) );
  EXPECT_EQ( "0123456789", mResponse );

  /* Tear-down */
  // Done automatically
}
