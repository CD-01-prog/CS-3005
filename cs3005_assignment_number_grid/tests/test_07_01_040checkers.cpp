#include "NumberGrid.h"
#include "NumberGrid.h" // Did you #ifndef your file?

#include "gtest/gtest.h"
#include <fstream>

class NumberGridCheckersTest : public ::testing::Test {
protected:

  virtual void SetUp( ) {
  }

  virtual void TearDown( ) {
  }

  /* data members */
  NumberGrid grid;
};



TEST_F( NumberGridCheckersTest, calculatesIndex1 ) {

  /* Setup */
  int height = 100;
  int width = 200;
  int row = 33;
  int column = 7;
  int expected_index = 6607;
  grid.setGridSize( height, width );

  /* Stimulus */
  const NumberGrid& grid_const = grid;

  /* Comparison */
  EXPECT_EQ( expected_index, grid_const.index( row, column ) )
    << "row: " << row << " column: " << column;

  /* Tear-down */
  // Done automatically
}

TEST_F( NumberGridCheckersTest, calculatesIndex2 ) {

  /* Setup */
  int height = 10;
  int width = 20;
  int row = 3;
  int column = 17;
  int expected_index = 77;
  grid.setGridSize( height, width );

  /* Stimulus */
  const NumberGrid& grid_const = grid;

  /* Comparison */
  EXPECT_EQ( expected_index, grid_const.index( row, column ) )
    << "row: " << row << " column: " << column;

  /* Tear-down */
  // Done automatically
}

TEST_F( NumberGridCheckersTest, calculatesIndexValid1 ) {

  /* Setup */
  int height = 100;
  int width = 200;
  int row = 33;
  int column = 7;
  grid.setGridSize( height, width );

  /* Stimulus */
  const NumberGrid& grid_const = grid;

  /* Comparison */
  row = 0; column = 0;
  EXPECT_EQ( true, grid_const.indexValid( row, column ) )
    << "row: " << row << " column: " << column;
  row = 99; column = 0;
  EXPECT_EQ( true, grid_const.indexValid( row, column ) )
    << "row: " << row << " column: " << column;
  row = 0; column = 199;
  EXPECT_EQ( true, grid_const.indexValid( row, column ) )
    << "row: " << row << " column: " << column;
  row = 99; column = 199;
  EXPECT_EQ( true, grid_const.indexValid( row, column ) )
    << "row: " << row << " column: " << column;

  /* Tear-down */
  // Done automatically
}

TEST_F( NumberGridCheckersTest, calculatesIndexValid2 ) {

  /* Setup */
  int height = 10;
  int width = 20;
  int row = 33;
  int column = 7;
  grid.setGridSize( height, width );

  /* Stimulus */
  const NumberGrid& grid_const = grid;

  /* Comparison */
  row = 0; column = 0;
  EXPECT_EQ( true, grid_const.indexValid( row, column ) )
    << "row: " << row << " column: " << column;
  row = 9; column = 0;
  EXPECT_EQ( true, grid_const.indexValid( row, column ) )
    << "row: " << row << " column: " << column;
  row = 0; column = 19;
  EXPECT_EQ( true, grid_const.indexValid( row, column ) )
    << "row: " << row << " column: " << column;
  row = 9; column = 19;
  EXPECT_EQ( true, grid_const.indexValid( row, column ) )
    << "row: " << row << " column: " << column;

  /* Tear-down */
  // Done automatically
}

TEST_F( NumberGridCheckersTest, calculatesIndexInvalid1 ) {

  /* Setup */
  int height = 100;
  int width = 200;
  int row = 33;
  int column = 7;
  grid.setGridSize( height, width );

  /* Stimulus */
  const NumberGrid& grid_const = grid;

  /* Comparison */
  row = -1; column = 0;
  EXPECT_EQ( false, grid_const.indexValid( row, column ) )
    << "row: " << row << " column: " << column;
  row = 0; column = -1;
  EXPECT_EQ( false, grid_const.indexValid( row, column ) )
    << "row: " << row << " column: " << column;
  row = 100; column = 0;
  EXPECT_EQ( false, grid_const.indexValid( row, column ) )
    << "row: " << row << " column: " << column;
  row = 99; column = -1;
  EXPECT_EQ( false, grid_const.indexValid( row, column ) )
    << "row: " << row << " column: " << column;
  row = 0; column = 200;
  EXPECT_EQ( false, grid_const.indexValid( row, column ) )
    << "row: " << row << " column: " << column;
  row = -1; column = 199;
  EXPECT_EQ( false, grid_const.indexValid( row, column ) )
    << "row: " << row << " column: " << column;
  row = 100; column = 199;
  EXPECT_EQ( false, grid_const.indexValid( row, column ) )
    << "row: " << row << " column: " << column;
  row = 99; column = 200;
  EXPECT_EQ( false, grid_const.indexValid( row, column ) )
    << "row: " << row << " column: " << column;

  /* Tear-down */
  // Done automatically
}

