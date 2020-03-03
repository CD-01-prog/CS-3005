#include "image_menu.h"
#include "image_menu.h" // Did you #ifndef your file?

#include "gtest/gtest.h"
#include <fstream>
#include <string>

class commentLineTest : public ::testing::Test {
protected:

  virtual void SetUp( ) {
    mInputStream.str( "" );
  }

  virtual void TearDown( ) {
  }

  /* data members */
  std::stringstream mInputStream;
  std::string mRemains;
  std::streampos mPosition;
};


TEST_F( commentLineTest, stopsAtEndOfStream1 ) {

  /* Setup */
  mPosition = -1;
  mRemains = "";
  mInputStream.str( "" );

  /* Stimulus */
  commentLine( mInputStream );

  /* Comparison */
  EXPECT_EQ( mPosition, mInputStream.tellg( ) );
  EXPECT_EQ( false, mInputStream.good( ) );
  EXPECT_EQ( true, mInputStream.eof( ) );
  EXPECT_EQ( true, mInputStream.fail( ) );

  /* Tear-down */
  // Done automatically
}

TEST_F( commentLineTest, stopsAtEndOfStream2 ) {

  /* Setup */
  mPosition = -1;
  mRemains = "";
  mInputStream.str( "letters-and-0123-@$%#@#"  );

  /* Stimulus */
  commentLine( mInputStream );

  /* Comparison */
  EXPECT_EQ( mPosition, mInputStream.tellg( ) );
  EXPECT_EQ( false, mInputStream.good( ) );
  EXPECT_EQ( true, mInputStream.eof( ) );
  EXPECT_EQ( true, mInputStream.fail( ) );

  /* Tear-down */
  // Done automatically
}

TEST_F( commentLineTest, stopsAtEndOfStream3 ) {

  /* Setup */
  mPosition = -1;
  mRemains = "";
  mInputStream.str( "letters and 0123 @$%#@#"  );

  /* Stimulus */
  commentLine( mInputStream );

  /* Comparison */
  EXPECT_EQ( mPosition, mInputStream.tellg( ) );
  EXPECT_EQ( false, mInputStream.good( ) );
  EXPECT_EQ( true, mInputStream.eof( ) );
  EXPECT_EQ( true, mInputStream.fail( ) );

  /* Tear-down */
  // Done automatically
}

TEST_F( commentLineTest, stopsAtEndOfLine1 ) {

  /* Setup */
  mPosition = 12;
  mRemains = "";
  mInputStream.str( "hello world\n"  );

  /* Stimulus */
  commentLine( mInputStream );

  /* Comparison */
  EXPECT_EQ( mPosition, mInputStream.tellg( ) );
  EXPECT_EQ( true, mInputStream.good( ) );
  EXPECT_EQ( false, mInputStream.eof( ) );
  EXPECT_EQ( false, mInputStream.fail( ) );

  /* Tear-down */
  // Done automatically
}

TEST_F( commentLineTest, stopsAtEndOfLine2 ) {

  /* Setup */
  mPosition = 28;
  mRemains = "more words here";
  mInputStream.str( "fred barney wilma and betty\nmore words here"  );

  /* Stimulus */
  commentLine( mInputStream );

  /* Comparison */
  EXPECT_EQ( mPosition, mInputStream.tellg( ) );
  EXPECT_EQ( (int)(mInputStream.str( ).size( ) - mRemains.size( )), (int)(mInputStream.tellg( )) );
  EXPECT_EQ( true, mInputStream.good( ) );
  EXPECT_EQ( false, mInputStream.eof( ) );
  EXPECT_EQ( false, mInputStream.fail( ) );

  /* Tear-down */
  // Done automatically
}

TEST_F( commentLineTest, stopsAtEndOfLine3 ) {

  /* Setup */
  mPosition = 7;
  mRemains = "the best of times.\nit was the worst\nof times.\n";
  mInputStream.str( "it was\nthe best of times.\nit was the worst\nof times.\n"  );

  /* Stimulus */
  commentLine( mInputStream );

  /* Comparison */
  EXPECT_EQ( mPosition, mInputStream.tellg( ) );
  EXPECT_EQ( (int)(mInputStream.str( ).size( ) - mRemains.size( )), (int)(mInputStream.tellg( )) );
  EXPECT_EQ( true, mInputStream.good( ) );
  EXPECT_EQ( false, mInputStream.eof( ) );
  EXPECT_EQ( false, mInputStream.fail( ) );

  /* Tear-down */
  // Done automatically
}

TEST_F( commentLineTest, stopsAtEndOfEmptyLine ) {

  /* Setup */
  mPosition = 4;
  mRemains = "the best of times.\nit was the worst\nof times.\n";
  mInputStream.str( "   \nthe best of times.\nit was the worst\nof times.\n"  );

  /* Stimulus */
  commentLine( mInputStream );

  /* Comparison */
  EXPECT_EQ( mPosition, mInputStream.tellg( ) );
  EXPECT_EQ( (int)(mInputStream.str( ).size( ) - mRemains.size( )), (int)(mInputStream.tellg( )) );
  EXPECT_EQ( true, mInputStream.good( ) );
  EXPECT_EQ( false, mInputStream.eof( ) );
  EXPECT_EQ( false, mInputStream.fail( ) );

  /* Tear-down */
  // Done automatically
}
