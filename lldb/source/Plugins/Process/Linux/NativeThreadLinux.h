//===-- NativeThreadLinux.h ----------------------------------- -*- C++ -*-===//
//
//                     The LLVM Compiler Infrastructure
//
// This file is distributed under the University of Illinois Open Source
// License. See LICENSE.TXT for details.
//
//===----------------------------------------------------------------------===//

#ifndef liblldb_NativeThreadLinux_H_
#define liblldb_NativeThreadLinux_H_

#include "lldb/Host/common/NativeThreadProtocol.h"
#include "lldb/lldb-private-forward.h"

#include <sched.h>

#include <map>
#include <memory>
#include <string>

namespace lldb_private {
namespace process_linux {

class NativeProcessLinux;

class NativeThreadLinux : public NativeThreadProtocol {
  friend class NativeProcessLinux;

public:
  NativeThreadLinux(NativeProcessLinux *process, lldb::tid_t tid);

  // ---------------------------------------------------------------------
  // NativeThreadProtocol Interface
  // ---------------------------------------------------------------------
  std::string GetName() override;

  lldb::StateType GetState() override;

  bool GetStopReason(ThreadStopInfo &stop_info,
                     std::string &description) override;

  NativeRegisterContextSP GetRegisterContext() override;

  Error SetWatchpoint(lldb::addr_t addr, size_t size, uint32_t watch_flags,
                      bool hardware) override;

  Error RemoveWatchpoint(lldb::addr_t addr) override;

private:
  // ---------------------------------------------------------------------
  // Interface for friend classes
  // ---------------------------------------------------------------------

  /// Resumes the thread.  If @p signo is anything but
  /// LLDB_INVALID_SIGNAL_NUMBER, deliver that signal to the thread.
  Error Resume(uint32_t signo);

  /// Single steps the thread.  If @p signo is anything but
  /// LLDB_INVALID_SIGNAL_NUMBER, deliver that signal to the thread.
  Error SingleStep(uint32_t signo);

  void SetStoppedBySignal(uint32_t signo, const siginfo_t *info = nullptr);

  /// Return true if the thread is stopped.
  /// If stopped by a signal, indicate the signo in the signo argument.
  /// Otherwise, return LLDB_INVALID_SIGNAL_NUMBER.
  bool IsStopped(int *signo);

  void SetStoppedByExec();

  void SetStoppedByBreakpoint();

  void SetStoppedByWatchpoint(uint32_t wp_index);

  bool IsStoppedAtBreakpoint();

  bool IsStoppedAtWatchpoint();

  void SetStoppedByTrace();

  void SetStoppedWithNoReason();

  void SetExited();

  Error RequestStop();

  // ---------------------------------------------------------------------
  // Private interface
  // ---------------------------------------------------------------------
  void MaybeLogStateChange(lldb::StateType new_state);

  NativeProcessLinux &GetProcess();

  void SetStopped();

  inline void MaybePrepareSingleStepWorkaround();

  inline void MaybeCleanupSingleStepWorkaround();

  // ---------------------------------------------------------------------
  // Member Variables
  // ---------------------------------------------------------------------
  lldb::StateType m_state;
  ThreadStopInfo m_stop_info;
  NativeRegisterContextSP m_reg_context_sp;
  std::string m_stop_description;
  using WatchpointIndexMap = std::map<lldb::addr_t, uint32_t>;
  WatchpointIndexMap m_watchpoint_index_map;
  cpu_set_t m_original_cpu_set; // For single-step workaround.
};

typedef std::shared_ptr<NativeThreadLinux> NativeThreadLinuxSP;
} // namespace process_linux
} // namespace lldb_private

#endif // #ifndef liblldb_NativeThreadLinux_H_
