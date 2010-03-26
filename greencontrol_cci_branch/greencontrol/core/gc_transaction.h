//   GreenControl framework
//
// LICENSETEXT
//
//   Copyright (C) 2007-2010 : GreenSocs Ltd
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

// doxygen comments

// If GCLOG_RETURN is used for the project it has to be set before GC_Logger.h or gc_transaction.h are included the first time. If it isn't defined while
// the header is included the first time, the flag GCLOG_RETURN_NOT_DEFINED is set. So if GCLOG_RETURN is set after the first inclusion of the header but not
// before, a warning is issued, because the GCLOG_RETURN flag has no effect in this case.
#ifdef GCLOG_RETURN
  #ifdef GCLOG_RETURN_NOT_DEFINED
    #ifdef _MSC_VER
      #pragma message("Warning: GCLOG_RETURN is not defined before including GC_Logger.h or gc_transaction.h. Transactions returning from their receivers won't be logged!")
    #else
      #warning GCLOG_RETURN is not defined before including GC_Logger.h or gc_transaction.h. Transactions returning from their receivers won't be logged!
    #endif
  #endif
#endif

#ifndef __GC_TRANSACTION_H__
#define __GC_TRANSACTION_H__

#ifndef GCLOG_RETURN
  #define GCLOG_RETURN_NOT_DEFINED
#endif

#include <sstream>

#include "boost/shared_ptr.hpp"
#include "transport/unevenpair.h"
#include "transport/gs_datatypes.h"
#include "greencontrol/gclog/log_config.h"
#include "log_if.h"
#include "command_if.h"

// for output:
#ifdef GC_VERBOSE
# include "greencontrol/gcnf/plugin/gcnf_datatypes.h"
#endif


namespace gs {
namespace ctr {

using boost::shared_ptr;
  
// based on the GernericTransaction

/// Control service specifier.
/**
 * Control service to route the transactions in the GreenControl Core 
 * and announce supported service from API or plugin to the Core.
 */
enum ControlService {
  /// No service.
  NO_SERVICE=0,
  // Config Service, provided by ConfigPlugin
  CONFIG_SERVICE=1,
  // Analysis and Visibility Service
  AV_SERVICE=2,
  // Logging Service
  LOG_SERVICE=3
};

/// Static method to get the string representation of the ControlService enumeration.
/**
 * @param cs  ControlService enumeration.
 * @return    String representation of cs.
 */
static const string getControlServiceString(enum ControlService cs) {
  switch (cs) {
    case NO_SERVICE:
      return string("NO_SERVICE");
    case CONFIG_SERVICE:
      return string("CONFIG_SERVICE");
    case AV_SERVICE:
      return string("AV_SERVICE");
    case LOG_SERVICE:
      return string("LOG_SERVICE");
    default:
      return string("unknown service");
  }
}

using gs::log::LogConfig;

/// Forward declaration of gc_port_if. Normal #include leads to cyclic inclusion.
class gc_port_if;

/// Type of the address for APIs and plugins.
typedef gc_port_if* cport_address_type;
   
/// Pointer
typedef void* AnyPointer;
typedef log_if* LogPointer;
typedef command_if* CommandPointer;
typedef LogConfig* LogConfigPointer;

/// Target object (e.g. parameter name).
typedef std::string ControlSpecifier;

/// Transported value.
typedef std::string ControlValue;

  

// //////////////   ControlTransaction   /////////////////////

/// Control transaction class.
/**
 * The default control transaction class is the container for submitted 
 * transactions. The command field is set with specialized enumerations
 * for the special service.
 */
class ControlTransaction
{
public:

  /// Constructor without parameters
  /**
   * The members are set to initial values.
   */
  ControlTransaction()
    : mService(NO_SERVICE),
      mCmd(0)
  {
    mTarget = 0;
    mValue  = "";
    mSpecifier = "";
    mError = 0;
    mAnyPointer = NULL;
    mAnyPointer2 = NULL;
    mMetaData = "";
    mLogPointer = NULL;
    mCmdIf = NULL;
    // Has to be initialized, because this NULL pointer is used as the end of the stack.
    mLogConfig = NULL;

    mHasChanged = false;

    // Use a default configuration object, so the LogConfig pointer is never NULL. This way the pointer doesn't have to be checked
    // each time a set_m*() method is called if GCLOG_RETURN is activated. Filters can use their own configs by activating them.
    // But after deactivating the filter configs, this default config is used again, especially to mark the changes made to a transaction
    // by its receiver before returning it, if GCLOG_RETURN is enabled. The default object can't be deactivated once it is in the stack.
    activateConfig(new LogConfig());
  }

