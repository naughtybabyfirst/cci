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


#ifndef __PARAMMANIPULATEMODULE_H__
#define __PARAMMANIPULATEMODULE_H__


#include <systemc>
#include "ex_globals.h"
#include "cci_configuration"


/// Module which changes parameter values of the Module ParameterOwnerModule
class ParamManipulateModule
: public sc_core::sc_module
{
public:

  SC_HAS_PROCESS(ParamManipulateModule);
  ParamManipulateModule(sc_core::sc_module_name name);
  
  /// Main action to make tests with parameters.
  void main_action();

protected:
  /// Pointer the the module's configuration broker
  cci::cci_broker_if* mBroker;

};


#endif
