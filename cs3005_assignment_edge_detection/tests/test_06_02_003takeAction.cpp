#include "image_menu.h"
#include "image_menu.h" // Did you #ifndef your file?

#include "gtest/gtest.h"
#include <fstream>
#include <string>

class RunFileTakeActionTest : public ::testing::Test {
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
  std::string mChoice;
  std::stringstream mInputStream;
  std::stringstream mOutputStream;
  std::string mExpectedOutput;
  PPM mInputImage1, mInputImage2, mOutputImage;
};


TEST_F( RunFileTakeActionTest, runsFile ) {

  /* Setup */
  mExpectedOutput = "File? ";
  mInputStream.str( mTmpFile2 );
  mChoice = "run";

  /* Stimulus */
  takeAction( mInputStream, mOutputStream, mChoice, mInputImage1, mInputImage2, mOutputImage );

  /* Comparison */
  EXPECT_EQ( mExpectedOutput, mOutputStream.str( ) );
  EXPECT_EQ( 13, mInputImage1.getHeight( ) );
  EXPECT_EQ( 17, mInputImage1.getWidth( ) );

  /* Tear-down */
  // Done automatically
}
