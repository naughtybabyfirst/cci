//   GreenControl framework
//
// LICENSETEXT
//
//   Copyright (C) 2007 : GreenSocs Ltd
// 	 http://www.greensocs.com/ , email: info@greensocs.com
//
//   Developed by :
//   
//   Christian Schroeder <schroeder@eis.cs.tu-bs.de>,
//   Wolfgang Klingauf <klingauf@eis.cs.tu-bs.de>
//     Technical University of Braunschweig, Dept. E.I.S.
//     http://www.eis.cs.tu-bs.de
//
//
//   This program is free software.
// 
//   If you have no applicable agreement with GreenSocs Ltd, this software
//   is licensed to you, and you can redistribute it and/or modify
//   it under the terms of the GNU General Public License as published by
//   the Free Software Foundation; either version 2 of the License, or
//   (at your option) any later version.
// 
//   If you have a applicable agreement with GreenSocs Ltd, the terms of that
//   agreement prevail.
// 
//   This program is distributed in the hope that it will be useful,
//   but WITHOUT ANY WARRANTY; without even the implied warranty of
//   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
//   GNU General Public License for more details.
// 
//   You should have received a copy of the GNU General Public License
//   along with this program; if not, write to the Free Software
//   Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA
//   02110-1301  USA 
// 
// ENDLICENSETEXT

#ifndef __GC_GLOBALS_H__
#define __GC_GLOBALS_H__

#include <vector>
#include <string>

/**
 * GreenControl globals; 
 * to be included by each file.
 */

// ////////////////// User defines /////////////////////////////// //

// Disables warnings for deprecated methods
//#define NO_DEPRECATED_WARNINGS

// if to show the gsconfig debug information: 
// (beware: Plugin debug outputs are switched separately in their globals files!)
//#define GC_VERBOSE

// ////////////////// Other defines etc. ///////////////////////// //

#include <boost/config.hpp> // needed for SystemC 2.1 (ulong_long issue)
#include <systemc>
#include <greencontrol/core/gs_sc_api_detection.h>

#include "gcexception.h"
#include "transport/gs_datatypes.h"

#define GS_INIT_STANDARD_GREENCONTROL \
  gs::ctr::GC_Core       core; \
  gs::cnf:: ConfigDatabase  cnfdatabase("ConfigDatabase"); \
  gs::cnf:: ConfigPlugin    configPlugin(&cnfdatabase); \
  gs::av::  GAV_Plugin      analysisPlugin(gs::av::STDOUT_OUT)


#define SC_NAME_DELIMITER '.'

#ifdef GC_VERBOSE
# include <stdio.h>
//# define GC_TRACE(name, msg, ...) { printf("@%s /%d (%s): ", sc_core::sc_time_stamp().to_string().c_str(), (unsigned)sc_core::sc_delta_count(), name); printf(msg, ##__VA_ARGS__); printf("\n"); } 
# define GC_DUMP_N(name, msg)       std::cout<<"@"<<sc_core::sc_time_stamp()<<" /"<<(unsigned)sc_core::sc_delta_count()<<" ("<<name  <<"): "<<msg<<std::endl
# define GC_PRINT_SPACE           { std::cout << "." << std::endl; }
// For code which should be run only if GC_VERBOSE
# define IF_VERBOSE(code)         { code }
#else
//# define GC_TRACE(name, msg, ...)
# define GC_DUMP_N(name, msg)
# define GC_PRINT_SPACE
# define IF_VERBOSE(code)
#endif

/*inline void GC_TRACE(std::string name, std::string msg, ...)
{
#if ( defined ( GC_VERBOSE ) )
  {
    printf ( "@%s /%d (%s): "
            , sc_core::sc_time_stamp().to_string().c_str()
            , (unsigned)sc_core::sc_delta_count()
            , name );
    char    buffer [ 1024 ]; // THIS IS A PROBLEM!!!!
    va_list args;
    va_start ( args, msg );
    vsprintf ( buffer, msg, args );
    printf ( "%s\n", buffer );
    va_end ( args )
  }
#endif // USE_GC_TRACE
} */

#ifndef NO_DEPRECATED_WARNINGS
# define DEPRECATED_WARNING(nam, str) SC_REPORT_WARNING(nam, str)
#else
# define DEPRECATED_WARNING(nam, str)
#endif

// ////////////////// //////////////// ////////////////////////// //


namespace gs {
namespace ctr {
  
  using std::string;
  using std::vector;
  using namespace sc_core;
  
} // end namespace ctr
} // end namespace gs

#endif
