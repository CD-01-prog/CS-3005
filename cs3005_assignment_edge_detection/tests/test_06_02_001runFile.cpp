#include "image_menu.h"
#include "image_menu.h" // Did you #ifndef your file?
#include "PPM.h"
#include "PPM.h" // Did you #ifndef your file?

#include "gtest/gtest.h"
#include <fstream>
#include <cstdio>

class RunFileTest : public ::testing::Test {
protected:

  void writeRunFile( const std::string& filename ) {
    std::ofstream fout( filename, std::ios::binary );
    fout << "# Ha! This is a comment." << std::endl;
    fout << "quit" << std::endl;
    fout.close();
  }

  void writeRunFile2( const std::string& filename ) {
    std::ofstream fout( filename, std::ios::binary );
    fout << "# Ha! This is a comment." << std::endl;
    fout << "size 13 17" << std::endl;
    fout << "quit" << std::endl;
    fout.close();
  }

  virtual void SetUp( ) {
    mTmpFile = "tmp_file.cmd";
    mTmpFile2 = "tmp_file_2.cmd";
    mInputStream.str( "" );
    mOutputStream.str( "" );
    writeRunFile( mTmpFile );
    writeRunFile2( mTmpFile2 );
  }

  virtual void TearDown( ) {
    remove( mTmpFile.c_str( ) );
    remove( mTmpFile2.c_str( ) );
  }

  /* data members */
  std::string mTmpFile;
  std::string mTmpFile2;
  std::stringstream mInputStream;
  std::stringstream mOutputStream;
  std::string mExpectedOutput;
  PPM mInputImage1, mInputImage2, mOutputImage;
};

TEST_F( RunFileTest, displaysPrompt ) {

  /* Setup */
  mInputStream.str( mTmpFile.c_str( ) );
  mExpectedOutput = "File? ";

  /* Stimulus */
  runFile( mInputStream, mOutputStream, mInputImage1, mInputImage2, mOutputImage );

  /* Comparison */
  EXPECT_EQ( mExpectedOutput, mOutputStream.str( ) );

  /* Tear-down */
  // Done automatically
}

TEST_F( RunFileTest, runsCommands ) {

  /* Setup */
  mInputStream.str( mTmpFile2 );
  mExpectedOutput = "File? ";

  /* Stimulus */
  runFile( mInputStream, mOutputStream, mInputImage1, mInputImage2, mOutputImage );

  /* Comparison */
  EXPECT_EQ( mExpectedOutput, mOutputStream.str( ) );
  EXPECT_EQ( 13, mInputImage1.getHeight( ) );
  EXPECT_EQ( 17, mInputImage1.getWidth( ) );

  /* Tear-down */
  // Done automatically
}
