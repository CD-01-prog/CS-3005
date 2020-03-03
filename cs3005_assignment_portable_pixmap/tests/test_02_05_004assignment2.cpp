#include "image_menu.h"
#include "image_menu.h" // Did you #ifndef your file?
#include "PPM.h"
#include "PPM.h" // Did you #ifndef your file?

#include "gtest/gtest.h"
#include <fstream>
#include <string>

class writeUserImageTest : public ::testing::Test {
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
  }

  void readFile( const std::string& filename, PPM& ppm ) {
    std::ifstream fin( filename, std::ios::binary );
    unsigned char new_line;
    fin >> mMagic >> mWidth >> mHeight >> mMaxColorValue;
    EXPECT_EQ( "P6", mMagic );
    EXPECT_LT( 0, mHeight );
    EXPECT_LT( 0, mWidth );
    EXPECT_LE( 0, mMaxColorValue );
    EXPECT_GE( 255, mMaxColorValue );

    fin.read( (char *)&new_line, 1 );
    EXPECT_EQ( '\n', (int)new_line );
    ppm.setHeight( mHeight );
    ppm.setWidth( mWidth );
    ppm.setMaxColorValue( mMaxColorValue );

    int row, column, channel;
    unsigned char v;
    for ( row = 0; row < mHeight ; row++ ) {
      for ( column = 0; column < mWidth ; column++ ) {
        for ( channel = 0; channel < 3 ; channel++ ) {
          fin.read( (char*)&v, 1 );
          EXPECT_LE( 0, ( int )v );
          EXPECT_GE( mMaxColorValue, ( int )v );
          ppm.setChannel( row, column, channel, ( int ) v );
        }
      }
    }
    fin.close();
  }

  virtual void SetUp( ) {
    mTmpFile = "tmp_file.ppm";
    mInputStream.str( "" );
    mOutputStream.str( "" );
    writeFile( mTmpFile );
    readFile( mTmpFile, mPPM );
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

  /* image read from file */
  std::string mMagic;
  int mWidth, mHeight, mMaxColorValue;
};


TEST_F( writeUserImageTest, displaysPrompt ) {

  /* Setup */
  mInputStream.str( "user_image.ppm" );
  mExpectedOutput = "Output filename? ";

  /* Stimulus */
  writeUserImage( mInputStream, mOutputStream, mPPM );

  /* Comparison */
  EXPECT_EQ( mExpectedOutput, mOutputStream.str( ) );

  /* Tear-down */
  // Done automatically
}

TEST_F( writeUserImageTest, createsFile ) {

  /* Setup */
  mInputStream.str( "user_image.ppm" );
  mExpectedOutput = "Output filename? ";

  /* Stimulus */
  writeUserImage( mInputStream, mOutputStream, mPPM );

  /* Comparison */
  std::ifstream fin( "user_image.ppm", std::ios::binary );
  EXPECT_TRUE( static_cast< bool >( fin ) );
  fin.close( );
  /* Tear-down */
  // Done automatically
}

TEST_F( writeUserImageTest, createsCorrectFileContent ) {

  /* Setup */
  mInputStream.str( "user_image.ppm" );
  mExpectedOutput = "Output filename? ";

  /* Stimulus */
  writeUserImage( mInputStream, mOutputStream, mPPM );

  /* Comparison */
  PPM ppm_tmp;
  readFile( "user_image.ppm", ppm_tmp );
  EXPECT_EQ( mPPM.getHeight( ), ppm_tmp.getHeight( ) );
  EXPECT_EQ( mPPM.getWidth( ), ppm_tmp.getWidth( ) );
  EXPECT_EQ( mPPM.getMaxColorValue( ), ppm_tmp.getMaxColorValue( ) );

  /* Tear-down */
  // Done automatically
}


class assignment2Test : public ::testing::Test {
protected:

  void readFile( const std::string& filename, PPM& ppm ) {
    std::ifstream fin( filename, std::ios::binary );
    unsigned char new_line;
    fin >> mMagic >> mWidth >> mHeight >> mMaxColorValue;
    EXPECT_EQ( "P6", mMagic );
    EXPECT_LT( 0, mHeight );
    EXPECT_LT( 0, mWidth );
    EXPECT_LE( 0, mMaxColorValue );
    EXPECT_GE( 255, mMaxColorValue );

    fin.read( (char *)&new_line, 1 );
    EXPECT_EQ( '\n', (int)new_line );
    ppm.setHeight( mHeight );
    ppm.setWidth( mWidth );
    ppm.setMaxColorValue( mMaxColorValue );

    int row, column, channel;
    unsigned char v;
    for ( row = 0; row < mHeight ; row++ ) {
      for ( column = 0; column < mWidth ; column++ ) {
        for ( channel = 0; channel < 3 ; channel++ ) {
          fin.read( (char*)&v, 1 );
          EXPECT_LE( 0, ( int )v );
          EXPECT_GE( mMaxColorValue, ( int )v );
          ppm.setChannel( row, column, channel, ( int ) v );
        }
      }
    }
    fin.close();
  }

  virtual void SetUp( ) {
    mInputStream.str( "" );
    mOutputStream.str( "" );
    mPrompts = "Image height? ";
    mPrompts += "Image width? ";
    mPrompts += "Output filename? ";
  }

