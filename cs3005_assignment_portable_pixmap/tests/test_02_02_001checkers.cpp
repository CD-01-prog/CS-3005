#include "PPM.h"
#include "PPM.h" // Did you #ifndef your file?

#include "gtest/gtest.h"
#include <fstream>

class PPMCheckerTest : public ::testing::Test {
protected:

  virtual void SetUp( ) {
  }

  virtual void TearDown( ) {
  }

  /* data members */
};



TEST_F( PPMCheckerTest, outOfRangeIndexInvalid ) {

  /* Setup */
  int height = 15;
  int width = 23;
  int max_color_value = 123;
  PPM ppm( height, width );
  ppm.setMaxColorValue( max_color_value );

  /* Stimulus */
  const PPM& ppm_const = ppm;

  /* Comparison */
  EXPECT_EQ( false, ppm_const.indexValid( -1, -1, -1 ) );
  EXPECT_EQ( false, ppm_const.indexValid( -1, 0, 0 ) );
  EXPECT_EQ( false, ppm_const.indexValid( 0, -1, 0 ) );
  EXPECT_EQ( false, ppm_const.indexValid( 0, 0, -1 ) );
  EXPECT_EQ( false, ppm_const.indexValid( 15, 23, 3 ) );
  EXPECT_EQ( false, ppm_const.indexValid( 15, 22, 2 ) );
  EXPECT_EQ( false, ppm_const.indexValid( 14, 23, 2 ) );
  EXPECT_EQ( false, ppm_const.indexValid( 14, 22, 3 ) );

  /* Tear-down */
  // Done automatically
}

TEST_F( PPMCheckerTest, inRangeIndexValid ) {

  /* Setup */
  int height = 15;
  int width = 23;
  int max_color_value = 123;
  PPM ppm( height, width );
  ppm.setMaxColorValue( max_color_value );

  /* Stimulus */
  const PPM& ppm_const = ppm;

  /* Comparison */
  EXPECT_EQ( true, ppm_const.indexValid( 0, 0, 0 ) );
  EXPECT_EQ( true, ppm_const.indexValid( 14, 22, 2 ) );

  /* Tear-down */
  // Done automatically
}


TEST_F( PPMCheckerTest, calculatesIndex ) {

  /* Setup */
  int height = 15;
  int width = 23;
  int max_color_value = 123;
  PPM ppm( height, width );
  ppm.setMaxColorValue( max_color_value );

  int row = 5;
  int column = 7;
  int channel = 1;
  int expected_index = ( 5 * 23 + 7 ) * 3 + channel;

  /* Stimulus */
  const PPM& ppm_const = ppm;

  /* Comparison */
  EXPECT_EQ( expected_index, ppm_const.index( row, column, channel ) );

  /* Tear-down */
  // Done automatically
}


TEST_F( PPMCheckerTest, outOfRangeValueInvalid ) {

  /* Setup */
  int height = 15;
  int width = 23;
  int max_color_value = 123;
  PPM ppm( height, width );
  ppm.setMaxColorValue( max_color_value );

  /* Stimulus */
  const PPM& ppm_const = ppm;

  /* Comparison */
  EXPECT_EQ( false, ppm_const.valueValid( -1 ) );
  EXPECT_EQ( false, ppm_const.valueValid( max_color_value + 1 ) );

  /* Tear-down */
  // Done automatically
}

TEST_F( PPMCheckerTest, inRangeValueValid ) {

  /* Setup */
  int height = 15;
  int width = 23;
  int max_color_value = 123;
  PPM ppm( height, width );
  ppm.setMaxColorValue( max_color_value );

  /* Stimulus */
  const PPM& ppm_const = ppm;

  /* Comparison */
  EXPECT_EQ( true, ppm_const.valueValid( 0 ) );
  EXPECT_EQ( true, ppm_const.valueValid( 1 ) );
  EXPECT_EQ( true, ppm_const.valueValid( max_color_value ) );
  EXPECT_EQ( true, ppm_const.valueValid( max_color_value - 1 ) );
  EXPECT_EQ( true, ppm_const.valueValid( max_color_value / 2 ) );

  /* Tear-down */
  // Done automatically
}
