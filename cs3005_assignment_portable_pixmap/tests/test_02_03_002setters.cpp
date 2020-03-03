#include "PPM.h"
#include "PPM.h" // Did you #ifndef your file?

#include "gtest/gtest.h"
#include <fstream>

class PPMSetterTest : public ::testing::Test {
protected:

  virtual void SetUp( ) {
    width = 20;
    height = 10;
    max_color_value = 255;
    row = 3;
    column = 4;
    channel = 1;
    channel_value = 17;
    bad_low_value = -3;
    bad_high_value = max_color_value + 1;
    ppm.setWidth( width );
    ppm.setHeight( height );
    ppm.setMaxColorValue( max_color_value );
    ppm.setChannel( row, column, channel, channel_value );
  }

  virtual void TearDown( ) {
  }

  /* data members */
  int width;
  int height;
  int max_color_value;
  int row, column, channel;
  int channel_value;
  int bad_low_value;
  int bad_high_value;
  PPM ppm;
};



TEST_F( PPMSetterTest, setsWidth ) {

  /* Setup */
  // Done automatically

  /* Stimulus */
  const PPM& ppm_const = ppm;

  /* Comparison */
  EXPECT_EQ( width, ppm_const.getWidth( ) );

  /* Tear-down */
  // Done automatically
}

TEST_F( PPMSetterTest, setsHeight ) {

  /* Setup */
  // Done automatically

  /* Stimulus */
  const PPM& ppm_const = ppm;

  /* Comparison */
  EXPECT_EQ( height, ppm_const.getHeight( ) );

  /* Tear-down */
  // Done automatically
}

TEST_F( PPMSetterTest, setsMaxColorValue ) {

  /* Setup */
  // Done automatically

  /* Stimulus */
  const PPM& ppm_const = ppm;

  /* Comparison */
  EXPECT_EQ( max_color_value, ppm_const.getMaxColorValue( ) );

  /* Tear-down */
  // Done automatically
}

TEST_F( PPMSetterTest, setsChannel ) {

  /* Setup */
  // Done automatically

  /* Stimulus */
  const PPM& ppm_const = ppm;

  /* Comparison */
  EXPECT_EQ( channel_value, ppm_const.getChannel( row, column, channel ) );

  /* Tear-down */
  // Done automatically
}


TEST_F( PPMSetterTest, doesNotSetBadWidth ) {

  /* Setup */
  // Done automatically

  /* Stimulus */
  ppm.setWidth( -1 );
  const PPM& ppm_const = ppm;

  /* Comparison */
  EXPECT_EQ( width, ppm_const.getWidth( ) );

  /* Tear-down */
  // Done automatically
}

TEST_F( PPMSetterTest, doesNotSetBadHeight ) {

  /* Setup */
  // Done automatically

  /* Stimulus */
  ppm.setHeight( -1 );
  const PPM& ppm_const = ppm;

  /* Comparison */
  EXPECT_EQ( height, ppm_const.getHeight( ) );

  /* Tear-down */
  // Done automatically
}


TEST_F( PPMSetterTest, setWidthSetHeightResizeCorrectly ) {
  /* Intentionally try to break the vector underneath */
  int big_size = 1000;
  int mcv = 100;
  int value = 89;
  ppm.setWidth( big_size );
  ppm.setHeight( big_size );
  ppm.setMaxColorValue( mcv );
  // this is the last possible channel.  It should
  // cause a segmentation fault if the resize is too small
  ppm.setChannel( big_size - 1, big_size - 1, 2, value );
  EXPECT_EQ( value, ppm.getChannel( big_size - 1, big_size - 1, 2 ) );
  // this is the first possible channel.
  ppm.setChannel( 0, 0, 0, value );
  EXPECT_EQ( value, ppm.getChannel( 0, 0, 0 ) );
}


TEST_F( PPMSetterTest, doesNotSetLowMaxColorValue ) {

  /* Setup */
  // Done automatically

  /* Stimulus */
  ppm.setMaxColorValue( -1 );
  const PPM& ppm_const = ppm;

  /* Comparison */
  EXPECT_EQ( max_color_value, ppm_const.getMaxColorValue( ) );

  /* Tear-down */
  // Done automatically
}

TEST_F( PPMSetterTest, doesNotSetHighMaxColorValue ) {

  /* Setup */
  // Done automatically

  /* Stimulus */
  ppm.setMaxColorValue( 256 );
  const PPM& ppm_const = ppm;

  /* Comparison */
  EXPECT_EQ( max_color_value, ppm_const.getMaxColorValue( ) );

  /* Tear-down */
  // Done automatically
}

