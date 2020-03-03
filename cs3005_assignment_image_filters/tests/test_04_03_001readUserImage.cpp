#include "image_menu.h"
#include "image_menu.h" // Did you #ifndef your file?
#include "PPM.h"
#include "PPM.h" // Did you #ifndef your file?

#include "gtest/gtest.h"
#include <fstream>
#include <string>

class readUserImageTest : public ::testing::Test {
protected:

  void writeFile( const std::string& filename ) {
    int width = 13;
    int height = 7;
    int max_value = 255;
    int i, j, k, v;
    unsigned char c;
    std::ofstream fout( filename, std::ios::binary );
    fout << "P6 " << width << " " << height << " " << max_value << "\n";
    for ( i = 0; i < height ; i++ ) {
      for ( j = 0; j < width ; j++ ) {
        for ( k = 0; k < 3 ; k++ ) {
          v = ( ( i * width + j ) * 3 + k ) % ( max_value + 1 );
          c = ( unsigned char )v;
          fout.write( (char *)&c, 1 );
        }
      }
    }
    fout.close();
    mHeight = height;
    mWidth = width;
    mMaxColorValue = max_value;
  }

  void compareChannels( ) {
    const PPM& ppm_orig_const = mPPM;

    int row, column, channel;
    int v;
    for( row = 0; row < mHeight; row++ ) {
      for( column = 0; column < mWidth; column++ ) {
        for( channel = 0; channel < 3; channel++ ) {
          v = ( ( row * mWidth + column ) * 3 + channel ) % ( mMaxColorValue + 1 );

          EXPECT_EQ( v, ppm_orig_const.getChannel( row, column, channel ) )
            << "row: " << row << "  column: " << column << "  channel: " << channel;
        }
      }
    }
  }

  virtual void SetUp( ) {
    mTmpFile = "tmp_file.ppm";
    mInputStream.str( "" );
    mOutputStream.str( "" );
    writeFile( mTmpFile );
  }

  virtual void TearDown( ) {
    remove( mTmpFile.c_str( ) );
  }

  /* data members */
  std::string mTmpFile;
  std::stringstream mInputStream;
  std::stringstream mOutputStream;
  std::string mExpectedOutput;
  PPM mPPM;
  int mHeight;
  int mWidth;
  int mMaxColorValue;
};


TEST_F( readUserImageTest, displaysPrompt ) {

  /* Setup */
  mInputStream.str( mTmpFile.c_str( ) );
  mExpectedOutput = "Input filename? ";

  /* Stimulus */
  readUserImage( mInputStream, mOutputStream, mPPM );

  /* Comparison */
  EXPECT_EQ( mExpectedOutput, mOutputStream.str( ) );

  /* Tear-down */
  // Done automatically
}

TEST_F( readUserImageTest, readsPPMFromFile ) {

  /* Setup */
  mInputStream.str( mTmpFile.c_str( ) );
  mExpectedOutput = "Input filename? ";

  /* Stimulus */
  readUserImage( mInputStream, mOutputStream, mPPM );
  const PPM& ppm_const = mPPM;

  /* Comparison */
  EXPECT_EQ( mHeight, ppm_const.getHeight( ) );
  EXPECT_EQ( mWidth, ppm_const.getWidth( ) );
  EXPECT_EQ( mMaxColorValue, ppm_const.getMaxColorValue( ) );

  /* Tear-down */
  // Done automatically
}
