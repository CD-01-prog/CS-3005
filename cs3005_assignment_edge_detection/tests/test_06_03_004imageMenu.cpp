#include "image_menu.h"
#include "image_menu.h" // Did you #ifndef your file?

#include "gtest/gtest.h"
#include <fstream>
#include <string>
#include <sstream>

class QuietImageMenuTest : public ::testing::Test {
protected:

  int countChoice( const std::string& s ) {
    int count = 0;
    std::stringstream ss( s );
    std::string word;
    while( ss >> word ) {
      if( word == "Choice?" ) {
        count ++;
      }
    }
    return count;
  }

  virtual void SetUp( ) {
    mInputStream.str( "" );
    mOutputStream.str( "" );
  }

  virtual void TearDown( ) {
  }

  /* data members */
  std::stringstream mInputStream;
  std::stringstream mOutputStream;
};


TEST_F( QuietImageMenuTest, usesQuiet ) {

  /* Setup */
  mInputStream.str( "quiet size 11 19 max 23 copy write silly.ppm quit" );

  /* Stimulus */
  imageMenu( mInputStream, mOutputStream );
  int choice_count = countChoice( mOutputStream.str() );

  /* Comparison */
  PPM ppm_tmp;
  mInputStream.clear( );
  mInputStream.str( "silly.ppm" );
  readUserImage( mInputStream, mOutputStream, ppm_tmp );
  remove( "silly.ppm" );
  const PPM& ppm_const = ppm_tmp;

  EXPECT_EQ( 1, choice_count )
    << "After the quiet command is issued, no more menus or prompts should show up." << std::endl;
  EXPECT_EQ( 11, ppm_const.getHeight( ) );
  EXPECT_EQ( 19, ppm_const.getWidth( ) );
  EXPECT_EQ( 23, ppm_const.getMaxColorValue( ) );

  /* Tear-down */
  // Done automatically
}

TEST_F( QuietImageMenuTest, quietTogglesOffAndOn ) {

  /* Setup */
  mInputStream.str( "quiet size 11 19 quiet max 23 copy write silly.ppm quit" );

  /* Stimulus */
  imageMenu( mInputStream, mOutputStream );
  int choice_count = countChoice( mOutputStream.str() );

  /* Comparison */
  PPM ppm_tmp;
  mInputStream.clear( );
  mInputStream.str( "silly.ppm" );
  readUserImage( mInputStream, mOutputStream, ppm_tmp );
  remove( "silly.ppm" );
  const PPM& ppm_const = ppm_tmp;

  EXPECT_EQ( 5, choice_count )
    << "A second quiet should re-enable menus and prompts." << std::endl;
  EXPECT_EQ( 11, ppm_const.getHeight( ) );
  EXPECT_EQ( 19, ppm_const.getWidth( ) );
  EXPECT_EQ( 23, ppm_const.getMaxColorValue( ) );

  /* Tear-down */
  // Done automatically
}


TEST_F( QuietImageMenuTest, quietTogglesOffAndOnEveryTime ) {

  /* Setup */
  mInputStream.str( "quiet size 11 19 quiet max 23 quiet quiet copy quiet write silly.ppm quiet quit" );

  /* Stimulus */
  imageMenu( mInputStream, mOutputStream );
  int choice_count = countChoice( mOutputStream.str() );

  /* Comparison */
  PPM ppm_tmp;
  mInputStream.clear( );
  mInputStream.str( "silly.ppm" );
  readUserImage( mInputStream, mOutputStream, ppm_tmp );
  remove( "silly.ppm" );
  const PPM& ppm_const = ppm_tmp;

  EXPECT_EQ( 6, choice_count )
    << "Every quiet should toggle the menu and prompt." << std::endl;
  EXPECT_EQ( 11, ppm_const.getHeight( ) );
  EXPECT_EQ( 19, ppm_const.getWidth( ) );
  EXPECT_EQ( 23, ppm_const.getMaxColorValue( ) );

  /* Tear-down */
  // Done automatically
}