TEST_F( PPMSetterTest, doesNotSetBadChannelLow ) {

  /* Setup */
  // Done automatically

  /* Stimulus */
  ppm.setChannel( row, column, -1, channel_value );
  const PPM& ppm_const = ppm;

  /* Comparison */
  EXPECT_EQ( -1, ppm_const.getChannel( row, column, -1 ) );

  /* Tear-down */
  // Done automatically
}

TEST_F( PPMSetterTest, doesNotSetBadChannelHigh ) {

  /* Setup */
  // Done automatically

  /* Stimulus */
  ppm.setChannel( row, column, 3, channel_value );
  const PPM& ppm_const = ppm;

  /* Comparison */
  EXPECT_EQ( -1, ppm_const.getChannel( row, column, 4 ) );

  /* Tear-down */
  // Done automatically
}

TEST_F( PPMSetterTest, doesNotSetBadColumnLow ) {

  /* Setup */
  // Done automatically

  /* Stimulus */
  ppm.setChannel( row, -1, 2, channel_value );
  const PPM& ppm_const = ppm;

  /* Comparison */
  EXPECT_EQ( -1, ppm_const.getChannel( row, -1, 2 ) );

  /* Tear-down */
  // Done automatically
}

TEST_F( PPMSetterTest, doesNotSetBadColumnHigh ) {

  /* Setup */
  // Done automatically

  /* Stimulus */
  ppm.setChannel( row, width, 2, channel_value );
  const PPM& ppm_const = ppm;

  /* Comparison */
  EXPECT_EQ( -1, ppm_const.getChannel( row, width, 2 ) );

  /* Tear-down */
  // Done automatically
}

TEST_F( PPMSetterTest, doesNotSetBadRowLow ) {

  /* Setup */
  // Done automatically

  /* Stimulus */
  ppm.setChannel( -1, column, 2, channel_value );
  const PPM& ppm_const = ppm;

  /* Comparison */
  EXPECT_EQ( -1, ppm_const.getChannel( -1, column, 2 ) );

  /* Tear-down */
  // Done automatically
}

TEST_F( PPMSetterTest, doesNotSetBadRowHigh ) {

  /* Setup */
  // Done automatically

  /* Stimulus */
  ppm.setChannel( height, column, 2, channel_value );
  const PPM& ppm_const = ppm;

  /* Comparison */
  EXPECT_EQ( -1, ppm_const.getChannel( height, column, 2 ) );

  /* Tear-down */
  // Done automatically
}

TEST_F( PPMSetterTest, doesNotSetBadChannelValueLow ) {

  /* Setup */
  // Done automatically

  /* Stimulus */
  ppm.setChannel( row, column, 2, channel_value );
  ppm.setChannel( row, column, 2, bad_low_value );
  const PPM& ppm_const = ppm;

  /* Comparison */
  EXPECT_EQ( channel_value, ppm_const.getChannel( row, column, 2 ) );

  /* Tear-down */
  // Done automatically
}

TEST_F( PPMSetterTest, doesNotSetBadChannelValueHigh ) {

  /* Setup */
  // Done automatically

  /* Stimulus */
  ppm.setChannel( row, column, 2, channel_value );
  ppm.setChannel( row, column, 2, bad_high_value );
  const PPM& ppm_const = ppm;

  /* Comparison */
  EXPECT_EQ( channel_value, ppm_const.getChannel( row, column, 2 ) );

  /* Tear-down */
  // Done automatically
}

TEST_F( PPMSetterTest, setsManyChannelsCorrectly ) {
  int row, column, channel;

  /* Setup/Stimulus */
  for( row = 0; row < height; row++ ) {
    for( column = 0; column < width; column++ ) {
      for( channel = 0; channel < 3; channel++ ) {
        int value = ( row + column + channel ) % 17;
        ppm.setChannel( row, column, channel, value );
      }
    }
  }

  /* Comparison */
  for( row = 0; row < height; row++ ) {
    for( column = 0; column < width; column++ ) {
      for( channel = 0; channel < 3; channel++ ) {
        int value = ( row + column + channel ) % 17;
        EXPECT_EQ( value, ppm.getChannel( row, column, channel ) )
          << "row: " << row << " column: " << column << " channel: " << channel;
      }
    }
  }

}


TEST_F( PPMSetterTest, setsPixel ) {

  /* Setup */
  row = 9;
  column = 2;
  int red = 123;
  int green = 231;
  int blue = 78;

  /* Stimulus */
  ppm.setPixel( row, column, red, green, blue );
  const PPM& ppm_const = ppm;

  /* Comparison */
  EXPECT_EQ( red, ppm_const.getChannel( row, column, 0 ) );
  EXPECT_EQ( green, ppm_const.getChannel( row, column, 1 ) );
  EXPECT_EQ( blue, ppm_const.getChannel( row, column, 2 ) );

  /* Tear-down */
  // Done automatically
}
