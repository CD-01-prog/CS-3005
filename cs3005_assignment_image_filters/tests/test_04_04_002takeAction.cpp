#include "image_menu.h"
#include "image_menu.h" // Did you #ifndef your file?

#include "gtest/gtest.h"
#include <fstream>
#include <string>
#include <cmath>

class takeActionTest : public ::testing::Test {
protected:

  void setSourcePPM( int height, int width, int max_color_value, int red, int green, int blue ) {
    // save values
    mHeight = height;
    mWidth = width;
    mMaxColorValue = max_color_value;
    mRed = red;
    mGreen = green;
    mBlue = blue;
    mExpectedColorimetricValues.resize( mHeight * mWidth );

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
        mExpectedColorimetricValues[ row*mWidth + column ] = 0.2126*red + 0.7152*green + 0.0722*blue;
      }
    }
  }

  void clearDestinationPPM( ) {
    mFilteredPPM.setHeight( 0 );
    mFilteredPPM.setWidth( 0 );
    mFilteredPPM.setMaxColorValue( 0 );
  }

  void compareLinearColorimetricValues( ) {
    const PPM& ppm_orig_const = mPPM;

    int row, column, channel;
    for( row = 0; row < mHeight; row++ ) {
      for( column = 0; column < mWidth; column++ ) {
        for( channel = 0; channel < 3; channel++ ) {
          EXPECT_NEAR( mExpectedColorimetricValues[ row*mWidth+column ], ppm_orig_const.linearColorimetricPixelValue( row, column ), 0.001 )
            << "row: " << row << "  column: " << column;
        }
      }
    }
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
    int width, height, mcv;
    std::string magic;
    fin >> magic >> width >> height >> mcv;
    EXPECT_EQ( "P6", magic );
    EXPECT_LT( 0, height );
    EXPECT_LT( 0, width );
    EXPECT_LE( 0, mcv );
    EXPECT_GE( 255, mcv );

    fin.read( (char *)&new_line, 1 );
    EXPECT_EQ( '\n', (int)new_line );
    ppm.setHeight( height );
    ppm.setWidth( width );
    ppm.setMaxColorValue( mcv );

    int row, column, channel;
    unsigned char v;
    for ( row = 0; row < height ; row++ ) {
      for ( column = 0; column < width ; column++ ) {
        for ( channel = 0; channel < 3 ; channel++ ) {
          fin.read( (char*)&v, 1 );
          EXPECT_LE( 0, ( int )v );
          EXPECT_GE( mcv, ( int )v );
          ppm.setChannel( row, column, channel, ( int ) v );
        }
      }
    }
    fin.close();
  }


  virtual void SetUp( ) {
    mHeight = 35;
    mWidth = 45;
    input_image1.setHeight( mHeight );
    input_image1.setWidth( mWidth );
    input_image1.setMaxColorValue( 137 );
    int row, column;
    for( row = 0; row < mHeight; row++ ) {
      for( column = 0; column < mWidth; column++ ) {
        input_image1.setPixel( row, column, 100, 101, 102 );
      }
    }

  }

  virtual void TearDown( ) {
    mPPM.setHeight( 0 );
    mFilteredPPM.setHeight( 0 );
    input_image1.setHeight( 0 );
    input_image2.setHeight( 0 );
    output_image.setHeight( 0 );
  }

  /* data members */
  std::string mPrompt;
  std::stringstream mInputStream;
  std::stringstream mOutputStream;
  std::string mChoice;
  PPM input_image1, input_image2, output_image;
  int mRed, mGreen, mBlue;
  int mHeight, mWidth, mMaxColorValue;
  std::vector< double > mExpectedColorimetricValues;

  PPM mPPM;
  PPM mFilteredPPM;
  int expected_height, expected_width, expected_max_color_value;
};


TEST_F( takeActionTest, doesQuit ) {

  /* Setup */
  mPrompt = "";
  mChoice = "quit";
  mInputStream.str( "" );

  /* Stimulus */
  takeAction( mInputStream, mOutputStream, mChoice, input_image1, input_image2, output_image );

  /* Comparison */
  EXPECT_EQ( mPrompt, mOutputStream.str( ) );

  /* Tear-down */
  // Done automatically
}