  virtual void TearDown( ) {
  }

  /* data members */
  std::stringstream mInputStream;
  std::stringstream mOutputStream;
  int mResponse;
  std::string mPrompts;
  std::string mOutput;

  /* image read from file */
  std::string mMagic;
  int mWidth, mHeight, mMaxColorValue;
};


TEST_F( assignment2Test, displaysPrompts ) {

  /* Setup */
  mInputStream.str( "1 1 test.ppm" );

  /* Stimulus */
  mResponse = assignment2( mInputStream, mOutputStream );

  /* Comparison */
  EXPECT_EQ( mPrompts, mOutputStream.str( ) );

  /* Tear-down */
  // Done automatically
}

TEST_F( assignment2Test, givesReturnValue ) {

  /* Setup */
  mInputStream.str( "1 1 test.ppm" );

  /* Stimulus */
  mResponse = assignment2( mInputStream, mOutputStream );

  /* Comparison */
  EXPECT_EQ( 0, mResponse );

  /* Tear-down */
  // Done automatically
}


TEST_F( assignment2Test, savesFile ) {

  /* Setup */
  mInputStream.str( "1 1 test.ppm" );

  /* Stimulus */
  mResponse = assignment2( mInputStream, mOutputStream );

  /* Comparison */
  std::ifstream fin( "test.ppm", std::ios::binary );
  EXPECT_TRUE( static_cast< bool >( fin ) );
  fin.close( );

  /* Tear-down */
  // Done automatically
}

TEST_F( assignment2Test, savesCorrectlySizedFile1 ) {

  /* Setup */
  mInputStream.str( "1 1 test.ppm" );

  /* Stimulus */
  mResponse = assignment2( mInputStream, mOutputStream );
  PPM ppm_tmp;
  readFile( "test.ppm", ppm_tmp );

  /* Comparison */
  EXPECT_EQ( 1, ppm_tmp.getHeight( ) );
  EXPECT_EQ( 1, ppm_tmp.getWidth( ) );
  EXPECT_EQ( mPrompts, mOutputStream.str( ) );
  EXPECT_EQ( 0, mResponse );

  /* Tear-down */
  // Done automatically
}


TEST_F( assignment2Test, savesCorrectlySizedFile2 ) {

  /* Setup */
  mInputStream.str( "13 23 other_test.ppm" );

  /* Stimulus */
  mResponse = assignment2( mInputStream, mOutputStream );
  PPM ppm_tmp;
  readFile( "other_test.ppm", ppm_tmp );

  /* Comparison */
  EXPECT_EQ( 13, ppm_tmp.getHeight( ) );
  EXPECT_EQ( 23, ppm_tmp.getWidth( ) );
  EXPECT_EQ( mPrompts, mOutputStream.str( ) );
  EXPECT_EQ( 0, mResponse );

  /* Tear-down */
  // Done automatically
}

TEST_F( assignment2Test, savesCorrectMaxColorValue ) {

  /* Setup */
  mInputStream.str( "113 22 yet_other_test.ppm" );

  /* Stimulus */
  mResponse = assignment2( mInputStream, mOutputStream );
  PPM ppm_tmp;
  readFile( "yet_other_test.ppm", ppm_tmp );

  /* Comparison */
  EXPECT_EQ( 113, ppm_tmp.getHeight( ) );
  EXPECT_EQ( 22, ppm_tmp.getWidth( ) );
  EXPECT_EQ( (113+22)/3, ppm_tmp.getMaxColorValue( ) );
  EXPECT_EQ( mPrompts, mOutputStream.str( ) );
  EXPECT_EQ( 0, mResponse );

  /* Tear-down */
  // Done automatically
}

TEST_F( assignment2Test, savesCorrectChannelValues ) {

  /* Setup */
  mInputStream.str( "7 11 test.ppm" );

  /* Stimulus */
  mResponse = assignment2( mInputStream, mOutputStream );
  PPM ppm_tmp;
  readFile( "test.ppm", ppm_tmp );

  /* Comparison */
  EXPECT_EQ( 7, ppm_tmp.getHeight( ) );
  EXPECT_EQ( 11, ppm_tmp.getWidth( ) );
  EXPECT_EQ( 6, ppm_tmp.getMaxColorValue( ) );
  EXPECT_EQ( mPrompts, mOutputStream.str( ) );
  EXPECT_EQ( 0, mResponse );
  int row, column;
  int expected_red, expected_green, expected_blue;
  for( row = 0; row < 7; row++ ) {
    for( column = 0; column < 11; column++ ) {
      expected_red = ( row < 3 ) ? 0 : 6;
      expected_green = ( row + column ) % 7;
      expected_blue = ( column < 5 ) ? 0 : 6;
      EXPECT_EQ( expected_red, ppm_tmp.getChannel( row, column, 0 ) )
        << " row: " << row << " column: " << column << " red" << std::endl;
      EXPECT_EQ( expected_green, ppm_tmp.getChannel( row, column, 1 ) )
        << " row: " << row << " column: " << column << " green" << std::endl;
      EXPECT_EQ( expected_blue, ppm_tmp.getChannel( row, column, 2 ) )
        << " row: " << row << " column: " << column << " blue" << std::endl;
    }
  }

  /* Tear-down */
  // Done automatically
}
