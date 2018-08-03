//===- MockBuildSystemDelegate.cpp ----------------------------------------===//
//
// This source file is part of the Swift.org open source project
//
// Copyright (c) 2017 Apple Inc. and the Swift project authors
// Licensed under Apache License v2.0 with Runtime Library Exception
//
// See http://swift.org/LICENSE.txt for license information
// See http://swift.org/CONTRIBUTORS.txt for the list of Swift project authors
//
//===----------------------------------------------------------------------===//

#include "MockBuildSystemDelegate.h"

using namespace llvm;
using namespace llbuild;
using namespace llbuild::buildsystem;
using namespace llbuild::unittests;

MockExecutionQueueDelegate::MockExecutionQueueDelegate() {}

MockBuildSystemDelegate::MockBuildSystemDelegate(bool trackAllMessages, std::shared_ptr<basic::FileSystem> fileSystem)
    : BuildSystemDelegate("mock", 0), fileSystem(fileSystem), trackAllMessages(trackAllMessages)
{
}

    
