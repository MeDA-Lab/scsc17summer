////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @file    def.hpp
/// @brief   The definitions
///
/// @author  Mu Yang <<emfomy@gmail.com>>
///

#ifndef SCSC_DEF_HPP
#define SCSC_DEF_HPP

#include <cassert>

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief  The enumeration of Laplacian construction methods.
///
/// @todo   Finish the enumeration.
///
enum class Method {
  SIMPLE = 0,   ///< Simple  method.
  COMPLEX = 1,  ///< Complex method.
  COUNT,        ///< Used for counting number of methods.
};

#endif  // SCSC_DEF_HPP
