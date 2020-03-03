#include "image_menu.h"
#include "image_menu.h" // Did you #ifndef your file?

#include "gtest/gtest.h"
#include <fstream>
#include <string>
#include <cmath>

class takeActionOperatorPlusEqualsIntTest : public ::testing::Test {
protected:

  virtual void SetUp( ) {
    mPrompt = "";
    mInputStream.str( "" );
    mOutputStream.str( "" );

    //
    mHeight = 2;
    mWidth = 2;
    mMaxColorValue = 255;
    mPPM.setWidth( mWidth );
    mPPM.setHeight( mHeight );
    mPPM.setMaxColorValue( mMaxColorValue );

    mPPM.setChannel( 0, 0, 0, 100 );
    mPPM.setChannel( 0, 0, 1, 150 );
    mPPM.setChannel( 0, 0, 2, 200 );

    mPPM.setChannel( 0, 1, 0, 132 );
    mPPM.setChannel( 0, 1, 1, 123 );
    mPPM.setChannel( 0, 1, 2, 231 );

    mPPM.setChannel( 1, 0, 0, 10 );
    mPPM.setChannel( 1, 0, 1, 100 );
    mPPM.setChannel( 1, 0, 2, 50 );

    mPPM.setChannel( 1, 1, 0, 255 );
    mPPM.setChannel( 1, 1, 1, 0   );
    mPPM.setChannel( 1, 1, 2, 127 );


    mPPM5.setWidth( mWidth );
    mPPM5.setHeight( mHeight );
    mPPM5.setMaxColorValue( mMaxColorValue );

    mPPM5.setChannel( 0, 0, 0, 110 );
    mPPM5.setChannel( 0, 0, 1, 160 );
    mPPM5.setChannel( 0, 0, 2, 210 );

    mPPM5.setChannel( 0, 1, 0, 142 );
    mPPM5.setChannel( 0, 1, 1, 133 );
    mPPM5.setChannel( 0, 1, 2, 241 );

    mPPM5.setChannel( 1, 0, 0, 20 );
    mPPM5.setChannel( 1, 0, 1, 110 );
    mPPM5.setChannel( 1, 0, 2, 60 );

    mPPM5.setChannel( 1, 1, 0, 255 );
    mPPM5.setChannel( 1, 1, 1, 10   );
    mPPM5.setChannel( 1, 1, 2, 137 );

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
  int mHeight, mWidth, mMaxColorValue;
  std::string mPrompt;
  std::string mChoice;
  std::stringstream mInputStream;
  std::stringstream mOutputStream;
  PPM mPPM;
  PPM mPPM5;
  PPM input_image1, input_image2, output_image;
};

TEST_F( takeActionOperatorPlusEqualsIntTest, addsInteger ) {

  /* Setup */
  mChoice = "+=-int";
  mPrompt = "Boost? ";
  mInputStream.str( "10" );

  /* Stimulus */
  input_image1 = mPPM;
  takeAction( mInputStream, mOutputStream, mChoice, input_image1, input_image2, output_image );
  const PPM& ppm_const = input_image1;

  /* Comparison */
  EXPECT_EQ( mPrompt, mOutputStream.str( ) );
  EXPECT_EQ( true, identical_pixels( mPPM5, ppm_const ) );


  /* Tear-down */
  // Done automatically
}
