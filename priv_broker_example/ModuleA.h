// LICENSETEXT
//
//   Copyright (C) 2009-2010 : GreenSocs Ltd
// 	 http://www.greensocs.com/ , email: info@greensocs.com
//
//   Developed by:
//    Christian Schroeder <schroeder@eis.cs.tu-bs.de>,
//    Mark Burton, mark@greensocs.com
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


#ifndef __MODULEA_H__
#define __MODULEA_H__


#include <systemc>
#include "ex_globals.h"
#include "cci.h"
#include "cci_params.h"
#include "cci_api.h"

#include "gs_cci_cnf_private_broker.h"

#include "ModuleB.h"

/// Module which owns some cci parameters.
class ModuleA
//: public cci::cnf::cci_broker_manager_module
: public sc_core::sc_module
, public cci::cnf::cci_broker_manager
{
  
public:
  
  SC_HAS_PROCESS(ModuleA);
	
  /// Constructor
  ModuleA(sc_core::sc_module_name name)
  //: cci::cnf::cci_broker_manager_module(name, new cci::cnf::gs_cci_private_broker(this, "int_param", END_OF_PUBLIC_PARAM_LIST))
  : sc_core::sc_module(name)
  , cci::cnf::cci_broker_manager(new cci::cnf::gs_cci_private_broker(this, "int_param", END_OF_PUBLIC_PARAM_LIST))
  , int_param ("int_param", 50 )
  , uint_param("uint_param", 12000)
  , uint_param2("uint_param2", 12)
  , str_param ("str_param", "This is a test string.")
  , bool_param("bool_param") // no default value
  , m_modB("ModuleB")
  { 
    SC_THREAD(main_action);
  }
  
  ~ModuleA() {
    // Don't delete while params existing!
    /*cci::cnf::cci_cnf_broker* pb = get_broker();
    register_private_broker(NULL);
    delete pb;*/
  }
  
  /// Main action to make tests with parameters.
  void main_action();
  
  /// Example parameter.
  cci::cnf::cci_param<int>             int_param;
  /// Example parameter.
  cci::cnf::cci_param<unsigned int>    uint_param;
  /// Example parameter.
  cci::cnf::cci_param<unsigned int>    uint_param2;
  /// Example parameter.
  cci::cnf::cci_param<std::string>     str_param;
  /// Example parameter.
  cci::cnf::cci_param<bool>            bool_param;
  
protected:
  ModuleB m_modB;
};


#endif