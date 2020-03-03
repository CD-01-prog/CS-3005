#include "image_menu.h"
#include "image_menu.h" // Did you #ifndef your file?

#include "gtest/gtest.h"
#include <fstream>
#include <string>

class assignment1Test : public ::testing::Test {
protected:

  virtual void SetUp( ) {
    mInputStream.str( "" );
    mOutputStream.str( "" );
    mPrompts = "What's your favorite color? ";
    mPrompts += "What's your favorite integer? ";
    mPrompts += "What's your favorite number? ";
  }

  virtual void TearDown( ) {
  }

  /* data members */
  std::stringstream mInputStream;
  std::stringstream mOutputStream;
  int mResponse;
  std::string mPrompts;
  std::string mOutput;
};


TEST_F( assignment1Test, displaysPrompts ) {

  /* Setup */
  mInputStream.str( "Blue 0 0" );

  /* Stimulus */
  mResponse = assignment1( mInputStream, mOutputStream );

  /* Comparison */
  EXPECT_EQ( mPrompts, mOutputStream.str( ) );

  /* Tear-down */
  // Done automatically
}

TEST_F( assignment1Test, givesReturnValue ) {

  /* Setup */
  mInputStream.str( "Blue 3 3.14" );

  /* Stimulus */
  mResponse = assignment1( mInputStream, mOutputStream );

  /* Comparison */
  EXPECT_EQ( 3, mResponse );

  /* Tear-down */
  // Done automatically
}


TEST_F( assignment1Test, displaysOneLoop ) {

  /* Setup */
  mInputStream.str( "Blue 1 3.14" );
  mOutput = "1 Blue 3.14\n";

  /* Stimulus */
  mResponse = assignment1( mInputStream, mOutputStream );

  /* Comparison */
  EXPECT_EQ( mPrompts + mOutput, mOutputStream.str( ) );
  EXPECT_EQ( 1, mResponse );

  /* Tear-down */
  // Done automatically
}

TEST_F( assignment1Test, displaysTwoLoops ) {

  /* Setup */
  mInputStream.str( "Blue 2 2.14" );
  mOutput = "1 Blue 2.14\n2 Blue 2.14\n";

  /* Stimulus */
  mResponse = assignment1( mInputStream, mOutputStream );

  /* Comparison */
  EXPECT_EQ( mPrompts + mOutput, mOutputStream.str( ) );
  EXPECT_EQ( 2, mResponse );

  /* Tear-down */
  // Done automatically
}

TEST_F( assignment1Test, displaysManyLoops ) {

  /* Setup */
  mInputStream.str( "Blue 100 -3.14" );
  mOutput = "";
  int i;
  std::stringstream ss;
  for( i = 0; i < 100; i++ ) {
    ss << ( i + 1 ) << " Blue -3.14\n";
  }
  mOutput = ss.str( );

  /* Stimulus */
  mResponse = assignment1( mInputStream, mOutputStream );

  /* Comparison */
  EXPECT_EQ( mPrompts + mOutput, mOutputStream.str( ) );
  EXPECT_EQ( 100, mResponse );

  /* Tear-down */
  // Done automatically
}

TEST_F( assignment1Test, displaysZeroLoops ) {

  /* Setup */
  mInputStream.str( "Blue 0 3.14" );
  mOutput = "";

  /* Stimulus */
  mResponse = assignment1( mInputStream, mOutputStream );

  /* Comparison */
  EXPECT_EQ( mPrompts + mOutput, mOutputStream.str( ) );
  EXPECT_EQ( 0, mResponse );

  /* Tear-down */
  // Done automatically
}

TEST_F( assignment1Test, displaysNoNegativeLoops ) {

  /* Setup */
  mInputStream.str( "Blue -1 -7.41" );
  mOutput = "";

  /* Stimulus */
  mResponse = assignment1( mInputStream, mOutputStream );

  /* Comparison */
  EXPECT_EQ( mPrompts + mOutput, mOutputStream.str( ) );
  EXPECT_EQ( -1, mResponse );

  /* Tear-down */
  // Done automatically
}