  /// Copy constructor.
  ControlTransaction(const ControlTransaction &t) {
    *this = t; // use copy-operator
  }

  /// Destructor.
  ~ControlTransaction()
  {
    // Deactivate all configs that are activated within this transaction, except the default config object. This was created within
    // the transaction, so it has to be destroyed here.
    while(mLogConfig->hasNextConfig())
      deactivateConfig();

    delete mLogConfig;
  }
    
protected:
  // quarks (also add in copy operator!)

  /// Command (equal to plugin address).
  ControlService mService; 
  /// Address of the target API or plugin (pointer address of the target gc_port).
  cport_address_type  mTarget;  
  /// Command enumeration, specialized by the service. Default for no command is '0'!
  unsigned int mCmd;
  /// void Pointer to be used for any kind of pointer transmission
  AnyPointer mAnyPointer;
  /// another void Pointer to be used for any kind of pointer transmission
  AnyPointer mAnyPointer2;
  /// unsigned int to be used for any kind of unsigned int transmission
  unsigned int mAnyUint;
  /// Specifier for specifier dependent on service and command (e.g. parameter name).
  ControlSpecifier  mSpecifier;  
  /// Transported data dependent on service and command (e.g. parameter value).
  ControlValue   mValue;   
  /// ID (API's or plugin's address) of sending master.
  cport_address_type   mID;
  /// Error flag (mError != 0: error).
  unsigned int   mError;  
  /// String to hold meta data
  std::string   mMetaData;
  /// log_if pointer to be used for any data transmission, providing additional information about the payload.
  LogPointer mLogPointer;
  /// command_if pointer to API or plugin (for string information about the command)
  CommandPointer mCmdIf;
  /// LogConfig pointer to configurations used to control logger output.
  LogConfigPointer mLogConfig;

  bool mHasChanged;


//     operator GenericTargetAccess() {
//       return reinterpret_cast<GenericTargetAccess&>(*this);
//     }
//     operator GenericMasterAccess() {
//       return reinterpret_cast<GenericMasterAccess&>(*this);
//     }

public:
  // quark access
  void set_mService(const ControlService& _mService){
    mService=_mService;
#ifdef GCLOG_RETURN
    // if the GCLOG_RETURN flag is active, every modification inside the transaction has to be recorded
    mHasChanged = true;
    mLogConfig->setService(true);
#endif
  }

  void set_mTarget(const cport_address_type& _mTarget){
    mTarget=_mTarget;
#ifdef GCLOG_RETURN
    mHasChanged = true;
    mLogConfig->setTarget(true);
#endif
  }

  void set_mCmd(const unsigned int& _mCmd){
    mCmd=_mCmd;
#ifdef GCLOG_RETURN
    mHasChanged = true;
    mLogConfig->setCmd(true);
#endif
  }

  void set_mAnyPointer(const AnyPointer& _mAnyPointer){
    mAnyPointer=_mAnyPointer;
#ifdef GCLOG_RETURN
    mHasChanged = true;
    mLogConfig->setAnyPointer(true);
#endif
  }

  void set_mAnyPointer2(const AnyPointer& _mAnyPointer2){
    mAnyPointer2=_mAnyPointer2;
#ifdef GCLOG_RETURN
    mHasChanged = true;
    mLogConfig->setAnyPointer2(true);
#endif
  }

  void set_mAnyUint(const unsigned int _mAnyUint){
    mAnyUint=_mAnyUint;
#ifdef GCLOG_RETURN
    mHasChanged = true;
    mLogConfig->setAnyUint(true);
#endif
  }

  void set_mSpecifier(const ControlSpecifier& _mSpecifier){
    mSpecifier=_mSpecifier;
#ifdef GCLOG_RETURN
    mHasChanged = true;
    mLogConfig->setSpecifier(true);
#endif
  }

  void set_mValue(const ControlValue& _mValue){
    mValue=_mValue;
#ifdef GCLOG_RETURN
    mHasChanged = true;
    mLogConfig->setValue(true);
#endif
  }

  void set_mID(const cport_address_type& _mID){
    mID=_mID;
#ifdef GCLOG_RETURN
    mHasChanged = true;
    mLogConfig->setID(true);
#endif
  }

  void set_mError(const unsigned int _mError){
    mError=_mError;
#ifdef GCLOG_RETURN
    mHasChanged = true;
    mLogConfig->setError(true);
#endif
  }

  void set_mMetaData(std::string _mMetaData){
    mMetaData=_mMetaData;
#ifdef GCLOG_RETURN
    mHasChanged = true;
    mLogConfig->setMetaData(true);
#endif
  }

