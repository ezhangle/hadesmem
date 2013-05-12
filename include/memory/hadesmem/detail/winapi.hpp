// Copyright (C) 2010-2013 Joshua Boyce.
// See the file COPYING for copying permission.

#pragma once

#include <windows.h>

#include <hadesmem/error.hpp>
#include <hadesmem/detail/assert.hpp>

namespace hadesmem
{

namespace detail
{

inline SYSTEM_INFO GetSystemInfo()
{
  SYSTEM_INFO sys_info;
  ::ZeroMemory(&sys_info, sizeof(sys_info));
  ::GetSystemInfo(&sys_info);
  return sys_info;
}
  
inline bool IsWoW64Process(HANDLE handle)
{
  BOOL is_wow64 = FALSE;
  if (!::IsWow64Process(handle, &is_wow64))
  {
    DWORD const last_error = ::GetLastError();
    HADESMEM_THROW_EXCEPTION(Error() << 
      ErrorString("IsWoW64Process failed.") << 
      ErrorCodeWinLast(last_error));
  }

  return is_wow64 != FALSE;
}

inline HANDLE OpenProcessAllAccess(DWORD id)
{
  HANDLE const handle = ::OpenProcess(PROCESS_ALL_ACCESS, TRUE, id);
  if (!handle)
  {
    DWORD const last_error = ::GetLastError();
    HADESMEM_THROW_EXCEPTION(Error() << 
      ErrorString("OpenProcess failed.") << 
      ErrorCodeWinLast(last_error));
  }

  return handle;
}

inline HANDLE DuplicateHandle(HANDLE handle)
{
  HADESMEM_ASSERT(handle != nullptr);

  HANDLE new_handle = nullptr;
  if (!::DuplicateHandle(::GetCurrentProcess(), handle, 
    ::GetCurrentProcess(), &new_handle, 0, TRUE, DUPLICATE_SAME_ACCESS))
  {
    DWORD const last_error = ::GetLastError();
    HADESMEM_THROW_EXCEPTION(Error() << 
      ErrorString("DuplicateHandle failed.") << 
      ErrorCodeWinLast(last_error));
  }

  return new_handle;
}

}

}