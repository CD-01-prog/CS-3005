#include "image_menu.h"
#include "image_menu.h" // Did you #ifndef your file?

#include "gtest/gtest.h"
#include <fstream>
#include <string>

class grayFromColorTest : public ::testing::Test {
protected:

  void setSourcePPM( int height, int width, int max_color_value, int red, int green, int blue ) {
    // save values
    mHeight = height;
    mWidth = width;
    mMaxColorValue = max_color_value;
    mRed = red;
    mGreen = green;
    mBlue = blue;

    // configure PPM
    mPPM.setHeight( height );
    mPPM.setWidth( width );
    mPPM.setMaxColorValue( max_color_value );
    int row, column;
    for( row = 0; row < mHeight; row++ ) {
      for( column = 0; column < mWidth; column++ ) {
        red = ( red + 2 ) % ( max_color_value + 1 );
        green = ( green + 3 ) % ( max_color_value + 1 );
        blue = ( blue + 7 ) % ( max_color_value + 1 );
        mPPM.setPixel( row, column, red, green, blue );
      }
    }
  }

  void clearDestinationPPM( ) {
    mFilteredPPM.setHeight( 0 );
    mFilteredPPM.setWidth( 0 );
    mFilteredPPM.setMaxColorValue( 0 );
  }

  void compareGrayPixels( int expected_channel ) {
    const PPM& ppm_orig_const = mPPM;
    const PPM& ppm_gray_const = mFilteredPPM;

    int row, column, channel;
    for( row = 0; row < mHeight; row++ ) {
      for( column = 0; column < mWidth; column++ ) {
        for( channel = 0; channel < 3; channel++ ) {
          EXPECT_EQ( ppm_orig_const.getChannel( row, column, expected_channel ), ppm_gray_const.getChannel( row, column, channel ) )
            << "row: " << row << "  column: " << column << "  channel: " << channel;
        }
      }
    }
  }

  virtual void SetUp( ) {
    setSourcePPM( 10, 20, 100, 30, 40, 50 );
    clearDestinationPPM( );
  }

  virtual void TearDown( ) {
  }

  /* data members */
  int mHeight, mWidth;
  int mMaxColorValue;
  int mRed, mGreen, mBlue;
  PPM mPPM;
  PPM mFilteredPPM;
};


TEST_F( grayFromColorTest, redSetsMetaData ) {

  /* Setup */
  // Automatic

  /* Stimulus */
  const PPM& ppm_orig_const = mPPM;
  const PPM& ppm_gray_const = mFilteredPPM;
  ppm_orig_const.grayFromRed( mFilteredPPM );

  /* Comparison */
  EXPECT_EQ( mHeight, ppm_gray_const.getHeight( ) );
  EXPECT_EQ( mWidth, ppm_gray_const.getWidth( ) );
  EXPECT_EQ( mMaxColorValue, ppm_gray_const.getMaxColorValue( ) );

  /* Tear-down */
  // Done automatically
}

TEST_F( grayFromColorTest, greenSetsMetaData ) {

  /* Setup */
  // Automatic

  /* Stimulus */
  const PPM& ppm_orig_const = mPPM;
  const PPM& ppm_gray_const = mFilteredPPM;
  ppm_orig_const.grayFromGreen( mFilteredPPM );

  /* Comparison */
  EXPECT_EQ( mHeight, ppm_gray_const.getHeight( ) );
  EXPECT_EQ( mWidth, ppm_gray_const.getWidth( ) );
  EXPECT_EQ( mMaxColorValue, ppm_gray_const.getMaxColorValue( ) );

  /* Tear-down */
  // Done automatically
}

TEST_F( grayFromColorTest, blueSetsMetaData ) {

  /* Setup */
  // Automatic

  /* Stimulus */
  const PPM& ppm_orig_const = mPPM;
  const PPM& ppm_gray_const = mFilteredPPM;
  ppm_orig_const.grayFromBlue( mFilteredPPM );

  /* Comparison */
  EXPECT_EQ( mHeight, ppm_gray_const.getHeight( ) );
  EXPECT_EQ( mWidth, ppm_gray_const.getWidth( ) );
  EXPECT_EQ( mMaxColorValue, ppm_gray_const.getMaxColorValue( ) );

  /* Tear-down */
  // Done automatically
}


TEST_F( grayFromColorTest, redSetsMetaDataAgain ) {

  /* Setup */
  setSourcePPM( 13, 7, 201, 9, 21, 31 );

  /* Stimulus */
  const PPM& ppm_orig_const = mPPM;
  const PPM& ppm_gray_const = mFilteredPPM;
  ppm_orig_const.grayFromRed( mFilteredPPM );

  /* Comparison */
  EXPECT_EQ( mHeight, ppm_gray_const.getHeight( ) );
  EXPECT_EQ( mWidth, ppm_gray_const.getWidth( ) );
  EXPECT_EQ( mMaxColorValue, ppm_gray_const.getMaxColorValue( ) );

  /* Tear-down */
  // Done automatically
}

TEST_F( grayFromColorTest, greenSetsMetaDataAgain ) {

  /* Setup */
  setSourcePPM( 13, 7, 201, 9, 21, 31 );

  /* Stimulus */
  const PPM& ppm_orig_const = mPPM;
  const PPM& ppm_gray_const = mFilteredPPM;
  ppm_orig_const.grayFromGreen( mFilteredPPM );

  /* Comparison */
  EXPECT_EQ( mHeight, ppm_gray_const.getHeight( ) );
  EXPECT_EQ( mWidth, ppm_gray_const.getWidth( ) );
  EXPECT_EQ( mMaxColorValue, ppm_gray_const.getMaxColorValue( ) );

  /* Tear-down */
  // Done automatically
}