TEST_F( takeActionTest, doesBox ) {

  /* Setup */
  mPrompt = "Top Row? Left Column? Bottom Row? Right Column? Red? Green? Blue? ";
  mChoice = "box";
  mRed = 88;
  mGreen = 44;
  mBlue = 55;
  mInputStream.str( "11 7 19 13 88 44 55" );

  /* Stimulus */
  takeAction( mInputStream, mOutputStream, mChoice, input_image1, input_image2, output_image );
  const PPM& ppm_const = input_image1;

  /* Comparison */
  EXPECT_EQ( mPrompt, mOutputStream.str( ) );

  int row, column;
  for( row = 0; row < mHeight; row++ ) {
    for( column = 0; column < mWidth; column++ ) {
      if( row < 11 || row > 19 || column < 7 || column > 13 ) {
        EXPECT_EQ( 100, ppm_const.getChannel( row, column, 0 ) )
          << "row: " << row << " column: " << column << " channel: " << 0;
        EXPECT_EQ( 101, ppm_const.getChannel( row, column, 1 ) )
          << "row: " << row << " column: " << column << " channel: " << 1;
        EXPECT_EQ( 102, ppm_const.getChannel( row, column, 2 ) )
          << "row: " << row << " column: " << column << " channel: " << 2;
      } else {
        EXPECT_EQ( mRed, ppm_const.getChannel( row, column, 0 ) )
          << "row: " << row << " column: " << column << " channel: " << 0;
        EXPECT_EQ( mGreen, ppm_const.getChannel( row, column, 1 ) )
          << "row: " << row << " column: " << column << " channel: " << 1;
        EXPECT_EQ( mBlue, ppm_const.getChannel( row, column, 2 ) )
          << "row: " << row << " column: " << column << " channel: " << 2;
      }
    }
  }

  /* Tear-down */
  // Done automatically

}

TEST_F( takeActionTest, doesCircle ) {

  /* Setup */
  mPrompt = "Center Row? Center Column? Radius? Red? Green? Blue? ";
  mChoice = "circle";
  mRed = 88;
  mGreen = 44;
  mBlue = 55;
  mInputStream.str( "25 15 5 88 44 55" );

  /* Stimulus */
  takeAction( mInputStream, mOutputStream, mChoice, input_image1, input_image2, output_image );
  const PPM& ppm_const = input_image1;

  /* Comparison */
  EXPECT_EQ( mPrompt, mOutputStream.str( ) );

  int row, column;
  for( row = 0; row < mHeight; row++ ) {
    for( column = 0; column < mWidth; column++ ) {
      if( ( (row-25)*(row-25) + (column-15)*(column-15) ) > 25 ) {
        EXPECT_EQ( 100, ppm_const.getChannel( row, column, 0 ) )
          << "row: " << row << " column: " << column << " channel: " << 0;
        EXPECT_EQ( 101, ppm_const.getChannel( row, column, 1 ) )
          << "row: " << row << " column: " << column << " channel: " << 1;
        EXPECT_EQ( 102, ppm_const.getChannel( row, column, 2 ) )
          << "row: " << row << " column: " << column << " channel: " << 2;
      } else {
        EXPECT_EQ( mRed, ppm_const.getChannel( row, column, 0 ) )
          << "row: " << row << " column: " << column << " channel: " << 0;
        EXPECT_EQ( mGreen, ppm_const.getChannel( row, column, 1 ) )
          << "row: " << row << " column: " << column << " channel: " << 1;
        EXPECT_EQ( mBlue, ppm_const.getChannel( row, column, 2 ) )
          << "row: " << row << " column: " << column << " channel: " << 2;
      }
    }
  }

  /* Tear-down */
  // Done automatically

}

TEST_F( takeActionTest, doesDiamond ) {

  /* Setup */
  mPrompt = "Center Row? Center Column? Size? Red? Green? Blue? ";
  mChoice = "diamond";
  mRed = 88;
  mGreen = 44;
  mBlue = 55;
  mInputStream.str( "15 10 5 88 44 55" );

  /* Stimulus */
  takeAction( mInputStream, mOutputStream, mChoice, input_image1, input_image2, output_image );
  const PPM& ppm_const = input_image1;

  /* Comparison */
  EXPECT_EQ( mPrompt, mOutputStream.str( ) );

  int row, column;
  for( row = 0; row < mHeight; row++ ) {
    for( column = 0; column < mWidth; column++ ) {
      if( ( std::abs(row-15) + std::abs(column-10) ) > 5 ) {
        EXPECT_EQ( 100, ppm_const.getChannel( row, column, 0 ) )
          << "row: " << row << " column: " << column << " channel: " << 0;
        EXPECT_EQ( 101, ppm_const.getChannel( row, column, 1 ) )
          << "row: " << row << " column: " << column << " channel: " << 1;
        EXPECT_EQ( 102, ppm_const.getChannel( row, column, 2 ) )
          << "row: " << row << " column: " << column << " channel: " << 2;
      } else {
        EXPECT_EQ( mRed, ppm_const.getChannel( row, column, 0 ) )
          << "row: " << row << " column: " << column << " channel: " << 0;
        EXPECT_EQ( mGreen, ppm_const.getChannel( row, column, 1 ) )
          << "row: " << row << " column: " << column << " channel: " << 1;
        EXPECT_EQ( mBlue, ppm_const.getChannel( row, column, 2 ) )
          << "row: " << row << " column: " << column << " channel: " << 2;
      }
    }
  }

  /* Tear-down */
  // Done automatically

}



