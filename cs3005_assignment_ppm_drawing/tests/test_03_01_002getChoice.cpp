#include "image_menu.h"
#include "image_menu.h" // Did you #ifndef your file?

#include "gtest/gtest.h"
#include <fstream>
#include <string>

class getChoiceTest : public ::testing::Test {
protected:

  virtual void SetUp( ) {
    mPrompt = "Choice? ";
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


TEST_F( getChoiceTest, displaysPrompt ) {

  /* Setup */
  mInputStream.str( "one-word-here"  );

  /* Stimulus */
  mResponse = getChoice( mInputStream, mOutputStream );

  /* Comparison */
  EXPECT_EQ( mPrompt, mOutputStream.str( ) );

  /* Tear-down */
  // Done automatically
}

TEST_F( getChoiceTest, readsWord ) {

  /* Setup */
  mInputStream.str( "one-word-here"  );

  /* Stimulus */
  mResponse = getChoice( mInputStream, mOutputStream );

  /* Comparison */
  EXPECT_EQ( mPrompt, mOutputStream.str( ) );
  EXPECT_EQ( mInputStream.str( ), mResponse );

  /* Tear-down */
  // Done automatically
}

TEST_F( getChoiceTest, readsOneWord ) {

  /* Setup */
  mInputStream.str( "many words here"  );

  /* Stimulus */
  mResponse = getChoice( mInputStream, mOutputStream );

  /* Comparison */
  EXPECT_EQ( mPrompt, mOutputStream.str( ) );
  EXPECT_EQ( "many", mResponse );

  /* Tear-down */
  // Done automatically
}


TEST_F( getChoiceTest, readsAnotherSingleWord ) {

  /* Setup */
  mInputStream.str( "0123456789 yes that's a word"  );

  /* Stimulus */
  mResponse = getChoice( mInputStream, mOutputStream );

  /* Comparison */
  EXPECT_EQ( mPrompt, mOutputStream.str( ) );
  EXPECT_EQ( "0123456789", mResponse );

  /* Tear-down */
  // Done automatically
}