  void set_mLogPointer(const LogPointer& _mLogPointer){
    mLogPointer=_mLogPointer;
#ifdef GCLOG_RETURN
    mHasChanged = true;
    mLogConfig->setLogPointer(true);
#endif
  }

  void set_mCmdIf(const CommandPointer& _mCmdIf){
    mCmdIf=_mCmdIf;
#ifdef GCLOG_RETURN
    mHasChanged = true;
    mLogConfig->setCmdIf(true);
#endif
  }

  const ControlService& get_mService() const {return mService; }
  const cport_address_type& get_mTarget() const {return mTarget; }
  const unsigned int& get_mCmd() const {return mCmd; }
  const AnyPointer& get_mAnyPointer() const {return mAnyPointer; }
  const AnyPointer& get_mAnyPointer2() const {return mAnyPointer2; }
  const unsigned int get_mAnyUint() const {return mAnyUint; }
  const ControlSpecifier& get_mSpecifier() const {return mSpecifier; }
  const ControlValue& get_mValue() const {return mValue; }
  const cport_address_type& get_mID() const {return mID; }
  const unsigned int get_mError() const {return mError; }
  std::string get_mMetaData() const {return mMetaData; }
  const LogPointer& get_mLogPointer() const {return mLogPointer;}
  const CommandPointer& get_mCmdIf() const {return mCmdIf;}
  const LogConfigPointer& get_mLogConfig() const {return mLogConfig;}

  /// Returns the name of the command specified by the mCmd quark, if the mCmdIf quark is valid.
  std::string getCommandName() const
  {
    if(mCmdIf)
      return mCmdIf->getCommandName(mCmd);
    else
      return std::string("Warning: API/Plugin doesn't implement command_if!");
  }

  /// Returns a description of the command specified by the mCmd quark, if the mCmdIf quark is valid.
  std::string getCommandDescription() const
  {
    if(mCmdIf)
      return mCmdIf->getCommandDescription(mCmd);
    else
      return std::string("Warning: API/Plugin doesn't implement command_if!");
  }

  /// Returns the name of the sender of the transaction, if the mCmdIf quark is valid.
  std::string getSenderName() const
  {
    if(mCmdIf)
      return mCmdIf->getName();
    else
      return std::string("Warning: API/Plugin doesn't implement command_if!");
  }

  /// Activate a LogConfig by pushing it into the integrated stack.
  void activateConfig(LogConfig* config)
  {
    if(config)
    {
      // Push the config into the stack, if it isn't active.
      if(!config->isActive())
      {
        config->setNextConfig(mLogConfig);
        config->setActive(true);
        mLogConfig = config;
      }
      else
        SC_REPORT_WARNING("ControlTransaction::activateConfig()", "Trying to activate a LogConfig which is already active.");
    }
    else
      SC_REPORT_WARNING("ControlTransaction::activateConfig()", "Trying to call activateConfig() with a NULL pointer.");
  }

  /// Deactivate the currently active LogConfig by deleting it from the integrated stack.
  void deactivateConfig()
  {
    // Deactivate the currently active config, if it isn't the default config of the transaction.
    if(mLogConfig->hasNextConfig())
    {
      mLogConfig->setActive(false);
      mLogConfig = mLogConfig->getNextConfig();
    }
    else
      SC_REPORT_WARNING("ControlTransaction::deactivateConfig()", "Trying to deactivate the default LogConfig, which is not allowed.");
  }

#ifdef GCLOG_RETURN
  /// Reset the flag that shows if a transation has changed since the last call of this method.
  /**
   * Reset the flag that shows if a transation has changed since the last call of this method. Also the currently
   * active LogConfig in the stack is reset to true.
   */
  void resetChangeFlag()
  {
    mHasChanged = false;
    mLogConfig->reset(true);
  }
#else
  void resetChangeFlag()
  {
  }
#endif

  /// Returns whether the transaction was modified since the last reset of the flag.
  bool hasChanged()
  {
    return mHasChanged;
  }

  /// Resets a transaction so it can be reused.
  /**
   * mID is not resetted because it is set automatically in the port.
   *
   * Only reset quarks that need to be resetted!!
   */
  void reset() {
    // TODO: check if quarks are missing
    mService= NO_SERVICE; // Do not remove this reset. Ensured in documetation to be reseted
    //mCmd    = 0;
    //mTarget = 0;
    //mValue  = "";
    mAnyPointer = NULL;  // must be resetted because of the config command CMD_ADD_PARAM which is used by legacy APIs  with string and by current APIs with this pointer. If a legacy API gets a transaction for an add command which was used by another API with this pointer before, the legacy API will not reset the pointer but only set the specifier.
    //mAnyPointer2 = NULL;
    // not reset mAnyUint
    //mSpecifier = "";
    mError = 0; // Do not remove this reset. Ensured in documetation to be reseted
    mMetaData = "";
    mLogPointer = NULL; // has to be resetted, because the logger or other classes may use some log_if methods if the pointer isn't NULL, but the object could already be destroyed.
  }
  
