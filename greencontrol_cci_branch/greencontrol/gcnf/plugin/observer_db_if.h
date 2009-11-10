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

// doygen comments

#ifndef __OBSERVER_DB_IF_H__
#define __OBSERVER_DB_IF_H__

#include "greencontrol/core/gc_globals.h"


namespace gs {
namespace cnf {


/// SystemC interface to allow the ConfigPlugin to get access to the observer database.
/**
 * The observer database has to implement this interface to be connected to the port of the
 * observer_port of the ConfigPlugin.
 */
struct observer_db_if
: virtual public sc_interface
{
public:

  /// Adds an observer to the observer list of the parameter.
  /**
   * Creates an implicit parameter if parameter does not (yet) exist.
   *
   * @param hier_parname  Parameter name to whom the observer should be added.
   * @param observer      Address of the observer.
   * @return              Success, if adding successful and parameter existing.
   */
  //virtual bool registerObserver(const std::string &hier_parname, const cport_address_type observer) = 0;
  
  /// Get a list (set) of all oberserver APIs for the parameter.
  /**
   * Creates an implicit parameter if parameter does not (yet) exist.
   *
   * @param hier_parname  Parameter whose observers should be returned.
   * @return              Set containing API addresses.
   */
  //virtual const std::set<cport_address_type> getObservers(const std::string &hier_parname) = 0;

  /// Adds an observer for new added (or first time set implicit) parameter to the database.
  /**
   * @param observer      Address of the observer.
   * @return              Success, if adding successful.
   */
  virtual bool registerNewParamObserver(const cport_address_type observer) = 0;
  
  /// Get a list (set) of all oberserver APIs for new added (or first time set implicit) parameters.
  /**
   * @return              Set containing API addresses.
   */
  virtual const std::set<cport_address_type> getNewParamObservers() = 0;

};


} // end namespace cnf
} // end namespace gs

#endif