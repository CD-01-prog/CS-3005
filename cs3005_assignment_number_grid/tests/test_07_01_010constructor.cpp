#include "NumberGrid.h"
#include "NumberGrid.h" // Did you #ifndef your file?

#include "gtest/gtest.h"
#include <fstream>

class NumberGridConstructorTest : public ::testing::Test {
protected:

  virtual void SetUp( ) {
  }

  virtual void TearDown( ) {
  }

  /* data members */
  NumberGrid grid;
};



TEST_F( NumberGridConstructorTest, setsHeight300 ) {

  /* Setup */
  // Done automatically

  /* Stimulus */
  const NumberGrid& grid_const = grid;

  /* Comparison */
  EXPECT_EQ( 300, grid_const.getHeight( ) );

  /* Tear-down */
  // Done automatically
}

TEST_F( NumberGridConstructorTest, setsWidth400 ) {

  /* Setup */
  // Done automatically

  /* Stimulus */
  const NumberGrid& grid_const = grid;

  /* Comparison */
  EXPECT_EQ( 400, grid_const.getWidth( ) );

  /* Tear-down */
  // Done automatically
}

TEST_F( NumberGridConstructorTest, setsMaxNumber255 ) {

  /* Setup */
  // Done automatically

  /* Stimulus */
  const NumberGrid& grid_const = grid;

  /* Comparison */
  EXPECT_EQ( 255, grid_const.getMaxNumber( ) );

  /* Tear-down */
  // Done automatically
}


class NumberGridConstructorParameterTest : public ::testing::Test {
protected:

  virtual void SetUp( ) {
  }

  virtual void TearDown( ) {
  }

  /* data members */
};



TEST_F( NumberGridConstructorParameterTest, setsHeight250 ) {

  /* Setup */
  NumberGrid grid( 250, 350 ) ;

  /* Stimulus */
  const NumberGrid& grid_const = grid;

  /* Comparison */
  EXPECT_EQ( 250, grid_const.getHeight( ) );

  /* Tear-down */
  // Done automatically
}

TEST_F( NumberGridConstructorParameterTest, setsWidth350 ) {

  /* Setup */
  NumberGrid grid( 250, 350 ) ;

  /* Stimulus */
  const NumberGrid& grid_const = grid;

  /* Comparison */
  EXPECT_EQ( 350, grid_const.getWidth( ) );

  /* Tear-down */
  // Done automatically
}

TEST_F( NumberGridConstructorParameterTest, setsMaxNumber255 ) {

  /* Setup */
  NumberGrid grid( 250, 350 ) ;

  /* Stimulus */
  const NumberGrid& grid_const = grid;

  /* Comparison */
  EXPECT_EQ( 255, grid_const.getMaxNumber( ) );

  /* Tear-down */
  // Done automatically
}