  /// Copy operator.
  ControlTransaction & operator=(const ControlTransaction &t) {
    if (&t==this)
      return *this;

    mService= t.mService;
    mTarget = t.mTarget;
    mCmd    = t.mCmd;
    mAnyPointer = t.mAnyPointer;
    mAnyPointer2 = t.mAnyPointer2;
    mAnyUint = t.mAnyUint;
    mSpecifier = t.mSpecifier;
    mValue  = t.mValue;
    mID     = t.mID;
    mError  = t.mError;
    mMetaData  = t.mMetaData;
    mLogPointer = t.mLogPointer;
    mCmdIf = t.mCmdIf;
    // Don't copy mLogConfig!!! This could compromise the internal stack, since two or more transactions use the same objects in their stacks. If one transaction
    // deactivates its config, the config may get reactivated, which could lead to loops in the stack.

    mHasChanged = t.mHasChanged;

    // TODO: check if quarks are missing
    
    return *this;
  }

  /// Get human readable string of the transaction.
  std::string toString() const { 
    std::stringstream ss;
    ss << "  Transaction " << this << ":"  << std::endl 
       << "    mService     = " << mService << " (" << getControlServiceString(mService) << ")"  << std::endl
       << "    mTarget      = " << mTarget      << std::endl 
       << "    mCmd         = " << mCmd; 
#ifdef GC_VERBOSE
# ifdef __GCNF_DATATYPES_H__
    if (mService == CONFIG_SERVICE)
      ss << " (" << cnf::gcnfCommandToString(mCmd) << ")";
# endif
# ifdef __gav_datatypes_h__
    if (mService == AV_SERVICE)
      ss << " (" << av::gavCommandToString(mCmd) << ")";
# endif
#endif
    ss << std::endl
       << "    mAnyPointer  = " << mAnyPointer  << std::endl
       << "    mAnyPointer2 = " << mAnyPointer2 << std::endl
       << "    mAnyUint     = " << mAnyUint     << std::endl
       << "    mSpecifier   = " << mSpecifier   << std::endl 
       << "    mValue       = " << mValue       << std::endl 
       << "    mID          = " << mID          << std::endl 
       << "    mMetaData    = " << mMetaData    << std::endl 
       << "    mError       = " << mError       << std::endl
       << "    mLogPointer  = " << mLogPointer  << std::endl
       << "    mCmdIf       = " << mCmdIf       << std::endl
       << "    mLogConfig   = " << mLogConfig;
    return ss.str();
  }

  /// Get detailed human readable string of the transaction, including information provided by log_if.
  std::string toDetailedString() const
  {
    std::stringstream ss;
    ss << "  Transaction " << this;
    if(!mHasChanged)
      ss << ":\n";
    else
      ss << " returning:\n";
    ss << "    mService     = " << mService     << " (" << getControlServiceString(mService) << ")"  << std::endl
       << "    mTarget      = " << mTarget      << std::endl 
       << "    mCmd         = " << mCmd         << " (" << getCommandName() << ")" << std::endl
       << "    mAnyPointer  = " << mAnyPointer  << std::endl
       << "    mAnyPointer2 = " << mAnyPointer2 << std::endl
       << "    mAnyUint     = " << mAnyUint     << std::endl
       << "    mSpecifier   = " << mSpecifier   << std::endl 
       << "    mValue       = " << mValue       << std::endl 
       << "    mID          = " << mID          << " (" << getSenderName() << ")" << std::endl 
       << "    mMetaData    = " << mMetaData    << std::endl 
       << "    mError       = " << mError       << std::endl
       << "    mLogPointer  = " << mLogPointer;
    if(mLogPointer)
      ss << " ( " << mLogPointer->toString() << " )" << std::endl;
    else
      ss << std::endl;
    ss << "    mCmdIf       = " << mCmdIf       << std::endl
       << "    mLogConfig   = " << mLogConfig;
    return ss.str();
  }

