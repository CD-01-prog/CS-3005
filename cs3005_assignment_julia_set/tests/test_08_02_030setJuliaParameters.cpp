#include "image_menu.h"
#include "image_menu.h" // Did you #ifndef your file?

#include "gtest/gtest.h"
#include <fstream>

class JuliaSetSetJuliaParametersTest : public ::testing::Test {
protected:

  virtual void SetUp( ) {
    mExpectedOutput = "";
    mInputStream.str( "" );
    mOutputStream.str( "" );
  }

  virtual void TearDown( ) {
  }

  /* data members */
  std::string mExpectedOutput;
  std::stringstream mInputStream;
  std::stringstream mOutputStream;
  JuliaSet js;
};



TEST_F( JuliaSetSetJuliaParametersTest, setsParameters ) {

  /* Setup */
  js.setParameters( -1.1, 1.2 );
  mInputStream.str( "1.0 -1.3" );
  mExpectedOutput = "Parameter a? Parameter b? ";

  /* Stimulus */
  setJuliaParameters( mInputStream, mOutputStream, js );
  const JuliaSet& js_const = js;

  /* Comparison */
  EXPECT_EQ( mExpectedOutput, mOutputStream.str( ) );
  EXPECT_EQ(  1.0, js_const.getA( ) );
  EXPECT_EQ( -1.3, js_const.getB( ) );

  /* Tear-down */
  // Done automatically
}



TEST_F( JuliaSetSetJuliaParametersTest, setsParameters2 ) {

  /* Setup */
  js.setParameters( -1.1, 1.2 );
  mInputStream.str( "-0.3 1.11" );
  mExpectedOutput = "Parameter a? Parameter b? ";

  /* Stimulus */
  setJuliaParameters( mInputStream, mOutputStream, js );
  const JuliaSet& js_const = js;

  /* Comparison */
  EXPECT_EQ( mExpectedOutput, mOutputStream.str( ) );
  EXPECT_EQ( -0.3, js_const.getA( ) );
  EXPECT_EQ(  1.11, js_const.getB( ) );

  /* Tear-down */
  // Done automatically
}
