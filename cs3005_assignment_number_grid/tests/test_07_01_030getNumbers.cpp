#include "NumberGrid.h"
#include "NumberGrid.h" // Did you #ifndef your file?

#include "gtest/gtest.h"
#include <fstream>

class NumberGridGetNumbersTest : public ::testing::Test {
protected:

  virtual void SetUp( ) {
  }

  virtual void TearDown( ) {
  }

  /* data members */
  NumberGrid grid;
};



TEST_F( NumberGridGetNumbersTest, calculatesIndex1 ) {

  /* Setup */
  int height = 100;
  int width = 200;
  grid.setGridSize( height, width );

  /* Stimulus */
  const NumberGrid& grid_const = grid;

  /* Comparison */
  EXPECT_EQ( height*width, (int)grid_const.getNumbers( ).size( ) );

  /* Tear-down */
  // Done automatically
}
