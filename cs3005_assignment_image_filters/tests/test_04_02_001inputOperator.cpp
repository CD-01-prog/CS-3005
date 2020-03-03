#include "PPM.h"
#include "PPM.h" // Did you #ifndef your file?

#include "gtest/gtest.h"
#include <fstream>

class PPMInputOperatorTest : public ::testing::Test {
protected:

  PPMInputOperatorTest( ) {
  }

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

  virtual void SetUp( ) {
    filename = "oneLineHeader.ppm";
    writeFile( filename );
    fin.open( filename, std::ios::binary );
    ASSERT_TRUE( static_cast< bool >( fin ) );
    /* find the length of the file */
    fin.seekg ( 0, fin.end );
    length = fin.tellg( );
    fin.seekg ( 0, fin.beg );

    fin >> ppm;
    width = ppm.getWidth( );
    height = ppm.getHeight( );
  }

  virtual void TearDown( ) {
    fin.close( );
    remove( filename.c_str( ) );
  }

  /* data members */
  std::string filename;
  std::ifstream fin;
  int width;
  int height;
  int length;
  PPM ppm;

  int expected_width;
  int expected_height;
  int expected_max_color_value;
};



TEST_F( PPMInputOperatorTest, readsFileWithOneLineHeader ) {

  /* Setup */
  // Done automatically

  /* Stimulus */
  // Done automatically

  /* Comparison */
  // None

  /* Tear-down */
  // Done automatically
}

TEST_F( PPMInputOperatorTest, readsHeight ) {

  /* Setup */
  // Done automatically

  /* Stimulus */
  // Done automatically

  /* Comparison */
  EXPECT_EQ( expected_height, ppm.getHeight( ) );

  /* Tear-down */
  // Done automatically
}

TEST_F( PPMInputOperatorTest, readsWidth ) {

  /* Setup */
  // Done automatically

  /* Stimulus */
  // Done automatically

  /* Comparison */
  EXPECT_EQ( expected_width, ppm.getWidth( ) );

  /* Tear-down */
  // Done automatically
}

TEST_F( PPMInputOperatorTest, readsMaxColorValue ) {

  /* Setup */
  // Done automatically

  /* Stimulus */
  // Done automatically

  /* Comparison */
  EXPECT_EQ( expected_max_color_value, ppm.getMaxColorValue( ) );

  /* Tear-down */
  // Done automatically
}

TEST_F( PPMInputOperatorTest, doesNotReadPastTheEnd ) {

  /* Setup */
  // Done automatically

  /* Stimulus */
  // Done automatically

  /* Comparison */
  EXPECT_EQ( false, fin.eof( ) ); // should not have read beyond the end of the file

  /* Tear-down */
  // Done automatically
}

TEST_F( PPMInputOperatorTest, readsToTheEnd ) {

  /* Setup */
  // Done automatically

  /* Stimulus */
  // Done automatically

  /* Comparison */
  EXPECT_EQ( length, fin.tellg( ) ); // should have read everything in the file.

  /* Tear-down */
  // Done automatically
}

TEST_F( PPMInputOperatorTest, doesNotFailToRead ) {

  /* Setup */
  // Done automatically

  /* Stimulus */
  // Done automatically

  /* Comparison */
  EXPECT_EQ( false, fin.fail( ) ); // should not have any errors

  /* Tear-down */
  // Done automatically
}

TEST_F( PPMInputOperatorTest, readsFirstPixel ) {

  /* Setup */
  // Done automatically

  /* Stimulus */
  // Done automatically

  /* Comparison */
  EXPECT_EQ( 0, ppm.getChannel( 0, 0, 0 ) ); // red
  EXPECT_EQ( 1, ppm.getChannel( 0, 0, 1 ) ); // green
  EXPECT_EQ( 2, ppm.getChannel( 0, 0, 2 ) ); // blue

  /* Tear-down */
  // Done automatically
}

TEST_F( PPMInputOperatorTest, readsLastPixel ) {

  /* Setup */
  // Done automatically

  /* Stimulus */
  // Done automatically

  /* Comparison */
  int v;
  v = ( ( (height-1) * width + (width-1) ) * 3 + 0 ) % ( expected_max_color_value + 1 );
  EXPECT_EQ( v, ppm.getChannel( height-1, width-1, 0 ) ); // red
  v = ( ( (height-1) * width + (width-1) ) * 3 + 1 ) % ( expected_max_color_value + 1 );
  EXPECT_EQ( v, ppm.getChannel( height-1, width-1, 1 ) ); // green
  v = ( ( (height-1) * width + (width-1) ) * 3 + 2 ) % ( expected_max_color_value + 1 );
  EXPECT_EQ( v, ppm.getChannel( height-1, width-1, 2 ) ); // blue

  /* Tear-down */
  // Done automatically
}

TEST_F( PPMInputOperatorTest, readsUnsignedChar ) {

  /* Setup */
  // Done automatically

  /* Stimulus */
  // Done automatically

  /* Comparison */
  EXPECT_EQ( 255, ppm.getChannel( 6, 7, 0 ) );

  /* Tear-down */
  // Done automatically
}


class PPMInputOperatorMultilineHeaderTest : public ::testing::Test {
protected:

