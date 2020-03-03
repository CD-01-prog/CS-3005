#include "image_menu.h"
#include "image_menu.h" // Did you #ifndef your file?

#include "gtest/gtest.h"
#include <fstream>
#include <string>

class EdgesTakeActionTest : public ::testing::Test {
protected:

  EdgesTakeActionTest( )
    : nonEdgePixels( { {1,2}, {2,4}, {3,6}, {4,8}, {5,10}, {6,12}, {7,14}, {8,16} } ),
      edgePixels( { {8,1}, {6,5}, {5,7}, {2,13}, {1,15} } ) {
  }

  void writeFile( const std::string& filename, const PPM& ppm ) {
    std::ofstream fout( filename, std::ios::binary );
    fout << ppm;
    fout.close();
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

    mInputStream.str( "" );
    mOutputStream.str( "" );
    //mTmpFile = "pre-edge.ppm";
    //writeFile( mTmpFile, ppm );
  }

  virtual void TearDown( ) {
    //remove( mTmpFile.c_str() );
  }

  /* data members */
  PPM ppm;
  PPM filtered_ppm;
  std::vector< std::pair<int,int> > nonEdgePixels;
  std::vector< std::pair<int,int> > edgePixels;

  /* data members */
  //std::string mTmpFile;
  std::string mChoice;
  std::stringstream mInputStream;
  std::stringstream mOutputStream;
  std::string mExpectedOutput;
  PPM mInputImage1, mInputImage2, mOutputImage;
};


TEST_F( EdgesTakeActionTest, setsVerticalEdges ) {

  /* Setup */
  mExpectedOutput = "";
  mChoice = "v-edge";

  /* Stimulus */
  mInputImage1 = ppm;
  takeAction( mInputStream, mOutputStream, mChoice, mInputImage1, mInputImage2, mOutputImage );

  /* Comparison */
  EXPECT_EQ( mExpectedOutput, mOutputStream.str( ) );
  EXPECT_EQ( mInputImage1.getHeight( ), mOutputImage.getHeight( ) );
  EXPECT_EQ( mInputImage1.getWidth( ), mOutputImage.getWidth( ) );
  EXPECT_EQ( mInputImage1.getMaxColorValue( ), mOutputImage.getMaxColorValue( ) );

  int row, column, channel;
  const PPM& ppm_orig_const = mInputImage1;
  const PPM& ppm_edge_const = mOutputImage;
  for( row = 0; row < ppm_edge_const.getHeight( ); row++ ) {
    for( column = 0; column < ppm_edge_const.getWidth( ); column++ ) {
      for( channel = 0; channel < 3; channel++ ) {
        bool found = false;
        for( auto it = edgePixels.begin(); it != edgePixels.end(); it++ ) {
          if(( it->first == row && it->second == column )
             || ( it->first == row && it->second == column-1 )) {
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

TEST_F( EdgesTakeActionTest, setsHorizontalEdges ) {

  /* Setup */
  mExpectedOutput = "";
  mChoice = "h-edge";

  /* Stimulus */
  mInputImage1 = ppm;
  takeAction( mInputStream, mOutputStream, mChoice, mInputImage1, mInputImage2, mOutputImage );

  /* Comparison */
  EXPECT_EQ( mExpectedOutput, mOutputStream.str( ) );
  EXPECT_EQ( mInputImage1.getHeight( ), mOutputImage.getHeight( ) );
  EXPECT_EQ( mInputImage1.getWidth( ), mOutputImage.getWidth( ) );
  EXPECT_EQ( mInputImage1.getMaxColorValue( ), mOutputImage.getMaxColorValue( ) );

  int row, column, channel;
  const PPM& ppm_orig_const = mInputImage1;
  const PPM& ppm_edge_const = mOutputImage;
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
