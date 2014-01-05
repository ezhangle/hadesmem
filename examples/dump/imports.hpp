// Copyright (C) 2010-2013 Joshua Boyce.
// See the file COPYING for copying permission.

#pragma once

namespace hadesmem
{

class Process;
class PeFile;
}

void DumpImports(hadesmem::Process const& process,
                 hadesmem::PeFile const& pe_file,
                 bool& has_new_bound_imports_any);

void DumpBoundImports(hadesmem::Process const& process,
                      hadesmem::PeFile const& pe_file,
                      bool has_new_bound_imports_any);