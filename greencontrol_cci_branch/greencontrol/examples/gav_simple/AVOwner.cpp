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


#include "AVOwner.h"

using namespace std;
using namespace sc_core;

void AVOwner::main_action() {

  cout << endl << endl;
  cout << name() << ": set parameters to different values at different time points" << endl;

  //m_GAV_Api.add_to_default_output(gs::av::CSV_FILE_OUT, &uint_param);
  uint_param = 1;

  wait(1, SC_NS);
  int_param = 100;
  uint_param = 670;
  str_param = "Hello World!";
  int_param = 101;
  wait(SC_ZERO_TIME);
  
  wait(1, SC_NS);
  int_param = 102;
  int_param = 103;
  int_param = 104;
  wait(SC_ZERO_TIME);
  int_param = 105;
  int_param = 106;
  
  str_param = "Hello Germany!";
  wait(SC_ZERO_TIME);
  str_param = "Hello Arizona!";
  wait(SC_ZERO_TIME);
  str_param = "Hello France!";

  cout << endl << endl;

}