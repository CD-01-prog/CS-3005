#include "PPM.h"
#include "PPM.h" // Did you #ifndef your file?

#include "gtest/gtest.h"
#include <fstream>
#include <cstdio>

class EdgePixelValueTest : public ::testing::Test {
protected:

  EdgePixelValueTest( )
    : nonEdgePixels( { {1,2}, {2,4}, {3,6}, {4,8}, {5,10}, {6,12}, {7,14}, {8,16} } ),
      edgePixels( { {8,1}, {6,5}, {5,7}, {2,13}, {1,15} } )  {
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
  std::vector< std::pair<int,int> > nonEdgePixels;
  std::vector< std::pair<int,int> > edgePixels;
};

TEST_F( EdgePixelValueTest, findsNonEdge ) {

  /* Setup */
  // Done automatically

  for( auto it = nonEdgePixels.begin(); it != nonEdgePixels.end(); it++ ) {
    /* Stimulus */
    int row1 = it->first;
    int col1 = it->second;
    int row2 = row1;
    int col2 = col1-1;

    /* Comparison */
    EXPECT_EQ( 0, ppm.edgePixelValue( row1, col1, row2, col2 ) )
      << " row1,col1: " << row1 << "," << col1 << " lcm1: " << ppm.linearColorimetricPixelValue( row1, col1 )
      << " row2,col2: " << row2 << "," << col2 << " lcm2: " << ppm.linearColorimetricPixelValue( row2, col2 );
  }

  /* Tear-down */
  // Done automatically
}

TEST_F( EdgePixelValueTest, findsEdge ) {

  /* Setup */
  // Done automatically

  for( auto it = edgePixels.begin(); it != edgePixels.end(); it++ ) {
    /* Stimulus */
    int row1 = it->first;
    int col1 = it->second;
    int row2 = row1;
    int col2 = col1-1;

    /* Comparison */
    EXPECT_EQ( 150, ppm.edgePixelValue( row1, col1, row2, col2 ) )
      << " row1,col1: " << row1 << "," << col1 << " lcm1: " << ppm.linearColorimetricPixelValue( row1, col1 )
      << " row2,col2: " << row2 << "," << col2 << " lcm2: " << ppm.linearColorimetricPixelValue( row2, col2 );
  }

  /* Tear-down */
  // Done automatically
}
