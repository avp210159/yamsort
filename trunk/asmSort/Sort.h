/*                                                                        Sort.h
################################################################################
# Encoding: UTF-8                                                  Tab size: 4 #
#                                                                              #
#              ARRAY SORTING ALGORITHMS WRITTEN ON FLAT ASSEMBLER              #
#                                                                              #
# License: LGPLv3+                               Copyleft (Ɔ) 2012, Jack Black #
################################################################################
*/
// This code is part of LinAsm libraries collection
// Web-site: http://linasm.sourceforge.net/
// E-mail: ezamlinsky@gmail.com (Jack Black)
# pragma	once
# include	"Types.h"

# ifdef	__cplusplus
/*
################################################################################
#       C++ prototypes                                                         #
################################################################################
*/
class Array
{
public:

//****************************************************************************//
//      Sorting algorithms                                                    //
//****************************************************************************//

//============================================================================//
//      Quick sort                                                            //
//============================================================================//

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~//
//      Ascending sort order                                                  //
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~//

// Unsigned integer types
static void QuickSortAsc (uint8_t array[], size_t size);
static void QuickSortAsc (uint16_t array[], size_t size);
static void QuickSortAsc (uint32_t array[], size_t size);
static void QuickSortAsc (uint64_t array[], size_t size);

// Signed integer types
static void QuickSortAsc (sint8_t array[], size_t size);
static void QuickSortAsc (sint16_t array[], size_t size);
static void QuickSortAsc (sint32_t array[], size_t size);
static void QuickSortAsc (sint64_t array[], size_t size);

// Floating-point types
static void QuickSortAsc (flt32_t array[], size_t size);
static void QuickSortAsc (flt64_t array[], size_t size);

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~//
//      Descending sort order                                                 //
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~//

// Unsigned integer types
static void QuickSortDsc (uint8_t array[], size_t size);
static void QuickSortDsc (uint16_t array[], size_t size);
static void QuickSortDsc (uint32_t array[], size_t size);
static void QuickSortDsc (uint64_t array[], size_t size);

// Signed integer types
static void QuickSortDsc (sint8_t array[], size_t size);
static void QuickSortDsc (sint16_t array[], size_t size);
static void QuickSortDsc (sint32_t array[], size_t size);
static void QuickSortDsc (sint64_t array[], size_t size);

// Floating-point types
static void QuickSortDsc (flt32_t array[], size_t size);
static void QuickSortDsc (flt64_t array[], size_t size);

//============================================================================//
//      Radix sort                                                            //
//============================================================================//

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~//
//      Ascending sort order                                                  //
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~//

// Unsigned integer types
static void RadixSortAsc (uint8_t array[], uint8_t temp[], size_t size);
static void RadixSortAsc (uint16_t array[], uint16_t temp[], size_t size);
static void RadixSortAsc (uint32_t array[], uint32_t temp[], size_t size);
static void RadixSortAsc (uint64_t array[], uint64_t temp[], size_t size);

// Signed integer types
static void RadixSortAsc (sint8_t array[], sint8_t temp[], size_t size);
static void RadixSortAsc (sint16_t array[], sint16_t temp[], size_t size);
static void RadixSortAsc (sint32_t array[], sint32_t temp[], size_t size);
static void RadixSortAsc (sint64_t array[], sint64_t temp[], size_t size);

// Floating-point types
static void RadixSortAsc (flt32_t array[], flt32_t temp[], size_t size);
static void RadixSortAsc (flt64_t array[], flt64_t temp[], size_t size);

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~//
//      Descending sort order                                                 //
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~//

// Unsigned integer types
static void RadixSortDsc (uint8_t array[], uint8_t temp[], size_t size);
static void RadixSortDsc (uint16_t array[], uint16_t temp[], size_t size);
static void RadixSortDsc (uint32_t array[], uint32_t temp[], size_t size);
static void RadixSortDsc (uint64_t array[], uint64_t temp[], size_t size);

// Signed integer types
static void RadixSortDsc (sint8_t array[], sint8_t temp[], size_t size);
static void RadixSortDsc (sint16_t array[], sint16_t temp[], size_t size);
static void RadixSortDsc (sint32_t array[], sint32_t temp[], size_t size);
static void RadixSortDsc (sint64_t array[], sint64_t temp[], size_t size);

// Floating-point types
static void RadixSortDsc (flt32_t array[], flt32_t temp[], size_t size);
static void RadixSortDsc (flt64_t array[], flt64_t temp[], size_t size);
};
# else
/*
################################################################################
#       C prototypes                                                           #
################################################################################
*/

