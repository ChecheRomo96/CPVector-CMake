#include <gtest/gtest.h>
#include <CPVector.h>
#include <iostream>

//////////////////////////////////////////////////////////////////////////////////
// exception

    TEST(Exceptions, exception )
    {
        EXPECT_THROW({
            try
            {
                throw CPVector::exception();
            }
            catch( const CPVector::exception& e )
            {
                // and this tests that it has the correct message
                EXPECT_STREQ( "CPVector::exception", e.what() );
                throw;
            }
        }, CPVector::exception );
    }
//
//////////////////////////////////////////////////////////////////////////////////
// logic_error

    TEST(Exceptions, logic_error )
    {
        EXPECT_THROW({
            try
            {
                throw CPVector::logic_error();
            }
            catch( const CPVector::logic_error& e )
            {
                // and this tests that it has the correct message
                EXPECT_STREQ( "CPVector::logic_error", e.what() );
                throw;
            }
        }, CPVector::logic_error );
    }
//
//////////////////////////////////////////////////////////////////////////////////
// bad_alloc

    TEST(Exceptions, bad_alloc )
    {
        EXPECT_THROW({
            try
            {
                throw CPVector::bad_alloc();
            }
            catch( const CPVector::bad_alloc& e )
            {
                // and this tests that it has the correct message
                EXPECT_STREQ( "CPVector::bad_alloc", e.what() );
                throw;
            }
        }, CPVector::bad_alloc );
    }
//
//////////////////////////////////////////////////////////////////////////////////
// out_of_range

    TEST(Exceptions, out_of_range )
    {
        EXPECT_THROW({
            try
            {
                throw CPVector::out_of_range();
            }
            catch( const CPVector::out_of_range& e )
            {
                // and this tests that it has the correct message
                EXPECT_STREQ( "CPVector::out_of_range", e.what() );
                throw;
            }
        }, CPVector::out_of_range );
    }
//
//////////////////////////////////////////////////////////////////////////////////
// out_of_range

    TEST(Exceptions, out_of_range2 )
    {
        EXPECT_THROW({
            try
            {
                CPVector::vector<uint8_t> vec(5);

                vec[5];
            }
            catch( const CPVector::out_of_range& e )
            {
                // and this tests that it has the correct message
                EXPECT_STREQ( "CPVector::out_of_range", e.what() );
                throw;
            }
        }, CPVector::out_of_range );
    }
//
//////////////////////////////////////////////////////////////////////////////////
// length_error

    TEST(Exceptions, length_error )
    {
        EXPECT_THROW({
            try
            {
                throw CPVector::length_error();
            }
            catch( const CPVector::length_error& e )
            {
                // and this tests that it has the correct message
                EXPECT_STREQ( "CPVector::length_error", e.what() );
                throw;
            }
        }, CPVector::length_error );
    }
//
//////////////////////////////////////////////////////////////////////////////////