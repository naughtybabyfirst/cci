/*****************************************************************************
  Copyright 2016 Accellera Systems Initiative Inc.
  All rights reserved.

  Copyright 2009-2010 GreenSocs
  All rights reserved.
  Authors:
      Christian Schroeder <schroeder@eis.cs.tu-bs.de>
      Mark Burton <mark@greensocs.com>

  Copyright 2016 Ericsson
  All rights reserved.

  Licensed under the Apache License, Version 2.0 (the "License");
  you may not use this file except in compliance with the License.
  You may obtain a copy of the License at

    http://www.apache.org/licenses/LICENSE-2.0

  Unless required by applicable law or agreed to in writing, software
  distributed under the License is distributed on an "AS IS" BASIS,
  WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
  See the License for the specific language governing permissions and
  limitations under the License.
 *****************************************************************************/


#ifndef __MODULEB_H__
#define __MODULEB_H__


#include <systemc>
#include "ex_globals.h"
#include "cci_configuration"
#include "ModuleC.h"

/// Module which owns some cci parameters.
class ModuleB
: public sc_core::sc_module
{
  
public:
  
  SC_HAS_PROCESS(ModuleB);
	
  /// Constructor
  ModuleB(sc_core::sc_module_name name);
  
  /// Main action to make tests with parameters.
  void main_action();
  
  /// Example parameter.
  cci::cci_param<int>             int_param;
  /// Example parameter.
  cci::cci_param<unsigned int>    uint_param;
  /// Example parameter.
  cci::cci_param<unsigned int>    uint_param2;
  /// Example parameter.
  cci::cci_param<std::string>     str_param;
  /// Example parameter.
  cci::cci_param<bool>            bool_param;
  
protected:
  
  /// Points to the broker being responsible for this module; This is needed to be set during construction to get the correct private broker from stack
  /// Alternatively this module could derive from the cci_broker_manager even without having an own private broker - that would allow to use its get_broker() function
  cci::cci_broker_if* m_broker_accessor;
  
  ModuleC mC;
};


#endif
