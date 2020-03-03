#include "PPM.h"
#include "PPM.h" // Did you #ifndef your file?

#include "gtest/gtest.h"
#include <fstream>

class PPMConstructorTest : public ::testing::Test {
protected:

  virtual void SetUp( ) {
  }

  virtual void TearDown( ) {
  }

  /* data members */
  PPM ppm;
};



TEST_F( PPMConstructorTest, setsWidth0 ) {

  /* Setup */
  // Done automatically

  /* Stimulus */
  const PPM& ppm_const = ppm;

  /* Comparison */
  EXPECT_EQ( 0, ppm_const.getWidth( ) );

  /* Tear-down */
  // Done automatically
}

TEST_F( PPMConstructorTest, setsHeight0 ) {

  /* Setup */
  // Done automatically

  /* Stimulus */
  const PPM& ppm_const = ppm;

  /* Comparison */
  EXPECT_EQ( 0, ppm_const.getHeight( ) );

  /* Tear-down */
  // Done automatically
}

TEST_F( PPMConstructorTest, setsMaxColorValue0 ) {

  /* Setup */
  // Done automatically

  /* Stimulus */
  const PPM& ppm_const = ppm;

  /* Comparison */
  EXPECT_EQ( 0, ppm_const.getMaxColorValue( ) );

  /* Tear-down */
  // Done automatically
}

TEST_F( PPMConstructorTest, setsNoChannels ) {

  /* Setup */
  // Done automatically

  /* Stimulus */
  const PPM& ppm_const = ppm;

  /* Comparison */
  EXPECT_EQ( -1, ppm_const.getChannel( 0, 0, 0 ) );

  /* Tear-down */
  // Done automatically
}



class PPMConstructorSizeTest : public ::testing::Test {
protected:

  virtual void SetUp( ) {
  }

  virtual void TearDown( ) {
  }

  /* data members */
};



TEST_F( PPMConstructorSizeTest, setsWidth23 ) {

  /* Setup */
  int height = 15;
  int width = 23;
  PPM ppm( height, width );

  /* Stimulus */
  const PPM& ppm_const = ppm;

  /* Comparison */
  EXPECT_EQ( width, ppm_const.getWidth( ) );

  /* Tear-down */
  // Done automatically
}

TEST_F( PPMConstructorSizeTest, setsWidth37 ) {

  /* Setup */
  int height = 15;
  int width = 37;
  PPM ppm( height, width );

  /* Stimulus */
  const PPM& ppm_const = ppm;

  /* Comparison */
  EXPECT_EQ( width, ppm_const.getWidth( ) );

  /* Tear-down */
  // Done automatically
}

TEST_F( PPMConstructorSizeTest, setsHeight15 ) {

  /* Setup */
  int height = 15;
  int width = 37;
  PPM ppm( height, width );

  /* Stimulus */
  const PPM& ppm_const = ppm;

  /* Comparison */
  EXPECT_EQ( height, ppm_const.getHeight( ) );

  /* Tear-down */
  // Done automatically
}

TEST_F( PPMConstructorSizeTest, setsHeight19 ) {

  /* Setup */
  int height = 19;
  int width = 37;
  PPM ppm( height, width );

  /* Stimulus */
  const PPM& ppm_const = ppm;

  /* Comparison */
  EXPECT_EQ( height, ppm_const.getHeight( ) );

  /* Tear-down */
  // Done automatically
}

TEST_F( PPMConstructorSizeTest, setsMaxColorValue0 ) {

  /* Setup */
  int height = 19;
  int width = 37;
  PPM ppm( height, width );

  /* Stimulus */
  const PPM& ppm_const = ppm;

  /* Comparison */
  EXPECT_EQ( 0, ppm_const.getMaxColorValue( ) );

  /* Tear-down */
  // Done automatically
}

TEST_F( PPMConstructorSizeTest, setsSomeChannels ) {

  /* Setup */
  int height = 19;
  int width = 37;
  PPM ppm( height, width );

  /* Stimulus */
  const PPM& ppm_const = ppm;

  /* Comparison */
  EXPECT_EQ( -1, ppm_const.getChannel( -1, 0, 0 ) );
  EXPECT_EQ( -1, ppm_const.getChannel( 0, -1, 0 ) );
  EXPECT_EQ( -1, ppm_const.getChannel( 0, 0, -1 ) );

  EXPECT_NE( -1, ppm_const.getChannel( 0, 0, 0 ) );
  EXPECT_NE( -1, ppm_const.getChannel( 1, 0, 0 ) );
  EXPECT_NE( -1, ppm_const.getChannel( 0, 1, 0 ) );
  EXPECT_NE( -1, ppm_const.getChannel( 0, 0, 1 ) );
  EXPECT_NE( -1, ppm_const.getChannel( 18, 36, 2 ) );

  EXPECT_EQ( -1, ppm_const.getChannel( 19, 0, 0 ) );
  EXPECT_EQ( -1, ppm_const.getChannel( 0, 37, 0 ) );
  EXPECT_EQ( -1, ppm_const.getChannel( 0, 0, 3 ) );

  /* Tear-down */
  // Done automatically
}