TEST_F( grayFromColorTest, blueSetsMetaDataAgain ) {

  /* Setup */
  setSourcePPM( 13, 7, 201, 9, 21, 31 );

  /* Stimulus */
  const PPM& ppm_orig_const = mPPM;
  const PPM& ppm_gray_const = mFilteredPPM;
  ppm_orig_const.grayFromBlue( mFilteredPPM );

  /* Comparison */
  EXPECT_EQ( mHeight, ppm_gray_const.getHeight( ) );
  EXPECT_EQ( mWidth, ppm_gray_const.getWidth( ) );
  EXPECT_EQ( mMaxColorValue, ppm_gray_const.getMaxColorValue( ) );

  /* Tear-down */
  // Done automatically
}



TEST_F( grayFromColorTest, setsGrayFromRed ) {

  /* Setup */
  // Automatic

  /* Stimulus */
  const PPM& ppm_orig_const = mPPM;
  const PPM& ppm_gray_const = mFilteredPPM;
  ppm_orig_const.grayFromRed( mFilteredPPM );

  /* Comparison */
  EXPECT_EQ( mHeight, ppm_gray_const.getHeight( ) );
  EXPECT_EQ( mWidth, ppm_gray_const.getWidth( ) );
  EXPECT_EQ( mMaxColorValue, ppm_gray_const.getMaxColorValue( ) );
  compareGrayPixels( 0 );

  /* Tear-down */
  // Done automatically
}

TEST_F( grayFromColorTest, setsGrayFromRedAgain ) {

  /* Setup */
  setSourcePPM( 13, 7, 201, 9, 21, 31 );

  /* Stimulus */
  const PPM& ppm_orig_const = mPPM;
  const PPM& ppm_gray_const = mFilteredPPM;
  ppm_orig_const.grayFromRed( mFilteredPPM );

  /* Comparison */
  EXPECT_EQ( mHeight, ppm_gray_const.getHeight( ) );
  EXPECT_EQ( mWidth, ppm_gray_const.getWidth( ) );
  EXPECT_EQ( mMaxColorValue, ppm_gray_const.getMaxColorValue( ) );
  compareGrayPixels( 0 );

  /* Tear-down */
  // Done automatically
}

TEST_F( grayFromColorTest, setsGrayFromGreen ) {

  /* Setup */
  // Automatic

  /* Stimulus */
  const PPM& ppm_orig_const = mPPM;
  const PPM& ppm_gray_const = mFilteredPPM;
  ppm_orig_const.grayFromGreen( mFilteredPPM );

  /* Comparison */
  EXPECT_EQ( mHeight, ppm_gray_const.getHeight( ) );
  EXPECT_EQ( mWidth, ppm_gray_const.getWidth( ) );
  EXPECT_EQ( mMaxColorValue, ppm_gray_const.getMaxColorValue( ) );
  compareGrayPixels( 1 );

  /* Tear-down */
  // Done automatically
}

TEST_F( grayFromColorTest, setsGrayFromGreenAgain ) {

  /* Setup */
  setSourcePPM( 13, 7, 201, 9, 21, 31 );

  /* Stimulus */
  const PPM& ppm_orig_const = mPPM;
  const PPM& ppm_gray_const = mFilteredPPM;
  ppm_orig_const.grayFromGreen( mFilteredPPM );

  /* Comparison */
  EXPECT_EQ( mHeight, ppm_gray_const.getHeight( ) );
  EXPECT_EQ( mWidth, ppm_gray_const.getWidth( ) );
  EXPECT_EQ( mMaxColorValue, ppm_gray_const.getMaxColorValue( ) );
  compareGrayPixels( 1 );

  /* Tear-down */
  // Done automatically
}

TEST_F( grayFromColorTest, setsGrayFromBlue ) {

  /* Setup */
  // Automatic

  /* Stimulus */
  const PPM& ppm_orig_const = mPPM;
  const PPM& ppm_gray_const = mFilteredPPM;
  ppm_orig_const.grayFromBlue( mFilteredPPM );

  /* Comparison */
  EXPECT_EQ( mHeight, ppm_gray_const.getHeight( ) );
  EXPECT_EQ( mWidth, ppm_gray_const.getWidth( ) );
  EXPECT_EQ( mMaxColorValue, ppm_gray_const.getMaxColorValue( ) );
  compareGrayPixels( 2 );

  /* Tear-down */
  // Done automatically
}

TEST_F( grayFromColorTest, setsGrayFromBlueAgain ) {

  /* Setup */
  setSourcePPM( 13, 7, 201, 9, 21, 31 );

  /* Stimulus */
  const PPM& ppm_orig_const = mPPM;
  const PPM& ppm_gray_const = mFilteredPPM;
  ppm_orig_const.grayFromBlue( mFilteredPPM );

  /* Comparison */
  EXPECT_EQ( mHeight, ppm_gray_const.getHeight( ) );
  EXPECT_EQ( mWidth, ppm_gray_const.getWidth( ) );
  EXPECT_EQ( mMaxColorValue, ppm_gray_const.getMaxColorValue( ) );
  compareGrayPixels( 2 );

  /* Tear-down */
  // Done automatically
}