  /// Get complete human readable string of the transaction for debugging.
  std::string toDebugString() const
  {
    LogConfig* pConf;
    std::stringstream ss;

    pConf = mLogConfig->getNextConfig();
    ss << "  Transaction " << this;
    if(!mHasChanged)
      ss << ":" << std::endl;
    else
      ss << " returning:" << std::endl;
    ss << "    mHasChanged      = " << mHasChanged << std::endl
       << "    mService     (" << mLogConfig->getService()     << ") = " << mService     << " (" << getControlServiceString(mService) << ")"  << std::endl
       << "    mTarget      (" << mLogConfig->getTarget()      << ") = " << mTarget      << std::endl 
       << "    mCmd         (" << mLogConfig->getCmd()         << ") = " << mCmd         << " (" << getCommandName() << ")" << std::endl
       << "    mAnyPointer  (" << mLogConfig->getAnyPointer()  << ") = " << mAnyPointer  << std::endl
       << "    mAnyPointer2 (" << mLogConfig->getAnyPointer2() << ") = " << mAnyPointer2 << std::endl
       << "    mAnyUint     (" << mLogConfig->getAnyUint()     << ") = " << mAnyUint     << std::endl
       << "    mSpecifier   (" << mLogConfig->getSpecifier()   << ") = " << mSpecifier   << std::endl 
       << "    mValue       (" << mLogConfig->getValue()       << ") = " << mValue       << std::endl 
       << "    mID          (" << mLogConfig->getID()          << ") = " << mID          << " (" << getSenderName() << ")" << std::endl 
       << "    mMetaData    (" << mLogConfig->getMetaData()    << ") = " << mMetaData    << std::endl 
       << "    mError       (" << mLogConfig->getError()       << ") = " << mError       << std::endl
       << "    mLogPointer  (" << mLogConfig->getLogPointer()  << ") = " << mLogPointer;
    if(mLogPointer)
      ss << " ( " << mLogPointer->toString() << " )" << std::endl;
    else
      ss << std::endl;
    ss << "    mCmdIf       (" << mLogConfig->getCmdIf()       << ") = " << mCmdIf << std::endl
       << "    mLogConfig   (" << mLogConfig->getLogConfig()   << ") = " << mLogConfig << " (hasChanged: " << mLogConfig->hasChanged() << ")" << std::endl
       << "    -> pNext     (" << mLogConfig->hasNextConfig()  << ") = " << pConf;

    // show the configs in the stack
    while(pConf != NULL)
    {
      pConf = pConf->getNextConfig();
      ss << " -> " << pConf;
    }

    return ss.str();
  }

  /// Get human readable string of the transaction, using the currently active LogConfig object.
  std::string toConfigString() const
  {
    std::stringstream ss;
    ss << "  Transaction " << this;
    if(!mHasChanged)
      ss << ":\n";
    else
      ss << " returning:\n";
    if(mLogConfig->getService())     ss << "    mService     = " << mService     << " (" << getControlServiceString(mService) << ")\n";
    if(mLogConfig->getTarget())      ss << "    mTarget      = " << mTarget      << "\n";
    if(mLogConfig->getCmd())         ss << "    mCmd         = " << mCmd         << " (" << getCommandName() << ")\n";
    if(mLogConfig->getAnyPointer())  ss << "    mAnyPointer  = " << mAnyPointer  << "\n";
    if(mLogConfig->getAnyPointer2()) ss << "    mAnyPointer2 = " << mAnyPointer2 << "\n";
    if(mLogConfig->getAnyUint())     ss << "    mAnyUint     = " << mAnyUint     << "\n";
    if(mLogConfig->getSpecifier())   ss << "    mSpecifier   = " << mSpecifier   << "\n";
    if(mLogConfig->getValue())       ss << "    mValue       = " << mValue       << "\n";
    if(mLogConfig->getID())          ss << "    mID          = " << mID          << " (" << getSenderName() << ")\n";
    if(mLogConfig->getMetaData())    ss << "    mMetaData    = " << mMetaData    << "\n";
    if(mLogConfig->getError())       ss << "    mError       = " << mError       << "\n";
    if(mLogConfig->getLogPointer())
    {
      ss << "    mLogPointer  = " << mLogPointer;
      if(mLogPointer)
        ss << " ( " << mLogPointer->toString() << " )\n";
      else
        ss << "\n";
    }
    if(mLogConfig->getCmdIf())     ss << "    mCmdIf       = " << mCmdIf       << "\n";
    if(mLogConfig->getLogConfig()) ss << "    mLogConfig   = " << mLogConfig   << "\n";
    return ss.str();
  }

  // TODO: GenericTransaction in generic.static_casts.h provides more functionality
  
};


/// Shared pointer type for GenericTransaction. 
typedef shared_ptr<ControlTransaction>               ControlTransactionHandle;


} // end namespace ctr
} // end namespace gs   
  
#endif