TEST_F( NumberGridCheckersTest, calculatesIndexInvalid2 ) {

  /* Setup */
  int height = 10;
  int width = 20;
  int row = 33;
  int column = 7;
  grid.setGridSize( height, width );

  /* Stimulus */
  const NumberGrid& grid_const = grid;

  /* Comparison */
  row = -1; column = 0;
  EXPECT_EQ( false, grid_const.indexValid( row, column ) )
    << "row: " << row << " column: " << column;
  row = 0; column = -1;
  EXPECT_EQ( false, grid_const.indexValid( row, column ) )
    << "row: " << row << " column: " << column;
  row = 10; column = 0;
  EXPECT_EQ( false, grid_const.indexValid( row, column ) )
    << "row: " << row << " column: " << column;
  row = 9; column = -1;
  EXPECT_EQ( false, grid_const.indexValid( row, column ) )
    << "row: " << row << " column: " << column;
  row = 0; column = 20;
  EXPECT_EQ( false, grid_const.indexValid( row, column ) )
    << "row: " << row << " column: " << column;
  row = -1; column = 19;
  EXPECT_EQ( false, grid_const.indexValid( row, column ) )
    << "row: " << row << " column: " << column;
  row = 10; column = 19;
  EXPECT_EQ( false, grid_const.indexValid( row, column ) )
    << "row: " << row << " column: " << column;
  row = 9; column = 20;
  EXPECT_EQ( false, grid_const.indexValid( row, column ) )
    << "row: " << row << " column: " << column;

  /* Tear-down */
  // Done automatically
}

TEST_F( NumberGridCheckersTest, calculatesNumberValid1 ) {

  /* Setup */
  int height = 50;
  int width = 75;
  int max_number = 1000;
  int number = 0;
  grid.setGridSize( height, width );
  grid.setMaxNumber( max_number );


  /* Stimulus */
  const NumberGrid& grid_const = grid;

  /* Comparison */
  number = 0;
  EXPECT_EQ( true, grid_const.numberValid( number ) )
    << "number: " << number;
  number = 1;
  EXPECT_EQ( true, grid_const.numberValid( number ) )
    << "number: " << number;
  number = max_number - 1;
  EXPECT_EQ( true, grid_const.numberValid( number ) )
    << "number: " << number;
  number = max_number;
  EXPECT_EQ( true, grid_const.numberValid( number ) )
    << "number: " << number;

  /* Tear-down */
  // Done automatically
}

TEST_F( NumberGridCheckersTest, calculatesNumberInvalid1 ) {

  /* Setup */
  int height = 50;
  int width = 75;
  int max_number = 1000;
  int number = 0;
  grid.setGridSize( height, width );
  grid.setMaxNumber( max_number );

  /* Stimulus */
  const NumberGrid& grid_const = grid;

  /* Comparison */
  number = -1;
  EXPECT_EQ( false, grid_const.numberValid( number ) )
    << "number: " << number;
  number = max_number + 1;
  EXPECT_EQ( false, grid_const.numberValid( number ) )
    << "number: " << number;

  /* Tear-down */
  // Done automatically
}

TEST_F( NumberGridCheckersTest, calculatesNumberValid2 ) {

  /* Setup */
  int height = 50;
  int width = 75;
  int max_number = 765;
  int number = 0;
  grid.setGridSize( height, width );
  grid.setMaxNumber( max_number );


  /* Stimulus */
  const NumberGrid& grid_const = grid;

  /* Comparison */
  number = 0;
  EXPECT_EQ( true, grid_const.numberValid( number ) )
    << "number: " << number;
  number = 1;
  EXPECT_EQ( true, grid_const.numberValid( number ) )
    << "number: " << number;
  number = max_number - 1;
  EXPECT_EQ( true, grid_const.numberValid( number ) )
    << "number: " << number;
  number = max_number;
  EXPECT_EQ( true, grid_const.numberValid( number ) )
    << "number: " << number;

  /* Tear-down */
  // Done automatically
}

TEST_F( NumberGridCheckersTest, calculatesNumberInvalid2 ) {

  /* Setup */
  int height = 50;
  int width = 75;
  int max_number = 365;
  int number = 0;
  grid.setGridSize( height, width );
  grid.setMaxNumber( max_number );

  /* Stimulus */
  const NumberGrid& grid_const = grid;

  /* Comparison */
  number = -1;
  EXPECT_EQ( false, grid_const.numberValid( number ) )
    << "number: " << number;
  number = max_number + 1;
  EXPECT_EQ( false, grid_const.numberValid( number ) )
    << "number: " << number;

  /* Tear-down */
  // Done automatically
}
