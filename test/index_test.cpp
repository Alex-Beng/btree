//  index_test.cpp  --------------------------------------------------------------------//

//  Copyright Beman Dawes 2013

//  Distributed under the Boost Software License, Version 1.0.
//  See http://www.boost.org/LICENSE_1_0.txt

//--------------------------------------------------------------------------------------//
//                                                                                      //
//  These tests lightly exercise many portions of the interface. They do not attempt    //
//  to stress the many combinations of control paths possible in large scale use.       //
//                                                                                      //
//--------------------------------------------------------------------------------------//

#include <boost/btree/index.hpp>
#include <boost/detail/lightweight_main.hpp>
#include <boost/detail/lightweight_test.hpp>

#include <iostream>
#include <iomanip>
#include <utility>
#include <set>
#include <algorithm>

using namespace boost;
namespace fs = boost::filesystem;
using std::cout;
using std::endl;
using std::make_pair;

namespace
{
bool dump_dot(false);

filesystem::path file_path("test.file");
filesystem::path idx1_path("test.1.idx");
filesystem::path idx2_path("test.2.idx");


//-------------------------------------- instantiate -----------------------------------//

void instantiate_test()
{
  cout << "  instantiate_test..." << endl;

  // set
  {
    btree::btree_index<int> x;
    BOOST_TEST(!x.is_open());
    BOOST_TEST(x.index_size() == 0U);
    BOOST_TEST(x.index_empty());
  }
 
  cout << "    instantiate_test complete" << endl;
}


//---------------------------------  open_all_new_test  --------------------------------//

void  open_all_new_test()
{
  cout << "  open_all_new_test..." << endl;

  {
    cout << "      default construct, then open..." << endl;
    btree::btree_index<int> idx;
    idx.open(file_path, 1000000u, idx1_path, btree::flags::truncate, -1, 128);
    BOOST_TEST(idx.is_open());
    BOOST_TEST_EQ(idx.file_path(), file_path);
    BOOST_TEST_EQ(idx.file_size(), 0u);
    BOOST_TEST_EQ(idx.file_reserve(), 1000000u);
    BOOST_TEST_EQ(idx.index_path(), idx1_path);
    BOOST_TEST_EQ(idx.index_size(), 0u);
  }

  {
    cout << "      open via constructor..." << endl;
    btree::btree_index<int> idx(file_path, 1000000,
      idx1_path, btree::flags::truncate, -1, 128);
    BOOST_TEST(idx.is_open());
    BOOST_TEST_EQ(idx.file_path(), file_path);
    BOOST_TEST_EQ(idx.file_size(), 0u);
    BOOST_TEST_EQ(idx.file_reserve(), 1000000u);
    BOOST_TEST_EQ(idx.index_path(), idx1_path);
    BOOST_TEST_EQ(idx.index_size(), 0u);
  }

  cout << "    open_all_new_test complete" << endl;
}

//---------------------------------  open_new_index_test  ------------------------------//

void  open_new_index_test()
{
  cout << "  open_new_index_test with existing flat file..." << endl;

  cout << "    open_new_index_test with existing flat file complete" << endl;
}

//-------------------------------------  _test  ----------------------------------------//

void  _test()
{
  cout << "  _test..." << endl;

  cout << "     _test complete" << endl;
}

}  // unnamed namespace

//------------------------------------ cpp_main ----------------------------------------//

int cpp_main(int argc, char* argv[])
{
  std::string command_args;

  for (int a = 0; a < argc; ++a)
  {
    command_args += argv[a];
    if (a != argc-1)
      command_args += ' ';
  }

  cout << command_args << '\n';;

  for (; argc > 1; ++argv, --argc) 
  {
    if ( std::strcmp( argv[1]+1, "b" )==0 )
      dump_dot = true;
    else
    {
      cout << "Error - unknown option: " << argv[1] << "\n\n";
      argc = -1;
      break;
    }
  }

  if (argc < 1) 
  {
    cout << "Usage: index_test [Options]\n"
//      " The argument n specifies the number of test cases to run\n"
      " Options:\n"
//      "   path     Specifies the test file path; default test.btree\n"
      "   -d       Dump tree using Graphviz dot format; default is no dump\n"
      ;
    return 1;
  }

  instantiate_test();
  open_all_new_test();
  open_new_index_test();


  cout << "all tests complete" << endl;

  return boost::report_errors();
}


