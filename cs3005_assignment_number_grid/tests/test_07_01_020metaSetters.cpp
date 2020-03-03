#include "NumberGrid.h"
#include "NumberGrid.h" // Did you #ifndef your file?

#include "gtest/gtest.h"
#include <fstream>

class NumberGridMetaSetterTest : public ::testing::Test {
protected:

  virtual void SetUp( ) {
  }

  virtual void TearDown( ) {
  }

  /* data members */
  NumberGrid grid;
};



TEST_F( NumberGridMetaSetterTest, setsGridSize ) {

  /* Setup */
  grid.setGridSize( 100, 200 );

  /* Stimulus */
  const NumberGrid& grid_const = grid;

  /* Comparison */
  EXPECT_EQ( 100, grid_const.getHeight( ) );
  EXPECT_EQ( 200, grid_const.getWidth( ) );

  /* Tear-down */
  // Done automatically
}

TEST_F( NumberGridMetaSetterTest, setsMaxNumber ) {

  /* Setup */
  grid.setMaxNumber( 100000 );

  /* Stimulus */
  const NumberGrid& grid_const = grid;

  /* Comparison */
  EXPECT_EQ( 100000, grid_const.getMaxNumber( ) );

  /* Tear-down */
  // Done automatically
}

TEST_F( NumberGridMetaSetterTest, setsGridSize2 ) {

  /* Setup */
  grid.setGridSize( 10, 20 );

  /* Stimulus */
  const NumberGrid& grid_const = grid;

  /* Comparison */
  EXPECT_EQ( 10, grid_const.getHeight( ) );
  EXPECT_EQ( 20, grid_const.getWidth( ) );

  /* Tear-down */
  // Done automatically
}

TEST_F( NumberGridMetaSetterTest, setsGridSizeHeight2 ) {

  /* Setup */
  grid.setGridSize( 2, 10 );

  /* Stimulus */
  const NumberGrid& grid_const = grid;

  /* Comparison */
  EXPECT_EQ( 2, grid_const.getHeight( ) );
  EXPECT_EQ( 10, grid_const.getWidth( ) );

  /* Tear-down */
  // Done automatically
}

TEST_F( NumberGridMetaSetterTest, setsGridSizeWidth2 ) {

  /* Setup */
  grid.setGridSize( 10, 2 );

  /* Stimulus */
  const NumberGrid& grid_const = grid;

  /* Comparison */
  EXPECT_EQ( 10, grid_const.getHeight( ) );
  EXPECT_EQ( 2, grid_const.getWidth( ) );

  /* Tear-down */
  // Done automatically
}

TEST_F( NumberGridMetaSetterTest, setsGridSizeHeightWidth2 ) {

  /* Setup */
  grid.setGridSize( 2, 2 );

  /* Stimulus */
  const NumberGrid& grid_const = grid;

  /* Comparison */
  EXPECT_EQ( 2, grid_const.getHeight( ) );
  EXPECT_EQ( 2, grid_const.getWidth( ) );

  /* Tear-down */
  // Done automatically
}

TEST_F( NumberGridMetaSetterTest, setsMaxNumber2 ) {

  /* Setup */
  grid.setMaxNumber( 20 );

  /* Stimulus */
  const NumberGrid& grid_const = grid;

  /* Comparison */
  EXPECT_EQ( 20, grid_const.getMaxNumber( ) );

  /* Tear-down */
  // Done automatically
}

TEST_F( NumberGridMetaSetterTest, doesNotSetGridSize1 ) {

  /* Setup */
  grid.setGridSize( 100, 200 );
  grid.setGridSize( 1, 20 );

  /* Stimulus */
  const NumberGrid& grid_const = grid;

  /* Comparison */
  EXPECT_EQ( 100, grid_const.getHeight( ) );
  EXPECT_EQ( 200, grid_const.getWidth( ) );

  /* Tear-down */
  // Done automatically
}

TEST_F( NumberGridMetaSetterTest, doesNotSetGridSize2 ) {

  /* Setup */
  grid.setGridSize( 100, 200 );
  grid.setGridSize( 10, 1 );

  /* Stimulus */
  const NumberGrid& grid_const = grid;

  /* Comparison */
  EXPECT_EQ( 100, grid_const.getHeight( ) );
  EXPECT_EQ( 200, grid_const.getWidth( ) );

  /* Tear-down */
  // Done automatically
}

TEST_F( NumberGridMetaSetterTest, doesNotSetGridSize3 ) {

  /* Setup */
  grid.setGridSize( 100, 200 );
  grid.setGridSize( 1, 1 );

  /* Stimulus */
  const NumberGrid& grid_const = grid;

  /* Comparison */
  EXPECT_EQ( 100, grid_const.getHeight( ) );
  EXPECT_EQ( 200, grid_const.getWidth( ) );

  /* Tear-down */
  // Done automatically
}

TEST_F( NumberGridMetaSetterTest, doesNotSetGridSize4 ) {

  /* Setup */
  grid.setGridSize( 100, 200 );
  grid.setGridSize( 35, -100 );

  /* Stimulus */
  const NumberGrid& grid_const = grid;

  /* Comparison */
  EXPECT_EQ( 100, grid_const.getHeight( ) );
  EXPECT_EQ( 200, grid_const.getWidth( ) );

  /* Tear-down */
  // Done automatically
}

TEST_F( NumberGridMetaSetterTest, doesNotSetGridSize5 ) {

  /* Setup */
  grid.setGridSize( 100, 200 );
  grid.setGridSize( -100, 23 );

  /* Stimulus */
  const NumberGrid& grid_const = grid;

  /* Comparison */
  EXPECT_EQ( 100, grid_const.getHeight( ) );
  EXPECT_EQ( 200, grid_const.getWidth( ) );

  /* Tear-down */
  // Done automatically
}

TEST_F( NumberGridMetaSetterTest, doesNotSetGridSize6 ) {

  /* Setup */
  grid.setGridSize( 100, 200 );
  grid.setGridSize( -34, -150 );

  /* Stimulus */
  const NumberGrid& grid_const = grid;

  /* Comparison */
  EXPECT_EQ( 100, grid_const.getHeight( ) );
  EXPECT_EQ( 200, grid_const.getWidth( ) );

  /* Tear-down */
  // Done automatically
}

TEST_F( NumberGridMetaSetterTest, doesNotSetMaxNumber ) {

  /* Setup */
  grid.setMaxNumber( 20 );
  grid.setMaxNumber( -1 );

  /* Stimulus */
  const NumberGrid& grid_const = grid;

  /* Comparison */
  EXPECT_EQ( 20, grid_const.getMaxNumber( ) );

  /* Tear-down */
  // Done automatically
}


TEST_F( NumberGridMetaSetterTest, doesNotSetMaxNumber2 ) {

  /* Setup */
  grid.setMaxNumber( 30 );
  grid.setMaxNumber( -100 );

  /* Stimulus */
  const NumberGrid& grid_const = grid;

  /* Comparison */
  EXPECT_EQ( 30, grid_const.getMaxNumber( ) );

  /* Tear-down */
  // Done automatically
}