  void writeFile( const std::string& filename ) {
    int width = 11;
    int height = 9;
    int max_value = 255;
    int i, j, k, v;
    unsigned char c;
    std::ofstream fout( filename, std::ios::binary );
    fout << "P6\n" << width << "\n" << height << "\n" << max_value << "\n";
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

  virtual void SetUp( ) {
    filename = "multiLineHeader.ppm";
    writeFile( filename );
    fin.open( filename, std::ios::binary );
    ASSERT_TRUE( static_cast< bool >( fin ) );
    /* find the length of the file */
    fin.seekg ( 0, fin.end );
    length = fin.tellg( );
    fin.seekg ( 0, fin.beg );
    fin >> ppm;
  }

  virtual void TearDown( ) {
    fin.close( );
    remove( filename.c_str( ) );
  }

  /* data members */
  std::string filename;
  std::ifstream fin;
  int length;
  PPM ppm;

  int expected_width;
  int expected_height;
  int expected_max_color_value;
};



TEST_F( PPMInputOperatorMultilineHeaderTest, readsFileWithMultiLineHeader ) {

  /* Setup */
  // Done automatically

  /* Stimulus */
  // Done automatically

  /* Comparison */
  // None

  /* Tear-down */
  // Done automatically
}

TEST_F( PPMInputOperatorMultilineHeaderTest, readsHeight ) {

  /* Setup */
  // Done automatically

  /* Stimulus */
  // Done automatically

  /* Comparison */
  EXPECT_EQ( expected_height, ppm.getHeight( ) );

  /* Tear-down */
  // Done automatically
}

TEST_F( PPMInputOperatorMultilineHeaderTest, readsWidth ) {

  /* Setup */
  // Done automatically

  /* Stimulus */
  // Done automatically

  /* Comparison */
  EXPECT_EQ( expected_width, ppm.getWidth( ) );

  /* Tear-down */
  // Done automatically
}

TEST_F( PPMInputOperatorMultilineHeaderTest, readsMaxColorValue ) {

  /* Setup */
  // Done automatically

  /* Stimulus */
  // Done automatically

  /* Comparison */
  EXPECT_EQ( expected_max_color_value, ppm.getMaxColorValue( ) );

  /* Tear-down */
  // Done automatically
}

TEST_F( PPMInputOperatorMultilineHeaderTest, doesNotReadPastTheEnd ) {

  /* Setup */
  // Done automatically

  /* Stimulus */
  // Done automatically

  /* Comparison */
  EXPECT_EQ( false, fin.eof( ) ); // should not have read beyond the end of the file

  /* Tear-down */
  // Done automatically
}

TEST_F( PPMInputOperatorMultilineHeaderTest, readsToTheEnd ) {

  /* Setup */
  // Done automatically

  /* Stimulus */
  // Done automatically

  /* Comparison */
  EXPECT_EQ( length, fin.tellg( ) ); // should have read everything in the file.

  /* Tear-down */
  // Done automatically
}


TEST_F( PPMInputOperatorMultilineHeaderTest, doesNotFailToRead ) {

  /* Setup */
  // Done automatically

  /* Stimulus */
  // Done automatically

  /* Comparison */
  EXPECT_EQ( false, fin.fail( ) ); // should not have any errors

  /* Tear-down */
  // Done automatically
}

TEST_F( PPMInputOperatorMultilineHeaderTest, readsFirstPixel ) {

  /* Setup */
  // Done automatically

  /* Stimulus */
  // Done automatically

  /* Comparison */
  EXPECT_EQ( 0, ppm.getChannel( 0, 0, 0 ) ); // red
  EXPECT_EQ( 1, ppm.getChannel( 0, 0, 1 ) ); // green
  EXPECT_EQ( 2, ppm.getChannel( 0, 0, 2 ) ); // blue

  /* Tear-down */
  // Done automatically
}

TEST_F( PPMInputOperatorMultilineHeaderTest, readsLastPixel ) {

  /* Setup */
  // Done automatically

  /* Stimulus */
  // Done automatically

  /* Comparison */
  int v;
  int height = expected_height;
  int width = expected_width;
  v = ( ( (height-1) * width + (width-1) ) * 3 + 0 ) % ( expected_max_color_value + 1 );
  EXPECT_EQ( v, ppm.getChannel( height-1, width-1, 0 ) ); // red
  v = ( ( (height-1) * width + (width-1) ) * 3 + 1 ) % ( expected_max_color_value + 1 );
  EXPECT_EQ( v, ppm.getChannel( height-1, width-1, 1 ) ); // green
  v = ( ( (height-1) * width + (width-1) ) * 3 + 2 ) % ( expected_max_color_value + 1 );
  EXPECT_EQ( v, ppm.getChannel( height-1, width-1, 2 ) ); // blue

  /* Tear-down */
  // Done automatically
}

TEST_F( PPMInputOperatorMultilineHeaderTest, readsUnsignedChar ) {

  /* Setup */
  // Done automatically

  /* Stimulus */
  // Done automatically

  /* Comparison */
  EXPECT_EQ( 255, ppm.getChannel( 7, 8, 0 ) );

  /* Tear-down */
  // Done automatically
}
