#include "PPM.h"
#include "PPM.h" // Did you #ifndef your file?

#include "gtest/gtest.h"
#include <fstream>
#include <cstdio>

class FindHorizontalEdgesTest : public ::testing::Test {
protected:

  FindHorizontalEdgesTest( )
    : nonEdgePixels( { {1,2}, {2,4}, {3,6}, {4,8}, {5,10}, {6,12}, {7,14}, {8,16} } ),
      edgePixels( { {8,1}, {6,5}, {5,7}, {2,13}, {1,15} } ) {
  }

  virtual void SetUp( ) {
    ppm.setHeight( 10 );
    ppm.setWidth( 20 );
    ppm.setMaxColorValue( 150 );
    int row, column;
    for( row = 0; row < ppm.getHeight( ); row++ ) {
      for( column = 0; column < ppm.getWidth( ); column++ ) {
        ppm.setPixel( row, column, 50, 75, 100 );
      }
    }
    int red, green, blue;
    // brightness = 0.2126*red + 0.7152*green + 0.0722*blue
    // brightness0 = 71.49
    /*******************************************/
    // make some pixels that are not 10% different
    // max color value == 150, 10% == 15
    red = 120; green = 75; blue = 100; // more red
    ppm.setPixel( 1, 2, red, green, blue );
    red = 0; green = 75; blue = 100; // less red
    ppm.setPixel( 2, 4, red, green, blue );

    red = 50; green = 95; blue = 100; // more green
    ppm.setPixel( 3, 6, red, green, blue );
    red = 50; green = 55; blue = 100; // less green
    ppm.setPixel( 4, 8, red, green, blue );

    red = 50; green = 75; blue = 150; // more blue
    ppm.setPixel( 5, 10, red, green, blue );
    red = 50; green = 75; blue = 0; // less blue
    ppm.setPixel( 6, 12, red, green, blue );

    // mixture
    red = 73; green = 81; blue = 150; // more brightness
    ppm.setPixel( 7, 14, red, green, blue );
    red = 27; green = 69; blue = 31; // less brightness
    ppm.setPixel( 8, 16, red, green, blue );

    /*******************************************/
    // make some pixels that are more than 10% different
    red = 121; green = 75; blue = 100; // more red
    ppm.setPixel( 8, 1, red, green, blue );
    //red = 0; green = 75; blue = 100; // less red
    //ppm.setPixel( 7, 3, red, green, blue );

    red = 50; green = 96; blue = 100; // more green
    ppm.setPixel( 6, 5, red, green, blue );
    red = 50; green = 54; blue = 100; // less green
    ppm.setPixel( 5, 7, red, green, blue );

    // can't do it with blue alone
    // red = 50; green = 75; blue = 150; // more blue
    // ppm.setPixel( 5, 10, red, green, blue );
    // red = 50; green = 75; blue = 0; // less blue
    // ppm.setPixel( 6, 12, red, green, blue );

    // mixture
    red = 77; green = 83; blue = 150; // more brightness
    ppm.setPixel( 2, 13, red, green, blue );
    red = 26; green = 68; blue = 30; // less brightness
    ppm.setPixel( 1, 15, red, green, blue );

  }

  virtual void TearDown( ) {
  }

  /* data members */
  PPM ppm;
  PPM filtered_ppm;
  std::vector< std::pair<int,int> > nonEdgePixels;
  std::vector< std::pair<int,int> > edgePixels;
};

TEST_F( FindHorizontalEdgesTest, setsMetaData ) {

  /* Setup */
  // Done automatically

  /* Stimulus */
  const PPM& ppm_orig_const = ppm;
  const PPM& ppm_gray_const = filtered_ppm;
  ppm_orig_const.findHorizontalEdges( filtered_ppm );

  /* Comparison */
  EXPECT_EQ( ppm_orig_const.getHeight( ), ppm_gray_const.getHeight( ) );
  EXPECT_EQ( ppm_orig_const.getWidth( ), ppm_gray_const.getWidth( ) );
  EXPECT_EQ( ppm_orig_const.getMaxColorValue( ), ppm_gray_const.getMaxColorValue( ) );


  /* Tear-down */
  // Done automatically
}

TEST_F( FindHorizontalEdgesTest, setsPixelData ) {

  /* Setup */
  // Done automatically

  /* Stimulus */
  const PPM& ppm_orig_const = ppm;
  const PPM& ppm_edge_const = filtered_ppm;
  ppm_orig_const.findHorizontalEdges( filtered_ppm );

  /* Comparison */
  EXPECT_EQ( ppm_orig_const.getHeight( ), ppm_edge_const.getHeight( ) );
  EXPECT_EQ( ppm_orig_const.getWidth( ), ppm_edge_const.getWidth( ) );
  EXPECT_EQ( ppm_orig_const.getMaxColorValue( ), ppm_edge_const.getMaxColorValue( ) );

  int row, column, channel;
  for( row = 0; row < ppm_edge_const.getHeight( ); row++ ) {
    for( column = 0; column < ppm_edge_const.getWidth( ); column++ ) {
      for( channel = 0; channel < 3; channel++ ) {
        bool found = false;
        for( auto it = edgePixels.begin(); it != edgePixels.end(); it++ ) {
          if(( it->first == row && it->second == column )
             || ( it->first == row-1 && it->second == column )) {
            found = true;
            break;
          }
        }
        if( found ) {
          EXPECT_EQ( ppm_orig_const.getMaxColorValue( ), ppm_edge_const.getChannel( row, column, channel ) )
          << "row: " << row << "  column: " << column << "  channel: " << channel;
        } else {
          EXPECT_EQ( 0, ppm_edge_const.getChannel( row, column, channel ) )
          << "row: " << row << "  column: " << column << "  channel: " << channel;
        }
      }
    }
  }

  /* Tear-down */
  // Done automatically
}