//****************************************************************************//
//      Sorting algorithms                                                    //
//****************************************************************************//

//============================================================================//
//      Quick sort                                                            //
//============================================================================//

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~//
//      Ascending sort order                                                  //
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~//

// Unsigned integer types
void Array_QuickSortAsc_uint8 (uint8_t array[], size_t size);
void Array_QuickSortAsc_uint16 (uint16_t array[], size_t size);
void Array_QuickSortAsc_uint32 (uint32_t array[], size_t size);
void Array_QuickSortAsc_uint64 (uint64_t array[], size_t size);

// Signed integer types
void Array_QuickSortAsc_sint8 (sint8_t array[], size_t size);
void Array_QuickSortAsc_sint16 (sint16_t array[], size_t size);
void Array_QuickSortAsc_sint32 (sint32_t array[], size_t size);
void Array_QuickSortAsc_sint64 (sint64_t array[], size_t size);

// Floating-point types
void Array_QuickSortAsc_flt32 (flt32_t array[], size_t size);
void Array_QuickSortAsc_flt64 (flt64_t array[], size_t size);

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~//
//      Descending sort order                                                 //
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~//

// Unsigned integer types
void Array_QuickSortDsc_uint8 (uint8_t array[], size_t size);
void Array_QuickSortDsc_uint16 (uint16_t array[], size_t size);
void Array_QuickSortDsc_uint32 (uint32_t array[], size_t size);
void Array_QuickSortDsc_uint64 (uint64_t array[], size_t size);

// Signed integer types
void Array_QuickSortDsc_sint8 (sint8_t array[], size_t size);
void Array_QuickSortDsc_sint16 (sint16_t array[], size_t size);
void Array_QuickSortDsc_sint32 (sint32_t array[], size_t size);
void Array_QuickSortDsc_sint64 (sint64_t array[], size_t size);

// Floating-point types
void Array_QuickSortDsc_flt32 (flt32_t array[], size_t size);
void Array_QuickSortDsc_flt64 (flt64_t array[], size_t size);

//============================================================================//
//      Radix sort                                                            //
//============================================================================//

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~//
//      Ascending sort order                                                  //
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~//

// Unsigned integer types
void Array_RadixSortAsc_uint8 (uint8_t array[], uint8_t temp[], size_t size);
void Array_RadixSortAsc_uint16 (uint16_t array[], uint16_t temp[], size_t size);
void Array_RadixSortAsc_uint32 (uint32_t array[], uint32_t temp[], size_t size);
void Array_RadixSortAsc_uint64 (uint64_t array[], uint64_t temp[], size_t size);

// Signed integer types
void Array_RadixSortAsc_sint8 (sint8_t array[], sint8_t temp[], size_t size);
void Array_RadixSortAsc_sint16 (sint16_t array[], sint16_t temp[], size_t size);
void Array_RadixSortAsc_sint32 (sint32_t array[], sint32_t temp[], size_t size);
void Array_RadixSortAsc_sint64 (sint64_t array[], sint64_t temp[], size_t size);

// Floating-point types
void Array_RadixSortAsc_flt32 (flt32_t array[], flt32_t temp[], size_t size);
void Array_RadixSortAsc_flt64 (flt64_t array[], flt64_t temp[], size_t size);

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~//
//      Descending sort order                                                 //
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~//

// Unsigned integer types
void Array_RadixSortDsc_uint8 (uint8_t array[], uint8_t temp[], size_t size);
void Array_RadixSortDsc_uint16 (uint16_t array[], uint16_t temp[], size_t size);
void Array_RadixSortDsc_uint32 (uint32_t array[], uint32_t temp[], size_t size);
void Array_RadixSortDsc_uint64 (uint64_t array[], uint64_t temp[], size_t size);

// Signed integer types
void Array_RadixSortDsc_sint8 (sint8_t array[], sint8_t temp[], size_t size);
void Array_RadixSortDsc_sint16 (sint16_t array[], sint16_t temp[], size_t size);
void Array_RadixSortDsc_sint32 (sint32_t array[], sint32_t temp[], size_t size);
void Array_RadixSortDsc_sint64 (sint64_t array[], sint64_t temp[], size_t size);

// Floating-point types
void Array_RadixSortDsc_flt32 (flt32_t array[], flt32_t temp[], size_t size);
void Array_RadixSortDsc_flt64 (flt64_t array[], flt64_t temp[], size_t size);

# endif
/*
################################################################################
#                                 END OF FILE                                  #
################################################################################
*/