TEST_F( takeActionTest, doesClear ) {

  /* Setup */
  mPrompt = "";
  mChoice = "clear";
  mInputStream.str( "" );

  /* Stimulus */
  takeAction( mInputStream, mOutputStream, mChoice, input_image1, input_image2, output_image );
  const PPM& ppm_const = input_image1;

  /* Comparison */
  EXPECT_EQ( mPrompt, mOutputStream.str( ) );

  int row, column;
  for( row = 0; row < mHeight; row++ ) {
    for( column = 0; column < mWidth; column++ ) {
      EXPECT_EQ( 0, ppm_const.getChannel( row, column, 0 ) )
        << "row: " << row << " column: " << column << " channel: " << 0;
      EXPECT_EQ( 0, ppm_const.getChannel( row, column, 1 ) )
        << "row: " << row << " column: " << column << " channel: " << 1;
      EXPECT_EQ( 0, ppm_const.getChannel( row, column, 2 ) )
        << "row: " << row << " column: " << column << " channel: " << 2;
    }
  }

  /* Tear-down */
  // Done automatically

}

TEST_F( takeActionTest, doesSetPixel ) {

  /* Setup */
  mPrompt = "Row? Column? Red? Green? Blue? ";
  mChoice = "pixel";
  mRed = 88;
  mGreen = 44;
  mBlue = 55;
  mInputStream.str( "7 8 88 44 55" );

  /* Stimulus */
  takeAction( mInputStream, mOutputStream, mChoice, input_image1, input_image2, output_image );
  const PPM& ppm_const = input_image1;

  /* Comparison */
  EXPECT_EQ( mPrompt, mOutputStream.str( ) );

  int row, column;
  for( row = 0; row < mHeight; row++ ) {
    for( column = 0; column < mWidth; column++ ) {
      if( ( std::abs(row-7) + std::abs(column-8) ) > 0 ) {
        EXPECT_EQ( 100, ppm_const.getChannel( row, column, 0 ) )
          << "row: " << row << " column: " << column << " channel: " << 0;
        EXPECT_EQ( 101, ppm_const.getChannel( row, column, 1 ) )
          << "row: " << row << " column: " << column << " channel: " << 1;
        EXPECT_EQ( 102, ppm_const.getChannel( row, column, 2 ) )
          << "row: " << row << " column: " << column << " channel: " << 2;
      } else {
        EXPECT_EQ( mRed, ppm_const.getChannel( row, column, 0 ) )
          << "row: " << row << " column: " << column << " channel: " << 0;
        EXPECT_EQ( mGreen, ppm_const.getChannel( row, column, 1 ) )
          << "row: " << row << " column: " << column << " channel: " << 1;
        EXPECT_EQ( mBlue, ppm_const.getChannel( row, column, 2 ) )
          << "row: " << row << " column: " << column << " channel: " << 2;
      }
    }
  }

  /* Tear-down */
  // Done automatically

}

TEST_F( takeActionTest, doesSetChannel ) {

  /* Setup */
  mPrompt = "Row? Column? Channel? Value? ";
  mChoice = "channel";
  mRed = 88;
  mGreen = 44;
  mBlue = 55;
  mInputStream.str( "9 3 1 44"  );

  /* Stimulus */
  takeAction( mInputStream, mOutputStream, mChoice, input_image1, input_image2, output_image );
  const PPM& ppm_const = input_image1;

  /* Comparison */
  EXPECT_EQ( mPrompt, mOutputStream.str( ) );

  int row, column;
  for( row = 0; row < mHeight; row++ ) {
    for( column = 0; column < mWidth; column++ ) {
      if( ( std::abs(row-9) + std::abs(column-3) ) > 0 ) {
        EXPECT_EQ( 100, ppm_const.getChannel( row, column, 0 ) )
          << "row: " << row << " column: " << column << " channel: " << 0;
        EXPECT_EQ( 101, ppm_const.getChannel( row, column, 1 ) )
          << "row: " << row << " column: " << column << " channel: " << 1;
        EXPECT_EQ( 102, ppm_const.getChannel( row, column, 2 ) )
          << "row: " << row << " column: " << column << " channel: " << 2;
      } else {
        EXPECT_EQ( 100, ppm_const.getChannel( row, column, 0 ) )
          << "row: " << row << " column: " << column << " channel: " << 0;
        EXPECT_EQ( mGreen, ppm_const.getChannel( row, column, 1 ) )
          << "row: " << row << " column: " << column << " channel: " << 1;
        EXPECT_EQ( 102, ppm_const.getChannel( row, column, 2 ) )
          << "row: " << row << " column: " << column << " channel: " << 2;
      }
    }
  }

  /* Tear-down */
  // Done automatically

}


