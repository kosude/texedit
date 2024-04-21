/*
 *   Copyright (c) 2024 Jack Bennett.
 *   All Rights Reserved.
 *
 *   See the LICENCE file for more information.
 */

#pragma once
#ifndef __texedit__resources_hpp__
#define __texedit__resources_hpp__

#include <string>
#include <vector>

namespace te::util::res {
    std::string GetTexeditDir();

    std::string RelToExec(std::vector<std::string> dirs, std::string filename);
    std::string RelToExec(std::string filename);

    bool ValidateExecutable(std::string path);
}

#endif
