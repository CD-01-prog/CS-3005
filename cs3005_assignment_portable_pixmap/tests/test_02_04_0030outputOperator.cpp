#include "PPM.h"
#include "PPM.h" // Did you #ifndef your file?

#include "gtest/gtest.h"
#include <fstream>
#include <cstdio>

class PPMOutputOperatorTest : public ::testing::Test {
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
    expected_width = width;
    expected_height = height;
    expected_max_color_value = max_value;
  }

  void readFile( const std::string& filename, PPM& ppm ) {
    std::ifstream fin( filename, std::ios::binary );
    unsigned char new_line;
    fin >> mMagic >> mWidth >> mHeight >> mMaxColorValue;
    EXPECT_EQ( "P6", mMagic );
    EXPECT_LT( 0, mHeight );
    EXPECT_LT( 0, mWidth );
    EXPECT_LT( 0, mMaxColorValue );
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
    in_filename = "oneLineHeader.ppm";
    writeFile( in_filename );

    fin.open( in_filename, std::ios::binary );
    ASSERT_TRUE( static_cast< bool >( fin ) );

    out_filename = "oneLineHeaderCopy.ppm";
    fout.open( out_filename, std::ios::binary );
    ASSERT_TRUE( static_cast< bool >( fout ) );

    /* find the length of the file */
    fin.seekg ( 0, fin.end );
    length = fin.tellg( );
    fin.seekg ( 0, fin.beg );
    fin.close( );

    /* read the PPM from file */
    readFile( in_filename, ppm );
  }

  virtual void TearDown( ) {
    fout.close( );
    remove( out_filename.c_str( ) );
    remove( in_filename.c_str( ) );
  }

  /* data members */
  std::string in_filename;
  std::string out_filename;
  std::ifstream fin;
  std::ofstream fout;
  int length;
  PPM ppm;

  int expected_width;
  int expected_height;
  int expected_max_color_value;

  /* image read from file */
  std::string mMagic;
  int mWidth, mHeight, mMaxColorValue;
};



TEST_F( PPMOutputOperatorTest, writesFile ) {

  /* Setup */
  // Done automatically

  /* Stimulus */
  // A compiler error here means you have not declared the operator<< correctly.
  fout << ppm;

  /* Comparison */
  // None

  /* Tear-down */
  // Done automatically
}

TEST_F( PPMOutputOperatorTest, writesTheWholeFile ) {

  /* Setup */
  // Done automatically

  /* Stimulus */
  fout << ppm;

  /* Comparison */
  {
    fout.flush( );
    fout.close( );
    std::ifstream size_test( out_filename, std::ios::binary );
    ASSERT_TRUE( static_cast< bool >( size_test ) );
    size_test.seekg ( 0, size_test.end );
    int actual_length = size_test.tellg( );
    size_test.seekg ( 0, size_test.beg );

    EXPECT_EQ( length, actual_length ); // should have written everything in the file.
    size_test.close( );
  }

  /* Tear-down */
  // Done automatically
}

TEST_F( PPMOutputOperatorTest, writesP6 ) {

  /* Setup */
  // Done automatically

  /* Stimulus */
  fout << ppm;
  fout.close( );
  {
    std::ifstream f( out_filename );
    std::string s;
    f >> s;
    f.close( );
    EXPECT_EQ( "P6", s );
  }

  /* Comparison */

  /* Tear-down */
  // Done automatically
}




TEST_F( PPMOutputOperatorTest, doesNotFailToWrite ) {

  /* Setup */
  // Done automatically

  /* Stimulus */
  fout << ppm;

  /* Comparison */
  EXPECT_EQ( false, fout.fail( ) ); // should not have any errors

  /* Tear-down */
  // Done automatically
}


TEST_F( PPMOutputOperatorTest, writesUnsignedChar ) {

  /* Setup */
  // Done automatically

  /* Stimulus */
  fout << ppm;
  fout.flush( );
  fout.close( );

  PPM ppm_tmp;
  readFile( out_filename, ppm_tmp );

  /* Comparison */
  EXPECT_EQ( 255, ppm_tmp.getChannel( 6, 7, 0 ) );

  /* Tear-down */
  // Done automatically
}


class CustomPPMOutputOperatorTest : public ::testing::Test {
protected:

  void readFile( const std::string& filename, PPM& ppm ) {
    std::ifstream fin( filename, std::ios::binary );
    unsigned char new_line;
    fin >> mMagic >> mWidth >> mHeight >> mMaxColorValue;
    EXPECT_EQ( "P6", mMagic );
    EXPECT_LT( 0, mHeight );
    EXPECT_LT( 0, mWidth );
    EXPECT_LT( 0, mMaxColorValue );
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
    ppm_original.setWidth( 10 );
    ppm_original.setHeight( 20 );
    ppm_original.setMaxColorValue( 255 );
    int i, j, k, v;
    for ( i = 0 ; i < ppm_original.getHeight( ) ; i++ ) {
      for ( j = 0 ; j < ppm_original.getWidth( ) ; j++ ) {
        for ( k = 0 ; k < 3 ; k++ ) {
          v = ( i * j * k + i + j + k ) % 256;
          ppm_original.setChannel( i, j, k, v );
        }
      }
    }

    out_filename = "custom_file.ppm";
    fout.open( out_filename, std::ios::binary );
    ASSERT_TRUE( static_cast< bool >( fout ) );
    fout << ppm_original;
    fout.close( );

    readFile( out_filename, ppm_copy );
  }

  virtual void TearDown( ) {
    remove( out_filename.c_str( ) );
  }

  /* data members */
  std::string out_filename;
  std::ifstream fin;
  std::ofstream fout;
  PPM ppm_original, ppm_copy;

  /* image read from file */
  std::string mMagic;
  int mWidth, mHeight, mMaxColorValue;
};

TEST_F( CustomPPMOutputOperatorTest, preservesWidth ) {

  /* Setup */
  // Done automatically

  /* Stimulus */
  // Done automatically

  /* Comparison */
  EXPECT_EQ( ppm_original.getWidth( ), ppm_copy.getWidth( ) );

  /* Tear-down */
  // Done automatically
}

TEST_F( CustomPPMOutputOperatorTest, preservesHeight ) {

  /* Setup */
  // Done automatically

  /* Stimulus */
  // Done automatically

  /* Comparison */
  EXPECT_EQ( ppm_original.getHeight( ), ppm_copy.getHeight( ) );

  /* Tear-down */
  // Done automatically
}

TEST_F( CustomPPMOutputOperatorTest, preservesMaxColorValue ) {

  /* Setup */
  // Done automatically

  /* Stimulus */
  // Done automatically

  /* Comparison */
  EXPECT_EQ( ppm_original.getMaxColorValue( ), ppm_copy.getMaxColorValue( ) );

  /* Tear-down */
  // Done automatically
}


TEST_F( CustomPPMOutputOperatorTest, preservesChannelValues ) {

  /* Setup */
  // Done automatically

  /* Stimulus */
  // Done automatically

  /* Comparison */
  int i, j, k;
  for ( i = 0; i < ppm_original.getHeight( ); i++ ) {
    for ( j = 0; j < ppm_original.getWidth( ); j++ ) {
      for ( k = 0; k < 3; k++ ) {
        EXPECT_EQ( ppm_original.getChannel( i, j, k ), ppm_copy.getChannel( i, j, k ) );
      }
    }
  }

  /* Tear-down */
  // Done automatically
}