TEST_F( takeActionTest, doesSetMaxColorValue ) {

  /* Setup */
  mPrompt = "Max color value? ";
  mChoice = "max";
  mInputStream.str( "157"  );

  /* Stimulus */
  takeAction( mInputStream, mOutputStream, mChoice, input_image1, input_image2, output_image );
  const PPM& ppm_const = input_image1;

  /* Comparison */
  EXPECT_EQ( mPrompt, mOutputStream.str( ) );
  EXPECT_EQ( 157, ppm_const.getMaxColorValue( ) );

  /* Tear-down */
  // Done automatically

}

TEST_F( takeActionTest, doesSetSize ) {

  /* Setup */
  mPrompt = "Height? Width? ";
  mChoice = "size";
  mInputStream.str( "123 456"  );

  /* Stimulus */
  takeAction( mInputStream, mOutputStream, mChoice, input_image1, input_image2, output_image );
  const PPM& ppm_const = input_image1;

  /* Comparison */
  EXPECT_EQ( mPrompt, mOutputStream.str( ) );
  EXPECT_EQ( 123, ppm_const.getHeight( ) );
  EXPECT_EQ( 456, ppm_const.getWidth( ) );

  /* Tear-down */
  // Done automatically

}


TEST_F( takeActionTest, doesComment ) {

  /* Setup */
  mPrompt = "";
  mChoice = "#";
  std::string remains = "hello world";
  std::streampos position = 12;
  mInputStream.str( "x y zdef1 f\nhello world"  );

  /* Stimulus */
  takeAction( mInputStream, mOutputStream, mChoice, input_image1, input_image2, output_image );

  /* Comparison */
  EXPECT_EQ( mPrompt, mOutputStream.str( ) );
  EXPECT_EQ( position, mInputStream.tellg( ) );
  EXPECT_EQ( mInputStream.str( ).size( ) - remains.size( ), mInputStream.tellg( ) );
  EXPECT_EQ( true, mInputStream.good( ) );
  EXPECT_EQ( false, mInputStream.eof( ) );
  EXPECT_EQ( false, mInputStream.fail( ) );

  /* Tear-down */
  // Done automatically

}

TEST_F( takeActionTest, doesCopy ) {

  /* Setup */
  mPrompt = "";
  mChoice = "copy";
  mInputStream.str( "" );

  /* Stimulus */
  takeAction( mInputStream, mOutputStream, mChoice, input_image1, input_image2, output_image );
  const PPM& ppm_const = input_image1;
  const PPM& ppm_const2 = output_image;

  /* Comparison */
  EXPECT_EQ( ppm_const.getHeight( ), ppm_const2.getHeight( ) );
  EXPECT_EQ( ppm_const.getWidth( ), ppm_const2.getWidth( ) );
  EXPECT_EQ( ppm_const.getMaxColorValue( ), ppm_const2.getMaxColorValue( ) );
  int row, column, channel;
  for( row = 0; row < mHeight; row++ ) {
    for( column = 0; column < mWidth; column++ ) {
      for( channel = 0; channel < 3; channel++ ) {
        EXPECT_EQ( ppm_const.getChannel( row, column, channel ), ppm_const2.getChannel( row, column, channel ) )
          << "row: " << row << " column: " << column << " channel: " << channel;
      }
    }
  }

  /* Tear-down */
  // Done automatically

}

TEST_F( takeActionTest, doesWrite ) {

  /* Setup */
  mPrompt = "Output filename? ";
  mChoice = "write";
  mInputStream.str( "test_file.ppm" );
  output_image = input_image1;

  /* Stimulus */
  takeAction( mInputStream, mOutputStream, mChoice, input_image1, input_image2, output_image );
  const PPM& ppm_const = input_image1;
  PPM ppm_tmp;
  readFile( "test_file.ppm", ppm_tmp );
  const PPM& ppm_const2 = ppm_tmp;

  /* Comparison */
  EXPECT_EQ( ppm_const.getHeight( ), ppm_const2.getHeight( ) );
  EXPECT_EQ( ppm_const.getWidth( ), ppm_const2.getWidth( ) );
  EXPECT_EQ( ppm_const.getMaxColorValue( ), ppm_const2.getMaxColorValue( ) );
  int row, column, channel;
  for( row = 0; row < mHeight; row++ ) {
    for( column = 0; column < mWidth; column++ ) {
      for( channel = 0; channel < 3; channel++ ) {
        EXPECT_EQ( ppm_const.getChannel( row, column, channel ), ppm_const2.getChannel( row, column, channel ) )
          << "row: " << row << " column: " << column << " channel: " << channel;
      }
    }
  }

  /* Tear-down */
  // Done automatically

}
