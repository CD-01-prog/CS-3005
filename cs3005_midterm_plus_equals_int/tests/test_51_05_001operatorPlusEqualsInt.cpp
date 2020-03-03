#include "PPM.h"
#include "PPM.h" // Did you #ifndef your file?

#include "gtest/gtest.h"
#include <fstream>
#include <cstdio>

class operatorPlusEqualsTest : public ::testing::Test {
protected:

  virtual void SetUp( ) {
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

    /* + -5 */
    ppm_plus_neg5.setWidth( 1 );
    ppm_plus_neg5.setHeight( 1 );
    ppm_plus_neg5.setMaxColorValue( 255 );
    ppm_plus_neg5.setChannel( 0, 0, 0, 95 );
    ppm_plus_neg5.setChannel( 0, 0, 1, 145 );
    ppm_plus_neg5.setChannel( 0, 0, 2, 248 );

    /* + -125 */
    ppm_plus_neg125.setWidth( 1 );
    ppm_plus_neg125.setHeight( 1 );
    ppm_plus_neg125.setMaxColorValue( 255 );
    ppm_plus_neg125.setChannel( 0, 0, 0, 0 );
    ppm_plus_neg125.setChannel( 0, 0, 1, 25 );
    ppm_plus_neg125.setChannel( 0, 0, 2, 128 );
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
  PPM ppm_a;
  PPM ppm_plus_5;
  PPM ppm_plus_50;
  PPM ppm_plus_neg5;
  PPM ppm_plus_neg125;
};

TEST_F( operatorPlusEqualsTest, addsToAllChannels ) {

  /* Setup */
  // Done automatically

  /* Stimulus */
  PPM ppm_x = ppm_a;
  ppm_x += 5;

  /* Comparison */
  EXPECT_EQ( true, identical_pixels( ppm_plus_5, ppm_x ) )
    << "Adding 5";


  /* Stimulus */
  ppm_x = ppm_a;
  ppm_x += 50;

  /* Comparison */
  EXPECT_EQ( true, identical_pixels( ppm_plus_50, ppm_x ) )
    << "Adding 50";

  /* Stimulus */
  ppm_x = ppm_a;
  ppm_x += -5;

  /* Comparison */
  EXPECT_EQ( true, identical_pixels( ppm_plus_neg5, ppm_x ) )
    << "Adding -5";

  /* Stimulus */
  ppm_x = ppm_a;
  ppm_x += -125;

  /* Comparison */
  EXPECT_EQ( true, identical_pixels( ppm_plus_neg125, ppm_x ) )
    << "Adding -125";

  /* Tear-down */
  // Done automatically
}
