#include "image_menu.h"
#include "image_menu.h" // Did you #ifndef your file?

#include "gtest/gtest.h"
#include <fstream>
#include <string>
#include <cmath>

class takeActionRotateColorFilterTest : public ::testing::Test {
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
  }

  virtual void TearDown( ) {
  }

  /* data members */
  int mHeight, mWidth, mMaxColorValue;
  std::string mPrompt;
  std::string mChoice;
  std::stringstream mInputStream;
  std::stringstream mOutputStream;
  PPM mPPM;
  PPM input_image1, input_image2, output_image;
};

TEST_F( takeActionRotateColorFilterTest, createsTestPattern ) {

  /* Setup */
  mChoice = "rotate-color";

  /* Stimulus */
  input_image1 = mPPM;
  takeAction( mInputStream, mOutputStream, mChoice, input_image1, input_image2, output_image );
  const PPM& ppm_original_const = mPPM;
  const PPM& ppm_const = output_image;


  /* Comparison */
  EXPECT_EQ( mPrompt, mOutputStream.str( ) );
  EXPECT_EQ( mHeight, ppm_const.getHeight( ) );
  EXPECT_EQ( mWidth, ppm_const.getWidth( ) );
  EXPECT_EQ( mMaxColorValue, ppm_const.getMaxColorValue( ) );

  int row, column;
  for( row = 0; row < mHeight; row++ ) {
    for( column = 0; column < mWidth; column++ ) {
      EXPECT_EQ( ppm_original_const.getChannel( row, column, 1 ), ppm_const.getChannel( row, column, 0 ) )
        << "row: " << row << " column: " << column << " channel: " << 0;
      EXPECT_EQ( ppm_original_const.getChannel( row, column, 2 ), ppm_const.getChannel( row, column, 1 ) )
        << "row: " << row << " column: " << column << " channel: " << 1;
      EXPECT_EQ( ppm_original_const.getChannel( row, column, 0 ), ppm_const.getChannel( row, column, 2 ) )
        << "row: " << row << " column: " << column << " channel: " << 2;
    }
  }

  /* Tear-down */
  // Done automatically
}
