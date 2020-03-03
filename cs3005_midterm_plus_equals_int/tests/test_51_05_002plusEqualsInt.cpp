#include "image_menu.h"
#include "image_menu.h" // Did you #ifndef your file?

#include "gtest/gtest.h"
#include <fstream>
#include <string>
#include <cmath>

class plusEqualsIntTest : public ::testing::Test {
protected:

  virtual void SetUp( ) {
    mPrompt = "";
    mInputStream.str( "" );
    mOutputStream.str( "" );

    ppm_a.setWidth( 1 );
    ppm_a.setHeight( 1 );
    ppm_a.setMaxColorValue( 255 );
    ppm_a.setChannel( 0, 0, 0, 100 );
    ppm_a.setChannel( 0, 0, 1, 150 );
    ppm_a.setChannel( 0, 0, 2, 253 );

    /* + 5 */
    ppm_plus_5.setWidth( 1 );
    ppm_plus_5.setHeight( 1 );
    ppm_plus_5.setMaxColorValue( 255 );
    ppm_plus_5.setChannel( 0, 0, 0, 105 );
    ppm_plus_5.setChannel( 0, 0, 1, 155 );
    ppm_plus_5.setChannel( 0, 0, 2, 255 );

    /* + 50 */
    ppm_plus_50.setWidth( 1 );
    ppm_plus_50.setHeight( 1 );
    ppm_plus_50.setMaxColorValue( 255 );
    ppm_plus_50.setChannel( 0, 0, 0, 150 );
    ppm_plus_50.setChannel( 0, 0, 1, 200 );
    ppm_plus_50.setChannel( 0, 0, 2, 255 );
  }

  virtual void TearDown( ) {
  }

  virtual bool identical_pixels( const PPM& expected, const PPM& actual, bool show_error=true ) {
    int row, col, chan;
    bool same = true;
    for ( row = 0; row < expected.getHeight( ); row++ ) {
      for ( col = 0; col < expected.getWidth( ); col++ ) {
        for ( chan = 0; chan < 3 ; chan++ ) {
          if ( expected.getChannel( row, col, chan ) != actual.getChannel( row, col, chan ) ) {
            same = false;
            if( show_error ) {
              EXPECT_EQ( expected.getChannel( row, col, chan ), actual.getChannel( row, col, chan ) )
                << " row = " << row << " col = " << col << " chan = " << chan;
            }
          }
        }
      }
    }
    return same;
  }

  /* data members */
  std::string mPrompt;
  std::stringstream mInputStream;
  std::stringstream mOutputStream;

  PPM ppm_a;
  PPM ppm_plus_5;
  PPM ppm_plus_50;

};


TEST_F( plusEqualsIntTest, addsInteger5 ) {

  /* Setup */
  mPrompt = "Boost? ";
  mInputStream.str( "5" );

  /* Stimulus */
  plusEqualsInt( mInputStream, mOutputStream, ppm_a );

  /* Comparison */
  EXPECT_EQ( mPrompt, mOutputStream.str( ) );
  EXPECT_EQ( true, identical_pixels( ppm_plus_5, ppm_a ) );

  /* Tear-down */
  // Done automatically
}


TEST_F( plusEqualsIntTest, addsInteger50 ) {

  /* Setup */
  mPrompt = "Boost? ";
  mInputStream.str( "50" );

  /* Stimulus */
  plusEqualsInt( mInputStream, mOutputStream, ppm_a );

  /* Comparison */
  EXPECT_EQ( mPrompt, mOutputStream.str( ) );
  EXPECT_EQ( true, identical_pixels( ppm_plus_50, ppm_a ) );

  /* Tear-down */
  // Done automatically
}
